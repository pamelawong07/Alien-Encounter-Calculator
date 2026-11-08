#pragma once
#include "encounter.h"
#include <cmath>
#include <string>
#include <vector>

class MinHeap{
private:
    struct Node{
        double distance = 0.0;
        std::vector<City> cities;
    };

    static const int NONE = -1;
    static constexpr double EPS = 1e-9; //moved definition to inside the class so it doesnt break

    std::vector<Node> data;
    int totalSightings = 0;

    static void swapNodes(Node& a, Node& b){
        std::swap(a.distance,b.distance);
        a.cities.swap(b.cities);
    }

    int findNode(int i, double distance) const {
        if (i >= (int)data.size()){
            return NONE;
        }
        if (data[i].distance > distance + EPS){
            return NONE;
        }
        if (std::abs(data[i].distance - distance) <= EPS){
            return i;
        }
        int found = findNode(2*i+1, distance);
        if (found != NONE){
            return found;
        }
        return findNode(2*i+2, distance);
    }

    void siftUp(int i){
        while(i>0){
            int p = (i-1) / 2;
            if (data[i].distance <data[p].distance){
                swapNodes(data[i], data[p]);
                i = p;
            } else {
                break;
            }
        }
    }
    City* cityInNode(int i, const std::string& name, const std::string& state){ //made passing in as const
        for (City& c : data[i].cities){
            if (c.name == name && c.state == state) {
                return &c;
            }
        }
        return nullptr;

    }

public:

    void insert(const City& city, double distance){
        totalSightings += (int)city.encounters.size();

        int i = findNode(0, distance);
        if (i != NONE){
            City* exists = cityInNode(i,city.name,city.state);
            if (exists){
                exists->encounters.insert(exists->encounters.end(), city.encounters.begin(), city.encounters.end());
            } else {
                data[i].cities.push_back(city);
            }
            return;
        }
        data.push_back(Node{distance, {city}});
        siftUp((int)data.size()-1);
    }

    City* search(const std::string& name, const std::string& state, double distance){ //made passing in as const
        int i = findNode(0, distance);
        if (i == NONE){
            return nullptr;
        }
        return cityInNode(i, name, state);
    }

    bool reportSighting(const std::string& name,const std::string& state, double distance, const Encounter& e){ //made passing in as const
        City* c = search(name, state, distance);
        if (c) {
            c->encounters.push_back(e);
            totalSightings++;
            return true;
        }
        City newCity;
        newCity.name = name;
        newCity.state = state;
        newCity.encounters.push_back(e);
        insert(newCity, distance);
        return false;

    }

    double probability(const std::string& name, const std::string state, double distance){ //made passing in as const
        City* c = search(name, state, distance);
        if (!c || totalSightings == 0){
            return 0.0;
        }
        return 100.0 * (double)c->encounters.size() / (double)totalSightings;
    }

    //helpers (mostly to help with the UI connection if needed)
    int nodeCount(){
        return (int)data.size();
    }
    int total(){
        return totalSightings;
    }
    double rootDistance(){
        if (data.empty()){
            return 0.0;
        } else {
            return data[0].distance;
        }
    }
};
