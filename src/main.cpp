#include "parking.h"
#include <iostream>
#include <cassert>

using namespace std;

const char *PASS { "PASS" };
const char *OBJ_CREATION_TEST { "Test (Basic Object Creation): " };
const char *LEGAL_PARKING_TEST { "Test (Legal Parking): " };
const char *ILLEGAL_PARKING { "Test (Illegal Parking): " };
const char *MULTIPLE_CARS { "Test (Multiple Cars): " };
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

  fineCalculationTest();
  cout << endl;

  return 0;
}

void objCreationTest(void)
{
  string make { "Honda" }, model { "Odyssey" }, license_plate { "SPDRACER" };
  // directions say license number so I didn't use a string
  unsigned minutes_parked { 45 };
  ParkedCar car { make, model, RED, license_plate, minutes_parked };  

  ParkingMeter meter { 60 };
  PoliceOfficer popo { "Jordaenius Charmichael III", 42111 };


}
