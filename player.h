#pragma once 
#include <string>
#include<vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Player{
    private:
        std::string name;
        int playerID;
        double personalCash;
        std::vector<int> ownedAirlines;

        Player(std::string n){
            name = n;
            playerID = 1;
            personalCash = 1000000.0;
        }
        void acquireAirline(int airlineID){
            ownedAirlines.push_back(airlineID);
        }
        json toJSON(){
            return {
                {"player_name", name},
                {"personal_cash", personalCash},
                {"owned_airlines", ownedAirlines}
            }
        }
};