#pragma once
#include <string>

class Tower;
class Aircraft;

class AircraftFactory
{
private:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    Aircraft* create_aircraft(Tower& tower) const;

public:
    friend class TowerSimulation;
};