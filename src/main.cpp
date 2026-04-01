#include "parking.h"
#include <iostream>
#include <cassert>
#include <optional>

using namespace std;

const char *PASS { "PASS" };

const char *OBJ_CREATION_TEST { "Test (Basic Object Creation): " };
const char *LEGAL_PARKING_TEST { "Test (Legal Parking): " };
const char *ILLEGAL_PARKING_TEST { "Test (Illegal Parking): " };
const char *MULTIPLE_CARS_TEST { "Test (Multiple Cars): " };
const char *FINE_TEST { "Test (Fine Calculation Verification): " };

void objCreationTest(void);

void legalParkingTest(void);

void illegalParkingTest(void);

void multipleCarsTest(void);

void fineCalculationTest(void);

int main(void) {
  objCreationTest(); 
  cout << '\n';

  legalParkingTest();
  cout << '\n';

  illegalParkingTest();
  cout << '\n';

  //multipleCarsTest();
  //cout << '\n';

  //fineCalculationTest();
  //cout << endl;

  return 0;
}

void objCreationTest(void)
{
  cout << OBJ_CREATION_TEST;
  string make { "Honda" }, model { "Odyssey" }, license_plate { "SPDRACER" };
  unsigned minutes_parked { 45 };

  ParkedCar car { make, model, RED, license_plate, minutes_parked };  
  ParkingMeter meter { 60 };
  PoliceOfficer popo { "Jordaenius Charmichael III", 42111 };
  cout << PASS;
}

void legalParkingTest(void)
{
  cout << LEGAL_PARKING_TEST;
  string make { "Honda" }, model { "Odyssey" }, license_plate { "SPDRACER" };
  unsigned minutes_parked { 45 };

  ParkedCar car { make, model, RED, license_plate, minutes_parked };  
  ParkingMeter meter { 60 };
  PoliceOfficer popo { "Jordaenius Charmichael III", 42111 };

  // should be an empty optional since parking is legal
  optional<ParkingTicket> no_ticket { popo.inspectParking(car, meter) };
  // implicit bool conv. of optional returns true if there's an obj.
  assert(!no_ticket);
  cout << PASS;
}

void illegalParkingTest(void)
{
  cout << ILLEGAL_PARKING_TEST << '\n';
  string make { "Honda" }, model { "Odyssey" }, license_plate { "SPDRACER" };
  /// parked minutes exceeds purchased minutes by more than 60
  unsigned minutes_parked { 130 };

  ParkedCar car { make, model, RED, license_plate, minutes_parked };  
  ParkingMeter meter { 60 };
  PoliceOfficer popo { "Jordaenius Charmichael III", 42111 };

  optional<ParkingTicket> ticket { popo.inspectParking(car, meter) };

  // make sure there a ticket
  assert(ticket);
  // make sure the fine is correct
  assert(ticket->getFine() == 35);

  // display the ticket to verify it's output
  cout << *ticket << '\n' << PASS;
}
