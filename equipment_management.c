#include "equipment_management.h"
#include "register_interface.h"
#include "login_interface.h"
#include "management_interface.h"

void Run(EquipmentManagement* em)
{
    int option = 0;
    switch (em->current_state)
    {
    case Login:
        option = ShowLoginMenu();
        RunLoginInterface(option, em);
        break;
    case Register:
        option = ShowRegisterMenu();
        RunRegisterInterface(option, em);
        break;
    case Management:
        option = ShowManagementMenu(em->current_account->account_type);
        RunManagementInterface(option, em, em->current_account->account_type);
        break;
    }
}

EquipmentManagement* CreateEquipmentManagement()
{
    EquipmentManagement* em = (EquipmentManagement*)malloc(sizeof(EquipmentManagement));
    if (em == NULL)
    {
        printf("系统创建失败\n");
        exit(1);
    }

    em->current_account = NULL;
    em->running = True;
    em->current_state = Login;
    CreateAccountList();

    LoadId();
    return em;
}

void DestoryEquipmentManagement(EquipmentManagement* em)
{
    SaveAccountList();
    SaveId();
    DestoryIdManager();
    DestoryResourceManage();
    free(em);
}
