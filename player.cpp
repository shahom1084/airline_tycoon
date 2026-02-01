#include "player.h"
#include <fstream> 
#include <iostream>

Player::Player(std::string n) {
    id = 1
    name = n;
    personalCash = 1000000.0;
}

void Player::acquireAirline(int airlineId) {
    ownedAirlineIds.push_back(airlineId);
}

json Player::toJson() {
    return {
        {"player_id", id},
        {"player_name", name},
        {"personal_cash", personalCash},
        {"owned_airlines", ownedAirlineIds}
    };
}

void Player::saveGame() {
    std::ofstream file("savegame.json");
    file << toJson().dump(4);
    file.close();
    std::cout << "Game Saved!\n";
}