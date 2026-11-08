//bc frontend needs specific main.cpp
//no Qt for testing without GUi
//no splay tree implementation yet, just the min heap

#pragma once
#include "encounter.h"
#include "minheap.h"
#include "SplayTree.h"
#include <cmath>
#include <string>
#include <vector>
#include <utility>
#include <chrono>
#include <ctime>
#include <fstream>
#include <cstdio>
#include <map>
#include <unordered_map>
#include <set>

//haversine distance between two points **IN MILES NOT KM
//calculates the distance between two points on a sphere, we will be using this formula to determine distance to the nearest 0.01 mile to gainesville
inline double haversine(double lat1, double long1, double lat2, double long2){
    const double R = 3958.8;
    const double rad = 3.14159265358979323846 / 180.0; //pi to 20 digits :sob:
    double distancelat = (lat2 - lat1) * rad;
    double distancelong = (long2 - long1) * rad;
    double a = std::sin(distancelat/2) * std::sin(distancelat/2) + std::cos (lat1 * rad) * std::cos(lat2 * rad) * std::sin(distancelong/2) * std::sin(distancelong/2); //the haversine formula
    if (a > 1.0){
        a = 1.0;
    }
    double miles = 2*R*std::asin(std::sqrt(a));
    return std::round(miles * 100.0) / 100.0; //round it to the nearest 0.01 miles
}

//struct to hold data to return to the GUI
struct QueryResult{
    bool found = false; //false means no sightings for the city
    int count = 0; //#sightings in city
    int total = 0; //#sightings total
    double probability = 0.0; // count/total*100 -> a percentage
    double seconds = 0.0; //time the structure took
    std::vector<std::string> descriptions; //description idk kinda self explanatory
};

class Backend{
private:
    using Clock = std::chrono::steady_clock;

    MinHeap heap;
    SplayTree splay;
    std::string lastError;
    bool loaded = false;
    std::unordered_map<std::string, double> info; //has distance from
    std::map<std::string,std::set<std::string>> citymap; //state and city

    std::string makeKey(const std::string& city, const std::string& state){
        return city + "|" + state;
    }

    //same query for each data structure so that when it runs its comparable using time taken
    template <class DS>
    QueryResult run(DS& ds, const std::string& city, const std::string& state){
        QueryResult r;
        r.total = ds.total();
        auto it = info.find(makeKey(city, state));
        if (it == info.end()){
            return r;
        }
        //time the search
        auto t0 = Clock::now();
        City* c = ds.search(city, state, it->second);
        auto t1 = Clock::now();

        //subtract to ge the total time taken
        r.seconds = std::chrono::duration<double>(t1-t0).count();

        //build the result
        if (c){
            r.found = true;
            r.count = (int)c->encounters.size();
            if (r.total > 0){
                r.probability = 100.0 * r.count / r.total;
            } else {
                r.probability = 0.0;
            }
            r.descriptions.reserve(c->encounters.size());
            for(const Encounter& e: c->encounters){
                r.descriptions.push_back(formatEncounter(e));
            }
        }
        return r;
    }

    //helper funcitons for the csv stuff
    std::vector<std::string>parseLine(std::string& line){
        std::vector<std::string> fields;
        std::string field;
        bool quotes = false;
        for(int i = 0; i < line.size(); i++){
            char c = line[i];
            if(c == '"'){
                if(quotes && i + 1 <line.size() && line[i+1] == '"'){
                    field += '"';
                    i++;
                } else{
                    quotes = !quotes;
                }
            } else if(c == ',' && !quotes){
                fields.push_back(field);
                field.clear();
            } else if (c != '\r'){
                field += c;
            }
        }
        fields.push_back(field);
        return fields;
    }

    std::string cleanText(const std::string& s){
        std::string out;
        for(int i= 0; i< s.size(); i++){
            if(s[i] == '&' && i+1< s.size() && s[i+1] == '#'){
                int j = i+2;
                int code = 0;
                while(j<s.size() && s[j] >= '0' && s[j] <= '9'){
                    code = code * 10 + (s[j++]-'0');
                }
                if (j<s.size() && s[j] == ';'){
                    j++;
                }
                if (j > i +2){
                    out += (char)code;
                    i = j -1;
                    continue;
                }
            }
            if (s.compare(i, 6, "&quot;") ==0){
                out += '"';
                i+=5;
                continue;

            }
            if(s.compare(i, 5, "&amp;") == 0){
                out += '&'; i += 4; continue;
            }
            out += s[i];
        }
        return out;
    }

    std::string normalize(std::string& city){
        std::string s = city;
        while(!s.empty() && s.back() == ' '){
            s.pop_back();
        }
        return cleanText(s);
    }

    Encounter makeEncounter(std::string& dateTime, std::string& desc){
        Encounter e;
        std::sscanf(dateTime.c_str(), "%d/%d/%d", &e.month, &e.day, &e.year);
        e.description = cleanText(desc);
        return e;
    }

    //if we dont want the date we can remove that
    std::string formatEncounter(const Encounter& e){
        return std::to_string(e.month) + "/" + std::to_string(e.day) + "/" + std::to_string(e.year) + ": " + e.description;
    }

public:
    Backend() = default;
    Backend(const Backend&) = delete;

    bool load(const std::string& csvPath){
        std::ifstream in(csvPath);
        if (!in){
            lastError = "Could not open " + csvPath;
            return false;
        }
        heap = MinHeap();
        info.clear();
        citymap.clear();
        loaded = false;

        struct Group{
            City city;
            double lat = 0;
            double lon = 0; //cant call it long bc of the data type
        };
        std::map<std::pair<std::string, std::string>, Group> groups;
        
        std::string line;
        std::getline(in, line);
        while (std::getline(in, line)){
            if (line.empty()) {
                continue;
            }
            std::vector<std::string> f = parseLine(line);
            if (f.size() != 15){
                continue;
            }
            std::string name = normalize(f[1]);
            std::string state = f[2];
            if (name.empty() || state.empty()){
                continue;
            }
            auto key = std::make_pair(name, state);
            auto it = groups.find(key);
            if (it == groups.end()){
                Group g;
                g.city.name = name;
                g.city.state = state;
                g.lat = std::stod(f[9]);
                g.lon = std::stod(f[10]);
                it = groups.emplace(key, g).first;
            }
            it->second.city.encounters.push_back(makeEncounter(f[0], f[7]));

        }

        auto origin = groups.find({"gainesville", "fl"});
        if (origin == groups.end()){
            lastError = "Gainesville, FL not found in data";
            return false;
        }
        double oLat = origin->second.lat; 
        double oLong = origin->second.lon;

        for (auto& k :groups){
            double d = haversine(oLat, oLong, k.second.lat, k.second.lon);
            info[makeKey(k.first.first, k.first.second)] = d;
            citymap[k.first.second].insert(k.first.first);
        }

        //gainesville distance from gainesvill is  0
        for (auto& k : groups){
            if (k.first == origin->first){
                continue;
            }
            double d = info[makeKey(k.first.first, k.first.second)];
            heap.insert(k.second.city, d);
            splay.insert(k.second.city, d);
        }
        heap.insert(origin->second.city, 0.0);
        splay.insert(origin->second.city, 0.0);
        loaded = true;
        return true;
    }

    bool isLoaded(){
        return loaded;
    }

    std::string& error(){
        return lastError;
    }

    const std::set<std::string>& cities(const std::string& state){
        static const std::set<std::string> none;
        auto it = citymap.find(state);
        if (it == citymap.end()){
            return none;
        } else {
            return it->second;
        }
    }

    const std::map<std::string, std::set<std::string>>& cityMap() {
        return citymap;
    }

    int totalSightings(){
        return heap.total();
    }
    
    //returning the minheap result
    QueryResult queryHeap(const std::string& city, const std::string& state){
        return run(heap, city, state);
    }

    //splay tree version here
    QueryResult querySplay(const std::string& city, const std::string& state){
        return run(splay, city, state);
    }

    //user submitted sighting
    bool report(const std::string& city, const std::string& state, const std::string& description){
        auto it = info.find(makeKey(city, state));
        if (it == info.end()){
            return false;
        }
        Encounter e;
        std::time_t t = std::time(nullptr);
        std::tm tmv{};
#ifdef _WIN32
        localtime_s(&tmv, &t);
#else 
        localtime_r(&t, &tmv); //for linux and mac
#endif
        e.month = tmv.tm_mon + 1;
        e.day = tmv.tm_mday;
        e.year = tmv.tm_year + 1900;
        e.description = description;
        heap.reportSighting(city, state, it->second, e);
        splay.reportSighting(city, state, it->second, e);
        return true;
    }

};