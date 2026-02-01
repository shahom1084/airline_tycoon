#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "player.h"
#include "airline.h"
#include <nlohmann/json.hpp>

#include<random>
using namespace std;
using json = nlohmann::json;
int generateRandomID() {
    
    std::random_device rd; 
    
    std::mt19937 gen(rd()); 
    
    std::uniform_int_distribution<> distr(100000, 999999); 
    
    return distr(gen);
}

int main (){
    cout << "Welcome to Airline Tycoon!" <<'\n';

    cout << "Enter your player name: ";
    string playerName;
    getline(std::cin, playerName);

    cout << "Enter Airline Name: ";
    string airlineName;
    getline(std::cin, airlineName);

    cout << "Enter HQ Location (e.g. Mumbai): ";
    string hqLoc;
    getline(std::cin, hqLoc);

    int newAirlineID = generateRandomID();
    Airline  newAirline(newAirlineID, airlineName, hqLoc);
    Player player(playerName);

    player.acquireAirline(newAirlineID);

    json rootSaveFile;

    rootSaveFile["player"] = player.toJson();
    rootSaveFile["airlines"] = json::array();
    rootSaveFile["airlines"].push_back(newAirline.toJson());
    ofstream file("savegame.json");

    if (file.is_open()) {
        file << rootSaveFile.dump(4); 
        file.close();
        std::cout << "\nSUCCESS: Game saved to 'savegame.json'.\n";
        std::cout << "Check your project folder to see the database!\n";
    } else {
        std::cerr << "ERROR: Could not open file for saving.\n";
    }
    std::cout << "Press Enter to exit...";
    std::cin.ignore();
    return 0;
}
