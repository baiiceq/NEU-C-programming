#include "experimental_equipment.h"
#include "lab_room.h"


ExperimentalEquipment* CreateExperimentalEquipment(Category* category, char* name, int room_id, 
    int price, char* purchase_date,EquipmentState state,int service_time)
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
		printf("�����豸״̬(0:����ʹ�� 1:���� 2:��ʧ 3:��4:����5:����ά��)->");
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
            printf("�Ƿ�ָ��\n");
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

        printf("�����ɹ���\n�豸id: %d\n�豸����: %s\n�豸�۸�: %d Ԫ\n�豸����ʱ��: %s", 
            new_ee->id, name, price, purchase_date);
        system("pause");

    }
}

void DeleteExperimentalEquipment(ExperimentalEquipment* ee)
{
	// ����豸��ʵ�����У���ʵ�������Ƴ�
    if (ee->room_id != -1) {
        LabRoom* lab = RoomId_to_LabRoom(ee->room_id);
        if (lab != NULL) {
            DeleteEquipment(lab, ee->id);
            printf("�Ѵ�ʵ���� %s (ID: %d) ���Ƴ��豸\n", lab->name, lab->id);
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
			printf("ɾ���ɹ�\n");
			return;
		}
		temp = temp->next;
	}
}

void ChangeExperimentalEquipment()
{
    int equipment_id;
    printf("������Ҫ�޸ĵ��豸ID��\n");
    scanf_s("%d", &equipment_id);
    getchar(); // ���������

    ExperimentalEquipment* equipment = (ExperimentalEquipment*)EFindById
    (GetResourceManage()->equipment_list, equipment_id)->head->next->data;
    if (equipment == NULL)
    {
        printf("���豸������\n");
        return;
    }

    while (1)
    {
        system("cls");
        printf("---            �豸��Ϣ�޸Ĳ˵�         ---\n");
        printf("��ǰ�豸��Ϣ��\n");
        printf("ID: %d\n", equipment->id);
        printf("����: %s\n", equipment->name);
        printf("�۸�: %d\n", equipment->price);
        printf("����ʵ����ID: %d\n", equipment->room_id);
        printf("��������: %s\n", equipment->purchase_date);
        printf("���: %s\n", equipment->category->name);
        switch (equipment->state)
        {
        case Using:
            printf("״̬: ����ʹ��\n");
            break;
        case Idle:
            printf("״̬: ����\n");
            break;
        case Lost:
            printf("״̬: ��ʧ\n");
            break;
        case Damaged:
            printf("״̬: ��\n");
            break;
        case Scrapped:
            printf("״̬: ����\n");
            break;
        case Repairing:
            printf("״̬: ����ά��\n");
            break;
        }
        printf("\n");
        printf("---            1. �޸�����               ---\n");
        printf("---            2. �޸ļ۸�               ---\n");
        printf("---            3. �޸�����ʵ����         ---\n");
        printf("---            4. �޸Ĺ�������           ---\n");
        printf("---            5. �޸��豸���           ---\n");
		printf("---            6. �޸��豸״̬           ---\n");
        printf("---            0. �˳�                   ---\n");
        printf("--- ѡ��->");

        int option = 0;
        scanf_s("%d", &option);
        getchar(); 

        bool result = False;
        switch (option)
        {
        case 1:
        {
            printf("�������µ��豸���ƣ�ֱ�ӻس������޸ģ���\n");
            char new_name[EQUIPMENT_LENGTH] = "";
            fgets(new_name, EQUIPMENT_LENGTH, stdin);
            result = ChangeName(equipment, new_name);
            break;
        }
        case 2:
        {
            printf("�������µ��豸�۸�ֱ�ӻس������޸ģ���\n");
			int new_price = 0;
			scanf_s("%d", &new_price);
            getchar();
            result = ChangePrice(equipment, new_price);
            break;
        }
        case 3:
        {
            printf("�������µ�����ʵ����ID��ֱ�ӻس������޸ģ���\n");
            char new_room_id[10] = "";
            fgets(new_room_id, 10, stdin);
            result = ChangeRoom_id(equipment, new_room_id);
            break;
        }
        case 4:
        {
            printf("�������µĹ������ڣ�YYYY-MM-DD��ֱ�ӻس������޸ģ���\n");
            char new_date[DATE_LENGTH] = "";
            fgets(new_date, DATE_LENGTH, stdin);
            result = ChangePurchaseDate(equipment, new_date);
            break;
        }
        case 5:
        {
            printf("��ѡ���µ��豸���ֱ�ӻس������޸ģ���\n");
            ResourceManager* rm = GetResourceManage();
            size_t category_count = rm->category_list->size;
            Node* temp = rm->category_list->head;
            for (size_t i = 0; i < category_count; i++)
            {
                temp = temp->next;
                Category* category = (Category*)temp->data;
                printf("--- No%d. %s\n", (int)i + 1, category->name);
            }
            printf("--- ѡ��->");
            int select = 0;
            char input[10] = "";
            fgets(input, 10, stdin);
            if (strcmp(input, "\n") == 0)
            {
                result = True; // �����޸�
            }
            else
            {
                select = atoi(input);
                if (select > category_count)
                {
                    printf("�Ƿ�ָ��\n");
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
			printf("��ѡ���µ��豸״̬��0:����ʹ�� 1:���� 2:��ʧ 3:��4:����5:����ά�ޣ���\n");
			int new_state = 0;
			scanf_s("%d", &new_state);
			getchar();
			result = ChangeState(equipment, new_state);
			break;
		}
        case 0:
            return; // ֱ�ӷ��أ����践��ֵ
        default:
            printf("��Ч��ѡ��\n");
            result = False;
            break;
        }

        if (result)
        {
            printf("�������\n");
        }
        else
        {
            printf("����ʧ��\n");
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
        return True; // �����޸�
    newdate[strcspn(newdate, "\n")] = '\0';
    strcpy_s(eq->purchase_date, DATE_LENGTH, newdate);
    return True;
}

bool ChangeExperimentalCategory(ExperimentalEquipment* eq, Category* newcategory)
{
    if (newcategory == NULL)
        return True; // �����޸�

    eq->category = newcategory;
    return True;
}

bool ChangeState(ExperimentalEquipment* eq, EquipmentState newstate)
{
	if (newstate < 0 || newstate>5)
	{
		printf("״̬�Ƿ�\n");
		return False;
	}
	eq->state = newstate;
	return True;
}

//E��ʾequipment�Ĳ���
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
	//Ϊ���������ڴ棬��ʱ����������
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
    //Ϊ���������ڴ棬��ʱ����������
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
    //Ϊ���������ڴ棬��ʱ����������
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
    //Ϊ���������ڴ棬��ʱ����������
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
    //Ϊ���������ڴ棬��ʱ����������
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
    //Ϊ���������ڴ棬��ʱ����������
    if (eqlist != GetResourceManage()->equipment_list)
    {
        destoryLinkedList(eqlist);
    }
	return list;
}