#include "SplayTree.h"
#include <stack>
#include <fstream>
#include <iostream>

SplayNode::SplayNode(double distance, const City& city) {
    this->distance = distance;
    cities.push_back(city);
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

SplayTree::SplayTree() {
    root = nullptr;
}

SplayTree::~SplayTree() {
    clear();
}

void SplayTree::clear() {
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
    root = nullptr;
    totalSightings = 0;
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

void SplayTree::insert(const City& city, double distance) {
    totalSightings += (int)city.encounters.size();
    if (root == nullptr) {
        root = new SplayNode(distance, city);
        return;
    }
    SplayNode* current = root;
    SplayNode* parent = nullptr;
    while (current != nullptr) {
        parent = current;
        if (distance == current->distance) {
            for (City& existing : current->cities) {
                if (existing.name == city.name && existing.state == city.state) {
                    existing.encounters.insert(existing.encounters.end(), city.encounters.begin(), city.encounters.end());
                    splay(current);
                    return;
                }
            }
            current->cities.push_back(city);
            splay(current);
            return;
        } else if (distance < current->distance) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    SplayNode* newNode = new SplayNode(distance, city);
    newNode->parent = parent;
    if (distance < parent->distance)
        parent->left = newNode;
    else
        parent->right = newNode;
    splay(newNode);
}

SplayNode* SplayTree::searchDistance(double distance) {
    SplayNode* current = root;
    SplayNode* last = nullptr;

    while (current != nullptr) {
        last = current;
        if (distance == current->distance) {
            splay(current);
            return current;
        } else if (distance < current->distance) {
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

City* SplayTree::search(const string& name, const string& state, double distance) {
    SplayNode* node = searchDistance(distance);
    if (node == nullptr)
        return nullptr;
    for (City& city : node->cities) {
        if (city.name == name && city.state == state) {
            return &city;
        }
    }
    return nullptr;
}

bool SplayTree::reportSighting(const string& name, const string& state, double distance, const Encounter& encounter) {
    City* existing = search(name, state, distance);
    if (existing != nullptr) {
        existing->encounters.push_back(encounter);
        totalSightings++;
        return true;
    }
    City newCity;
    newCity.name = name;
    newCity.state = state;
    newCity.encounters.push_back(encounter);
    insert(newCity, distance);
    return false;
}

int SplayTree::total() const {
    return totalSightings;
}