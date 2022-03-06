#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <cstdlib>
#include <ctime>

using namespace std::string_literals;

TowerSimulation::~TowerSimulation()
{
    delete airport;
}

void TowerSimulation::create_random_aircraft()
{
    auto aircraft = aircraftFactory.create_random_aircraft(airport);
    auto aircraftNumbers = aircraftFactory.get_aircraft_numbers();
    if(aircraftNumbers.find(aircraft->get_flight_num()) != aircraftNumbers.end())
    {
        std::cout << "This flight number has already been used !" << std::endl;
    }else{
        aircraftFactory.add_aircraft_number(aircraft->get_flight_num());
        aircraftManager.add_aircraft(move(aircraft));
    }
}

void TowerSimulation::create_keystrokes() const
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { create_random_aircraft(); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    GL::keystrokes.emplace('j', []() { GL::increase_framerate(); });
    GL::keystrokes.emplace('k', []() { GL::decrease_framerate(); });
    GL::keystrokes.emplace('p', []() { GL::pause(); });
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& ks_pair : GL::keystrokes)
    {
        std::cout << ks_pair.first << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    airport = new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                            new img::Image { one_lane_airport_sprite_path.get_full_path() } };

    GL::display_queue.emplace_back(airport);
    GL::move_queue.emplace(airport);
}

void TowerSimulation::init_aircraft_manager()
{
    GL::move_queue.emplace(&aircraftManager);
}


void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    init_airport();
    init_aircraft_manager();
    GL::loop();
}

