#pragma once
#ifndef REGISTER_INTERFACE
#define REGISTER_INTERFACE

#include "resource_manager.h"
#include "equipment_management.h"

int ShowRegisterMenu();

void RunRegisterInterface(int option, EquipmentManagement* em);


// 注册函数（包括输入账号和密码，检查账号合法性等操作）, 返回账号
Account* AccountRegister();

#endif // !REGISTER_INTERFACE
