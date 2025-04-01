#pragma once
#ifndef LAB_ROOM_H
#define LAB_ROOM_H

#include "configs.h"
#include "linked_list.h"
#include "experimental_equipment.h"
#include "account.h"

typedef struct _LabRoom {
    int id;                            // 房间编号
    char name[LABROOM_LENGTH];         // 房间名称
    LinkedList* technician_id_list;     // 负责实验员ID链
    LinkedList* equipments_list;        // 所属设备id链
} LabRoom;

LabRoom* CreateLabRoom(char* name);

void DestoryLabRoom(LabRoom* lab_room);

void AddLabRoom();

bool ChangeLabRoom();
bool DeleteLabRoom(int room_id);
bool ChangeLabName(LabRoom* lab_room, char* newname);
bool AddEquipment(LabRoom* lab_room, int eqid);
bool DeleteEquipment(LabRoom* lab_room, int eqid);
bool DeleteTechnician(LabRoom* lab_room, int techid);
bool AddTechnician(LabRoom* lab_room, int techid);
LabRoom* RoomId_to_LabRoom(int room_id);

#endif // !LAB_ROOM_H
