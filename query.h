#pragma once
#include "experimental_equipment.h"
#include "category.h"
#include "lab_room.h"
#include "account.h"
#include "configs.h"

typedef bool (*QueryCondition)(void* data, void* param);

void QueryEquipment(LinkedList* list, QueryCondition condition, void* param, void (*PrintResult)(void*))
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
    if (query->category_id != -1 && eq->category->id == query->category_id)
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
    if (query->room_id != -1 && eq->room_id == query->room_id)
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
    char date[DATE_LENGTH];              // 设备购买日期 

    system("cls");
    printf("---          查询实验设备信息          ---\n\n");

    // 询问设备名称（可选）
    printf("--- 输入设备名称（按回车跳过）-> ");
    fgets(name, EQUIPMENT_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // 去掉换行符
    system("cls");

    // 询问类别 ID（可选）
    printf("--- 输入设备类别 ID（按回车跳过）-> ");
    char input[20];
    fgets(input, 20, stdin);
    if (strlen(input) > 1) 
    {
        category_id = atoi(input);
    }
    system("cls");

    // 询问设备购买时间（可选）
    printf("--- 输入设备名称（按回车跳过）-> ");
    fgets(date, DATE_LENGTH, stdin);
    date[strcspn(name, "\n")] = 0; // 去掉换行符
    system("cls");

    // 询问实验室 ID（可选）
    printf("--- 输入实验室 ID（按回车跳过）-> ");
    fgets(input, 20, stdin);
    if (strlen(input) > 1) 
    {
        room_id = atoi(input);
    }
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
    strcpy_s(query.purchase_date, DATE_LENGTH, date);
    
    QueryEquipment(list, QueryEquipmenCondition, &query, PrintEquipment);
}