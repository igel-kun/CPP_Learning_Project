#pragma once

#include "aircraft.hpp"

#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<Aircraft*> aircrafts = {};

public:
    virtual ~AircraftManager()
    {
        for (auto it = aircrafts.begin(); it != aircrafts.end();)
        {
            auto* aircraft = *it;
            it             = aircrafts.erase(it);
            delete aircraft;
        }
    }
    void add_aircraft(Aircraft* aircraft) { aircrafts.emplace_back(aircraft); }
    bool move() override
    {
        for (auto it = aircrafts.begin(); it != aircrafts.end();)
        {
            auto* aircraft = *it;
            if (aircraft->move())
            {
                ++it;
            }
            else
            {
                it = aircrafts.erase(it);
                delete aircraft;
            }
        }

        return true;
    }
};