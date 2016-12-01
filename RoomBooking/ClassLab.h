#ifndef CLASS_LAB_H
#define CLASS_LAB_H

#include <iostream>
#include <string>
#include <iomanip>

#include "ClassRoom.h"

class lab : public room {
private:
  int nocomp;
public:
  lab( const std::string& v_name, double v_area, int v_doors, int v_x, int v_y, int v_nocomp);
  lab( const std::string& v_name, double v_area, int v_doors, int v_x, int v_y, int v_nocomp, bool v_booking);
  virtual ~lab();
  virtual void print();
  int getnocomp() const;
  void setnocomp(int v_no_comp);
  friend std::ostream& operator<< (std::ostream& out, const lab& l);

};

std::ostream& operator<< (std::ostream& out, const lab& l);

#endif