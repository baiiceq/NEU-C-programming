#ifndef EXPERIMENTAL_EQUIPMENT_H
#define EXPERIMENTAL_EQUIPMENT_H

#include "configs.h"
#include "category.h"

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
	int id;                         // 设备id(类别id+自身id)
	Category category;              // 设备类别
	char name[EQUIPMENT_LENGTH];    // 设备名字
	int room_id;                    // 所在实验室ID
	int price;                      // 设备价格
	char purchase_date[11];         // 购入日期 (YYYY-MM-DD)
}ExperimentalEquipment;
#endif // !EXPERIMENTAL_EQUIPMENT_H

ExperimentalEquipment* CreateExperimentalEquipment();

void DestoryExperimentalEquipment(ExperimentalEquipment* experimental_equipment);