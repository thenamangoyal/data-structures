#ifndef FUNCTIONS_DATA_HANDLING_H
#define FUNCTIONS_DATA_HANDLING_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ClassRoom.h"
#include "ClassLab.h"
#include "ClassLec.h"


void reset_state(bool v_whether_reset);

void read_state (std::vector<room*>& room_list, std::vector<lab*>& lab_list, std::vector<lec*>& lec_list);

void save_state(const std::vector<room*>& v_room_list, const std::vector<lab*>& v_lab_list, const std::vector<lec*>& v_lec_list);

#endif