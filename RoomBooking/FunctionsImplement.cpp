#include "FunctionsImplement.h"
using namespace std;

int smallest_lec_given_student (const vector<lec*>& list, int no_student, bool only_available) {
  vector<lec*> list_to_search= list;
  if (only_available){
    for(int k=0; k<list_to_search.size(); k++){
      if (list_to_search[k]->getbooking()){
        list_to_search.erase(list_to_search.begin() + k);
        k--;
      }
    }
  }


  if (list_to_search.empty()){
    return -1;
  }
  int r = -1;
  int curr_min;
  for(int i=0; i< list_to_search.size(); i++){
    int curr_val = list_to_search[i]->getnochairs();
    if (curr_val >= no_student && r==-1){
      r = i;
      curr_min = curr_val;
    }
    if (curr_val >= no_student && curr_val < curr_min && r!=-1){
      r = i;
      curr_min = curr_val;
    }
  }
  if (r>=0){
  r = search_list<lec*> (list, list_to_search[r]->getname());
  }
  return r;
}

int least_equip_dens_lab (const vector<lab*>& list) {
  if (list.empty()){
    return -1;
  }
  int l = 0;
  double min_dens = (double(list[0]->getnocomp()))/(list[0]->getarea());
  for(int i=1;i<list.size();i++){
    double curr_dens = (double(list[i]->getnocomp()))/(list[i]->getarea());
    if (curr_dens < min_dens){
      min_dens = curr_dens;
      l = i;
    }
  }
  return l;
}

vector<int> min_room_given_person (const vector<room*>& list, int no_person, bool only_available) {
  vector<room*> sorted_list = list;
  if (only_available){
    for(int k=0; k<sorted_list.size(); k++){
      if (sorted_list[k]->getbooking()){
        sorted_list.erase(sorted_list.begin() + k);
        k--;
      }
    }
  }
  sort(sorted_list.begin(),sorted_list.end(), sort_using_area<room*>);
  reverse(sorted_list.begin(), sorted_list.end());
  long int current_space = 0;
  long int required_space = no_person * 30;
  
  
  vector<string> room_name;
  for (int i=0;i<sorted_list.size() && current_space < required_space;i++){
    current_space += 30*floor((sorted_list[i]->getarea())/30);
    room_name.push_back(sorted_list[i]->getname());
  }
  
  if (current_space < required_space) {
    room_name.clear();    
  }

  vector<int> required_room_list;
  for(int j=0;j<room_name.size();j++){
    int room_no = search_list<room*>(list, room_name[j]) ;
    required_room_list.push_back(room_no);
  }

  return required_room_list;

}