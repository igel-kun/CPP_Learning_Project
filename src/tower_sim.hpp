#pragma once

#include "aircraft_manager.hpp"
#include "aircraft_factory.hpp"

class Airport;
struct AircraftType;

struct ContextInitialiser
{
private:
    int _argc;
    char ** _argv;
public:
    ContextInitialiser(int argc, char** argv) :
        _argc {argc},
        _argv {argv}
    {
        MediaPath::initialize(argv[0]);
        srand(time(NULL));
        GL::init_gl(argc, argv, "Init tower_sim");
    }
    int getArgc() { return _argc;}
    char** getArgv() { return _argv;}
};

class TowerSimulation
{
private:
    bool help        = false;
    Airport* airport = nullptr;
    AircraftManager aircraftManager;
    ContextInitialiser _contextInitialiser;
    AircraftFactory aircraftFactory;

    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    void create_random_aircraft();

    void create_keystrokes();
    void display_help() const;

    void init_airport();
    void init_aircraft_manager();

public:
    TowerSimulation(ContextInitialiser& contextInitializer) :
            help {(contextInitializer.getArgc() > 1) && (std::string { contextInitializer.getArgv()[1] } == "--help" || std::string { contextInitializer.getArgv()[1] } == "-h") },
            _contextInitialiser {contextInitializer}
    {
        create_keystrokes();
    }
    ~TowerSimulation();

    void launch();
};
