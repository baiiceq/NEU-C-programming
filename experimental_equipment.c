#include "experimental_equipment.h"
#include "lab_room.h"

ExperimentalEquipment* CreateExperimentalEquipment(Category* category, char* name, int room_id, int price, char* purchase_date)
{
    ExperimentalEquipment* ee = (ExperimentalEquipment*)malloc(sizeof(ExperimentalEquipment));

    if (ee == NULL)
    {
        printf("�����豸ʧ��\n");
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

void AddExperimentalEquipment()
{
    system("cls");
    ResourceManager* rm = GetResourceManage();
    size_t category_count = rm->category_list->size;
    if (category_count == 0)
    {
        printf("��ǰ�޷�����豸\n");
        return; 
    }
    printf("---      ѡ����Ҫ��ӵ�����        ---\n\n");

    Node* temp = rm->category_list->head;
    for (size_t i = 0; i < category_count; i++)
    {
        temp = temp->next;
        Category* category = (Category*)temp->data;
        printf("--- No%d. %s\n", (int)i + 1, category->name);
    }
    printf("--- 0. ȡ��\n");
    printf("--- ѡ��->");
    int select = 0;
    scanf_s("%d", &select);

    if (select == 0)
    {
        return;
    }
    else if (select > category_count)
    {
        printf("�Ƿ�ָ��\n");
        system("pause");
        return;
    }
    else
    {
        char name[EQUIPMENT_LENGTH];
        int room_id;
        int price;
        char purchase_date[DATE_LENGTH];

        printf("--- �����豸����->   ");
        scanf_s("%s", name, EQUIPMENT_LENGTH);

        printf("--- ��������ʵ����id->  ");
        scanf_s("%d", &room_id);
        LabRoom* labroom = RoomId_to_LabRoom(room_id);
        if (labroom == NULL)
        {
            printf("��ʵ���Ҳ�����\n");
            system("pause");
            return;
        }

        printf("--- �����豸�۸�->  ");
        scanf_s("%d", &price);

        printf("--- ���빺��ʱ�䣨yyyymmdd��->  ");
        scanf_s("%s", purchase_date, DATE_LENGTH);

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
	//���ڶ�Ӧʵ���ҵ��豸������ɾ�����豸
	ResourceManager* resource_manager = GetResourceManage();
	LinkedList* list = resource_manager->laboratory_list;
	LabRoom* lab_room1=SeekByRoom_id(list, eq->room_id);
	DeleteEquipment(lab_room1, eq->id);

	eq->room_id = atoi(newroomid);

	//�����µ�ʵ���ҵ��豸��������Ӹ��豸
	LabRoom* lab_room2 = SeekByRoom_id(list, eq->room_id);
	AddEquipment(lab_room2, eq->id);
	return True;
}

//E��ʾequipment�Ĳ���
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

        Category* category = LinkedList_at(rm->category_list, select - 1);
        ExperimentalEquipment* new_ee = CreateExperimentalEquipment(category, name, room_id, price, purchase_date);
        if (new_ee == NULL)
            return;

        LinkedList_pushback(rm->equipment_list, new_ee);
        LinkedList_pushback(labroom->equipments_list, new_ee->id);

        printf("�����ɹ���\n�豸id: %d\n�豸����: %s\n�豸�۸�: %d Ԫ\n�豸����ʱ��: %s", new_ee->id, name, price,purchase_date);
        system("pause");

    }
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