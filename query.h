#pragma once
#include "experimental_equipment.h"
#include "category.h"
#include "lab_room.h"
#include "account.h"
#include "configs.h"
#include "service.h"

typedef bool (*QueryCondition)(void* data, void* param);

void Query(LinkedList* list, QueryCondition condition, void* param, void (*PrintResult)(void*))
{
    if (list == NULL || condition == NULL || PrintResult == NULL) {
        printf("��ѯʧ��: ������Ч��\n");
        return;
    }

    Node* node = list->head;
    bool found = False;
    while (node->next != NULL)
    {
        node = node->next;
        if (condition(node->data, param))
        {
            PrintResult(node->data);
            found = True;
        }
        
    }

    system("pause");

    if (!found) 
    {
        printf("δ�ҵ����������ļ�¼��\n\n");
        system("pause");
    }
}

// ά�޼�¼��ѯ�����ṹ
typedef struct _ServiceQuery
{
    int equipment_id;           // �豸ID
    int user_id;                // �û�ID
    Service_type type;          // ��������
    char time[DATE_LENGTH];     // ʱ��
} ServiceQuery;

// ά�޼�¼��ѯ��������
bool QueryServiceCondition(void* data, void* param)
{
    Service* service = (Service*)data;
    ServiceQuery* query = (ServiceQuery*)param;

    if (query->equipment_id != -1 && service->equipment_id != query->equipment_id)
        return False;

    if (query->user_id != -1 && service->user_id != query->user_id)
        return False;

    if (query->type != -1 && service->type != query->type)
        return False;

    if (strlen(query->time) > 0 && strcmp(service->data, query->time) != 0)
        return False;

    return True;  // ��������������
}

// ��ӡά�޼�¼
void PrintService(void* data)
{
    Service* service = (Service*)data;
	char str[20];
    switch (service->type)
    {
	case LostRegister:
		strcpy_s(str, 20, "��ʧ�Ǽ�");
		break;
	case DamagedRegister:
		strcpy_s(str, 20, "�𻵵Ǽ�");
		break;
	case ServiceRegister:
		strcpy_s(str, 20, "ά�޵Ǽ�");
		break;
	case ServiceFinish:
		strcpy_s(str, 20, "ά�����");
		break;
	case ScrapRegister:
		strcpy_s(str, 20, "����");
        break;
    }
    printf("�豸ID: %d, �豸����: %s, �û�ID: %d, ʱ��: %s, ����: %s, ԭ��/��ע: %s\n",
        service->equipment_id, service->equipment_name, service->user_id, service->data,
        str, service->reason);
}

// ��ѯά�޼�¼�˵�
void QueryServiceMenu()
{
    int equipment_id = -1;           // �豸ID
    int user_id = -1;                // �û�ID
    Service_type type = -1;          // ��������
    char time[DATE_LENGTH] = "";     // ʱ��

    system("cls");
    printf("---          ��ѯά�޼�¼          ---\n\n");

    // ѯ���豸ID����ѡ��
    printf("--- �����豸ID�����س�������-> ");
    char input[20];
    fgets(input, 20, stdin);
    if (strlen(input) > 1)
    {
        equipment_id = atoi(input);
    }
    fflush(stdin);
    system("cls");

    // ѯ���û�ID����ѡ��
    printf("--- �����û�ID�����س�������-> ");
    fgets(input, 20, stdin);
    if (strlen(input) > 1)
    {
        user_id = atoi(input);
    }
    fflush(stdin);
    system("cls");

    // ѯ�ʷ������ͣ���ѡ��
    printf("--- 1.LostRegister\n");
    printf("--- 2.DamagedRegister\n");
	printf("--- 3.ServiceRegister\n");
	printf("--- 4.ServiceFinish\n");
	printf("--- 5.ScrapRegister\n");
    printf("--- ����������ͣ����س�������-> ");
    fgets(input, 20, stdin);
    if (strlen(input) > 1)
    {
        int temp = atoi(input);
        if (temp >= 4 || temp <= 0)
        {
            printf("�Ƿ�ָ��\n");
            system("pause");
            return;
        }
        type = (Service_type)(temp - 1);
    }
    fflush(stdin);
    system("cls");

    // ѯ��ʱ�䣨��ѡ��
    printf("--- ����ʱ�䣨���س�������-> ");
    fgets(time, DATE_LENGTH, stdin);
    time[strcspn(time, "\n")] = 0; // ȥ�����з�
    fflush(stdin);
    system("cls");

    LinkedList* list = GetResourceManage()->service_list;    // ��ȡά�޼�¼�б�
    ServiceQuery query;

    query.equipment_id = equipment_id;
    query.user_id = user_id;
    query.type = type;
    strcpy_s(query.time, DATE_LENGTH, time);

    Query(list, QueryServiceCondition, &query, PrintService);
}



typedef struct _EquipmentQuery
{
    int id;                            // ID
    int category_id;                   // ���
    char purchase_date[DATE_LENGTH];   // ��������
    int min_price;                     // ��С�۸�
    int max_price;                     // ���۸�
    char name[EQUIPMENT_LENGTH];       // ����
    int room_id;                       // ��������
    EquipmentState state;              //�豸״̬
} EquipmentQuery;

bool QueryEquipmenCondition(void* data, void* param)
{
    ExperimentalEquipment* eq = (ExperimentalEquipment*)data;
    EquipmentQuery* query = (EquipmentQuery*)param;

    // �ж������� query->category ���ǿգ���ƥ�䣩
    if (query->category_id != -1 && eq->category->id != query->category_id)
        return False;

    if (query->id != -1 && query->id != eq->id)
        return False;

    // �жϹ�������
    if (strlen(query->purchase_date) > 0 && strcmp(eq->purchase_date, query->purchase_date) != 0)
        return False;

    // �жϼ۸�Χ
    if ((query->min_price >= 0 && eq->price < query->min_price) ||
        (query->max_price >= 0 && eq->price > query->max_price))
        return False;

    // �ж��豸���ƣ�ģ��ƥ�䣩
    if (strlen(query->name) > 0 && strstr(eq->name, query->name) == NULL)
        return False;

    // �ж���������
    if (query->room_id != -1 && eq->room_id != query->room_id)
        return False;
    //�ж��豸״̬
    if (query->state!=-1&&eq->state != query->state)
        return False;

    return True;  // ��������������
}

void PrintEquipment(void* data)
{
    ExperimentalEquipment* eq = (ExperimentalEquipment*)data;
    char str[20];
    switch (eq->state)
    {
    case Using:
        strcpy_s(str, 20, "Using");
        break;
    case Idle:
        strcpy_s(str, 20, "Idle");
        break;
    case Lost:
        strcpy_s(str, 20, "Lost");
        break;
    case Damaged:
        strcpy_s(str, 20, "Damaged");
        break;
    case Scrapped:
        strcpy_s(str, 20, "Scrapped");
        break;
    case Repairing:
        strcpy_s(str, 20, "Repairing");
        break;
    }
    printf("ID: %d, ����: %s, ���: %s, �۸�: %d, ���������: %d���豸״̬:%s\n",
        eq->id, eq->name, eq->category->name, eq->price, eq->room_id,str);
}

void QueryEquipmentMenu()
{
    char name[EQUIPMENT_LENGTH] = "";    // �豸����
    int category_id = -1;                // �豸���ID��-1 ����ɸѡ
    int room_id = -1;                    // �豸����ʵ����ID��-1 ����ɸѡ
    double min_price = -1;               // �豸��ͼ۸�-1 ����ɸѡ
    double max_price = -1;               // �豸��߼۸�-1 ����ɸѡ
    char date[DATE_LENGTH] = "";         // �豸�������� 
    int id = -1;                         // �豸id
    EquipmentState state=-1;                //�豸״̬
    system("cls");
    printf("---          ��ѯʵ���豸��Ϣ          ---\n\n");

    // ѯ���豸���ƣ���ѡ��
    printf("--- �����豸���ƣ����س�������-> ");
    while (getchar() != '\n');
    fgets(name, EQUIPMENT_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // ȥ�����з�'
    fflush(stdin);
    system("cls");

    // ѯ���豸 ID����ѡ��
    printf("--- �����豸 ID�����س�������-> ");
    char input[20];
    fgets(input, 20, stdin);
    if (strlen(input) > 1)
    {
        id = atoi(input);
    }
    fflush(stdin);
    system("cls");

    // ѯ����� ID����ѡ��
    printf("--- �����豸��� ID�����س�������-> ");
    fgets(input, 20, stdin);
    if (strlen(input) > 1) 
    {
        category_id = atoi(input);
    }
    fflush(stdin);
    system("cls");

    // ѯ���豸����ʱ�䣨��ѡ��
    printf("--- �����豸����ʱ�䣨���س�������-> ");
    fgets(date, DATE_LENGTH, stdin);
    date[strcspn(date, "\n")] = 0; // ȥ�����з�
    fflush(stdin);
    system("cls");

    // ѯ��ʵ���� ID����ѡ��
    printf("--- ����ʵ���� ID�����س�������-> ");
    fgets(input, 20, stdin);
    if (strlen(input) > 1) 
    {
        room_id = atoi(input);
    }
    fflush(stdin);
    system("cls");

    // ѯ�ʼ۸����䣨��ѡ��
    printf("--- ������ͼ۸񣨰��س�������-> ");
    fgets(input, 20, stdin);
    if (strlen(input) > 1) 
    {
        min_price = atof(input);
    }

    printf("--- ������߼۸񣨰��س�������-> ");
    fgets(input, 20, stdin);
    if (strlen(input) > 1) 
    {
        max_price = atof(input);
    }
	fflush(stdin);
	system("cls");

    //ѯ���豸״̬
	printf("--- 1.Using\n");
	printf("--- 2.Idle\n");
	printf("--- 3.Lost\n");
	printf("--- 4.Damaged\n");
	printf("--- 5.Scrapped\n");
	printf("--- 6.Repairing\n");
	printf("--- �����豸״̬�����س�������-> ");
	fgets(input, 20, stdin);
    if (strlen(input) > 1)
    {
        int temp = atoi(input);
        if (temp >= 7 || temp <= 0)
        {
            printf("�Ƿ�ָ��\n");
            system("pause");
            return;
        }
        state = (EquipmentState)(temp - 1);
    }
	fflush(stdin);
	system("cls");

    LinkedList* list = GetResourceManage()->equipment_list;
    EquipmentQuery query;

    strcpy_s(query.name, EQUIPMENT_LENGTH, name);
    query.category_id = category_id;
    query.room_id = room_id;
    query.min_price = min_price;
    query.max_price = max_price;
    query.id = id;
	query.state = state;
    strcpy_s(query.purchase_date, DATE_LENGTH, date);
    
    Query(list, QueryEquipmenCondition, &query, PrintEquipment);
}

typedef struct _AccountQuery
{
    AccountType account_type;            // �˻����
    char user_name[USER_NMAE_LENGTH];    // �˻�����
    int id;                              //�˻�ID
    int room_id;                          //����ʵ����id
} AccountQuery;

bool QueryAccountCondition(void* data, void* param)
{
    Account* account = (Account*)data;
    AccountQuery* query = (AccountQuery*)param;

    // �ж������� query->category ���ǿգ���ƥ�䣩
     if (query->account_type != Unknow && account->account_type != query->account_type)
        return False;

    if (query->id != -1 && query->id != account->id)
        return False;


    // �ж��豸���ƣ�ģ��ƥ�䣩
    if (strlen(query->user_name) > 0 && strstr(account->user_name, query->user_name) == NULL)
        return False;

    // �ж���������
    if (query->room_id != -1 && account->roomid != query->room_id)
        return False;


    return True;  // ��������������
}

void PrintAccount(void* data)
{
    Account* account = (Account*)data;
    char type[10] = "";
    switch (account->account_type)
    {
    case Admin:
        strcpy_s(type, 10, "����Ա");
        break;
    case Experimenter:
        strcpy_s(type, 10, "ʵ��Ա");
        break;
    case User:
        strcpy_s(type, 10, "һ���û�");
        break;
    default:
        break;
    }

    printf("ID: %d, �˻�����: %s, �˻�����: %s, ���������: %d\n",
        account->id, type, account->user_name, account->roomid);
}

void QueryAccountMenu()
{
    char name[USER_NMAE_LENGTH] = "";              // �˻�����
    AccountType account_type = Unknow;             // ���ID
    int room_id = -1;                              // �˻�����ʵ����ID
    int id = -1;                                   // �˻�id

    system("cls");
    printf("---          ��ѯ�˻���Ϣ          ---\n\n");

    // ѯ�����ƣ���ѡ��
    printf("--- �����˻��û��������س�������-> ");
    while (getchar() != '\n');
    fgets(name, USER_NMAE_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // ȥ�����з�'
    fflush(stdin);
    system("cls");

    // ѯ�� ID����ѡ��
    printf("--- �����˻� ID�����س�������-> ");
    char input[20];
    fgets(input, 20, stdin);
    if (strlen(input) > 1)
    {
        id = atoi(input);
    }
    fflush(stdin);
    system("cls");

    // ѯ����𣨿�ѡ��
    printf("--- 1.����Ա\n");
    printf("--- 2.ʵ��Ա\n");
    printf("--- 3.һ���û�\n");
    printf("--- �����˻���𣨰��س�������-> ");
    fgets(input, 20, stdin);
    if (strlen(input) > 1)
    {
        int temp = atoi(input);
        if (temp >= 4 || temp <= 0)
        {
            printf("�Ƿ�ָ��\n");
            system("pause");
            return;
        }
        account_type = (AccountType)(temp - 1);
    }
    fflush(stdin);
    system("cls");


    // ѯ��ʵ���� ID����ѡ��
    printf("--- ����ʵ���� ID�����س�������-> ");
    fgets(input, 20, stdin);
    if (strlen(input) > 1)
    {
        room_id = atoi(input);
    }
    fflush(stdin);
    system("cls");


    LinkedList* list = GetResourceManage()->account_list;
    AccountQuery query;

    strcpy_s(query.user_name, USER_NMAE_LENGTH, name);
    query.room_id = room_id;
    query.id = id;
    query.account_type = account_type;

    Query(list, QueryAccountCondition, &query, PrintAccount);
}

typedef struct _LabroomQuery
{
    char name[LABROOM_LENGTH];           // ʵ��������
    int id;                              // ʵ����ID
} LabroomQuery;

bool QueryLabroomCondition(void* data, void* param)
{
    LabRoom* Labroom = (LabRoom*)data;
    LabroomQuery* query = (LabroomQuery*)param;

    if (query->id != -1 && query->id != Labroom->id)
        return False;

    // �ж����ƣ�ģ��ƥ�䣩
    if (strlen(query->name) > 0 && strstr(Labroom->name, query->name) == NULL)
        return False;

    return True;  // ��������������
}

void PrintLabroom(void* data)
{
    LabRoom* Labroom = (LabRoom*)data;
 
    printf("ID: %d, ʵ��������: %s ",
        Labroom->id, Labroom->name);
    //���id��
	printf("ʵ�����������豸id ");
	Node* node = Labroom->equipments_list->head;
	while (node->next != NULL)
	{
		node = node->next;
		int* id = (int*)node->data;
		printf("%d ", *id);
	}
	printf("ʵ���������м���Աid ");
	node = Labroom->technician_id_list->head;
	while (node->next != NULL)
	{
		node = node->next;
		int* id = (int*)node->data;
		printf("%d ", *id);
	}
	printf("\n");
}

void QueryLabroomMenu()
{
    char name[LABROOM_LENGTH] = "";                // ʵ��������
    int id = -1;                                   // ʵ����id

    system("cls");
    printf("---          ��ѯʵ������Ϣ          ---\n\n");

    // ѯ�����ƣ���ѡ��
    printf("--- ����ʵ�������֣����س�������-> ");
    while (getchar() != '\n');
    fgets(name, LABROOM_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // ȥ�����з�'
    fflush(stdin);
    system("cls");

    // ѯ�� ID����ѡ��
    printf("--- ����ʵ���� ID�����س�������-> ");
    char input[20];
    fgets(input, 20, stdin);
    if (strlen(input) > 1)
    {
        id = atoi(input);
    }
    fflush(stdin);
    system("cls");

    LinkedList* list = GetResourceManage()->laboratory_list;
    LabroomQuery query;

    strcpy_s(query.name, LABROOM_LENGTH, name);
    query.id = id;

    Query(list, QueryLabroomCondition, &query, PrintLabroom);
}

typedef struct _CategoryQuery
{
    char name[LABROOM_LENGTH];           // ʵ��������
    int id;                              // ʵ����ID
} CategoryQuery;

bool QueryCategoryCondition(void* data, void* param)
{
    Category* category = (Category*)data;
    CategoryQuery* query = (CategoryQuery*)param;

    if (query->id != -1 && query->id != category->id)
        return False;

    // �ж����ƣ�ģ��ƥ�䣩
    if (strlen(query->name) > 0 && strstr(category->name, query->name) == NULL)
        return False;

    return True;  // ��������������
}

void PrintCategory(void* data)
{
    Category* category = (Category*)data;

    printf("ID: %d, �������: %s, ��������: %d\n",
        category->id, category->name,category->disposal_years);
}

void QueryCategoryMenu()
{
    char name[CATEGORY_LENGTH] = "";                // �������
    int id = -1;                                    // ���id

    system("cls");
    printf("---          ��ѯ�����Ϣ          ---\n\n");

    // ѯ�����ƣ���ѡ��
    printf("--- ����������֣����س�������-> ");
    while (getchar() != '\n');
    fgets(name, LABROOM_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // ȥ�����з�'
    fflush(stdin);
    system("cls");

    // ѯ�� ID����ѡ��
    printf("--- ������� ID�����س�������-> ");
    char input[20];
    fgets(input, 20, stdin);
    if (strlen(input) > 1)
    {
        id = atoi(input);
    }
    fflush(stdin);
    system("cls");

    LinkedList* list = GetResourceManage()->category_list;
    CategoryQuery query;

    strcpy_s(query.name, LABROOM_LENGTH, name);
    query.id = id;

    Query(list, QueryCategoryCondition, &query, PrintCategory);
}