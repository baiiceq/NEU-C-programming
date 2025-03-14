#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "linked_list.h"
#include "configs.h"

typedef struct _ResourceManager
{
	LinkedList* account_list;    // �˻�
	LinkedList* equipment_list;   // ʵ���豸
	LinkedList* laboratory_list;  // ʵ����
}ResourceManager;


ResourceManager* GetResourceManage();
bool CreateAccountList();
bool SaveAccountList();

void DestoryResourceManage();

#endif // !RESOURCE_MANAGER_H