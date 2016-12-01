#ifndef FUNCTIONS_TEMPLATE_H
#define FUNCTIONS_TEMPLATE_H

#include <string>
#include <vector>

#include "ClassRoom.h"
#include "ClassLab.h"
#include "ClassLec.h"

template <typename T>
int search_list (const std::vector<T>& list, const std::string& search_name) {
  int i;
  for(i=0;i< list.size() && ( (list[i]->getname()) != search_name );i++){
  }
  if (i < list.size()){
    return i;
  }
  return -1;
}

template <typename T>
void delete_list (std::vector<T>& list, int pos) {
  
  if (pos >= 0){
    delete list[pos];
    list.erase(list.begin() + pos);
  }
  
}

template <typename T>
int find_nearest_room (const std::vector<T>& list, int pos_x, int pos_y) {
  if (list.empty()){
    return -1;
  }
  int r = 0;
  int least_distance = ((list[0]->getx()) - pos_x )*((list[0]->getx()) - pos_x ) + ((list[0]->gety()) - pos_y )*((list[0]->gety()) - pos_y ) ;
  for(int i = 1; i < list.size(); i++ ){
    int temp_distance = ((list[i]->getx()) - pos_x )*((list[i]->getx()) - pos_x ) + ((list[i]->gety()) - pos_y )*((list[i]->gety()) - pos_y ) ;
    if (least_distance > temp_distance){
      least_distance = temp_distance;
      r = i;
    }
  }
  return r;
}

template <typename T>
bool sort_using_area (const T& e1, const T& e2) {
  return (e1->getarea() < e2->getarea());
}


#endif