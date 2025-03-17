#pragma once
#ifndef LOGIN_INTERFACE
#define LOGIN_INTERFACE

#include "configs.h"
#include "linked_list.h"
#include "equipment_management.h"

int ShowLoginMenu();

void RunLoginInterface(int option, EquipmentManagement* em);

// 登录函数（包括输入账号和密码，检查账号合法性等操作）, 返回账号
Account* AccountLogin();

#endif // !LOGIN_INTERFACE