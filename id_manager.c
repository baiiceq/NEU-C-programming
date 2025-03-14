#include "id_manager.h"

static IdManager* instance = NULL;

int GetNewId(IdType type)
{
    if (instance == NULL)
    {
        instance = (IdManager*)malloc(sizeof(IdManager));
        if (instance == NULL)
        {
            printf("ID¹ÜÀíÆ÷¼ÓÔØÊ§°Ü");
            exit(-1);
        }
    }
    switch (type)
    {
    case Account:
        return instance->current_account_id++;
        break;
    case Equipment:
        return instance->current_equipment_id++;
        break;
    case Room:
        return instance->current_room_id++;
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
    return false;
}

bool LoadId()
{
    return false;
}
