#ifndef EXPERIMENTAL_EQUIPMENT_H
#define EXPERIMENTAL_EQUIPMENT_H

#include "configs.h"
#include "category.h"
#include "lab_room.h"

enum EquipmentState
{
	Using,     // 正在使用
	Idle,      // 空闲
	Lost,      // 遗失
	Damaged,   // 损坏（未在维修）
	Scrapped,  // 报废（准备删除？）
	Repairing  // 正在维修
};

typedef struct _ExperimentalEquipment
{
	int id;                                   // 设备id
	Category* category;                        // 设备类别
	char name[EQUIPMENT_LENGTH];              // 设备名字
	int room_id;                              // 所在实验室ID
	int price;                                // 设备价格
	char purchase_date[DATE_LENGTH];          // 购入日期 (YYYY-MM-DD)
}ExperimentalEquipment;

ExperimentalEquipment* CreateExperimentalEquipment(Category* category, char* name, int room_id, int price, char* purchase_date);

void DestoryExperimentalEquipment(ExperimentalEquipment* experimental_equipment);

void AddExperimentalEquipment();

#endif // !EXPERIMENTAL_EQUIPMENT_H