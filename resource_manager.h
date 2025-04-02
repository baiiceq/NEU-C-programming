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
	LinkedList* service_list;      // 维修记录
}ResourceManager;


ResourceManager* GetResourceManage();

void LoadResource();
void SaveResource();

bool LoadAccountList(char*);
bool SaveAccountList(char*);


bool LoadEquipmentList(char*);
bool SaveEquipmentList(char*);


bool LoadCategoryList(char*);
bool SaveCategoryList(char*);


bool LoadLaboratoryList(char*);
bool SaveLaboratoryList(char*);

bool LoadServiceList(char*);
bool SaveServiceList(char*);

bool reLordAccountList();

bool SaveBackUp(char* time,char* formattedtime);

void DestoryResourceManage();

#endif // !RESOURCE_MANAGER_H