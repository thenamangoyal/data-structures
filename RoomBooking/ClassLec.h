#ifndef CLASS_LEC_H
#define CLASS_LEC_H

#include <iostream>
#include <string>
#include <iomanip>

#include "ClassRoom.h"

class lec : public room {
private:
  int nochairs;
public:
  lec( const std::string& v_name, double v_area, int v_doors, int v_x, int v_y, int v_nochairs);
  lec( const std::string& v_name, double v_area, int v_doors, int v_x, int v_y, int v_nochairs, bool v_booking);
  virtual ~lec();
  virtual void print();
  int getnochairs() const;
  friend std::ostream& operator<< (std::ostream& out, const lec& le);
};

std::ostream& operator<< (std::ostream& out, const lec& le);

#endif