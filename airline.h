#pragma once
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Airline {
public:
    int id;                 
    std::string name;
    std::string headquarters;
    double cashBalance; 
    int fleetCount;
    
    Airline(int id, std::string name, std::string hq);

    json toJson();
};