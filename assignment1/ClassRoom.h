#ifndef CLASS_ROOM_H
#define CLASS_ROOM_H

#include <iostream>
#include <string>
#include <iomanip>


class room {
protected:
  std::string name;
  double area;
  int doors;
  int x;
  int y;
  bool booking;
public:
  room( const std::string& v_name, double v_area, int v_doors, int v_x, int v_y);
  room( const std::string& v_name, double v_area, int v_doors, int v_x, int v_y, bool v_booking);
  virtual ~room();
  void book();
  void unbook();
  virtual void print() const;
  const std::string& getname() const;
  int getx() const;
  int gety() const;
  double getarea() const;
  bool getbooking() const;
  friend std::ostream& operator<< (std::ostream& out, const room& r);
};

std::ostream& operator<< (std::ostream& out, const room& r);

#endif