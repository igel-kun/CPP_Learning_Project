#include "aircraft_factory.hpp"

#include "aircraft.hpp"

Aircraft* AircraftFactory::create_aircraft(Tower& tower) const
{
    const std::string flight_number =
        AircraftFactory::airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    Aircraft* aircraft =
        new Aircraft { *(aircraft_types[rand() % 3]), flight_number, start, direction, tower };

    return aircraft;
}