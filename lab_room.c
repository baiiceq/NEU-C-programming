#include "lab_room.h"

LabRoom* CreateLabRoom(char* name)
{
    LabRoom* new_labroom = (LabRoom*)malloc(sizeof(LabRoom));

    if (new_labroom == NULL)
    {
        printf("����ʵ����ʧ��\n");
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

void AddLabRoom()
{
    char name[LABROOM_LENGTH];
    system("cls");
    printf("---          �����ʵ����          ---\n\n");
    printf("--- ������������->   ");
    scanf_s("%s", name, LABROOM_LENGTH);

    LabRoom* new_labroom= CreateLabRoom(name);
    if (new_labroom == NULL)
        return;

    LinkedList_pushback(GetResourceManage()->laboratory_list, new_labroom);

    printf("�����ɹ���\nʵ����id: %d\nʵ��������: %s\n", new_labroom->id, name);
    system("pause");
}

LabRoom* RoomId_to_LabRoom(int room_id)
{
    Node* temp = GetResourceManage()->laboratory_list->head;

    while (temp->next)
    {
        temp = temp->next;
        LabRoom* labroom = (LabRoom*)temp->data;
        if (room_id == labroom->id)
            return labroom;
    }
    return NULL;
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
	printf("��ɾ�����豸������\n");
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
