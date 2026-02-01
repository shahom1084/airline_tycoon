#include "airline.h"

Airline::Airline(int id, std::string name, std::string hq) {
    this->id = id;
    this->name = name;
    this->headquarters = hq;
    
    this->cashBalance = 500000.0; 
    this->fleetCount = 1;
}

json Airline::toJson() {
    return {
        {"id", id},
        {"airline_name", name},
        {"headquarters", headquarters},
        {"corporate_cash", cashBalance},
        {"fleet_count", fleetCount}

    };
}