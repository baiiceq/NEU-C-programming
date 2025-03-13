#include "register_interface.h"

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
            return;
        }
        
        // 储存新账户
        LoginInterface* login_interface = GetLoginInterface();
        LinkedList_pushback(login_interface->account_list, account);
    }
    break;
    case 2:
        em->current_state = Login;
        break;
    default:
        printf("操作非法！\n");
        break;
    }
}

Account* AccountRegister()
{
    Account* account = (Account*)malloc(sizeof(Account));
    printf("请输入用户类型1.管理员2.实验员3.一般用户\n");
    scanf_s("%d", &account->account_type);
    printf("请输入用户名\n");
    scanf_s("%s", account->user_name);
    printf("请输入用户密码\n");
    scanf_s("%s", account->user_password);
    if (!IsValidAccount(account))
    {
		free(account);
		return NULL;
    }
    return account;
}
