#pragma once
#ifndef MARTYRS_DATA_STRUCTURE_H
#define MARTYRS_DATA_STRUCTURE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>

class Martyr {
public:
    std::string name;
    std::string age;
    std::string eventLocation;
    std::string dateOfDeath;
    std::string gender;

    Martyr(const std::string& n, const std::string& a, const std::string& loc, const std::string& dod, const std::string& g)
        : name(n), age(a), eventLocation(loc), dateOfDeath(dod), gender(g) {}
};

struct LocationRecord {
    std::string locationName;
    std::vector<Martyr> martyrsByName;
    std::vector<Martyr> martyrsByDate;

    LocationRecord(const std::string& locName) : locationName(locName) {}
};

struct Node {
    LocationRecord data;
    Node* next;
    Node* prev;

    Node(const std::string& locName) : data(locName), next(nullptr), prev(nullptr) {}
};


#endif 