#include "register_interface.h"

int ShowRegisterMenu()
{
    system("cls");

    int option = 0;
    printf("---   ×¢²á½çÃæ   ---\n\n");
    printf("---   1. ×¢²á    ---\n");
    printf("---   2. µÇÂ¼    ---\n");
    printf("---   0. ÍË³ö    ---\n");
    printf("--- ÇëÊäÈëÑ¡Ïî->");

    scanf_s("%d", &option);
    while (getchar() != '\n');

    system("pause");
    return option;
}

void RunRegisterInterface(int option, EquipmentManagement* em)
{
    switch (option)
    {
    case 0:
        em->running = False;
        break;
    case 1:
    {
        Account* account = AccountRegister();
        if (account == NULL)
        {
            printf("×¢²áÊ§°Ü\n");
            return;
        }
        
        // ´¢´æÐÂÕË»§
        ResourceManager* resource_manager = GetResourceManage();
        LinkedList_pushback(resource_manager->account_list, account);
    }
    break;
    case 2:
        em->current_state = Login;
        break;
    default:
        printf("²Ù×÷·Ç·¨£¡\n");
        break;
    }
}

Account* AccountRegister()
{
    return NULL;
}
