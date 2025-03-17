#pragma once
#ifndef LAB_ROOM_H
#define LAB_ROOM_H

#include "configs.h"
#include "linked_list.h"
#include "experimental_equipment.h"

typedef struct _LabRoom {
    int id;                            // ������
    char name[LABROOM_LENGTH];         // ��������
    LinkedList* technician_id_list;     // ����ʵ��ԱID��
    LinkedList* equipments_list;        // �����豸id��
} LabRoom;

LabRoom* CreateLabRoom(char* name);

void DestoryLabRoom(LabRoom* lab_room);

void AddLabRoom();

LabRoom* RoomId_to_LabRoom(int room_id);

bool ChangeLabName(LabRoom* lab_room, char* newname);
bool AddEquipment(LabRoom* lab_room, int eqid);
bool DeleteEquipment(LabRoom* lab_room, int eqid);
LabRoom* SeekByRoom_id(LinkedList* list, int id);
#endif // !LAB_ROOM_H
