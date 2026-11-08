#include "SplayTree.h"
#include <stack>
#include <fstream>
#include <iostream>

SplayNode::SplayNode(string stateName, string sighting) {
    state = stateName;
    sightings.push_back(sighting);
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

SplayTree::SplayTree() {
    root = nullptr;
}

SplayTree::~SplayTree() {
    stack<SplayNode*> nodes;
    if (root != nullptr)
        nodes.push(root);
    while (!nodes.empty()) {
        SplayNode* current = nodes.top();
        nodes.pop();
        if (current->left != nullptr)
            nodes.push(current->left);
        if (current->right != nullptr)
            nodes.push(current->right);
        delete current;
    }
}

void SplayTree::rotateLeft(SplayNode* node) {
    SplayNode* child = node->right;
    if (child == nullptr)
        return;
    node->right = child->left;
    if (child->left != nullptr)
        child->left->parent = node;
    child->parent = node->parent;
    if (node->parent == nullptr)
        root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;
    child->left = node;
    node->parent = child;
}

void SplayTree::rotateRight(SplayNode* node) {
    SplayNode* child = node->left;
    if (child == nullptr)
        return;
    node->left = child->right;
    if (child->right != nullptr)
        child->right->parent = node;
    child->parent = node->parent;
    if (node->parent == nullptr)
        root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;
    child->right = node;
    node->parent = child;
}

void SplayTree::splay(SplayNode* node) {
    while (node->parent != nullptr) {
        SplayNode* parent = node->parent;
        SplayNode* grandparent = parent->parent;

        if (grandparent == nullptr) { //Zig
            if (node == parent->left)
                rotateRight(parent);
            else
                rotateLeft(parent);
        } else if (node == parent->left && parent == grandparent->left) { //Zig Zig left left
            rotateRight(grandparent);
            rotateRight(parent);
        } else if (node == parent->right && parent == grandparent->right) { //Zig Zig right right
            rotateLeft(grandparent);
            rotateLeft(parent);
        } else if (node == parent->right && parent == grandparent->left) { //Zig Zag left right
            rotateLeft(parent);
            rotateRight(grandparent);
        } else { //Zig Zag right left
            rotateRight(parent);
            rotateLeft(grandparent);
        }
    }
}

void SplayTree::insert(string state, string sighting) {
    if (root == nullptr) {
        root = new SplayNode(state, sighting);
        return;
    }
    SplayNode* current = root;
    SplayNode* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (state == current->state) {
            current->sightings.push_back(sighting);
            splay(current);
            return;
        } else if (state < current->state) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    SplayNode* newNode = new SplayNode(state, sighting);
    newNode->parent = parent;
    if (state < parent->state) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    splay(newNode);
}

SplayNode* SplayTree::search(const string& state) {
    SplayNode* current = root;
    SplayNode* last = nullptr;

    while (current != nullptr) {
        last = current;
        if (state == current->state) {
            splay(current);
            return current;
        } else if (state < current->state) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (last != nullptr) {
        splay(last);
    }
    return nullptr;
}

vector<string> SplayTree::parseLine(const string& line) {
    vector<string> fields;
    string field;
    bool insideQuotes = false;

    for (int i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == '\"') {
            if (insideQuotes && i+1 < line.size() && line[i+1] == '\"') {
                field += '\"';
                i++;
            } else {
                insideQuotes = !insideQuotes;
            }
        } else if (c == ',' && !insideQuotes) {
            fields.push_back(field);
            field = "";
        } else {
            field += c;
        }
    }
    fields.push_back(field);
    return fields;
}

bool SplayTree::loadCSV(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Couldn't open file: " << fileName << endl;
        return false;
    }
    string line;
    getline(file, line);
    int c = 0;
    while (getline(file, line)) {
        if (line.empty())
            continue;
        vector<string> fields = parseLine(line);
        if (fields.size() != 14)
            continue;
        string state = fields[2];
        if (state.empty())
            continue;
        insert(state, line);
        c++;
    }
    cout << "Loaded " << c << " UFO sightings into the Splay Tree." << endl;
    return !file.bad();
}







