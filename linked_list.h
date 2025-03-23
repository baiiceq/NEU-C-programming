#pragma once
#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void* DataType; // 通过 void* 适配任意类型变量

typedef struct _Node    // 结点
{
    DataType data;         // 结点储存的数据(头结点时为空)
    struct _Node* next;    // 下一个结点
} Node;

typedef struct _LinkedList
{
    Node* head;    // 头结点
    size_t size;   // 链表结点数
} LinkedList;

// 创建链表
LinkedList* CreateLinkedList();

// 销毁链表
void destoryLinkedList(LinkedList* list); 

// 创建结点
Node* createNode(void* data);

// 在链表后添加元素
void LinkedList_pushback(LinkedList* list, void* data);

// 在链表中插入元素
void LinkedList_insert(LinkedList* list, void* data, int index);

// 删除链表中的元素
DataType LinkedList_delete(LinkedList* list, int index);

// 返回链表中最后一个元素
DataType LinkedList_back(LinkedList* list);

// 返回链表中的元素
DataType LinkedList_at(LinkedList* list, int index);

// 返回链表大小
size_t LinkedList_size(LinkedList* list);

// 列表排序
void LinkedList_sort(LinkedList* list, int (*cmp)(const void*, const void*, void*), void* arg);

// 列表遍历输出
void LinkedList_print(LinkedList* list, void (*PrintResult)(void*));

#endif // !LINKED_LIST
