#ifndef FUNCTIONS_IO_H
#define FUNCTIONS_IO_H

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

void read_input(std::vector<room*>& room_list, std::vector<lab*>& lab_list, std::vector<lec*>& lec_list);

void print_operations();

#endif