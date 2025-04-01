#include "register_interface.h"
#include "account.h"

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
            system("pause");
            return;
        }
        
        // �������˻�
        ResourceManager* resource_manager = GetResourceManage();
        LinkedList_pushback(resource_manager->account_list, account);
		printf("ע��ɹ�\n");
    }
    break;
    case 2:
        em->current_state = Login;
        break;
    default:
        printf("�����Ƿ���\n");
        break;
    }
    system("pause");
}