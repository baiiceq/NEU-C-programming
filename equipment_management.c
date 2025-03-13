#include "equipment_management.h"
#include "login_interface.h" 
#include "register_interface.h"

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
        
    }
}

EquipmentManagement* CreateEquipmentManagement()
{
    EquipmentManagement* em = (EquipmentManagement*)malloc(sizeof(EquipmentManagement));
    if (em == NULL)
    {
        printf("ϵͳ����ʧ��\n");
        exit(1);
    }

    em->current_account = NULL;
    em->running = True;
    em->current_state = Login;

    return em;
}

void DestoryEquipmentManagement(EquipmentManagement* em)
{
    DestoryResourceManage();
    free(em);
}
