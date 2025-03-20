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

typedef struct _EquipmentQuery
{
    int id;                            // ID
    int category_id;                   // ���
    char purchase_date[DATE_LENGTH];   // ��������
    int min_price;                     // ��С�۸�
    int max_price;                     // ���۸�
    char name[EQUIPMENT_LENGTH];       // ����
    int room_id;                       // ��������
} EquipmentQuery;

bool QueryEquipmenCondition(void* data, void* param)
{
    ExperimentalEquipment* eq = (ExperimentalEquipment*)data;
    EquipmentQuery* query = (EquipmentQuery*)param;

    // �ж������� query->category ���ǿգ���ƥ�䣩
    if (query->category_id != -1 && eq->category->id == query->category_id)
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
    if (query->room_id != -1 && eq->room_id == query->room_id)
        return False;
    

    return True;  // ��������������
}

void PrintEquipment(void* data)
{
    ExperimentalEquipment* eq = (ExperimentalEquipment*)data;
    printf("ID: %d, ����: %s, ���: %s, �۸�: %d, ���������: %d\n",
        eq->id, eq->name, eq->category->name, eq->price, eq->room_id);
}

void QueryEquipmentMenu()
{
    char name[EQUIPMENT_LENGTH] = "";    // �豸����
    int category_id = -1;                // �豸���ID��-1 ����ɸѡ
    int room_id = -1;                    // �豸����ʵ����ID��-1 ����ɸѡ
    double min_price = -1;               // �豸��ͼ۸�-1 ����ɸѡ
    double max_price = -1;               // �豸��߼۸�-1 ����ɸѡ
    char date[DATE_LENGTH];              // �豸�������� 

    system("cls");
    printf("---          ��ѯʵ���豸��Ϣ          ---\n\n");

    // ѯ���豸���ƣ���ѡ��
    printf("--- �����豸���ƣ����س�������-> ");
    fgets(name, EQUIPMENT_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // ȥ�����з�
    system("cls");

    // ѯ����� ID����ѡ��
    printf("--- �����豸��� ID�����س�������-> ");
    char input[20];
    fgets(input, 20, stdin);
    if (strlen(input) > 1) 
    {
        category_id = atoi(input);
    }
    system("cls");

    // ѯ���豸����ʱ�䣨��ѡ��
    printf("--- �����豸���ƣ����س�������-> ");
    fgets(date, DATE_LENGTH, stdin);
    date[strcspn(name, "\n")] = 0; // ȥ�����з�
    system("cls");

    // ѯ��ʵ���� ID����ѡ��
    printf("--- ����ʵ���� ID�����س�������-> ");
    fgets(input, 20, stdin);
    if (strlen(input) > 1) 
    {
        room_id = atoi(input);
    }
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