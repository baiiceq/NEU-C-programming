#ifndef EXPERIMENTAL_EQUIPMENT_H
#define EXPERIMENTAL_EQUIPMENT_H

#include "configs.h"
#include "category.h"
#include "lab_room.h"
#include "resource_manager.h"



typedef enum _EquipmentState
{
	Using,     // 正在使用
	Idle,      // 空闲
	Lost,      // 遗失
	Damaged,   // 损坏（未在维修）
	Scrapped,  // 报废（准备删除？）
	Repairing  // 正在维修
}EquipmentState;

typedef struct _ExperimentalEquipment
{
	int id;                                   // 设备id
	Category* category;                        // 设备类别
	char name[EQUIPMENT_LENGTH];              // 设备名字
	int room_id;                              // 所在实验室ID,-1表示未分配
	int price;                                // 设备价格
	char purchase_date[DATE_LENGTH];          // 购入日期 (YYYY-MM-DD)
	EquipmentState state;                     // 设备状态
}ExperimentalEquipment;

ExperimentalEquipment* CreateExperimentalEquipment(Category* category, char* name, int room_id, int price, char* purchase_date);

void DestoryExperimentalEquipment(ExperimentalEquipment* experimental_equipment);

void AddExperimentalEquipment();
void DeleteExperimentalEquipment(ExperimentalEquipment* ee);
void ChangeExperimentalEquipment();

bool ChangeName(ExperimentalEquipment* eq, char* newname);
bool ChangePrice(ExperimentalEquipment* eq, int newprice);
bool ChangeRoom_id(ExperimentalEquipment* eq, char* newroomid);
bool ChangePurchaseDate(ExperimentalEquipment* eq, char* newdate);
bool ChangeExperimentalCategory(ExperimentalEquipment* eq, Category* newcategory);


LinkedList* EFindByName(LinkedList* eqlist, char* name);
LinkedList* EFindById(LinkedList* eqlist, int id);
LinkedList* EFindByRoom_id(LinkedList* eqlist, int roomid);
LinkedList* EFindByCategory(LinkedList* eqlist, int categoryid);
LinkedList* EFindByDate(LinkedList* eqlist, char* start, char* end);
LinkedList* EFindByPrice(LinkedList* eqlist, int min, int max);
#endif // !EXPERIMENTAL_EQUIPMENT_H
