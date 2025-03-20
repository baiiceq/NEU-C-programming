#include "management_interface.h"
#include "query.h"


int ShowManagementMenu(AccountType account_type)
{
    system("cls");

    int option = 0;
    printf("---         管理界面        ---\n\n");
    switch (account_type)
    {
    case Admin:
        printf("---        1. 基本信息管理      ---\n");
        printf("---        2. 信息调整管理      ---\n");
        printf("---        3. 信息查询          ---\n");
        printf("---        4. 信息排序          ---\n");
        printf("---        5. 信息统计          ---\n");
        printf("---        6. 系统维护          ---\n");
        break;
    case Experimenter:
        printf("---        1. 设备管理          ---\n");
        printf("---        2. 信息查询          ---\n");
        printf("---        3. 信息排序          ---\n");
        printf("---        4. 信息统计          ---\n");
        printf("---        5. 系统维护          ---\n");
        break;
    case User:
        printf("---        1. 信息查询          ---\n");
        printf("---        2. 信息排序          ---\n");
        printf("---        3. 信息统计          ---\n");
        printf("---        4. 系统维护          ---\n");
        break;
    }

    printf("---        0. 退出          ---\n");
    printf("--- 请输入选项->");

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
        case 1:
            BasicInformationManagement();
            break;
        case 3:
            QueryInformation();
            break;
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
    system("cls");

    printf("---             信息查询           ---\n\n");
    printf("---        请选择你要查询的信息      ---\n");
    printf("---          1. 实验室               ---\n");
    printf("---          2. 实验员               ---\n");
    printf("---          3. 实验设备类别         ---\n");
    printf("---          4. 实验设备             ---\n");
    printf("---          0. 返  回               ---\n");
    printf("选择->");

    int option = 0;
    scanf_s("%d", &option);

    switch (option)
    {
    case 0:
        return;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        QueryEquipmentMenu();
        break;
    default:
        printf("非法指令\n");
        system("pause");
        break;
    }
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
    system("cls");

    printf("---            基本信息管理          ---\n\n");
    printf("---        请选择你要管理的信息      ---\n");
    printf("---          1. 实验室               ---\n");
    printf("---          2. 实验员               ---\n");
    printf("---          3. 实验设备类别         ---\n");
    printf("---          4. 实验设备             ---\n");
    printf("---          0. 返  回               ---\n");
    printf("选择->");

    int option = 0;
    scanf_s("%d", &option);

    switch (option)
    {
    case 0:
        return;
    case 1:
        ManageLabRoom();
        break;
    case 2:
        ManageAccount();
        break;
    case 3:
        ManageCategory();
        break;
    case 4:
        ManageExperimentalEquipment();
        break;
    default:
        printf("非法指令\n");
        system("pause");
        break;
    }
}

void AdjustmentInformation()
{
}

void EquipmentsManagement()
{
}

