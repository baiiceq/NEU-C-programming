#pragma once
#ifndef LAB_ROOM_H
#define LAB_ROOM_H

#include "configs.h"
#include "linked_list.h"
#include "experimental_equipment.h"

typedef struct _LabRoom {
    int id;                            // 房间编号
    char name[LABROOM_LENGTH];         // 房间名称
    LinkedList* technician_id_list;     // 负责实验员ID链
    LinkedList* equipments_list;        // 所属设备id链
} LabRoom;

LabRoom* CreateLabRoom(char* name);

void DestoryLabRoom(LabRoom* lab_room);

void AddLabRoom();

LabRoom* RoomId_to_LabRoom(int room_id);

#endif // !LAB_ROOM_H
