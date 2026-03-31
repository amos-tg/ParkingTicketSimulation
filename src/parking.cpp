#include "parking.h"
#include <string>
#include <iostream>
#include <optional>

using namespace std;

ParkedCar::ParkedCar(
  string make, string model, Color color, 
  unsigned license_num, unsigned minutes_parked):
    make_m(make), model_m(model), color_m(color),
    license_num_m(license_num), minutes_parked_m(minutes_parked) {}

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

  if (car.getMinutesParked() > meter.getMinutesPurchased())
    option = ParkingTicket { car, meter, *this };

  return option;
}

ParkingTicket::ParkingTicket(
  ParkedCar &ticketed, ParkingMeter &meter, PoliceOfficer &popo):
    ticketed_m(ticketed), meter_m(meter), popo_m(popo) {}

unsigned ParkingTicket::getFine(unsigned mins_parked, unsigned mins_purchased) 
{
  // only gets called if minutes_parked > minutes_purchased
  unsigned fine {};
  unsigned mins_violated { mins_parked - mins_purchased };

  // add ten for any partial hours not handled by the rounded division
  if (mins_violated % 60) fine += 10; 

  // add 25 for the number of whole hours.
  fine += mins_violated / 60 * 25;

  return fine;
}
