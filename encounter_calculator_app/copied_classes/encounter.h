#pragma once
#include <string>
#include <vector>

struct Encounter {
    int month = 0, day = 0, year = 0;
    std::string description;
};

struct City {
    std::string name;
    std::string state;
    std::vector<Encounter> encounters;
};