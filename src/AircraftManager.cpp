//
// Created by Xhavit Osaj on 28/02/2022.
//

#include "AircraftManager.hpp"

void AircraftManager::move()
{
    for (auto item = aircrafts.begin(); item != aircrafts.end();){
        auto& obj = **item;
        obj.move();
        if ((*item)->delete_asap())
        {
            item = aircrafts.erase(item);
        }
        else
        {
            item++;
        }
    }

}

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.push_back(std::move(aircraft));
}
