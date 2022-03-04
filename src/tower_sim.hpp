#pragma once

#include "GL/opengl_interface.hpp"
#include "img/media_path.hpp"

class Airport;
class AircraftManager;
class AircraftFactory;
struct AircraftType;

struct ContextInitializer
{
public:
    ContextInitializer(int argc, char** argv)
    {
        MediaPath::initialize(argv[0]);
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        GL::init_gl(argc, argv, "Airport Tower Simulation");
    }
};

class TowerSimulation
{
private:
    bool help                         = false;
    Airport* airport                  = nullptr;
    AircraftManager* aircraft_manager = nullptr;
    AircraftFactory* aircraft_factory = nullptr;
    ContextInitializer* context       = nullptr;

    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    // void create_aircraft(const AircraftType& type) const;
    void create_random_aircraft() const;

    void create_keystrokes() const;
    void display_help() const;

    void init_airport();

public:
    TowerSimulation(int argc, char** argv);
    ~TowerSimulation();

    void launch();
};
