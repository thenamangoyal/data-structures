#include "ClassLab.h"
using namespace std;

lab::lab (const string& v_name, double v_area, int v_doors, int v_x, int v_y, int v_nocomp): room(v_name, v_area, v_doors, v_x, v_y), nocomp(v_nocomp) {}


lab::lab (const string& v_name, double v_area, int v_doors, int v_x, int v_y, int v_nocomp, bool v_booking): room(v_name, v_area, v_doors, v_x, v_y, v_booking), nocomp(v_nocomp) {}

lab::~lab() {
}

void lab::print(){
  cout<<"-------------------------"<<endl;
  cout<<"Type: Lab"<<endl;
  cout<<"Name: "<<name<<endl;
  cout<<"Area: "<<area<<endl;
  cout<<"Doors: "<<doors<<endl;
  cout<<"x: "<<x<<endl;
  cout<<"y: "<<y<<endl;
  cout<<"No of computers: "<<nocomp<<endl;
  cout<<"Booking Status: "<<(booking ? "Booked": "Available")<<endl;
  cout<<"-------------------------"<<endl;

}

int lab::getnocomp() const{
  return nocomp;
}

void lab::setnocomp(int v_no_comp){
  nocomp = v_no_comp; 
}

ostream& operator<< (ostream& out, const lab& l){
  
  out<<l.name<<"\t"<<fixed<<setprecision(4)<<l.area<<"\t"<<l.doors<<"\t"<<l.x<<"\t"<<l.y<<"\t"<<l.nocomp<<"\t"<<(l.booking ? 1: 0)<<endl;
  return out;
}