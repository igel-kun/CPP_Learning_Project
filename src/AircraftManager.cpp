//
// Created by Xhavit Osaj on 28/02/2022.
//

#include "AircraftManager.hpp"

void AircraftManager::move()
{
    for (auto& i : aircrafts){
        i->move();
    }
}

void AircraftManager::add(const Aircraft& aircraft) const
{
    aircrafts.emplace_back(std::make_unique<Aircraft>(aircraft));
}
