#ifndef COP3530_PROJECT_2_SPLAY_H
#define COP3530_PROJECT_2_SPLAY_H

#include <string>
#include <vector>
#include "encounter.h"
using namespace std;

struct SplayNode {
    double distance;
    vector<City> cities;

    SplayNode* left;
    SplayNode* right;
    SplayNode* parent;

    SplayNode(double distance, const City& city);
};

class SplayTree {
private:
    SplayNode* root;
    int totalSightings = 0;
    void rotateLeft(SplayNode* node);
    void rotateRight(SplayNode* node);
    void splay(SplayNode* node);
    SplayNode* searchDistance(double distance);

public:
    SplayTree();
    ~SplayTree();

    SplayTree(const SplayTree&) = delete;
    SplayTree& operator=(const SplayTree&) = delete;

    void clear();
    void insert(const City& city, double distance);
    City* search(const string& name, const string& state, double distance);
    bool reportSighting(const string& name, const string& state, double distance, const Encounter& encounter);
    int total() const;
};

#endif //COP3530_PROJECT_2_SPLAY_H