#pragma once
#ifndef ID_MANAGER_H
#define ID_MANAGER_H

#include "linked_list.h"
#include "configs.h"

typedef enum _IdType
{
    EquipmentID,
    CategoryID,
    RoomID,
    AccountID
}IdType;

typedef struct _IdManager
{
    int current_equipment_id;   // 设备ID
    int current_category_id;    // 设备类别ID
    int current_room_id;        // 房间ID
    int current_account_id;     // 账户ID
}IdManager;

// 获取一个新ID
int GetNewId(IdType type);

void DestoryIdManager();

// 保存ID
bool SaveId();

// 读取ID
bool LoadId();
#endif // !ID_MANAGER_H
