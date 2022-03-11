#pragma once

#include "aircraft.hpp"

#include <memory>
#include <utility>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts = {};

public:
    void add_aircraft(std::unique_ptr<Aircraft> aircraft) { aircrafts.emplace_back(std::move(aircraft)); }

    bool move() override
    {
        for (auto it = aircrafts.begin(); it != aircrafts.end();)
        {
            auto& aircraft = *it;
            if (aircraft->move())
            {
                ++it;
            }
            else
            {
                it = aircrafts.erase(it);
            }
        }

        return true;
    }
};