#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

using namespace std::string_literals;

TowerSimulation::~TowerSimulation()
{
    delete airport;
}

void TowerSimulation::create_aircraft()
{
    assert(airport);

    std::unique_ptr<Aircraft> aircraft = aircraftFactory.create_random_aircraft(airport);

    aircraftManager.add(std::move(aircraft));


}

void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { create_aircraft(); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });

    GL::keystrokes.emplace('a', []() { GL::change_framerate_minus(); });
    GL::keystrokes.emplace('b', []() { GL::change_framerate_plus(); });
    GL::keystrokes.emplace('p', []() { GL::pause(); });

    GL::keystrokes.emplace('0', [this]() { aircraftManager.numberAircraftAirline(0); });
    GL::keystrokes.emplace('1', [this]() { aircraftManager.numberAircraftAirline(1); });
    GL::keystrokes.emplace('2', [this]() { aircraftManager.numberAircraftAirline(2); });
    GL::keystrokes.emplace('3', [this]() { aircraftManager.numberAircraftAirline(3); });
    GL::keystrokes.emplace('4', [this]() { aircraftManager.numberAircraftAirline(4); });
    GL::keystrokes.emplace('5', [this]() { aircraftManager.numberAircraftAirline(5); });
    GL::keystrokes.emplace('6', [this]() { aircraftManager.numberAircraftAirline(6); });
    GL::keystrokes.emplace('7', [this]() { aircraftManager.numberAircraftAirline(7); });

    GL::keystrokes.emplace('m', [this]() { std::cout << "Total aircraft crashed : " << aircraftManager.getCrash() << std::endl;});




}

void TowerSimulation::display_help()
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keystrokes have meaning:" << std::endl;

    for (const auto& [key, value] : GL::keystrokes)
    {
        std::cout << key << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    assert(!airport);

    airport = new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                            new img::Image { one_lane_airport_sprite_path.get_full_path() },
                            aircraftManager };

    //GL::display_queue.emplace_back(airport);
    GL::move_queue.emplace(airport);
}

void TowerSimulation::init_aircraftManager()
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
    init_aircraftManager();

    GL::loop();
}
