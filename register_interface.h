#ifndef REGISTER_INTERFACE
#define REGISTER_INTERFACE

#include "login_interface.h"
#include "equipment_management.h"

int ShowRegisterMenu();

void RunRegisterInterface(int option, EquipmentManagement* em);


// ע�ắ�������������˺ź����룬����˺źϷ��ԵȲ�����, �����˺�
Account* AccountRegister();

#endif // !REGISTER_INTERFACE
