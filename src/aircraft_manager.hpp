#pragma once

#include "aircraft.hpp"

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts = {};

public:
    void add_aircraft(std::unique_ptr<Aircraft> aircraft) { aircrafts.emplace_back(std::move(aircraft)); }

    bool move()
    {
        std::sort(aircrafts.begin(), aircrafts.end(),
                  [](const std::unique_ptr<Aircraft>& a, const std::unique_ptr<Aircraft>& b)
                  { return a->has_terminal() > b->has_terminal() && a->get_fuel() < b->get_fuel(); });

        aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                       [](const std::unique_ptr<Aircraft>& aircraft)
                                       { return !aircraft->move(); }),
                        aircrafts.end());
        return true;
    }

    friend class TowerSimulation;
};