#pragma once

#include "GL/displayable.hpp"
#include "GL/dynamic_object.hpp"
#include "GL/texture.hpp"
#include "airport_type.hpp"
#include "geometry.hpp"
#include "img/image.hpp"
#include "runway.hpp"
#include "terminal.hpp"
#include "tower.hpp"
#include "AircraftManager.hpp"

#include <vector>

class Airport : public GL::Displayable, public GL::DynamicObject
{
private:
    const AirportType& type;
    const Point3D pos;
    const GL::Texture2D texture;
    std::vector<Terminal> terminals;
    Tower tower;
    float fuel_stock = 0;
    float ordered_fuel = 0;
    float next_refill_time = 0;
    const AircraftManager &aircraftManager;

    // reserve a terminal
    // if a terminal is free, return
    // 1. a sequence of waypoints reaching the terminal from the runway-end and
    // 2. the number of the terminal (used for liberating the terminal later)
    // otherwise, return an empty waypoint-vector and any number
    std::pair<WaypointQueue, size_t> reserve_terminal(Aircraft& aircraft)
    {
        const auto it =
            std::find_if(terminals.begin(), terminals.end(), [](const Terminal& t) { return !t.in_use(); });

        if (it != terminals.end())
        {
            it->assign_craft(aircraft);
            const auto term_idx = std::distance(terminals.begin(), it);
            return { type.air_to_terminal(pos, 0, term_idx), term_idx };
        }
        else
        {
            return { {}, 0u };
        }
    }

    WaypointQueue start_path(const size_t terminal_number)
    {
        assert(terminal_number < terminals.size());
        return type.terminal_to_air(pos, 0, terminal_number);
    }

    Terminal& get_terminal(const size_t terminal_num) { return terminals.at(terminal_num); }

    void free_term(const size_t terminal_number) { terminals.at(terminal_number).free(); }

public:
    Airport(const AirportType& type_, const Point3D& pos_, const img::Image* image, const AircraftManager& aircraftManager, const float z_ = 1.0f) :
        GL::Displayable { z_ },
        type { type_ },
        pos { pos_ },
        texture { image },
        terminals { type.create_terminals() },
        tower { *this },
        aircraftManager {aircraftManager}
    {}

    Tower& get_tower() { return tower; }

    void display() const override { texture.draw(project_2D(pos), { 2.0f, 2.0f }); }

    void move() override
    {

        if(next_refill_time <= 0.f){

            auto required_fuel = aircraftManager.get_required_fuel();
            ordered_fuel = required_fuel < 5000 ? required_fuel : 5000;
            fuel_stock += ordered_fuel;
            /*std::cout << "Fuel stock : " << fuel_stock
                      << ", Needed fuel : " << required_fuel
                      << ", Received fuel : " << ordered_fuel << std::endl;*/
            next_refill_time = 100.f;
        }
        next_refill_time--;
        for (auto& terminal: terminals){
            terminal.move(fuel_stock);
        }
    }

    friend class Tower;
};
