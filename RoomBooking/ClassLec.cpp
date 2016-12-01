#include "ClassLec.h"
using namespace std;

lec::lec (const string& v_name, double v_area, int v_doors, int v_x, int v_y, int v_nochairs): room(v_name, v_area, v_doors, v_x, v_y), nochairs(v_nochairs) {}

lec::lec (const string& v_name, double v_area, int v_doors, int v_x, int v_y, int v_nochairs, bool v_booking): room(v_name, v_area, v_doors, v_x, v_y, v_booking), nochairs(v_nochairs) {}

lec::~lec() {
}

void lec::print(){
  cout<<"-------------------------"<<endl;
  cout<<"Type: Lecture Hall"<<endl;
  cout<<"Name: "<<name<<endl;
  cout<<"Area: "<<area<<endl;
  cout<<"Doors: "<<doors<<endl;
  cout<<"x: "<<x<<endl;
  cout<<"y: "<<y<<endl;
  cout<<"No of chairs: "<<nochairs<<endl;
  cout<<"Booking Status: "<<(booking ? "Booked": "Available")<<endl;
  cout<<"-------------------------"<<endl;
}

int lec::getnochairs() const {
  return nochairs;
}

ostream& operator<< (ostream& out, const lec& le){
  
  out<<le.name<<"\t"<<fixed<<setprecision(4)<<le.area<<"\t"<<le.doors<<"\t"<<le.x<<"\t"<<le.y<<"\t"<<le.nochairs<<"\t"<<(le.booking ? 1: 0)<<endl;
  return out;
}