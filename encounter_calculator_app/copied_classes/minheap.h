#pragma once
#include "encounter.h"
#include <cmath>

class MinHeap{
private:
    struct Node{
        double distance = 0.0;
        std::vector<City> cities;
    };

    static const int NONE = -1;
    static const double EPS;

    std::vector<Node> data;
    int totalSightings = 0;

    static void swapNodes(Node& a, Node& b){
        double temp = a.distance;
        a.distance = b.distance;
        b.distance = temp;
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

public:

    void insert(const City& city, double distance){
        totalSightings += (int)city.encounters.size();

        int i = findNode(0, distance);
        if (i != NONE){
            data[i].cities.push_back(city);
            return;
        }
        data.push_back(Node());
        Node& node = data[data.size()-1];
        node.distance = distance;
        node.cities.push_back(city);
        siftUp((int)data.size()-1);
    }

    City* search(std::string& name, std::string& state, double distance){
        int i = findNode(0, distance);
        if (i == NONE){
            return nullptr;
        }
        for (int j = 0; j < (int)data[i].cities.size(); j++){
            City& c = data[i].cities[j];
            if (c.name == name && c.state == state){
                return &c;
            }
        }
        return nullptr;
    }

    bool reportSighting(std::string& name, std::string& state, double distance, Encounter& e){
        City* c = search(name, state, distance);
        if (!c){
            return false;
        }
        c->encounters.push_back(e);
        totalSightings++;
        return true;
    }

    double probability(std::string& name, std::string state, double distance){
        City* c = search(name, state, distance);
        if (!c || totalSightings == 0){
            return 0.0;
        }
        return 100.0 * (double)c->encounters.size() / (double)totalSightings;
    }
};

//EPS definition
const double MinHeap::EPS = 1e-9;