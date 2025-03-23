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

// 归并排序
Node* MergeSort(Node* head, int (*cmp)(const void*, const void*, void*), void* arg);

Node* GetMiddle(Node* head);

Node* Merge(Node* left, Node* right, int (*cmp)(const void*, const void*, void*), void* arg);


void LinkedList_sort(LinkedList* list, int (*cmp)(const void*, const void*, void*), void* arg)
{
    if (!list || !list->head || !list->head->next) return; 

    list->head->next = MergeSort(list->head->next, cmp, arg);
}

Node* MergeSort(Node* head, int (*cmp)(const void*, const void*, void*), void* arg)
{
    if (!head || !head->next) return head; 

    Node* middle = GetMiddle(head);
    Node* right_half = middle->next;
    middle->next = NULL;

    Node* left = MergeSort(head, cmp, arg);
    Node* right = MergeSort(right_half, cmp, arg);

    return Merge(left, right, cmp, arg);
}

Node* GetMiddle(Node* head)
{
    if (!head) return head;

    Node* slow = head;
    Node* fast = head->next;

    while (fast && fast->next) 
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node* Merge(Node* left, Node* right, int (*cmp)(const void*, const void*, void*), void* arg)
{
    if (!left) return right;
    if (!right) return left;

    Node dummy; // 头结点
    Node* tail = &dummy;

    while (left && right) 
    {
        if (cmp(left->data, right->data, arg) <= 0) 
        {
            tail->next = left;
            left = left->next;
        }
        else 
        {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }

    tail->next = left ? left : right;
    return dummy.next;
}

void LinkedList_print(LinkedList* list, void(*PrintResult)(void*))
{
    Node* temp = list->head;

    while (temp->next)
    {
        temp = temp->next;
        PrintResult(temp->data);
    }

    system("pause");
}