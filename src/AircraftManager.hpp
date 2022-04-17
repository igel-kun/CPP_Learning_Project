//
// Created by Xhavit Osaj on 28/02/2022.
//

#pragma once

#include "aircraft.hpp"
#include <algorithm>

class AircraftManager : public GL::DynamicObject
{
private:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    int crash_count = 0;

public:
    void move() override;
    void add(std::unique_ptr<Aircraft> aircraft);
    void numberAircraftAirline(int num);
    float get_required_fuel() const;
    int getCrash() const{ return crash_count;}
};
