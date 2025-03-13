#include "resource_manager.h"

static ResourceManager* instance = NULL;

ResourceManager* GetResourceManage()
{
    if (instance == NULL)
    {
        instance = (ResourceManager*)malloc(sizeof(ResourceManager));
        if (instance == NULL)
        {
            printf("资源管理器加载失败");
            exit(-1);
        }
        instance->account_list = CreateLinkedList();
        instance->equipment_list = CreateLinkedList();
        instance->laboratory_list = CreateLinkedList();
    }

    return instance;
}

void DestoryResourceManage()
{
    if (instance == NULL)
        return;

    destoryLinkedList(instance->account_list);
    destoryLinkedList(instance->equipment_list);
    destoryLinkedList(instance->laboratory_list);
}
