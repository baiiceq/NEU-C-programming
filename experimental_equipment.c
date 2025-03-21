#include "experimental_equipment.h"
#include "lab_room.h"

ExperimentalEquipment* CreateExperimentalEquipment(Category* category, char* name, int room_id, int price, char* purchase_date)
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

void AddExperimentalEquipment()
{
    system("cls");
    ResourceManager* rm = GetResourceManage();
    size_t category_count = rm->category_list->size;
    if (category_count == 0)
    {
        printf("当前无法添加设备\n");
        return;
    }
    printf("---      选择你要添加的类型        ---\n\n");

    Node* temp = rm->category_list->head;
    for (size_t i = 0; i < category_count; i++)
    {
        temp = temp->next;
        Category* category = (Category*)temp->data;
        printf("--- No%d. %s\n", (int)i + 1, category->name);
    }
    printf("--- 0. 取消\n");
    printf("--- 选择->");
    int select = 0;
    scanf_s("%d", &select);

    if (select == 0)
    {
        return;
    }
    else if (select > category_count)
    {
        printf("非法指令\n");
        system("pause");
        return;
    }
    else
    {
        char name[EQUIPMENT_LENGTH];
        int room_id;
        int price;
        char purchase_date[DATE_LENGTH];

        printf("--- 输入设备名称->   ");
        scanf_s("%s", name, EQUIPMENT_LENGTH);

        printf("--- 输入所属实验室id->  ");
        scanf_s("%d", &room_id);
        LabRoom* labroom = RoomId_to_LabRoom(room_id);
        if (labroom == NULL)
        {
            printf("该实验室不存在\n");
            system("pause");
            return;
        }

        printf("--- 输入设备价格->  ");
        scanf_s("%d", &price);

        printf("--- 输入购买时间（yyyymmdd）->  ");
        scanf_s("%s", purchase_date, DATE_LENGTH);
        Category* category = LinkedList_at(rm->category_list, select - 1);
        ExperimentalEquipment* new_ee = CreateExperimentalEquipment(category, name, room_id, price, purchase_date);
        if (new_ee == NULL)
            return;

        LinkedList_pushback(rm->equipment_list, new_ee);
        LinkedList_pushback(labroom->equipments_list, new_ee->id);

        printf("创建成功！\n设备id: %d\n设备名称: %s\n设备价格: %d 元\n设备购买时间: %d", new_ee->id, name, price, purchase_date);
        system("pause");

    }
}

bool ChangeName(ExperimentalEquipment* eq, char* newname)
{
    strcpy_s(eq->name, EQUIPMENT_LENGTH,newname);
    return True;
}

bool ChangePrice(ExperimentalEquipment* eq, char* newprice)
{
    eq->price = atoi(newprice);
    return True;
}

bool ChangeRoom_id(ExperimentalEquipment* eq, char* newroomid)
{
	//先在对应实验室的设备链表中删除该设备
	LabRoom* lab_room1= RoomId_to_LabRoom(eq->room_id);
	DeleteEquipment(lab_room1, eq->id);

	eq->room_id = atoi(newroomid);

	//再在新的实验室的设备链表中添加该设备
	LabRoom* lab_room2 = RoomId_to_LabRoom(eq->room_id);
	AddEquipment(lab_room2, eq->id);
	return True;
}

bool FindExperimentalEquipment()
{
	LinkedList* eqlist = GetResourceManage()->equipment_list;
	printf("请按顺序输入查找条件，不需要的条件请回车跳过\n");
	printf("设备名称：\n");
	char name[EQUIPMENT_LENGTH];
	fgets(name, EQUIPMENT_LENGTH, stdin);
    eqlist = EFindByName(eqlist, name);
	printf("设备ID：\n");
	int id=0;
	scanf_s("%d", &id);
    getchar();
	eqlist = EFindById(eqlist, id);
	printf("实验室ID：\n");
    id = 0;
	scanf_s("%d", &id);
	getchar();
	eqlist = EFindByRoom_id(eqlist, id);
	printf("设备类别ID：\n");
	id = 0;
	scanf_s("%d", &id);
	getchar();
	eqlist = EFindByCategory(eqlist, id);
	printf("购买起始时间:格式xxxx-xx-xx\n");
	char start[DATE_LENGTH];
	char end[DATE_LENGTH];
	fgets(start, DATE_LENGTH, stdin);
	printf("购买结束时间:格式xxxx-xx-xx\n");
	fgets(end, DATE_LENGTH, stdin);
	eqlist = EFindByDate(eqlist, start, end);
	printf("价格区间：\n");
	int min = 0;
	int max = 0;
	scanf_s("%d %d", &min, &max);
	getchar();
	eqlist = EFindByPrice(eqlist, min, max);
	if (eqlist->head->next == NULL)
	{
		printf("未找到符合条件的设备\n");
		system("pause");
		return False;
	}
	else
	{
		printf("找到的设备如下：\n");
		Node* temp = eqlist->head->next;
		while (temp)
		{
			ExperimentalEquipment* eq = (ExperimentalEquipment*)temp->data;
			printf("设备ID：%d\n设备名称：%s\n设备价格：%d\n设备购买时间：%s\n", eq->id, eq->name, eq->price, eq->purchase_date);
			temp = temp->next;
		}
		system("pause");   //等待后期整合
		return True;
	}
}

//E表示equipment的查找
LinkedList* EFindByName(LinkedList* eqlist,char* name)
{
	if (name == "\n")
	{
		return eqlist;
	}
    LinkedList* list = CreateLinkedList();
    Node* temp = eqlist->head->next;
    while (temp)
    {
        ExperimentalEquipment* eq = (ExperimentalEquipment*)temp->data;
        if (strcmp(eq->name, name))
            LinkedList_pushback(list, temp);
        temp = temp-> next;
    }
	//为合理利用内存，适时的销毁链表
    if (eqlist != GetResourceManage()->equipment_list)
    {
		destoryLinkedList(eqlist);
    }
    return list;
}

LinkedList* EFindById(LinkedList* eqlist, int id)
{
	if (id == 0)
	{
		return eqlist;
	}
	LinkedList* list = CreateLinkedList();
	Node* temp = eqlist->head->next;
	while (temp)
	{
		ExperimentalEquipment* eq = (ExperimentalEquipment*)temp->data;
		if (eq->id == id)
			LinkedList_pushback(list, temp);
		temp = temp->next;
	}
    //为合理利用内存，适时的销毁链表
    if (eqlist != GetResourceManage()->equipment_list)
    {
        destoryLinkedList(eqlist);
    }
	return list;
}

LinkedList* EFindByRoom_id(LinkedList* eqlist, int roomid)
{
    if (roomid == 0)
    {
        return eqlist;
    }
	LinkedList* list = CreateLinkedList();
	Node* temp = eqlist->head->next;
	while (temp)
	{
		ExperimentalEquipment* eq = (ExperimentalEquipment*)temp->data;
		if (eq->room_id == roomid)
			LinkedList_pushback(list, temp);
		temp = temp->next;
	}
    //为合理利用内存，适时的销毁链表
    if (eqlist != GetResourceManage()->equipment_list)
    {
        destoryLinkedList(eqlist);
    }
	return list;
}   

        
LinkedList* EFindByCategory(LinkedList* eqlist, int categoryid)
{
    if (categoryid == 0)
    {
        return eqlist;
    }
	LinkedList* list = CreateLinkedList();
	Node* temp = eqlist->head->next;
	while (temp)
	{
		ExperimentalEquipment* eq = (ExperimentalEquipment*)temp->data;
		if (eq->category->id == categoryid)
			LinkedList_pushback(list, temp);
		temp = temp->next;
	}
    //为合理利用内存，适时的销毁链表
    if (eqlist != GetResourceManage()->equipment_list)
    {
        destoryLinkedList(eqlist);
    }
	return list;
} 

LinkedList* EFindByDate(LinkedList* eqlist, char* start, char* end)
{
	if (!strcmp(start,"\n") && !strcmp(end,"\n"))
	{
		return eqlist;
	}
	if (!strcmp(start, "\n"))
	{
		strcpy_s(start,15, "0");
	}
    if (!strcmp(end, "\n"))
    {
        strcpy_s(end, 15,"9");
    }
	LinkedList* list = CreateLinkedList();
	Node* temp = eqlist->head->next;
	while (temp)
	{
		ExperimentalEquipment* eq = (ExperimentalEquipment*)temp->data;
		if (strcmp(eq->purchase_date, start) >= 0 && strcmp(eq->purchase_date, end) <= 0)
			LinkedList_pushback(list, temp);
		temp = temp->next;
	}
    //为合理利用内存，适时的销毁链表
    if (eqlist != GetResourceManage()->equipment_list)
    {
        destoryLinkedList(eqlist);
    }
	return list;
}

LinkedList* EFindByPrice(LinkedList* eqlist, int min, int max)
{
	if (min == 0 && max == 0)
	{
		return eqlist;
	}
    if(max==0)
	{
		max = 999999999;
	}
	LinkedList* list = CreateLinkedList();
	Node* temp = eqlist->head->next;
	while (temp)
	{
		ExperimentalEquipment* eq = (ExperimentalEquipment*)temp->data;
		if (eq->price >= min && eq->price <= max)
			LinkedList_pushback(list, temp);
		temp = temp->next;
	}
    //为合理利用内存，适时的销毁链表
    if (eqlist != GetResourceManage()->equipment_list)
    {
        destoryLinkedList(eqlist);
    }
	return list;
}