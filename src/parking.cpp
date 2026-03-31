#include "parking.h"
#include <string>
#include <sstream>
#include <iostream>
#include <optional>
using namespace std;

ParkedCar::ParkedCar(
  string make, string model, Color color, 
  unsigned license_num, unsigned minutes_parked):
    make_m(make), model_m(model), color_m(color),
    license_num_m(license_num), mins_parked_m(minutes_parked) {}

ParkedCar& ParkedCar::operator++() 
{
  ++mins_parked_m;
  return *this;
}

ParkedCar ParkedCar::operator++(int)
{
  ParkedCar copy { *this };
  ++mins_parked_m;
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

unsigned ParkingTicket::getFine() const
{
  // only gets called if minutes_parked > minutes_purchased
  unsigned fine {};
  unsigned mins_violated 
  { ticketed_m.getMinutesParked() - meter_m.getMinutesPurchased() };

  // add ten for any partial hours not handled by the rounded division
  if (mins_violated % 60) fine += 10; 

  // add 25 for the number of whole hours.
  fine += mins_violated / 60 * 25;

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
    << "Fine: " << this->getFine() << '\n'
    << "Officer Name: " << popo_m.getName() << '\n'
    << "Officer Badge Num: " << popo_m.getBadgeNum();

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
