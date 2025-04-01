#include "register_interface.h"
#include "account.h"

int ShowRegisterMenu()
{
    system("cls");

    int option = 0;
    printf("---   注册界面   ---\n\n");
    printf("---   1. 注册    ---\n");
    printf("---   2. 登录    ---\n");
    printf("---   0. 退出    ---\n");
    printf("--- 请输入选项->");

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
            printf("注册失败\n");
            system("pause");
            return;
        }
        
        // 储存新账户
        ResourceManager* resource_manager = GetResourceManage();
        LinkedList_pushback(resource_manager->account_list, account);
		printf("注册成功\n");
    }
    break;
    case 2:
        em->current_state = Login;
        break;
    default:
        printf("操作非法！\n");
        break;
    }
    system("pause");
}