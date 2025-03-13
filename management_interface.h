#ifndef MANAGEMENT_INTERFACE
#define MANAGEMENT_INTERFACE

#include "account.h"
#include "linked_list.h"
#include "equipment_management.h"

// ���ٹ������
void destoryManagementInterface();

// ��ȡ�������
LoginInterface* GetManagementInterface();

int ShowManagementMenu();

void RunManagementInterface(int option, EquipmentManagement* em);

#endif // !MANAGEMENT_INTERFACE
