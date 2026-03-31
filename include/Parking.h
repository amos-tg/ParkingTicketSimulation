#include <string>
#include <optional>

enum Color {

};

class ParkedCar
{
  std::string make, model;
  Color color;
  unsigned license_num;
  unsigned minutes_parked;
};

class ParkingMeter
{
  unsigned minutes_purchased;
};

class ParkingTicket;

class PoliceOfficer 
{
  std::string name;
  unsigned badge_num;

public:
  inline unsigned getBadgeNum() const { return badge_num; }
  std::string getName() const { return name; }

  /// returns an optional containing a ParkingTicket if the car needs to be 
  /// ticketed, if otherwise an empty optional is returned.
  std::optional<ParkingTicket> inspectParking();

private:
  /// returns true if a Car is violating the parking laws.
  bool isViolating() const;
};

class ParkingTicket 
{
  ParkedCar ticketed;
  ParkingMeter meter;
  PoliceOfficer popo;
};
