#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "linked_list.h"
#include "configs.h"

typedef struct _ResourceManager
{
	LinkedList* account_list;    // 账户
	LinkedList* equipment_list;   // 实验设备
	LinkedList* laboratory_list;  // 实验室
}ResourceManager;


ResourceManager* GetResourceManage();
bool CreateAccountList();
bool SaveAccountList();

void DestoryResourceManage();

#endif // !RESOURCE_MANAGER_H