#ifndef FUNCTIONS_IMPLEMENT_H
#define FUNCTIONS_IMPLEMENT_H

#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include "ClassRoom.h"
#include "ClassLab.h"
#include "ClassLec.h"

#include "FunctionsTemplate.h"


int smallest_lec_given_student (const std::vector<lec*>& list, int no_student, bool only_available= false);

int least_equip_dens_lab (const std::vector<lab*>& list);

std::vector<int> min_room_given_person (const std::vector<room*>& list, int no_person, bool only_available= false);

#endif