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

void AddLabRoom()
{
    char name[LABROOM_LENGTH];
    system("cls");
    printf("---          添加新实验室          ---\n\n");
    printf("--- 输入类型名称->   ");
    scanf_s("%s", name, LABROOM_LENGTH);

    LabRoom* new_labroom= CreateLabRoom(name);
    if (new_labroom == NULL)
        return;

    LinkedList_pushback(GetResourceManage()->laboratory_list, new_labroom);

    printf("创建成功！\n实验室id: %d\n实验室名称: %s\n", new_labroom->id, name);
    system("pause");
}

bool DeleteLabRoom()
{
    printf("请输入要删除的实验室编号\n");
    int room_id;
    scanf_s("%d", &room_id);
	Node* temp = GetResourceManage()->laboratory_list->head;
	while (temp->next)
	{
		LabRoom* labroom = (LabRoom*)temp->next->data;
		if (room_id == labroom->id)
		{
            Node* temp2 = temp->next;
			temp->next = temp->next->next;
            free(temp2);
			printf("删除成功\n");
			system("pause");
            return True;
		}
		temp = temp->next;
	}
	printf("需删除的实验室不存在\n");
	return False;
}

bool ChangeLabRoom()
{
	printf("请输入要修改的实验室编号\n");
	int room_id;
	scanf_s("%d", &room_id);
	LabRoom* labroom = RoomId_to_LabRoom(room_id);
	if (labroom == NULL)
	{
		printf("该实验室不存在\n");
		return False;
	}
	while (1)
	{
		system("cls");

		printf("---            选择要进行的操作         ---\n");
		printf("---            1. 修改实验室名称               ---\n");
		printf("---            2. 在该实验室添加设备           ---\n");
		printf("---            3. 在该实验室删除设备           ---\n");
		printf("---            4. 在该实验室添加实验员         ---\n");
		printf("---            5. 在该实验室删除实验员         ---\n");
		printf("---            0. 取消               ---\n");
		printf("--- 选择->");

		int option = 0;
		scanf_s("%d", &option);
		getchar();
		switch (option)
		{
		case 1:
		{
			printf("请输入新的实验室名称(无需更改可回车跳过)\n");
			char newname[LABROOM_LENGTH] = "";
			fgets(newname, LABROOM_LENGTH, stdin);
			ChangeLabName(labroom, newname);
			break;
		}
		case 2:
		{
			printf("请输入要在该实验室添加的设备id(无需更改可回车跳过)\n");
			int eqid = 0;
			scanf_s("%d", &eqid);
			getchar();
			AddEquipment(labroom, eqid);
			break;
		}
		case 3:
		{
			printf("请输入要在该实验室删除的设备id(无需更改可回车跳过)\n");
			int eqid = 0;
			scanf_s("%d", &eqid);
			getchar();
			DeleteEquipment(labroom, eqid);
			break;
		}
		case 4:
		{
			printf("请输入要在该实验室添加的实验员id(无需更改可回车跳过)\n");
			int techid = 0;
			scanf_s("%d", &techid);
			getchar();
			AddTechnician(labroom, techid);
			break;
		}
		case 5:
		{
			printf("请输入要在该实验室删除的实验员id(无需更改可回车跳过)\n");
			int techid = 0;
			scanf_s("%d", &techid);
			getchar();
			DeleteTechnician(labroom, techid);
			break;
		}
		case 0:
			return True;
		}
		system("pause");
	}
	
}

bool ChangeLabName(LabRoom* lab_room, char* newname)
{
	if (strcmp(newname, "\n") == 0)
	{		return False;
	}
	newname[strcspn(newname, "\n")] = '\0';
	strcpy_s(lab_room->name, LABROOM_LENGTH, newname);
	printf("修改成功\n");
	return True;
}

bool AddEquipment(LabRoom* lab_room, int eqid)
{
	if (eqid == 0)
		return False;
	LinkedList* temp=EFindById(GetResourceManage()->equipment_list, eqid);
	if (temp->head->next == NULL)
	{
		printf("该设备不存在\n");
		return False;
	}
	ExperimentalEquipment* eq = (ExperimentalEquipment*)temp->head->next->data;
	LinkedList_pushback(lab_room->equipments_list, &eq->id);
	if (eq->room_id != -1)
	{
		LabRoom* old_labroom = RoomId_to_LabRoom(eq->room_id);
		if (old_labroom != NULL)
		{
			DeleteEquipment(old_labroom, eqid);
		}
	}
	eq->room_id = lab_room->id;

	printf("添加设备成功\n");
	return True;
}

bool DeleteEquipment(LabRoom* lab_room, int eqid)
{
	if (eqid == 0)
		return False;
	Node* temp = lab_room->equipments_list->head;
	while (temp->next)
	{
		int* eq = (int*)temp->next->data;
		if (*eq == eqid)
		{
			ExperimentalEquipment* eq = (ExperimentalEquipment*)EFindById
			(GetResourceManage()->equipment_list, eqid)->head->next->data;
			eq->room_id = -1;
			temp->next = temp->next->next;
			return True;
		}
		temp = temp->next;
	}
	printf("需删除的设备不存在\n");
	return False;
}

bool AddTechnician(LabRoom* lab_room, int techid)
{
	if (techid == 0)
		return False;
	Account* tech = FindById(techid);
	if (tech == NULL)
	{
		printf("该实验员不存在\n");
		return False;
	}
	LinkedList_pushback(lab_room->technician_id_list, &tech->id);
	if (tech->roomid != -1)
	{
		LabRoom* old_labroom = RoomId_to_LabRoom(tech->roomid);
		if (old_labroom != NULL)
		{
			DeleteTechnician(old_labroom, techid);
		}
	}
	tech->roomid = lab_room->id;
	printf("添加实验员成功\n");
	return True;
}

bool DeleteTechnician(LabRoom* lab_room, int techid)
{
	if (techid == 0)
		return False;
	Node* temp = lab_room->technician_id_list->head;
	while (temp->next)
	{
		int* tech = (int*)temp->next->data;
		if (*tech == techid)
		{
			FindById(techid)->roomid = -1;
			temp->next = temp->next->next;
			return True;
		}
		temp = temp->next;
	}
	printf("需删除的实验员不存在\n");
	return False;
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

