#include "ClassRoom.h"
using namespace std;

room::room (const string& v_name, double v_area, int v_doors, int v_x, int v_y): name(v_name), area(v_area),doors(v_doors), x(v_x), y(v_y), booking(false)  {}

room::room (const string& v_name, double v_area, int v_doors, int v_x, int v_y, bool v_booking): name(v_name), area(v_area),doors(v_doors), x(v_x), y(v_y), booking(v_booking)  {}

room::~room() {
}

void room::book(){
  booking = true;
}
void room::unbook(){
  booking = false;
}
void room::print() const{
  cout<<"-------------------------"<<endl;
  cout<<"Type: Room"<<endl;
  cout<<"Name: "<<name<<endl;
  cout<<"Area: "<<area<<endl;
  cout<<"Doors: "<<doors<<endl;
  cout<<"x: "<<x<<endl;
  cout<<"y: "<<y<<endl;
  cout<<"Booking Status: "<<(booking ? "Booked": "Available")<<endl;
  cout<<"-------------------------"<<endl;
}

const string& room::getname() const{
  return name;
}

int room::getx() const{
  return x;
}

int room::gety() const{
  return y;
}

double room::getarea() const{
  return area;
}

bool room::getbooking() const{
  return booking;
}

ostream& operator<< (ostream& out, const room& r){
  
  out<<r.name<<"\t"<<fixed<<setprecision(4)<<r.area<<"\t"<<r.doors<<"\t"<<r.x<<"\t"<<r.y<<"\t"<<(r.booking ? 1: 0)<<endl;
  return out;
}