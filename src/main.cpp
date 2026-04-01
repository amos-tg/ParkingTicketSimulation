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

  multipleCarsTest();
  cout << '\n';

  fineCalculationTest();
  cout << endl;

  return 0;
}

void objCreationTest(void)
{
  cout << OBJ_CREATION_TEST;
  string make { "Honda" }, model { "Odyssey" }, license_plate { "SPDRACER" };
  unsigned minutes_parked { 45 };

  ParkedCar car { make, model, RED, license_plate, minutes_parked };  
  ParkingMeter meter { 60 };
  PoliceOfficer police { "Jordaenius Charmichael III", 42111 };
  cout << PASS;
}

void legalParkingTest(void)
{
  cout << LEGAL_PARKING_TEST;
  string make { "Honda" }, model { "Odyssey" }, license_plate { "SPDRACER" };
  unsigned minutes_parked { 45 };

  ParkedCar car { make, model, RED, license_plate, minutes_parked };  
  ParkingMeter meter { 60 };
  PoliceOfficer police { "Jordaenius Charmichael III", 42111 };

  // should be an empty optional since parking is legal
  optional<ParkingTicket> no_ticket { police.inspectParking(car, meter) };
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
  PoliceOfficer police { "Jordaenius Charmichael III", 42111 };

  optional<ParkingTicket> ticket { police.inspectParking(car, meter) };

  // make sure there a ticket
  assert(ticket);
  // make sure the fine is correct
  assert(ticket->getFine() == 35);

  // display the ticket to verify it's output
  cout << *ticket << '\n' << PASS;
}

void multipleCarsTest(void)
{
  cout << MULTIPLE_CARS_TEST << '\n';
  string make { "Honda" }, model { "Odyssey" };
  /// parked minutes exceeds purchased minutes by more than 60

  // there are a lot of honda odysseys in this lot
  
  // illegaly parked
  ParkedCar car1 { make, model, RED, "SPDRACER", 130 };  
  ParkingMeter meter1 { 60 };

  // illegaly parked
  ParkedCar car2 { make, model, BLUE, "ABANDOND", 10250 };
  ParkingMeter meter2 { 0 };

  // legally parked
  ParkedCar car3 { make, model, TAN, "LAWBIDER", 200 };
  ParkingMeter meter3 { 400 };

  // legally parked
  ParkedCar car4 { make, model, YELLOW, "SOCCRMOM", 60 };
  ParkingMeter meter4 { 80 };

  PoliceOfficer police { "Jordaenius Charmichael III", 42111 };

  // lawbreakers
  auto ticket1 { police.inspectParking(car1, meter1) };
  auto ticket2 { police.inspectParking(car2, meter2) };
  assert(ticket1 && ticket2);
  cout << '\n' << *ticket1 << '\n' << '\n' << *ticket2 << '\n';

  // lawbiders
  auto ticket3 { police.inspectParking(car3, meter3) };
  auto ticket4 { police.inspectParking(car4, meter4) };
  assert(!ticket3 && !ticket4);

  cout << PASS;
}

void fineCalculationTest(void)
{
  // non-static member getFine calls static member getFine overload internally
  
  // test the 25$ partial hour fine
  unsigned min_parked { 1 }, min_bought { 0 };
  assert(ParkingTicket::getFine(min_parked, min_bought) == 25);
  
  // test the 25$ full hour fine
  min_parked = 60;
  assert(ParkingTicket::getFine(min_parked, min_bought) == 25);

  // test that no fine works, police wouldn't call this though
  min_parked = 0;
  assert(ParkingTicket::getFine(min_parked, min_bought) == 0);

  // test multiple hours with a partial 
  min_parked = 361;
  min_bought = 120;
  assert(ParkingTicket::getFine(min_parked, min_bought) == 65);

  // test multiple whole hours
  min_parked = 360; 
  min_bought = 120;
  assert(ParkingTicket::getFine(min_parked, min_bought) == 55);
}
