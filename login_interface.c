#include "login_interface.h"
#include "account.h"

int ShowLoginMenu()
{
    system("cls");

    int option = 0;
    printf("---   登录界面   ---\n\n");
    printf("---   1. 登录    ---\n");
    printf("---   2. 注册    ---\n");
    printf("---   0. 退出    ---\n");
    printf("--- 请输入选项->");

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
            printf("登录失败\n");
            system("pause");
            return;
        }
        em->current_state = Management;
        em->current_account = account;
        printf("登录成功\n");
    }
        break;
    case 2:
        em->current_state = Register;
        break;
    default:
        printf("操作非法！\n");
        break;
    }
    system("pause");
}

Account* AccountLogin()
{
    Account* account = (Account*)malloc(sizeof(Account));

    printf("请输入用户名(长度在4-12位，且只能包含字母和数字）\n");
    fgets(account->user_name, USER_NMAE_LENGTH, stdin);
    account->user_name[strcspn(account->user_name, "\n")] = '\0';

    printf("请输入用户密码（长度在8-20位，且只能包含字母数字以及@+？）\n");
    fgets(account->user_password, sizeof(account->user_password), stdin);
    account->user_password[strcspn(account->user_password, "\n")] = '\0';

    if (!IsCorrectAccount(account))
    {
		free(account);
        return NULL;
    }

    return account;
}
