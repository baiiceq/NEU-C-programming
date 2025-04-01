#pragma once
#ifndef REGISTER_INTERFACE
#define REGISTER_INTERFACE

#include "resource_manager.h"
#include "equipment_management.h"

int ShowRegisterMenu();

void RunRegisterInterface(int option, EquipmentManagement* em);


#endif // !REGISTER_INTERFACE
