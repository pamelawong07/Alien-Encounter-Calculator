#ifndef COP3530_PROJECT_2_SPLAY_H
#define COP3530_PROJECT_2_SPLAY_H

#include <string>
#include <vector>
#include "encounter.h"
using namespace std;

struct SplayNode {
    string state;
    vector<City> cities;

    SplayNode* left;
    SplayNode* right;
    SplayNode* parent;

    SplayNode(string stateName, const City& city);
};

class SplayTree {
private:
    SplayNode* root;
    int totalSightings = 0;
    void rotateLeft(SplayNode* node);
    void rotateRight(SplayNode* node);
    void splay(SplayNode* node);

public:
    SplayTree();
    ~SplayTree();

    SplayTree(const SplayTree&) = delete;
    SplayTree& operator=(const SplayTree&) = delete;

    void clear();
    void insert(const City& city);

    SplayNode* searchStates(const string& state);
    City* searchCities(const string& city, const string& state);
    bool reportSighting(const string& city, const string& state, const Encounter& encounter);
    int total() const;
};

#endif //COP3530_PROJECT_2_SPLAY_H