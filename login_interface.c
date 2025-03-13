#include "login_interface.h"

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
