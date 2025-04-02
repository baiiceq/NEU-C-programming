#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "linked_list.h"
#include "configs.h"

typedef struct _ResourceManager
{
	LinkedList* account_list;      // �˻�
	LinkedList* equipment_list;    // ʵ���豸
	LinkedList* category_list;     // ʵ���豸����
	LinkedList* laboratory_list;   // ʵ����
	LinkedList* service_list;      // ά�޼�¼
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