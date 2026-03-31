#include "parking.h"
#include <iostream>

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
  
}
