#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include<random>

#include "player.h"
#include "airline.h"
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;
int generateRandomID() {
    
    std::random_device rd; 
    
    std::mt19937 gen(rd()); 
    
    std::uniform_int_distribution<> distr(100000, 999999); 
    
    return distr(gen);
}

bool fileExists(const std::string& name){
    ifstream f(name.c_str());
    return f.good();
}
int main (){
    cout << "Welcome to Airline Tycoon!" <<'\n';
    Player *player=nullptr;
    Airline *airline=nullptr;
    if(fileExists("savegame.json")){
        std::ifstream file("savegame.json");
        json saveData;
        file >> saveData;
        file.close();

        string Name = saveData["player"]["player_name"];
        player = new Player(Name);
        player->personalCash = saveData["player"]["personal_cash"];
        player->ownedAirlineIds = saveData["player"]["owned_airlines"].get<std::vector<int>>();
        

        auto& airlineData = saveData["airlines"][0];
        int airlineID = airlineData["airline_id"];
        string airlineName = airlineData["airline_name"];
        string hqLocation = airlineData["headquarters"];
        airline = new Airline(airlineID, airlineName, hqLocation);
        airline->id = airlineData["airline_id"];
        airline->name = airlineData["airline_name"];
        airline->headquarters = airlineData["headquarters"];
        airline->cashBalance = airlineData["corporate_cash"];
        airline->fleetCount = airlineData["fleet_count"];

    } else {
        cout << "Enter you player name" <<'\n';
        string playerName;
        getline(std::cin, playerName);

        cout<<"Enter Airline Name" << '\n';\
        string airline_name;
        getline(std::cin, airline_name);

        cout << "Enter HQ Location (e.g. Mumbai): ";
        string hqLoc;
        getline(std::cin, hqLoc);

        int newAirlineID = generateRandomID();
        airline = new Airline(newAirlineID, airline_name, hqLoc);
        player = new Player(playerName);

        player->acquireAirline(newAirlineID);
    }
    bool game = true;
    while(game){
        cout << "\nPlayer: " << player->name << " | Cash: ₹" <<std::fixed << std::setprecision(2) << player->personalCash << " | Owned Airlines: " << player->ownedAirlineIds.size() << '\n';
        cout << "1. View Airline Details\n";
        cout << "2. Save Game\n";
        cout << "3. Buy Airline\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;
        cin.ignore();
        if(choice == 1){
            cout << "\nAirline Details:\n";
            cout << "Name: " << airline->name << "\n";
            cout << "Headquarters: " << airline->headquarters << "\n";
            cout << "Corporate Cash: $" << airline->cashBalance << "\n";
            cout << "Fleet Count: " << airline->fleetCount << "\n";
        } else if(choice == 2){
            player->saveGame();
        } else if(choice == 3){
            cout << "Enter Airline ID to buy: ";
            int airlineIdToBuy;
            cin >> airlineIdToBuy;
            cout << "Enter Price: ";
            double price;
            cin >> price;
            string result = player->buy_airline(airlineIdToBuy, price);
            cout << result << '\n';
        } else if(choice == 4){
            game = false;
        }
    } 
    json rootSaveFile;

    rootSaveFile["player"] = player->toJson();
    rootSaveFile["airlines"] = json::array();
    rootSaveFile["airlines"].push_back(airline->toJson());
    ofstream file("savegame.json");

    if (file.is_open()) {
        file << rootSaveFile.dump(4); 
        file.close();
        std::cout << "\nSUCCESS: Game saved to 'savegame.json'.\n";
        
    } else {
        std::cerr << "ERROR: Could not open file for saving.\n";
    }
    delete player;
    delete airline;
    std::cout << "Press Enter to exit...";
    std::cin.ignore();
    return 0;
}