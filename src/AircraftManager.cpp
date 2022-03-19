//
// Created by Xhavit Osaj on 28/02/2022.
//

#include "AircraftManager.hpp"

void AircraftManager::move()
{
    //aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(), [](const std::unique_ptr<Aircraft> &aircraft) { aircraft->move(); return aircraft->delete_asap();  }), aircrafts.end());
    std::sort(aircrafts.begin(), aircrafts.end(),
              [](const std::unique_ptr<Aircraft>& aircraft1, const std::unique_ptr<Aircraft>& aircraft2)
              {
                  if (aircraft2->has_terminal())
                      return false;

                  if (aircraft1->has_terminal())
                      return true;

                  return (aircraft1->get_fuel() < aircraft2->get_fuel());
              });

    auto rm = std::remove_if(aircrafts.begin(), aircrafts.end(), [](const std::unique_ptr<Aircraft>& aircraft) {aircraft->move(); return aircraft->delete_asap();});
    aircrafts.erase(rm, aircrafts.end());

}

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.push_back(std::move(aircraft));
}

void AircraftManager::numberAircraftAirline(int num)
{
    long res =  std::count_if(aircrafts.begin(), aircrafts.end(), [&num](std::unique_ptr<Aircraft> &aircraft) {return aircraft->get_index() == num;});

    std::cout << "Airlines " << airlines[num] << " have " << res << " aircraft flying" << std::endl;
}

float AircraftManager::get_required_fuel() const
{
    return std::accumulate(aircrafts.begin(), aircrafts.end(), 0.f,
                           [](float acc, const std::unique_ptr<Aircraft>& aircraft)
                           {
                               if (aircraft->is_on_ground() && aircraft->is_low_on_fuel())
                               {
                                   return acc + 3000 - aircraft->get_fuel();
                               }
                               return acc;
                           });
}
