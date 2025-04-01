#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "linked_list.h"
#include "configs.h"

typedef struct _ResourceManager
{
	LinkedList* account_list;      // 账户
	LinkedList* equipment_list;    // 实验设备
	LinkedList* category_list;     // 实验设备类型
	LinkedList* laboratory_list;   // 实验室
}ResourceManager;


ResourceManager* GetResourceManage();

void LoadResource();
void SaveResource();

bool LoadAccountList();
bool SaveAccountList(char*);


bool LoadEquipmentList();
bool SaveEquipmentList(char*);


bool LoadCategoryList();
bool SaveCategoryList(char*);


bool LoadLaboratoryList();
bool SaveLaboratoryList(char*);

bool reLordAccountList();

bool SaveBackUp(char* time,char* formattedtime);

void DestoryResourceManage();

#endif // !RESOURCE_MANAGER_H