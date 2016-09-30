//2015CSB1021
//Naman Goyal
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>

#include "ClassRoom.h"
#include "ClassLab.h"
#include "ClassLec.h"

#include "FunctionsDataHandling.h"
#include "FunctionsTemplate.h"
#include "FunctionsImplement.h"
#include "FunctionsIO.h"


using namespace std;

int main(){

  vector<room*> room_list;
  vector<lab*> lab_list;
  vector<lec*> lec_list;

  read_state(room_list, lab_list, lec_list);

  ////////////////////////////////////////////////////
  
  read_input(room_list, lab_list, lec_list);

  
  ////////////////////////////////////////////////////

  
  return 0;
}
