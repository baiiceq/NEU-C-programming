#ifndef LOGIN_INTERFACE
#define LOGIN_INTERFACE

#include "configs.h"
#include "account.h"
#include "linked_list.h"
#include "equipment_management.h"

struct _EquipmentManagement;
typedef struct _EquipmentManagement EquipmentManagement;

typedef struct _LoginInterface 
{
    LinkedList* account_list;
} LoginInterface;

// ���ٵ�¼����
void destoryLoginInterface();

// ��ȡ��¼����
LoginInterface* GetLoginInterface();

int ShowLoginMenu();

void RunLoginInterface(int option, EquipmentManagement* em);

// ��¼���������������˺ź����룬����˺źϷ��ԵȲ�����, �����˺�
Account* AccountLogin();

#endif // !LOGIN_INTERFACE