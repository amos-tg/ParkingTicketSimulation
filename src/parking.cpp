#include "parking.h"
#include <string>
#include <sstream>
#include <iostream>
#include <optional>

using namespace std;

ParkedCar::ParkedCar(
  string make, string model, Color color, 
  string license_num, unsigned minutes_parked):
    make_m(make), model_m(model), color_m(color),
    mins_parked_m(minutes_parked) 
{
  // max size of a license plate on a car in USA in characters is 8
  const size_t max_len { 8 };
  if (license_num.size() > max_len || license_num.size() < 1)
  {
    license_num_m = INVALID_PLATE; 
    return;
  }

  license_num_m = license_num;
}

string ParkedCar::getColor() const
{
  // converts enum value to string name
  switch (color_m)
  {
  case RED:
    return "Red";
  case ORANGE:
    return "Orange";
  case YELLOW:
    return "Yellow";
  case GREEN:
    return "Green";
  case BLUE:
    return "Blue";
  case PURPLE:
    return "Purple";
  case BLACK:
    return "Black";
  case WHITE:
    return "White";
  case TAN:
    return "Tan";
  default:
    return "INVALID";
  }
}

optional<ParkingTicket> PoliceOfficer::inspectParking(
    ParkedCar &car, ParkingMeter &meter)
{
  // default-initialize an empty option
  optional<ParkingTicket> option;

  // add the ticket to the option if the car is violating parking rules 
  if (car.getMinutesParked() > meter.getMinutesPurchased())
    option = ParkingTicket { car, meter, *this };

  return option;
}

ParkingTicket::ParkingTicket(
  ParkedCar &ticketed, ParkingMeter &meter, PoliceOfficer &police):
    ticketed_m(ticketed), meter_m(meter), police_m(police) {}

int ParkingTicket::getFine() const
{
  // call the static member overload with the currently stored members
  return getFine(ticketed_m.getMinutesParked(), meter_m.getMinutesPurchased());
}

int ParkingTicket::getFine(unsigned mins_parked, unsigned mins_bought)
{
  unsigned fine {};
  unsigned mins_violated { mins_parked - mins_bought };
  
  // handle legal parkers appropriately, shouldn't be needed. 
  if (mins_violated <= 0) return 0;

  // add 25$ for any violation
  if (mins_violated) fine += 25; 

  // add 10$ for a partial hour
  if (mins_violated % 60) fine += 10;

  // add 10$ for the number of additional whole hours.
  fine += (mins_violated / 60 - 1) * 10;

  return fine;
}

string ParkingTicket::report() const 
{
  ostringstream report {};

  // generate the report
  report << "Make: " << ticketed_m.getMake() << '\n'
    << "Model: " << ticketed_m.getModel() << '\n'
    << "Color: " << ticketed_m.getColor() << '\n'
    << "License Number: " << ticketed_m.getLicenseNum() << '\n'
    << "Minutes Parked: " << ticketed_m.getMinutesParked() << '\n'
    << "Minutes Purchased: " << meter_m.getMinutesPurchased() << '\n'
    << "Fine: " << this->getFine() << '$' << '\n'
    << "Officer Name: " << police_m.getName() << '\n'
    << "Officer Badge Num: " << police_m.getBadgeNum();

  // convert to string and return
  return report.str();
}

ostream& operator<<(ostream &ostream, const ParkingTicket &ticket) 
{
  // check for and if present clear failure state on ostream
  if (ostream) ostream.clear();

  // insert the report into the ostream 
  ostream << ticket.report();

  // return for chaining
  return ostream;
}
