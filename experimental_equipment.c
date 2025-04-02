#include "experimental_equipment.h"
#include "lab_room.h"


ExperimentalEquipment* CreateExperimentalEquipment(Category* category, char* name, int room_id, 
    int price, char* purchase_date,EquipmentState state,int service_time)
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
    ee->state = state;
	ee->service_times = service_time;
    return ee;

}

void DestoryExperimentalEquipment(ExperimentalEquipment* experimental_equipment)
{
    free(experimental_equipment);
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
		printf("输入设备状态(0:正在使用 1:空闲 2:遗失 3:损坏4:报废5:正在维修)->");
		int state;
		scanf_s("%d", &state);
        getchar();
		EquipmentState state1;
        switch (state)
        {
        case 0:
            state1 = Using;
            break;
        case 1:
            state1 = Idle;
            break;
        case 2:
            state1 = Lost;
            break;
        case 3:
            state1 = Damaged;
            break;
        case 4:
            state1 = Scrapped;
            break;
        case 5:
            state1 = Repairing;
            break;
        default:
            printf("非法指令\n");
            system("pause");
            return;
        }
        int service_times;
        scanf_s("%d", &service_times);
        Category* category = LinkedList_at(rm->category_list, select);
        ExperimentalEquipment* new_ee = CreateExperimentalEquipment(category, name, room_id, price, purchase_date,state1,service_times);
        if (new_ee == NULL)
            return;

        LinkedList_pushback(rm->equipment_list, new_ee);
        LinkedList_pushback(labroom->equipments_list, &(new_ee->id));

        printf("创建成功！\n设备id: %d\n设备名称: %s\n设备价格: %d 元\n设备购买时间: %s", 
            new_ee->id, name, price, purchase_date);
        system("pause");

    }
}

void DeleteExperimentalEquipment(ExperimentalEquipment* ee)
{
	// 如果设备在实验室中，从实验室中移除
    if (ee->room_id != -1) {
        LabRoom* lab = RoomId_to_LabRoom(ee->room_id);
        if (lab != NULL) {
            DeleteEquipment(lab, ee->id);
            printf("已从实验室 %s (ID: %d) 中移除设备\n", lab->name, lab->id);
        }
    }
	Node* temp = GetResourceManage()->equipment_list->head;
	while (temp->next)
	{
		ExperimentalEquipment* equipment = (ExperimentalEquipment*)temp->next->data;
		if (equipment->id == ee->id)
		{
			Node* temp2 = temp->next;
			temp->next = temp->next->next;
			free(temp2);
			DestoryExperimentalEquipment(ee);
			printf("删除成功\n");
			return;
		}
		temp = temp->next;
	}
}

void ChangeExperimentalEquipment()
{
    int equipment_id;
    printf("请输入要修改的设备ID：\n");
    scanf_s("%d", &equipment_id);
    getchar(); // 清除缓冲区

    ExperimentalEquipment* equipment = (ExperimentalEquipment*)EFindById
    (GetResourceManage()->equipment_list, equipment_id)->head->next->data;
    if (equipment == NULL)
    {
        printf("该设备不存在\n");
        return;
    }

    while (1)
    {
        system("cls");
        printf("---            设备信息修改菜单         ---\n");
        printf("当前设备信息：\n");
        printf("ID: %d\n", equipment->id);
        printf("名称: %s\n", equipment->name);
        printf("价格: %d\n", equipment->price);
        printf("所属实验室ID: %d\n", equipment->room_id);
        printf("购买日期: %s\n", equipment->purchase_date);
        printf("类别: %s\n", equipment->category->name);
        switch (equipment->state)
        {
        case Using:
            printf("状态: 正在使用\n");
            break;
        case Idle:
            printf("状态: 空闲\n");
            break;
        case Lost:
            printf("状态: 遗失\n");
            break;
        case Damaged:
            printf("状态: 损坏\n");
            break;
        case Scrapped:
            printf("状态: 报废\n");
            break;
        case Repairing:
            printf("状态: 正在维修\n");
            break;
        }
        printf("\n");
        printf("---            1. 修改名称               ---\n");
        printf("---            2. 修改价格               ---\n");
        printf("---            3. 修改所属实验室         ---\n");
        printf("---            4. 修改购买日期           ---\n");
        printf("---            5. 修改设备类别           ---\n");
		printf("---            6. 修改设备状态           ---\n");
        printf("---            0. 退出                   ---\n");
        printf("--- 选择->");

        int option = 0;
        scanf_s("%d", &option);
        getchar(); 

        bool result = False;
        switch (option)
        {
        case 1:
        {
            printf("请输入新的设备名称（直接回车跳过修改）：\n");
            char new_name[EQUIPMENT_LENGTH] = "";
            fgets(new_name, EQUIPMENT_LENGTH, stdin);
            result = ChangeName(equipment, new_name);
            break;
        }
        case 2:
        {
            printf("请输入新的设备价格（直接回车跳过修改）：\n");
			int new_price = 0;
			scanf_s("%d", &new_price);
            getchar();
            result = ChangePrice(equipment, new_price);
            break;
        }
        case 3:
        {
            printf("请输入新的所属实验室ID（直接回车跳过修改）：\n");
            char new_room_id[10] = "";
            fgets(new_room_id, 10, stdin);
            result = ChangeRoom_id(equipment, new_room_id);
            break;
        }
        case 4:
        {
            printf("请输入新的购买日期（YYYY-MM-DD，直接回车跳过修改）：\n");
            char new_date[DATE_LENGTH] = "";
            fgets(new_date, DATE_LENGTH, stdin);
            result = ChangePurchaseDate(equipment, new_date);
            break;
        }
        case 5:
        {
            printf("请选择新的设备类别（直接回车跳过修改）：\n");
            ResourceManager* rm = GetResourceManage();
            size_t category_count = rm->category_list->size;
            Node* temp = rm->category_list->head;
            for (size_t i = 0; i < category_count; i++)
            {
                temp = temp->next;
                Category* category = (Category*)temp->data;
                printf("--- No%d. %s\n", (int)i + 1, category->name);
            }
            printf("--- 选择->");
            int select = 0;
            char input[10] = "";
            fgets(input, 10, stdin);
            if (strcmp(input, "\n") == 0)
            {
                result = True; // 跳过修改
            }
            else
            {
                select = atoi(input);
                if (select > category_count)
                {
                    printf("非法指令\n");
                    result = False;
                }
                else
                {
                    Category* new_category = LinkedList_at(rm->category_list, select-1);
                    result = ChangeExperimentalCategory(equipment, new_category);
                }
            }
            break;
        }
        case 6:
		{
			printf("请选择新的设备状态（0:正在使用 1:空闲 2:遗失 3:损坏4:报废5:正在维修）：\n");
			int new_state = 0;
			scanf_s("%d", &new_state);
			getchar();
			result = ChangeState(equipment, new_state);
			break;
		}
        case 0:
            return; // 直接返回，无需返回值
        default:
            printf("无效的选择\n");
            result = False;
            break;
        }

        if (result)
        {
            printf("操作完成\n");
        }
        else
        {
            printf("操作失败\n");
        }

        system("pause");
    }
}


bool ChangeName(ExperimentalEquipment* eq, char* newname)
{
    if (strcmp(newname, "\n") == 0)
    {
        return True;
    }
    newname[strcspn(newname, "\n")] = '\0';
    strcpy_s(eq->name, EQUIPMENT_LENGTH,newname);
    return True;
}

bool ChangePrice(ExperimentalEquipment* eq, int newprice)
{
    if (newprice == 0)
    {
        return True;
    }
    eq->price = newprice;
    return True;
}

bool ChangeRoom_id(ExperimentalEquipment* eq, char* newroomid)
{
    if (strcmp(newroomid, "\n") == 0)
    {
        return True; 
    }
	newroomid[strcspn(newroomid, "\n")] = '\0'; 
	LabRoom* lab_room = RoomId_to_LabRoom(atoi(newroomid));
	AddEquipment(lab_room, eq->id);
	return True;
}

bool ChangePurchaseDate(ExperimentalEquipment* eq, char* newdate)
{
    if (strcmp(newdate, "\n") == 0)
        return True; // 跳过修改
    newdate[strcspn(newdate, "\n")] = '\0';
    strcpy_s(eq->purchase_date, DATE_LENGTH, newdate);
    return True;
}

bool ChangeExperimentalCategory(ExperimentalEquipment* eq, Category* newcategory)
{
    if (newcategory == NULL)
        return True; // 跳过修改

    eq->category = newcategory;
    return True;
}

bool ChangeState(ExperimentalEquipment* eq, EquipmentState newstate)
{
	if (newstate < 0 || newstate>5)
	{
		printf("状态非法\n");
		return False;
	}
	eq->state = newstate;
	return True;
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
            LinkedList_pushback(list, eq);
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
			LinkedList_pushback(list, eq);
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
			LinkedList_pushback(list, eq);
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
			LinkedList_pushback(list, eq);
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
			LinkedList_pushback(list,eq);
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
			LinkedList_pushback(list, eq);
		temp = temp->next;
	}
    //为合理利用内存，适时的销毁链表
    if (eqlist != GetResourceManage()->equipment_list)
    {
        destoryLinkedList(eqlist);
    }
	return list;
}