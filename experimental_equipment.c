#include "experimental_equipment.h"
#include "lab_room.h"

ExperimentalEquipment* CreateExperimentalEquipment(Category category, char* name, int room_id, int price, char* purchase_date)
{
    ExperimentalEquipment* ee = (ExperimentalEquipment*)malloc(sizeof(ExperimentalEquipment));

    if (ee == NULL)
    {
        printf("创建设备失败\n");
        return NULL;
    }

    ee->id = GetNewId(EquipmentID);
    ee->category = category;
    strcpy_s(ee->name, EQUIPMENT_LENGTH, name);
    ee->price = price;
    ee->room_id = room_id;
    strcpy_s(ee->purchase_date, DATE_LENGTH, purchase_date);

    return ee;

}

void DestoryExperimentalEquipment(ExperimentalEquipment* experimental_equipment)
{

}

bool ChangeName(ExperimentalEquipment* eq, char* newname)
{
    strcpy_s(eq->name, EQUIPMENT_LENGTH,newname);
    return True;
}

bool ChangePrice(ExperimentalEquipment* eq, char* newprice)
{
    eq->price = newprice;
    return True;
}

bool ChangeRoom_id(ExperimentalEquipment* eq, char* newroomid)
{
	//先在对应实验室的设备链表中删除该设备
	ResourceManager* resource_manager = GetResourceManage();
	LinkedList* list = resource_manager->laboratory_list;
	LabRoom* lab_room1=SeekByRoom_id(list, eq->room_id);
	DeleteEquipment(lab_room1, eq->id);

	eq->room_id = atoi(newroomid);

	//再在新的实验室的设备链表中添加该设备
	LabRoom* lab_room2 = SeekByRoom_id(list, eq->room_id);
	AddEquipment(lab_room2, eq->id);
	return True;
}

//E表示equipment的查找
LinkedList* EFindByName(LinkedList* eqlist,char* name)
{
    LinkedList* list = CreateLinkedList();
    Node* temp = eqlist->head->next;
    while (temp)
    {
        ExperimentalEquipment* eq = (ExperimentalEquipment*)temp->data;
        if (strcmp(eq->name, name))
            LinkedList_pushback(list, temp);
        temp = temp-> next;
    }
    return list;
}

LinkedList* EFindById(LinkedList* eqlist, int id)
{
	LinkedList* list = CreateLinkedList();
	Node* temp = eqlist->head->next;
	while (temp)
	{
		ExperimentalEquipment* eq = (ExperimentalEquipment*)temp->data;
		if (eq->id == id)
			LinkedList_pushback(list, temp);
		temp = temp->next;
	}
	return list;
}

LinkedList* EFindByRoom_id(LinkedList* eqlist, int roomid)
{
	LinkedList* list = CreateLinkedList();
	Node* temp = eqlist->head->next;
	while (temp)
	{
		ExperimentalEquipment* eq = (ExperimentalEquipment*)temp->data;
		if (eq->room_id == roomid)
			LinkedList_pushback(list, temp);
		temp = temp->next;
	}
	return list;
}   

LinkedList* EFindByCategory(LinkedList* eqlist, int categoryid)
{
	LinkedList* list = CreateLinkedList();
	Node* temp = eqlist->head->next;
	while (temp)
	{
		ExperimentalEquipment* eq = (ExperimentalEquipment*)temp->data;
		if (eq->category.id == categoryid)
			LinkedList_pushback(list, temp);
		temp = temp->next;
	}
	return list;
} 

LinkedList* EFindByDate(LinkedList* eqlist, char* start, char* end)
{
	LinkedList* list = CreateLinkedList();
	Node* temp = eqlist->head->next;
	while (temp)
	{
		ExperimentalEquipment* eq = (ExperimentalEquipment*)temp->data;
		if (strcmp(eq->purchase_date, start) >= 0 && strcmp(eq->purchase_date, end) <= 0)
			LinkedList_pushback(list, temp);
		temp = temp->next;
	}
	return list;
}

LinkedList* EFindByPrice(LinkedList* eqlist, int min, int max)
{
	LinkedList* list = CreateLinkedList();
	Node* temp = eqlist->head->next;
	while (temp)
	{
		ExperimentalEquipment* eq = (ExperimentalEquipment*)temp->data;
		if (eq->price >= min && eq->price <= max)
			LinkedList_pushback(list, temp);
		temp = temp->next;
	}
	return list;
}