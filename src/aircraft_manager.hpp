#pragma once

#include "aircraft.hpp"

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    int total_crashed_aircraft = 0;

public:

	void aircrafts_by_airlines(int airline);
    void move() override;
    void add_aircraft(std::unique_ptr<Aircraft> aircraft);
    int get_required_fuel();
    int get_total_aircrfat_crashed(){return total_crashed_aircraft;};

};
    