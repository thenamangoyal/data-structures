#include "FunctionsDataHandling.h"
using namespace std;

void reset_state(bool v_whether_reset) {
  if (v_whether_reset) {
    if (ifstream("STATE_ROOM.txt")) {
      remove("STATE_ROOM.txt");
    }
    if (ifstream("STATE_LAB.txt")) {
      remove("STATE_LAB.txt");
    }
    if (ifstream("STATE_LEC.txt")) {
      remove("STATE_LEC.txt");
    }
  }
}


void read_state (vector<room*>& room_list, vector<lab*>& lab_list, vector<lec*>& lec_list) {
  bool resume_state = false;

  if (ifstream("STATE_ROOM.txt") && ifstream("STATE_LAB.txt") && ifstream("STATE_LEC.txt")){
    resume_state = true;
  }

  if (resume_state) {

    ifstream room_file;
    room_file.open("STATE_ROOM.txt",ios::in);  

    string temp_room_name;
    double temp_room_area;
    int temp_room_doors;
    int temp_room_x;
    int temp_room_y;
    int temp_room_booking_int;

    while(room_file>>temp_room_name>>temp_room_area>>temp_room_doors>>temp_room_x>>temp_room_y>>temp_room_booking_int) {
      bool temp_room_booking_bool = ((temp_room_booking_int == 1) ? true : false);
      room* temp_room = new room(temp_room_name,temp_room_area,temp_room_doors,temp_room_x,temp_room_y,temp_room_booking_bool);
      room_list.push_back(temp_room); 
    }
    
    room_file.close();

    ////////////////////////////////////////////////////

    ifstream lab_file;
    lab_file.open("STATE_LAB.txt",ios::in);  

    string temp_lab_name;
    double temp_lab_area;
    int temp_lab_doors;
    int temp_lab_x;
    int temp_lab_y;
    int temp_lab_nocomp;
    int temp_lab_booking_int;

    while(lab_file>>temp_lab_name>>temp_lab_area>>temp_lab_doors>>temp_lab_x>>temp_lab_y>>temp_lab_nocomp>>temp_lab_booking_int) {
      bool temp_lab_booking_bool = ((temp_lab_booking_int == 1) ? true : false);
      lab* temp_lab = new lab(temp_lab_name,temp_lab_area,temp_lab_doors,temp_lab_x,temp_lab_y,temp_lab_nocomp,temp_lab_booking_bool);
      lab_list.push_back(temp_lab);
    }
    
    lab_file.close();

    ////////////////////////////////////////////////////

    ifstream lec_file;
    lec_file.open("STATE_LEC.txt",ios::in);
    
    string temp_lec_name;
    double temp_lec_area;
    int temp_lec_doors;
    int temp_lec_x;
    int temp_lec_y;
    int temp_lec_nochairs;
    int temp_lec_booking_int;

    while(lec_file>>temp_lec_name>>temp_lec_area>>temp_lec_doors>>temp_lec_x>>temp_lec_y>>temp_lec_nochairs>>temp_lec_booking_int) {
      bool temp_lec_booking_bool = ((temp_lec_booking_int == 1) ? true : false);
      lec* temp_lec = new lec(temp_lec_name,temp_lec_area,temp_lec_doors,temp_lec_x,temp_lec_y,temp_lec_nochairs,temp_lec_booking_bool);
      lec_list.push_back(temp_lec);
    }

    lec_file.close();

  }
  else {

    ifstream room_file;
    room_file.open("ROOM.txt",ios::in);  

    string temp_room_name;
    double temp_room_area;
    int temp_room_doors;
    int temp_room_x;
    int temp_room_y;

    while(room_file>>temp_room_name>>temp_room_area>>temp_room_doors>>temp_room_x>>temp_room_y) {
      room* temp_room = new room(temp_room_name,temp_room_area,temp_room_doors,temp_room_x,temp_room_y);
      room_list.push_back(temp_room);    
    }
    
    room_file.close();

    ////////////////////////////////////////////////////

    ifstream lab_file;
    lab_file.open("LAB.txt",ios::in);  

    string temp_lab_name;
    double temp_lab_area;
    int temp_lab_doors;
    int temp_lab_x;
    int temp_lab_y;
    int temp_lab_nocomp;

    while(lab_file>>temp_lab_name>>temp_lab_area>>temp_lab_doors>>temp_lab_x>>temp_lab_y>>temp_lab_nocomp) {
      lab* temp_lab = new lab(temp_lab_name,temp_lab_area,temp_lab_doors,temp_lab_x,temp_lab_y,temp_lab_nocomp);
      lab_list.push_back(temp_lab);
    }
    
    lab_file.close();

    ////////////////////////////////////////////////////

    ifstream lec_file;
    lec_file.open("LEC.txt",ios::in);
    
    string temp_lec_name;
    double temp_lec_area;
    int temp_lec_doors;
    int temp_lec_x;
    int temp_lec_y;
    int temp_lec_nochairs;

    while(lec_file>>temp_lec_name>>temp_lec_area>>temp_lec_doors>>temp_lec_x>>temp_lec_y>>temp_lec_nochairs) {
      lec* temp_lec = new lec(temp_lec_name,temp_lec_area,temp_lec_doors,temp_lec_x,temp_lec_y,temp_lec_nochairs);
      lec_list.push_back(temp_lec);
    }

    lec_file.close();

  }
}

void save_state(const vector<room*>& v_room_list, const vector<lab*>& v_lab_list, const vector<lec*>& v_lec_list) {
  ofstream file_state_room;
  ofstream file_state_lab;
  ofstream file_state_lec;

  file_state_room.open("STATE_ROOM.txt", ios::out | ios::trunc);
  file_state_lab.open("STATE_LAB.txt", ios::out | ios::trunc);
  file_state_lec.open("STATE_LEC.txt", ios::out | ios::trunc);

  for(int i=0; i<v_room_list.size(); i++){
    file_state_room<<*v_room_list[i];
  }

  for(int i=0; i<v_lab_list.size(); i++){
    file_state_lab<<*v_lab_list[i];
  }

  for(int i=0; i<v_lec_list.size(); i++){
    file_state_lec<<*v_lec_list[i];
  }

  file_state_room.close();
  file_state_lab.close();
  file_state_lec.close();

}