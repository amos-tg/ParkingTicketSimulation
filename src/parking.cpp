#include "parking.h"
#include <string>
#include <iostream>
#include <optional>

using namespace std;

ParkedCar::ParkedCar(
  string make, string model, Color color, 
  unsigned license_num, unsigned minutes_parked):
    make_m(make), model_m(model), color_m(color),
    license_num_m(license_num), minutes_parked_m(minutes_parked) 
{};

ParkedCar& ParkedCar::operator++() 
{
  ++minutes_parked_m;
  return *this;
}

ParkedCar ParkedCar::operator++(int)
{
  ParkedCar copy { *this };
  ++minutes_parked_m;
  return copy;
}

optional<ParkingTicket> PoliceOfficer::inspectParking(
    ParkedCar &car, ParkingMeter &meter)
{
  // default-initialize an empty object
  optional<ParkingTicket> option;

  if (PoliceOfficer::isViolating(car, meter))
}
