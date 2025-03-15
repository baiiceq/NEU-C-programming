#include "management_interface.h"


int ShowManagementMenu(AccountType account_type)
{
    system("cls");

    int option = 0;
    printf("---        �������      ---\n\n");
    switch (account_type)
    {
    case Admin:
        printf("---        1. ������Ϣ����      ---\n");
        printf("---        2. ��Ϣ��������      ---\n");
        printf("---        3. ��Ϣ��ѯ          ---\n");
        printf("---        4. ��Ϣ����          ---\n");
        printf("---        5. ��Ϣͳ��          ---\n");
        printf("---        6. ϵͳά��          ---\n");
        break;
    case Experimenter:
        printf("---        1. �豸����          ---\n");
        printf("---        2. ��Ϣ��ѯ          ---\n");
        printf("---        3. ��Ϣ����          ---\n");
        printf("---        4. ��Ϣͳ��          ---\n");
        printf("---        5. ϵͳά��          ---\n");
        break;
    case User:
        printf("---        1. ��Ϣ��ѯ          ---\n");
        printf("---        2. ��Ϣ����          ---\n");
        printf("---        3. ��Ϣͳ��          ---\n");
        printf("---        4. ϵͳά��          ---\n");
        break;
    }

    printf("---        0. �˳�          ---\n");
    printf("--- ������ѡ��->");

    scanf_s("%d", &option);
    while (getchar() != '\n');

    system("pause");
    return option;
} 

void RunManagementInterface(int option, EquipmentManagement* em, AccountType account_type)
{
    switch (account_type)
    {
    case Admin:
        switch (option)
        {
        case 0:
            free(em->current_account);
            em->current_account = NULL;
            em->current_state = Login;
            return ;
        default:
            break;
        }
        break;
    case Experimenter:
        switch (option)
        {
        case 0:
            free(em->current_account);
            em->current_account = NULL;
            em->current_state = Login;
            return;
        default:
            break;
        }
        break;

    case User:
        switch (option)
        {
        case 0:
            free(em->current_account);
            em->current_account = NULL;
            em->current_state = Login;
            return;
        default:
            break;
        }
        break;
    }
}

void QueryInformation()
{
}

void SortInformation()
{
}

void Statistics()
{
}

void SystemMaintenance(AccountType account_type)
{
}

void BasicInformationManagement()
{

}

void AdjustmentInformation()
{
}

void EquipmentsManagement()
{
}

