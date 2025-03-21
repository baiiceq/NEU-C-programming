#include "id_manager.h"

static IdManager* instance = NULL;

static void init_instance()
{
    if (instance == NULL)
    {
        instance = (IdManager*)malloc(sizeof(IdManager));
        if (instance == NULL)
        {
            printf("ID管理器加载失败");
            exit(-1);
        }
    }
}

int GetNewId(IdType type)
{
    init_instance();

    switch (type)
    {
    case AccountID:
        return ++instance->current_account_id;
        break;
    case CategoryID:
        return ++instance->current_category_id;
        break;
    case EquipmentID:
        return ++instance->current_equipment_id;
        break;
    case RoomID:
        return ++instance->current_room_id;
        break;
    }
}

void DestoryIdManager()
{
    if (instance)
        free(instance);
}

bool SaveId()
{
    init_instance();

    FILE* fp = fopen("current_id.txt", "w");
    if (fp == NULL)
    {
        printf("文件打开失败\n");
        //system("pause");
        return False;
    }
    fprintf(fp, "%d %d %d %d\n",instance->current_account_id,
        instance->current_category_id,
        instance->current_equipment_id,
        instance->current_room_id);

    fclose(fp);
    return True;
}

bool LoadId()
{
    init_instance();
    FILE* fp = fopen("current_id.txt", "r");
    if (fp == NULL)
    {
        printf("文件打开失败\n");
        return False;
    }
    while (!feof(fp))
    {
        fscanf_s(fp, "%d %d %d %d",&instance->current_account_id,
            &instance->current_category_id,
            &instance->current_equipment_id,
            &instance->current_room_id);
    }
    fclose(fp);
}
