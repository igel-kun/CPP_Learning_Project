//
// Created by Xhavit Osaj on 28/02/2022.
//

#pragma once

#include "aircraft.hpp"

class AircraftManager : public GL::DynamicObject
{
private:
    const std::vector<std::unique_ptr<Aircraft>> aircrafts;

public:
    void move() override;
    void add(const Aircraft& aircraft) const;
};
