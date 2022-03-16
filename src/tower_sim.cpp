#include "tower_sim.hpp"

#include "aircraft.hpp"
#include "aircraft_factory.hpp"
#include "aircraft_manager.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std::string_literals;

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) }
{
    context          = new ContextInitializer(argc, argv);
    aircraft_manager = new AircraftManager();
    aircraft_factory = new AircraftFactory();
    GL::move_queue.emplace(aircraft_manager);
    airline_stat = aircraft_factory->airlines[0];

    create_keystrokes();
}

TowerSimulation::~TowerSimulation()
{
    delete airport;
    delete aircraft_manager;
    delete aircraft_factory;
}

void TowerSimulation::create_random_aircraft() const
{
    assert(airport);
    aircraft_manager->add_aircraft(aircraft_factory->create_aircraft(airport->get_tower()));
}

void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { create_random_aircraft(); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('*', []() { GL::ticks_per_sec = std::min(GL::ticks_per_sec + 1u, 200u); });
    GL::keystrokes.emplace('!', []() { GL::ticks_per_sec = std::max(GL::ticks_per_sec - 1u, 1u); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    GL::keystrokes.emplace('p', []() { GL::is_paused = !GL::is_paused; });
    GL::keystrokes.emplace('0', [this]() { airline_stat = aircraft_factory->airlines[0]; });
    GL::keystrokes.emplace('1', [this]() { airline_stat = aircraft_factory->airlines[1]; });
    GL::keystrokes.emplace('2', [this]() { airline_stat = aircraft_factory->airlines[2]; });
    GL::keystrokes.emplace('3', [this]() { airline_stat = aircraft_factory->airlines[3]; });
    GL::keystrokes.emplace('4', [this]() { airline_stat = aircraft_factory->airlines[4]; });
    GL::keystrokes.emplace('5', [this]() { airline_stat = aircraft_factory->airlines[5]; });
    GL::keystrokes.emplace('6', [this]() { airline_stat = aircraft_factory->airlines[6]; });
    GL::keystrokes.emplace('7', [this]() { airline_stat = aircraft_factory->airlines[7]; });
    GL::keystrokes.emplace(
        'x',
        [this]()
        {
            std::cout << "There is "
                      << std::count_if(
                             aircraft_manager->aircrafts.begin(), aircraft_manager->aircrafts.end(),
                             [this](const std::unique_ptr<Aircraft>& aircraft)
                             { return aircraft->get_flight_num().substr(0, 2).compare(airline_stat) == 0; })
                      << " " << airline_stat << " airlines" << std::endl;
        });
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [key, value] : GL::keystrokes)
    {
        std::cout << key << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    airport = new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                            new img::Image { one_lane_airport_sprite_path.get_full_path() } };

    GL::move_queue.emplace(airport);
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    init_airport();

    GL::loop();
}
