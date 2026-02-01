#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Player {
public:
    std::string name;
    double personalCash;
    std::vector<int> ownedAirlineIds;

    Player(std::string n);

    void acquireAirline(int airlineId);
    json toJson(); 
    void saveGame(); 
};