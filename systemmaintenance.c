#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "systemmaintenance.h"

// ϵͳά�����˵�������Ա��
void ASystemMaintenance(Account* account)
{
    int choice;
    bool exit = false;

    while (!exit) {
        system("cls");
        printf("\n=== ϵͳά���˵�������Ա��===\n");
        printf("1. �޸ĵ�ǰ�˻�����\n");
        printf("2. �����û�/ʵ��Ա����\n");
        printf("3. �޸ĵ�ǰ�˻��û���\n");
        printf("4. �޸��û�/ʵ��Ա�û���\n");
        printf("5. ����ϵͳ����\n");
        printf("6. �ָ�ϵͳ����\n");
        printf("0. ����\n");
        printf("��ѡ��: ");

        scanf_s("%d", &choice);
        getchar();

        system("cls");
        switch (choice)
        {
        case 1:
            ChangePassword(account);
            break;

        case 2:
        {
            int targetUserId;
            printf("������Ҫ����������û�ID: ");
            scanf_s("%d", &targetUserId);
            fflush(stdin);
            ResetUserPassword(targetUserId, account->id);
            break;
        }
        case 3:
            ChangeAccountName(account);
            break;
        case 4:
        {
            int targetUserId;
            printf("������Ҫ�޸��û������û�ID: ");
            scanf_s("%d", &targetUserId);
            fflush(stdin);
            AdminChangeUsername(account->id, targetUserId);
            break;
        }
        case 5:
            BackupSystemData(account->id);
            break;
        case 6:
			RestoreSystemData(account->id);
			break;
        case 0:
            exit = true;
            break;

        default:
            printf("��Ч��ѡ��������\n");
            break;
        }
        system("pause");
    }
}

// ϵͳά�����˵����û�/ʵ��Ա��
void USystemMaintenance(Account* account)
{
    int choice;
    bool exit = false;

    while (!exit) {
        system("cls");
        printf("\n=== ϵͳά���˵� ===\n");
        printf("1. �޸�����\n");
        printf("2.�޸��û���\n");
        printf("0. ����\n");
        printf("��ѡ��: ");

        scanf_s("%d", &choice);
        fflush(stdin);

        system("cls");
        switch (choice) {
        case 1:
            ChangePassword(account);
            break;
        case 2:
            ChangeAccountName(account);
            break;
        case 0:
            exit = true;
            break;

        default:
            printf("��Ч��ѡ��������\n");
            break;
        }
        system("pause");
    }
}
// ��¼ϵͳ������־
bool LogSystemOperation(const char* operation, int userId)
{
    FILE* fp;
    fopen_s(&fp,"system_log.txt", "a");
    if (fp == NULL)
    {
        printf("�޷�����־�ļ�\n");
        return false;
    }

    time_t now;
    time(&now);
    char time[26];
    ctime_s(time, sizeof(time), &now);
    time[24] = '\0'; //ctime�������Զ������з������������Ƴ����з�

    Account* account = FindById(userId);
    const char* username = account ? account->user_name : "δ֪�û�";

    fprintf(fp, "[%s] �û�: %s (ID: %d) ����: %s\n",
        time, username, userId, operation);

    fclose(fp);
    return true;
}

// �޸��Լ����û���
bool ChangeAccountName(Account* account)
{
    char newUsername[USER_NMAE_LENGTH];
    char password[USER_PASSWORD_LENGTH];

    printf("�޸��û�����Ҫ��֤�������\n");
    printf("�����뵱ǰ����: ");
    scanf_s("%s", password, USER_PASSWORD_LENGTH);
    fflush(stdin);

    // ��֤����
    if (strcmp(account->user_password, password) != 0) {
        printf("��������޷��޸��û���\n");
        return False;
    }

    printf("\n--- �޸��û��� ---\n");
    printf("��ǰ�û���: %s\n", account->user_name);
    printf("�û���Ҫ��4-12���ַ���ֻ�ܰ�����ĸ������\n");
    printf("���������û���: ");
    scanf_s("%s", newUsername, USER_NMAE_LENGTH);
    fflush(stdin);
    // ���ݾ��û����Ա��¼
    char oldUsername[USER_NMAE_LENGTH];
    strcpy_s(oldUsername, USER_NMAE_LENGTH, account->user_name);

    ChangeUsername(account, newUsername);

    printf("�û����޸ĳɹ����� '%s' �޸�Ϊ '%s'\n", oldUsername, newUsername);

    char operation[100];
    snprintf(operation, 100, "�û����޸�: %s -> %s", oldUsername, newUsername);
    LogSystemOperation(operation, account->id);

    return True;
}

// ����Ա�޸��û����û���
bool AdminChangeUsername(int adminId, int targetUserId)
{
    Account* targetAccount = FindById(targetUserId);
    if (targetAccount == NULL) {
        printf("Ŀ���û�������\n");
        return False;
    }

    printf("\n--- ����Ա�޸��û��� ---\n");
    printf("Ŀ���û�: %s (ID: %d)\n", targetAccount->user_name, targetUserId);
    printf("��ǰ�û���: %s\n", targetAccount->user_name);
    printf("�û���Ҫ��4-12���ַ���ֻ�ܰ�����ĸ������\n\n");

    char newUsername[USER_NMAE_LENGTH];
    printf("���������û���: ");
    scanf_s("%s", newUsername, USER_NMAE_LENGTH);
    fflush(stdin);

    // ���ݾ��û����Ա��¼
    char oldUsername[USER_NMAE_LENGTH];
    strcpy_s(oldUsername, USER_NMAE_LENGTH, targetAccount->user_name);

    ChangeUsername(targetAccount, newUsername);

    printf("�û����޸ĳɹ����� '%s' �޸�Ϊ '%s'\n", oldUsername, newUsername);

    char operation[100];
    snprintf(operation, 100, "�û����޸�: %s -> %s", oldUsername, newUsername);
    LogSystemOperation(operation, adminId);

    return True;
}

// �޸��Լ�������
bool ChangePassword(Account* account) {
    char currentPassword[USER_PASSWORD_LENGTH];
    char newPassword[USER_PASSWORD_LENGTH];
    char confirmPassword[USER_PASSWORD_LENGTH];

    printf("��������ԭ����\n");
    scanf_s("%s", currentPassword, USER_PASSWORD_LENGTH);
    fflush(stdin);
    Account testaccount;
    strcpy_s(testaccount.user_name, USER_NMAE_LENGTH, account->user_name);
    strcpy_s(testaccount.user_password, USER_PASSWORD_LENGTH, currentPassword);
    if (!IsCorrectAccount(&testaccount)) {
        return false;
    }
    printf("\n--- �޸����� ---\n");
    DisplayPasswordRules();
    scanf_s("%s", newPassword, USER_PASSWORD_LENGTH);
    fflush(stdin);

    if (!IsValidPassword(newPassword)) {
        return false;
    }

    printf("��ȷ��������: ");
    scanf_s("%s", confirmPassword, USER_PASSWORD_LENGTH);
    fflush(stdin);

    if (strcmp(newPassword, confirmPassword) != 0) {
        printf("������������벻һ��\n");
        return false;
    }

    strcpy_s(account->user_password, USER_PASSWORD_LENGTH, newPassword);
    printf("�����޸ĳɹ�\n");

    char operation[20];
    switch (account->account_type)
    {
    case Admin:
        strcpy_s(operation, 20, "�޸Ĺ���Ա����");
    case User:
        strcpy_s(operation, 20, "�޸�һ���û�����");
    case Experimenter:
        strcpy_s(operation, 20, "�޸�ʵ��Ա����");
    }
    LogSystemOperation(operation, account->id);
    return true;
}

// �����û���ʵ��Ա����
bool ResetUserPassword(int targetUserId, int adminId) {
    Account* targetAccount = FindById(targetUserId);
    if (targetAccount == NULL) {
        printf("Ŀ���û�������\n");
        return false;
    }

    // ����Ĭ�����루�û��� + "12345"��
    char defaultPassword[USER_PASSWORD_LENGTH];
    //��ѧ���ĺ���snprintf
    snprintf(defaultPassword, USER_PASSWORD_LENGTH, "%s12345", targetAccount->user_name);

    if (strlen(defaultPassword) < MIN_PASSWORD_LENGTH) {
        strcat_s(defaultPassword, USER_PASSWORD_LENGTH, "additional");
    }

    strcpy_s(targetAccount->user_password, USER_PASSWORD_LENGTH, defaultPassword);

    printf("�ѽ��û� %s (ID: %d) ����������Ϊ: %s\n",
        targetAccount->user_name, targetUserId, defaultPassword);

    LogSystemOperation("�����û�����", adminId);
    return true;
}

bool BackupSystemData(int adminId)
{
    //����backup�ļ���
    system("if not exist backups mkdir backups");
    //�н���ǰ�ӱ����ļ���
    time_t now;
    time(&now);
    char time[26];
    ctime_s(time, sizeof(time), &now);
    time[24] = '\0'; //ctime�������Զ������з������������Ƴ����з�

    char backupDir[100];
    char mkdirCmd[150];
    char formattedTime[30];
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);
    strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d_%H-%M-%S", &timeinfo);

    // ʹ�ø�ʽ�����ʱ�䴴��Ŀ¼��
    sprintf_s(backupDir, sizeof(backupDir), "backups\\%s", formattedTime);
    sprintf_s(mkdirCmd, sizeof(mkdirCmd), "mkdir %s", backupDir);

    system(mkdirCmd);
    char path[100];
    // ��������ͷ�ļ���������readme
    SaveBackUp(time,formattedTime);
    snprintf(path, 100, "backups/%s/account.txt", formattedTime);
    SaveAccountList(path);
    snprintf(path, 100, "backups/%s/category.txt", formattedTime);
    SaveCategoryList(path);
    snprintf(path, 100, "backups/%s/equipment.txt", formattedTime);
    SaveEquipmentList(path);
    snprintf(path, 100, "backups/%s/laboratory.txt", formattedTime);
    SaveLaboratoryList(path);
    LogSystemOperation("ϵͳ����", adminId);

    printf("ϵͳ���ݱ�����ɣ�������: %s\n", backupDir);

    return True;
}

// �ָ�ϵͳ����
bool RestoreSystemData(int adminId)
{
    char confirmInput;
    printf("���棺�ָ����������ǵ�ǰ�������ݣ�������(Y/N): ");
    printf("���鱸�ݵ�ǰ�ڵ�����\n");
    scanf_s("%c", &confirmInput, 1);
    getchar();

    if (confirmInput != 'Y' && confirmInput != 'y') {
        printf("��ȡ���ָ�����\n");
        return false;
    }
    
    printf("������Ҫ�ָ����Ľ��ʱ��/�ļ�����\n");
    char formattedtime[50];
    scanf_s("%s", formattedtime,100);
    fflush(stdin);
    char operation[50];
	snprintf(operation, sizeof(operation), "ϵͳ���ݻָ���%s", formattedtime);
    LogSystemOperation(operation, adminId);
    DestoryResourceManage();
    char path[100];
    snprintf(path, sizeof(path), "backups/%s/account.txt", formattedtime);
    LoadAccountList(path);
    snprintf(path, sizeof(path), "backups/%s/category.txt", formattedtime);
    LoadCategoryList(path);
    snprintf(path, sizeof(path), "backups/%s/equipment.txt", formattedtime);
    LoadEquipmentList(path);
    snprintf(path, sizeof(path), "backups/%s/laboratory.txt", formattedtime);
    LoadLaboratoryList(path);
    reLordAccountList;
    SaveResource();
    printf("ϵͳ���ݻָ��ɹ�\n");
    printf("�����ر�ϵͳ�����ֶ�����\n");

	system("pause");
    exit(0);
    return true;
}
