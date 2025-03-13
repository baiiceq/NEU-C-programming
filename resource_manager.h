#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "linked_list.h"

typedef struct _ResourceManager
{
	LinkedList* account_list;    // �˻�
	LinkedList* equipment_list;   // ʵ���豸
	LinkedList* laboratory_list;  // ʵ����
}ResourceManager;
#endif // !RESOURCE_MANAGER_H

ResourceManager* GetResourceManage();

void DestoryResourceManage();
