#ifndef COP3530_PROJECT_2_SPLAY_H
#define COP3530_PROJECT_2_SPLAY_H

#include <string>
#include <vector>
using namespace std;

struct Sighting {
    string city;
    string state;
    string country;
    string date;
    string shape;
    string description;
};

struct SplayNode {
    string state;
    vector<string> sightings;

    SplayNode* left;
    SplayNode* right;
    SplayNode* parent;

    SplayNode(string stateName, string sighting);
};

class SplayTree {
private:
    SplayNode* root;
    void rotateLeft(SplayNode* node);
    void rotateRight(SplayNode* node);
    void splay(SplayNode* node);

public:
    SplayTree();
    ~SplayTree();

    void insert(string state, string sighting);
    SplayNode* search (const string& state);
    vector<string> parseLine(const string& line);
    bool loadCSV(const string& fileName);
};

#endif //COP3530_PROJECT_2_SPLAY_H