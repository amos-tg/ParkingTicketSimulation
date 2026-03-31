#include <string>
#include <optional>

class ParkingTicket;

enum Color {
  RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, BLACK, WHITE, TAN,
};

class ParkedCar
{
  std::string make, model;
  Color color;
  unsigned license_num;
  unsigned minutes_parked;
public:
  ParkedCar(
      std::string make, std::string model, Color color, 
      unsigned license_num, unsigned minutes_parked);

  inline std::string getMake() const 
  { return make; }

  inline std::string getModel() const
  { return model; }

  inline Color getColor() const
  { return color; }

  inline unsigned getLicenseNum() const
  { return license_num; }

  inline unsigned getMinutedParked() const
  { return minutes_parked; }

  inline void setMinutesParked(unsigned minutes)
  { minutes_parked = minutes; }

  ParkedCar& operator++();
  ParkedCar& operator++(int);
};

class ParkingMeter
{
  unsigned minutes_purchased;
public:
  ParkingMeter(unsigned mins = 30);

  inline unsigned getMinutesPurchased(void) 
  { return minutes_purchased; }

  inline void setMinutesPurchased(unsigned mins) 
  { minutes_purchased = mins; }
};

class PoliceOfficer 
{
  std::string name;
  unsigned badge_num;
public:
  inline unsigned getBadgeNum() const
  { return badge_num; }

  std::string getName() const 
  { return name; }

  /// returns an optional containing a ParkingTicket if the car needs to be 
  /// ticketed, otherwise an empty optional is returned.
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
public:
  /// Generates a report 
  std::string report() const;
private:
  unsigned getFine() const;
};
