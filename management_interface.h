#ifndef MANAGEMENT_INTERFACE
#define MANAGEMENT_INTERFACE

#include "account.h"
#include "linked_list.h"
#include "equipment_management.h"

typedef struct _ManagementInterface
{
	AccountType current_type;    // ��ǰ�˻�����
	LinkedList equipment_list;   // ʵ���豸
	LinkedList laboratory_list;  // ʵ����
	// ��������δ������
}ManagementInterface;

#endif // !MANAGEMENT_INTERFACE
