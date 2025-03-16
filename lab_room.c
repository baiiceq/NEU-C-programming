#include "lab_room.h"

LabRoom* CreateLabRoom(char* name)
{
    LabRoom* new_labroom = (LabRoom*)malloc(sizeof(LabRoom));

    if (new_labroom == NULL)
    {
        printf("创建实验室失败\n");
        return NULL;
    }

    strcpy_s(new_labroom->name, LABROOM_LENGTH, name);
    new_labroom->id = GetNewId(RoomID);
    new_labroom->equipments_list = CreateLinkedList();
    new_labroom->technician_id_list = CreateLinkedList();

    return new_labroom;
}

void DestoryLabRoom(LabRoom* lab_room)
{
}

bool ChangeLabName(LabRoom* lab_room, char* newname)
{
	strcpy_s(lab_room->name, LABROOM_LENGTH, newname);
	return True;
}

bool AddEquipment(LabRoom* lab_room, int eqid)
{
	ExperimentalEquipment* eq=EFindById(GetResourceManage()->equipment_list, eqid);
	LinkedList_pushback(lab_room->equipments_list, eq);
	return True;
}

bool DeleteEquipment(LabRoom* lab_room, int eqid)
{
	Node* temp = lab_room->equipments_list->head;
	while (temp->next)
	{
		ExperimentalEquipment* eq = (ExperimentalEquipment*)temp->next->data;
		if (eq->id == eqid)
		{
			temp->next = temp->next->next;
			return True;
		}
	}
	printf("需删除的设备不存在\n");
	return False;
}

LabRoom* SeekByRoom_id(LinkedList* list, int id)
{
	Node* temp = list->head->next;
	while (temp)
	{
		LabRoom* room = (LabRoom*)temp->data;
		if (room->id == id)
			return room;
		temp = temp->next;
	}
	return NULL;
}
