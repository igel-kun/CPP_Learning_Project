//
// Created by Xhavit Osaj on 07/03/2022.
//

#pragma once

#include "airport.hpp"

class AircraftFactory
{
private:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};

    void init_aircraft_types();
    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Airport* airport);
    std::set<std::string> uniqueAircraft;
public:
    AircraftFactory() { init_aircraft_types(); }
    std::unique_ptr<Aircraft> create_random_aircraft(Airport* airport);

};

