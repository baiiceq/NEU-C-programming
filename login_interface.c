#include "login_interface.h"

static LoginInterface* login_instance = NULL;

void destoryLoginInterface()
{
    if (login_instance)
    {
        destoryLinkedList(login_instance->account_list);
        free(login_instance);
    }
}

LoginInterface* GetLoginInterface()
{
    if (login_instance == NULL)
    {
        login_instance = (LoginInterface*)malloc(sizeof(LoginInterface));
        if (login_instance == NULL) 
        {
            perror("登陆界面创建失败\n");
            return NULL;
        }
        login_instance->account_list = CreateLinkedList();
    }

    return login_instance;
}

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
        printf("操作非法！\n");
        break;
    }
}

Account* AccountLogin()
{
    return NULL;
}
