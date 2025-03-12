#ifndef MANAGEMENT_INTERFACE
#define MANAGEMENT_INTERFACE

#include "account.h"
#include "linked_list.h"
#include "equipment_management.h"

typedef struct _ManagementInterface
{
	AccountType current_type;    // 当前账户类型
	LinkedList equipment_list;   // 实验设备
	LinkedList laboratory_list;  // 实验室
	// 。。。。未来补充
}ManagementInterface;

#endif // !MANAGEMENT_INTERFACE
