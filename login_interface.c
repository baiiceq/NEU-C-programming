#include "login_interface.h"

int ShowLoginMenu()
{
    system("cls");

    int option = 0;
    printf("---   µÇÂ¼½çÃæ   ---\n\n");
    printf("---   1. µÇÂ¼    ---\n");
    printf("---   2. ×¢²á    ---\n");
    printf("---   0. ÍË³ö    ---\n");
    printf("--- ÇëÊäÈëÑ¡Ïî->");

    scanf_s("%d", &option);
    while (getchar() != '\n');

    system("pause");
    return option;
}

void RunLoginInterface(int option, EquipmentManagement* em)
{
    switch (option)
    {
    case 0:
        em->running = False;
        break;
    case 1:
    {
        Account* account = AccountLogin();
        if (account == NULL)
        {
            printf("µÇÂ¼Ê§°Ü\n");
            return;
        }
        em->current_state = Management;
        em->current_account = account;
    }
        break;
    case 2:
        em->current_state = Register;
        break;
    default:
        printf("²Ù×÷·Ç·¨£¡\n");
        break;
    }
}

Account* AccountLogin()
{
    return NULL;
}
