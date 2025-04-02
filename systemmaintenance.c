#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "systemmaintenance.h"

// 系统维护主菜单（管理员）
void ASystemMaintenance(Account* account)
{
    int choice;
    bool exit = false;

    while (!exit) {
        system("cls");
        printf("\n=== 系统维护菜单（管理员）===\n");
        printf("1. 修改当前账户密码\n");
        printf("2. 重置用户/实验员密码\n");
        printf("3. 修改当前账户用户名\n");
        printf("4. 修改用户/实验员用户名\n");
        printf("5. 备份系统数据\n");
        printf("6. 恢复系统数据\n");
        printf("0. 返回\n");
        printf("请选择: ");

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
            printf("请输入要重置密码的用户ID: ");
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
            printf("请输入要修改用户名的用户ID: ");
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
            printf("无效的选择，请重试\n");
            break;
        }
        system("pause");
    }
}

// 系统维护主菜单（用户/实验员）
void USystemMaintenance(Account* account)
{
    int choice;
    bool exit = false;

    while (!exit) {
        system("cls");
        printf("\n=== 系统维护菜单 ===\n");
        printf("1. 修改密码\n");
        printf("2.修改用户名\n");
        printf("0. 返回\n");
        printf("请选择: ");

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
            printf("无效的选择，请重试\n");
            break;
        }
        system("pause");
    }
}
// 记录系统操作日志
bool LogSystemOperation(const char* operation, int userId)
{
    FILE* fp;
    fopen_s(&fp,"system_log.txt", "a");
    if (fp == NULL)
    {
        printf("无法打开日志文件\n");
        return false;
    }

    time_t now;
    time(&now);
    char time[26];
    ctime_s(time, sizeof(time), &now);
    time[24] = '\0'; //ctime函数会自动补换行符，所以这里移除换行符

    Account* account = FindById(userId);
    const char* username = account ? account->user_name : "未知用户";

    fprintf(fp, "[%s] 用户: %s (ID: %d) 操作: %s\n",
        time, username, userId, operation);

    fclose(fp);
    return true;
}

// 修改自己的用户名
bool ChangeAccountName(Account* account)
{
    char newUsername[USER_NMAE_LENGTH];
    char password[USER_PASSWORD_LENGTH];

    printf("修改用户名需要验证您的身份\n");
    printf("请输入当前密码: ");
    scanf_s("%s", password, USER_PASSWORD_LENGTH);
    fflush(stdin);

    // 验证密码
    if (strcmp(account->user_password, password) != 0) {
        printf("密码错误，无法修改用户名\n");
        return False;
    }

    printf("\n--- 修改用户名 ---\n");
    printf("当前用户名: %s\n", account->user_name);
    printf("用户名要求：4-12个字符，只能包含字母和数字\n");
    printf("请输入新用户名: ");
    scanf_s("%s", newUsername, USER_NMAE_LENGTH);
    fflush(stdin);
    // 备份旧用户名以便记录
    char oldUsername[USER_NMAE_LENGTH];
    strcpy_s(oldUsername, USER_NMAE_LENGTH, account->user_name);

    ChangeUsername(account, newUsername);

    printf("用户名修改成功，从 '%s' 修改为 '%s'\n", oldUsername, newUsername);

    char operation[100];
    snprintf(operation, 100, "用户名修改: %s -> %s", oldUsername, newUsername);
    LogSystemOperation(operation, account->id);

    return True;
}

// 管理员修改用户的用户名
bool AdminChangeUsername(int adminId, int targetUserId)
{
    Account* targetAccount = FindById(targetUserId);
    if (targetAccount == NULL) {
        printf("目标用户不存在\n");
        return False;
    }

    printf("\n--- 管理员修改用户名 ---\n");
    printf("目标用户: %s (ID: %d)\n", targetAccount->user_name, targetUserId);
    printf("当前用户名: %s\n", targetAccount->user_name);
    printf("用户名要求：4-12个字符，只能包含字母和数字\n\n");

    char newUsername[USER_NMAE_LENGTH];
    printf("请输入新用户名: ");
    scanf_s("%s", newUsername, USER_NMAE_LENGTH);
    fflush(stdin);

    // 备份旧用户名以便记录
    char oldUsername[USER_NMAE_LENGTH];
    strcpy_s(oldUsername, USER_NMAE_LENGTH, targetAccount->user_name);

    ChangeUsername(targetAccount, newUsername);

    printf("用户名修改成功，从 '%s' 修改为 '%s'\n", oldUsername, newUsername);

    char operation[100];
    snprintf(operation, 100, "用户名修改: %s -> %s", oldUsername, newUsername);
    LogSystemOperation(operation, adminId);

    return True;
}

// 修改自己的密码
bool ChangePassword(Account* account) {
    char currentPassword[USER_PASSWORD_LENGTH];
    char newPassword[USER_PASSWORD_LENGTH];
    char confirmPassword[USER_PASSWORD_LENGTH];

    printf("请先输入原密码\n");
    scanf_s("%s", currentPassword, USER_PASSWORD_LENGTH);
    fflush(stdin);
    Account testaccount;
    strcpy_s(testaccount.user_name, USER_NMAE_LENGTH, account->user_name);
    strcpy_s(testaccount.user_password, USER_PASSWORD_LENGTH, currentPassword);
    if (!IsCorrectAccount(&testaccount)) {
        return false;
    }
    printf("\n--- 修改密码 ---\n");
    DisplayPasswordRules();
    scanf_s("%s", newPassword, USER_PASSWORD_LENGTH);
    fflush(stdin);

    if (!IsValidPassword(newPassword)) {
        return false;
    }

    printf("请确认新密码: ");
    scanf_s("%s", confirmPassword, USER_PASSWORD_LENGTH);
    fflush(stdin);

    if (strcmp(newPassword, confirmPassword) != 0) {
        printf("两次输入的密码不一致\n");
        return false;
    }

    strcpy_s(account->user_password, USER_PASSWORD_LENGTH, newPassword);
    printf("密码修改成功\n");

    char operation[20];
    switch (account->account_type)
    {
    case Admin:
        strcpy_s(operation, 20, "修改管理员密码");
    case User:
        strcpy_s(operation, 20, "修改一般用户密码");
    case Experimenter:
        strcpy_s(operation, 20, "修改实验员密码");
    }
    LogSystemOperation(operation, account->id);
    return true;
}

// 重置用户或实验员密码
bool ResetUserPassword(int targetUserId, int adminId) {
    Account* targetAccount = FindById(targetUserId);
    if (targetAccount == NULL) {
        printf("目标用户不存在\n");
        return false;
    }

    // 生成默认密码（用户名 + "12345"）
    char defaultPassword[USER_PASSWORD_LENGTH];
    //新学到的函数snprintf
    snprintf(defaultPassword, USER_PASSWORD_LENGTH, "%s12345", targetAccount->user_name);

    if (strlen(defaultPassword) < MIN_PASSWORD_LENGTH) {
        strcat_s(defaultPassword, USER_PASSWORD_LENGTH, "additional");
    }

    strcpy_s(targetAccount->user_password, USER_PASSWORD_LENGTH, defaultPassword);

    printf("已将用户 %s (ID: %d) 的密码重置为: %s\n",
        targetAccount->user_name, targetUserId, defaultPassword);

    LogSystemOperation("重置用户密码", adminId);
    return true;
}

bool BackupSystemData(int adminId)
{
    //创建backup文件夹
    system("if not exist backups mkdir backups");
    //切进当前子备份文件夹
    time_t now;
    time(&now);
    char time[26];
    ctime_s(time, sizeof(time), &now);
    time[24] = '\0'; //ctime函数会自动补换行符，所以这里移除换行符

    char backupDir[100];
    char mkdirCmd[150];
    char formattedTime[30];
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);
    strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d_%H-%M-%S", &timeinfo);

    // 使用格式化后的时间创建目录名
    sprintf_s(backupDir, sizeof(backupDir), "backups\\%s", formattedTime);
    sprintf_s(mkdirCmd, sizeof(mkdirCmd), "mkdir %s", backupDir);

    system(mkdirCmd);
    char path[100];
    // 创建备份头文件，类似于readme
    SaveBackUp(time,formattedTime);
    snprintf(path, 100, "backups/%s/account.txt", formattedTime);
    SaveAccountList(path);
    snprintf(path, 100, "backups/%s/category.txt", formattedTime);
    SaveCategoryList(path);
    snprintf(path, 100, "backups/%s/equipment.txt", formattedTime);
    SaveEquipmentList(path);
    snprintf(path, 100, "backups/%s/laboratory.txt", formattedTime);
    SaveLaboratoryList(path);
    LogSystemOperation("系统备份", adminId);

    printf("系统数据备份完成，保存在: %s\n", backupDir);

    return True;
}

// 恢复系统数据
bool RestoreSystemData(int adminId)
{
    char confirmInput;
    printf("警告：恢复操作将覆盖当前所有数据！继续？(Y/N): ");
    printf("建议备份当前节点数据\n");
    scanf_s("%c", &confirmInput, 1);
    getchar();

    if (confirmInput != 'Y' && confirmInput != 'y') {
        printf("已取消恢复操作\n");
        return false;
    }
    
    printf("请输入要恢复至的结点时间/文件夹名\n");
    char formattedtime[50];
    scanf_s("%s", formattedtime,100);
    fflush(stdin);
    char operation[50];
	snprintf(operation, sizeof(operation), "系统数据恢复至%s", formattedtime);
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
    printf("系统数据恢复成功\n");
    printf("即将关闭系统，请手动重启\n");

	system("pause");
    exit(0);
    return true;
}
