//
// Created by Xhavit Osaj on 07/03/2022.
//

#include "AircraftFactory.hpp"

#include <utility>


std::unique_ptr<Aircraft> AircraftFactory::create_aircraft(const AircraftType& type, Airport* airport)
{
    assert(airport); // make sure the airport is initialized before creating aircraft

    int index = std::rand() % 8;

    const std::string flight_number = airlines[index] + std::to_string(1000 + (rand() % 9000));
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    std::unique_ptr<Aircraft> aircraft = std::make_unique<Aircraft>( type, flight_number, start, direction, airport->get_tower(), index);

    return aircraft;
}

std::unique_ptr<Aircraft> AircraftFactory::create_random_aircraft(Airport* airport)
{
    return create_aircraft(*(aircraft_types[rand() % 3]), airport);
}

void AircraftFactory::init_aircraft_types()
{
    aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
    aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
    aircraft_types[2] = new AircraftType { .02f, .1f, .04f, MediaPath { "concorde_af.png" } };

}
