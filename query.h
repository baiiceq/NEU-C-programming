#pragma once
#include "experimental_equipment.h"
#include "category.h"
#include "lab_room.h"
#include "account.h"
#include "configs.h"

typedef bool (*QueryCondition)(void* data, void* param);

void Query(LinkedList* list, QueryCondition condition, void* param, void (*PrintResult)(void*))
{
    if (list == NULL || condition == NULL || PrintResult == NULL) {
        printf("查询失败: 参数无效！\n");
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
        printf("未找到符合条件的记录。\n\n");
        system("pause");
    }
}

typedef struct _EquipmentQuery
{
    int id;                            // ID
    int category_id;                   // 类别
    char purchase_date[DATE_LENGTH];   // 购入日期
    int min_price;                     // 最小价格
    int max_price;                     // 最大价格
    char name[EQUIPMENT_LENGTH];       // 名字
    int room_id;                       // 所属房间

} EquipmentQuery;

bool QueryEquipmenCondition(void* data, void* param)
{
    ExperimentalEquipment* eq = (ExperimentalEquipment*)data;
    EquipmentQuery* query = (EquipmentQuery*)param;

    // 判断类别（如果 query->category 不是空，就匹配）
    if (query->category_id != -1 && eq->category->id != query->category_id)
        return False;

    if (query->id != -1 && query->id != eq->id)
        return False;

    // 判断购入日期
    if (strlen(query->purchase_date) > 0 && strcmp(eq->purchase_date, query->purchase_date) != 0)
        return False;

    // 判断价格范围
    if ((query->min_price >= 0 && eq->price < query->min_price) ||
        (query->max_price >= 0 && eq->price > query->max_price))
        return False;

    // 判断设备名称（模糊匹配）
    if (strlen(query->name) > 0 && strstr(eq->name, query->name) == NULL)
        return False;

    // 判断所属房间
    if (query->room_id != -1 && eq->room_id != query->room_id)
        return False;
    

    return True;  // 所有条件都符合
}

void PrintEquipment(void* data)
{
    ExperimentalEquipment* eq = (ExperimentalEquipment*)data;
    printf("ID: %d, 名称: %s, 类别: %s, 价格: %d, 所属房间号: %d\n",
        eq->id, eq->name, eq->category->name, eq->price, eq->room_id);
}

void QueryEquipmentMenu()
{
    char name[EQUIPMENT_LENGTH] = "";    // 设备名称
    int category_id = -1;                // 设备类别ID，-1 代表不筛选
    int room_id = -1;                    // 设备所在实验室ID，-1 代表不筛选
    double min_price = -1;               // 设备最低价格，-1 代表不筛选
    double max_price = -1;               // 设备最高价格，-1 代表不筛选
    char date[DATE_LENGTH] = "";         // 设备购买日期 
    int id = -1;                         // 设备id

    system("cls");
    printf("---          查询实验设备信息          ---\n\n");

    // 询问设备名称（可选）
    printf("--- 输入设备名称（按回车跳过）-> ");
    while (getchar() != '\n');
    fgets(name, EQUIPMENT_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // 去掉换行符'
    fflush(stdin);
    system("cls");

    // 询问设备 ID（可选）
    printf("--- 输入设备 ID（按回车跳过）-> ");
    char input[20];
    fgets(input, 20, stdin);
    if (strlen(input) > 1)
    {
        id = atoi(input);
    }
    fflush(stdin);
    system("cls");

    // 询问类别 ID（可选）
    printf("--- 输入设备类别 ID（按回车跳过）-> ");
    fgets(input, 20, stdin);
    if (strlen(input) > 1) 
    {
        category_id = atoi(input);
    }
    fflush(stdin);
    system("cls");

    // 询问设备购买时间（可选）
    printf("--- 输入设备购买时间（按回车跳过）-> ");
    fgets(date, DATE_LENGTH, stdin);
    date[strcspn(date, "\n")] = 0; // 去掉换行符
    fflush(stdin);
    system("cls");

    // 询问实验室 ID（可选）
    printf("--- 输入实验室 ID（按回车跳过）-> ");
    fgets(input, 20, stdin);
    if (strlen(input) > 1) 
    {
        room_id = atoi(input);
    }
    fflush(stdin);
    system("cls");

    // 询问价格区间（可选）
    printf("--- 输入最低价格（按回车跳过）-> ");
    fgets(input, 20, stdin);
    if (strlen(input) > 1) 
    {
        min_price = atof(input);
    }

    printf("--- 输入最高价格（按回车跳过）-> ");
    fgets(input, 20, stdin);
    if (strlen(input) > 1) 
    {
        max_price = atof(input);
    }

    LinkedList* list = GetResourceManage()->equipment_list;
    EquipmentQuery query;

    strcpy_s(query.name, EQUIPMENT_LENGTH, name);
    query.category_id = category_id;
    query.room_id = room_id;
    query.min_price = min_price;
    query.max_price = max_price;
    query.id = id;
    strcpy_s(query.purchase_date, DATE_LENGTH, date);
    
    Query(list, QueryEquipmenCondition, &query, PrintEquipment);
}

typedef struct _AccountQuery
{
    AccountType account_type;            // 账户类别
    char user_name[USER_NMAE_LENGTH];    // 账户名称
    int id;                              //账户ID
    int room_id;                          //所属实验室id
} AccountQuery;

bool QueryAccountCondition(void* data, void* param)
{
    Account* account = (Account*)data;
    AccountQuery* query = (AccountQuery*)param;

    // 判断类别（如果 query->category 不是空，就匹配）
     if (query->account_type != Unknow && account->account_type != query->account_type)
        return False;

    if (query->id != -1 && query->id != account->id)
        return False;


    // 判断设备名称（模糊匹配）
    if (strlen(query->user_name) > 0 && strstr(account->user_name, query->user_name) == NULL)
        return False;

    // 判断所属房间
    if (query->room_id != -1 && account->roomid != query->room_id)
        return False;


    return True;  // 所有条件都符合
}

void PrintAccount(void* data)
{
    Account* account = (Account*)data;
    char type[10] = "";
    switch (account->account_type)
    {
    case Admin:
        strcpy_s(type, 10, "管理员");
        break;
    case Experimenter:
        strcpy_s(type, 10, "实验员");
        break;
    case User:
        strcpy_s(type, 10, "一般用户");
        break;
    default:
        break;
    }

    printf("ID: %d, 账户类型: %s, 账户名称: %s, 所属房间号: %d\n",
        account->id, type, account->user_name, account->roomid);
}

void QueryAccountMenu()
{
    char name[USER_NMAE_LENGTH] = "";              // 账户名称
    AccountType account_type = Unknow;             // 类别ID
    int room_id = -1;                              // 账户所在实验室ID
    int id = -1;                                   // 账户id

    system("cls");
    printf("---          查询账户信息          ---\n\n");

    // 询问名称（可选）
    printf("--- 输入账户用户名（按回车跳过）-> ");
    while (getchar() != '\n');
    fgets(name, USER_NMAE_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // 去掉换行符'
    fflush(stdin);
    system("cls");

    // 询问 ID（可选）
    printf("--- 输入账户 ID（按回车跳过）-> ");
    char input[20];
    fgets(input, 20, stdin);
    if (strlen(input) > 1)
    {
        id = atoi(input);
    }
    fflush(stdin);
    system("cls");

    // 询问类别（可选）
    printf("--- 1.管理员\n");
    printf("--- 2.实验员\n");
    printf("--- 3.一般用户\n");
    printf("--- 输入账户类别（按回车跳过）-> ");
    fgets(input, 20, stdin);
    if (strlen(input) > 1)
    {
        int temp = atoi(input);
        if (temp >= 4 || temp <= 0)
        {
            printf("非法指令\n");
            system("pause");
            return;
        }
        account_type = (AccountType)(temp - 1);
    }
    fflush(stdin);
    system("cls");


    // 询问实验室 ID（可选）
    printf("--- 输入实验室 ID（按回车跳过）-> ");
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
    char name[LABROOM_LENGTH];           // 实验室名称
    int id;                              // 实验室ID
} LabroomQuery;

bool QueryLabroomCondition(void* data, void* param)
{
    LabRoom* Labroom = (LabRoom*)data;
    LabroomQuery* query = (LabroomQuery*)param;

    if (query->id != -1 && query->id != Labroom->id)
        return False;

    // 判断名称（模糊匹配）
    if (strlen(query->name) > 0 && strstr(Labroom->name, query->name) == NULL)
        return False;

    return True;  // 所有条件都符合
}

void PrintLabroom(void* data)
{
    LabRoom* Labroom = (LabRoom*)data;
 
    printf("ID: %d, 实验室名字: %s\n",
        Labroom->id, Labroom->name);
}

void QueryLabroomMenu()
{
    char name[LABROOM_LENGTH] = "";                // 实验室名称
    int id = -1;                                   // 实验室id

    system("cls");
    printf("---          查询实验室信息          ---\n\n");

    // 询问名称（可选）
    printf("--- 输入实验室名字（按回车跳过）-> ");
    while (getchar() != '\n');
    fgets(name, LABROOM_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // 去掉换行符'
    fflush(stdin);
    system("cls");

    // 询问 ID（可选）
    printf("--- 输入实验室 ID（按回车跳过）-> ");
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
    char name[LABROOM_LENGTH];           // 实验室名称
    int id;                              // 实验室ID
} CategoryQuery;

bool QueryCategoryCondition(void* data, void* param)
{
    Category* category = (Category*)data;
    CategoryQuery* query = (CategoryQuery*)param;

    if (query->id != -1 && query->id != category->id)
        return False;

    // 判断名称（模糊匹配）
    if (strlen(query->name) > 0 && strstr(category->name, query->name) == NULL)
        return False;

    return True;  // 所有条件都符合
}

void PrintCategory(void* data)
{
    Category* category = (Category*)data;

    printf("ID: %d, 类别名字: %s, 报废年限: %d\n",
        category->id, category->name,category->disposal_years);
}

void QueryCategoryMenu()
{
    char name[CATEGORY_LENGTH] = "";                // 类别名称
    int id = -1;                                    // 类别id

    system("cls");
    printf("---          查询类别信息          ---\n\n");

    // 询问名称（可选）
    printf("--- 输入类别名字（按回车跳过）-> ");
    while (getchar() != '\n');
    fgets(name, LABROOM_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // 去掉换行符'
    fflush(stdin);
    system("cls");

    // 询问 ID（可选）
    printf("--- 输入类别 ID（按回车跳过）-> ");
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