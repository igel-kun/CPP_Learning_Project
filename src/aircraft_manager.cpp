#include "aircraft_manager.hpp"


void AircraftManager::move() {
    for (auto it = aircrafts.begin(); it != aircrafts.end();) {

        auto aircraft = **it;
        aircraft.move();

        if ((aircraft).del_object()) {
            it = aircrafts.erase(it);

        } else {
            ++it;
        }
    }
}

void AircraftManager::add_aircraft(std::unique_ptr<Aircraft> aircraft){
    aircrafts.push_back(std::move(aircraft));
}
