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
            perror("��½���洴��ʧ��\n");
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
    printf("---   ��¼����   ---\n\n");
    printf("---   1. ��¼    ---\n");
    printf("---   2. ע��    ---\n");
    printf("---   0. �˳�    ---\n");
    printf("--- ������ѡ��->");

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
            printf("��¼ʧ��\n");
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
        printf("�����Ƿ���\n");
        break;
    }
}

Account* AccountLogin()
{
    return NULL;
}
