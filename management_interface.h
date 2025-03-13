#ifndef MANAGEMENT_INTERFACE
#define MANAGEMENT_INTERFACE

#include "account.h"
#include "linked_list.h"
#include "equipment_management.h"

// 销毁管理界面
void destoryManagementInterface();

// 获取管理界面
LoginInterface* GetManagementInterface();

int ShowManagementMenu();

void RunManagementInterface(int option, EquipmentManagement* em);

#endif // !MANAGEMENT_INTERFACE
