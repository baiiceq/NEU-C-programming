#include "register_interface.h"

int ShowRegisterMenu()
{
    system("cls");

    int option = 0;
    printf("---   ע�����   ---\n\n");
    printf("---   1. ע��    ---\n");
    printf("---   2. ��¼    ---\n");
    printf("---   0. �˳�    ---\n");
    printf("--- ������ѡ��->");

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
            printf("ע��ʧ��\n");
            return;
        }
        
        // �������˻�
        LoginInterface* login_interface = GetLoginInterface();
        LinkedList_pushback(login_interface->account_list, account);
    }
    break;
    case 2:
        em->current_state = Login;
        break;
    default:
        printf("�����Ƿ���\n");
        break;
    }
}

Account* AccountRegister()
{
    Account* account = (Account*)malloc(sizeof(Account));
    printf("�������û�����1.����Ա2.ʵ��Ա3.һ���û�\n");
    scanf_s("%d", &account->account_type);
    printf("�������û���\n");
    scanf_s("%s", account->user_name);
    printf("�������û�����\n");
    scanf_s("%s", account->user_password);
    if (!IsValidAccount(account))
    {
		free(account);
		return NULL;
    }
    return account;
}
