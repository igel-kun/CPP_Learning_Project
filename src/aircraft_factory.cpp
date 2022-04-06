#include "aircraft_factory.hpp"

const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };

std::unique_ptr<Aircraft> AircraftFactory::create_aircraft(const AircraftType& type,Airport* airport){
    assert(airport); // make sure the airport is initialized before creating aircraft

    const int airline = std::rand() % 8;
    const std::string flight_number =  airlines[airline] + std::to_string(1000 + (rand() % 9000));
    
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0.f } * 3 + Point3D { 0.f, 0.f, 2.f };
    const Point3D direction = (-start).normalize();

    std::unique_ptr<Aircraft> aircraft = std::make_unique<Aircraft>(type, flight_number, airline, start, direction, airport->get_tower());
    return aircraft;
}