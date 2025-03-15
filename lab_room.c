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
