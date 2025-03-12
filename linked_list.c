#include "linked_list.h"

LinkedList* CreateLinkedList()
{
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (!list) 
    {
        printf("内存分配失败\n");
        return NULL;
    }
    list->head = createNode(NULL);
    list->size = 0;    // 初始化大小为0
    return list;
}

void destoryLinkedList(LinkedList* list)
{
    if (list == NULL) return;

    Node* current = list->head;
    while (current != NULL) 
    {
        Node* next = current->next;
        free(current);        
        current = next;
    }

    free(list); 
}

Node* createNode(void* data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode)
    {
        printf("内存分配失败\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void LinkedList_pushback(LinkedList* list, void* data)
{
    Node* newNode = createNode(data);
    if (!newNode) return;

    Node* temp = list->head;
    while (temp->next) 
    {
        temp = temp->next;
    }
    temp->next = newNode;

    list->size++;
}

void LinkedList_insert(LinkedList* list, void* data, int index)
{
    size_t lsize = LinkedList_size(list);
    if (index > lsize || index < 0)
    {
        printf("下标不合法\n");
        return;
    }

    Node* newNode = createNode(data);
    if (!newNode) return;

    Node* temp = list->head;
    for(size_t i = 0; i < index; i++)
        temp = temp->next;

    newNode->next = temp->next;
    temp->next = newNode;

    list->size++;
}

DataType LinkedList_delete(LinkedList* list, int index)
{
    size_t lsize = LinkedList_size(list);
    if (index < 0 || index >= lsize)
    {
        printf("下标不合法\n");
        return NULL;
    }
    
    Node* preNode = list->head;
    void* deletedData = NULL;

    for (size_t i = 0; i < index; i++)
        preNode = preNode->next;

    Node* deletedNode = preNode->next;
    deletedData = deletedNode->data;

    preNode->next = deletedNode->next;
    free(deletedNode);

    list->size--;
    return deletedData;
}

DataType LinkedList_back(LinkedList* list)
{
    Node* temp = list->head;

    while (temp->next)
    {
        temp = temp->next;
    }

    return temp->data;
}

DataType LinkedList_at(LinkedList* list, int index)
{
    size_t lsize = LinkedList_size(list);
    if (index < 0 || index >= lsize)
    {
        printf("下标不合法\n");
        return NULL;
    }

    Node* temp = list->head->next;
    for (size_t i = 0; i < index; i++)
        temp = temp->next;

    return temp->data;
}

size_t LinkedList_size(LinkedList* list)
{
    return list->size;
}
