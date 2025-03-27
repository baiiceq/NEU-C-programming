#include <ctype.h>
#include <string.h>
#include "resource_manager.h"
#include "account.h"
#include "experimental_equipment.h"



Account* CreateAccount()
{
	Account* new_account = (Account*)malloc(sizeof(Account));
	if (new_account == NULL)
	{
		printf("账户创建失败！\n");
		return NULL;
	}
	return new_account;
}

void DestoryAccount(Account* account)
{
	free(account);
}

// 修改用户名
bool ChangeUsername(Account* account, char* new_username)
{
    // 如果输入为空，表示跳过修改
    if (strlen(new_username) == 0)
        return True;

    if (!IsValidUsername(new_username))
    {
        printf("用户名不合法\n");
        return False;
    }

    Account* existing = FindByUsername(new_username);
    if (existing != NULL && existing != account)
    {
        printf("用户名已存在\n");
        return False;
    }

    strcpy_s(account->user_name, USER_NMAE_LENGTH, new_username);
    printf("用户名修改成功\n");
    return True;
}

// 修改密码
bool ChangePassword(Account* account, char* new_password)
{
    // 如果输入为空，表示跳过修改
    if (strlen(new_password) == 0)
        return True;

    if (!IsValidPassword(new_password))
    {
        printf("密码不合法\n");
        return False;
    }

    strcpy_s(account->user_password, USER_PASSWORD_LENGTH, new_password);
    printf("密码修改成功\n");
    return True;
}

// 修改账户类型
bool ChangeAccountType(Account* account, int type)
{
    // 如果输入为0，表示跳过修改
    if (type == 0)
        return True;

    switch (type)
    {
    case 1:
        account->account_type = Admin;
        break;
    case 2:
        account->account_type = Experimenter;
        break;
    case 3:
        account->account_type = User;
        break;
    default:
        printf("无效的账户类型\n");
        return False;
    }

    printf("账户类型修改成功\n");
    return True;
}

// 修改账户所属实验室
bool ChangeAccountLab(Account* account, int room_id)
{
    // 特殊值表示跳过
    if (room_id == -9999) // 使用一个不太可能出现的值作为"跳过"标记
        return True;

    if (room_id != -1)
    {
        // 验证实验室是否存在
        LabRoom* lab = RoomId_to_LabRoom(room_id);
        if (lab == NULL)
        {
            printf("指定的实验室不存在\n");
            return False;
        }

        // 如果原来属于其他实验室，需要从旧实验室移除
        if (account->roomid != -1 && account->roomid != room_id)
        {
            LabRoom* old_lab = RoomId_to_LabRoom(account->roomid);
            if (old_lab != NULL)
            {
                DeleteTechnician(old_lab, account->id);
            }
        }

        // 添加到新实验室
        LinkedList_pushback(lab->technician_id_list, &account->id);
    }

    account->roomid = room_id;
    printf("实验室归属修改成功\n");
    return True;
}



// 显示账户所管理的所有设备
void DisplayAccountEquipments(Account* account)
{
    if (account->equipment_id_list == NULL || account->equipment_id_list->head->next == NULL)
    {
        printf("该账户当前未管理任何设备\n");
        return;
    }

    printf("当前管理的设备ID列表：\n");
    Node* temp = account->equipment_id_list->head->next;
    int count = 0;
    while (temp)
    {
        int* eq_id = (int*)temp->data;
        printf("设备ID: %d", *eq_id);

        // 尝试获取设备名称
        ExperimentalEquipment* eq = NULL;
        Node* eq_node = GetResourceManage()->equipment_list->head->next;
        while (eq_node)
        {
            ExperimentalEquipment* cur_eq = (ExperimentalEquipment*)eq_node->data;
            if (cur_eq->id == *eq_id)
            {
                eq = cur_eq;
                break;
            }
            eq_node = eq_node->next;
        }

        if (eq != NULL)
        {
            printf(" (名称: %s)\n", eq->name);
        }
        else
        {
            printf(" (设备信息不可用)\n");
        }

        temp = temp->next;
        count++;
    }
    printf("共管理 %d 台设备\n", count);
}

// 向账户添加管理设备
bool AddEquipmentToAccount(Account* account, int equipment_id)
{
    // 检查设备是否存在
    bool found = False;
    Node* eq_node = GetResourceManage()->equipment_list->head->next;
    while (eq_node)
    {
        ExperimentalEquipment* eq = (ExperimentalEquipment*)eq_node->data;
        if (eq->id == equipment_id)
        {
            found = True;
            break;
        }
        eq_node = eq_node->next;
    }

    if (!found)
    {
        printf("指定的设备ID不存在\n");
        return False;
    }

    // 检查是否已经在管理列表中
    Node* temp = account->equipment_id_list->head->next;
    while (temp)
    {
        int* id = (int*)temp->data;
        if (*id == equipment_id)
        {
            printf("该设备已在管理列表中\n");
            return False;
        }
        temp = temp->next;
    }

    // 添加设备ID到管理列表
    int* new_id = (int*)malloc(sizeof(int));
    if (new_id == NULL)
    {
        printf("内存分配失败\n");
        return False;
    }

    *new_id = equipment_id;
    LinkedList_pushback(account->equipment_id_list, new_id);
    printf("设备ID: %d 已添加到管理列表\n", equipment_id);
    return True;
}

// 从账户移除管理设备
bool RemoveEquipmentFromAccount(Account* account, int equipment_id)
{
    if (account->equipment_id_list == NULL || account->equipment_id_list->head->next == NULL)
    {
        printf("该账户当前未管理任何设备\n");
        return False;
    }

    Node* prev = account->equipment_id_list->head;
    Node* current = prev->next;

    while (current)
    {
        int* id = (int*)current->data;
        if (*id == equipment_id)
        {
            // 找到设备ID，从链表中移除
            prev->next = current->next;
            free(current->data); // 释放存储ID的内存
            free(current);       // 释放节点内存
            printf("设备ID: %d 已从管理列表中移除\n", equipment_id);
            return True;
        }
        prev = current;
        current = current->next;
    }

    printf("该账户的管理列表中未找到设备ID: %d\n", equipment_id);
    return False;
}

// 修改账户管理的设备
bool ChangeAccountEquipments(Account* account)
{
    while (1)
    {
        system("cls");
        printf("---          账户管理设备修改菜单       ---\n");
        DisplayAccountEquipments(account);
        printf("\n");
        printf("---          1. 添加管理设备            ---\n");
        printf("---          2. 移除管理设备            ---\n");
        printf("---          0. 返回上级菜单            ---\n");
        printf("--- 选择->");

        int option = 0;
        scanf_s("%d", &option);
        getchar(); // 清除缓冲区

        switch (option)
        {
        case 1:
        {
            printf("请输入要添加到管理列表的设备ID (输入0取消)：\n");
            char input[10] = "";
            fgets(input, 10, stdin);

            if (input[0] == '\n' || strcmp(input, "0\n") == 0)
            {
                printf("已取消添加\n");
            }
            else
            {
                int equipment_id = atoi(input);
                AddEquipmentToAccount(account, equipment_id);
            }
            break;
        }
        case 2:
        {
            printf("请输入要从管理列表中移除的设备ID (输入0取消)：\n");
            char input[10] = "";
            fgets(input, 10, stdin);

            if (input[0] == '\n' || strcmp(input, "0\n") == 0)
            {
                printf("已取消移除\n");
            }
            else
            {
                int equipment_id = atoi(input);
                RemoveEquipmentFromAccount(account, equipment_id);
            }
            break;
        }
        case 0:
            return True;
        default:
            printf("无效的选择\n");
            break;
        }

        system("pause");
    }

    return True;
}

// 修改后的主修改函数，增加了管理设备的选项
void ChangeAccount()
{
    int account_id;
    printf("请输入要修改的账户ID：\n");
    scanf_s("%d", &account_id);
    getchar(); // 清除缓冲区

    Account* account = FindById(account_id);
    if (account == NULL)
    {
        printf("该账户不存在\n");
        return;
    }

    // 确保equipment_id_list已初始化
    if (account->equipment_id_list == NULL)
    {
        account->equipment_id_list = CreateLinkedList();
    }

    while (1)
    {
        system("cls");
        printf("---            账户信息修改菜单         ---\n");
        printf("当前账户信息：\n");
        printf("ID: %d\n", account->id);
        printf("用户名: %s\n", account->user_name);
        printf("账户类型: %s\n", account->account_type == Admin ? "管理员" :
            (account->account_type == Experimenter ? "实验员" : "普通用户"));
        printf("所属实验室: %d\n", account->roomid);
        printf("\n");
        printf("---            1. 修改用户名               ---\n");
        printf("---            2. 修改密码                 ---\n");
        printf("---            3. 修改账户类型             ---\n");
        printf("---            4. 修改所属实验室           ---\n");
        printf("---            5. 修改管理设备列表         ---\n");
        printf("---            0. 退出                    ---\n");
        printf("--- 选择->");

        int option = 0;
        scanf_s("%d", &option);
        getchar(); // 清除缓冲区

        bool result = False;
        switch (option)
        {
        case 1:
        {
            printf("请输入新的用户名（4-12个字符，只能包含字母和数字）：\n");
            printf("(直接回车可跳过修改)\n");
            char new_username[USER_NMAE_LENGTH] = "";
            fgets(new_username, USER_NMAE_LENGTH, stdin);

            // 移除可能的换行符
            int len = strlen(new_username);
            if (len > 0 && new_username[len - 1] == '\n')
                new_username[len - 1] = '\0';

            result = ChangeUsername(account, new_username);
            break;
        }
        case 2:
        {
            printf("请输入新的密码（8-20个字符，可包含字母、数字和@+?符号）：\n");
            printf("(直接回车可跳过修改)\n");
            char new_password[USER_PASSWORD_LENGTH] = "";
            fgets(new_password, USER_PASSWORD_LENGTH, stdin);

            // 移除可能的换行符
            int len = strlen(new_password);
            if (len > 0 && new_password[len - 1] == '\n')
                new_password[len - 1] = '\0';

            result = ChangePassword(account, new_password);
            break;
        }
        case 3:
        {
            printf("请选择新的账户类型：\n");
            printf("1. 管理员\n");
            printf("2. 实验员\n");
            printf("3. 普通用户\n");
            printf("(输入0可跳过修改)\n");
            printf("请选择 -> ");

            char input[10] = "";
            fgets(input, 10, stdin);

            if (input[0] == '\n') {
                result = True; // 直接回车跳过
            }
            else {
                int type = atoi(input);
                result = ChangeAccountType(account, type);
            }
            break;
        }
        case 4:
        {
            printf("当前所属实验室ID: %d\n", account->roomid);
            printf("请输入新的实验室ID（输入-1表示不属于任何实验室）：\n");
            printf("(直接回车可跳过修改)\n");

            char input[10] = "";
            fgets(input, 10, stdin);

            if (input[0] == '\n') {
                result = True; // 直接回车跳过
            }
            else {
                int room_id = atoi(input);
                result = ChangeAccountLab(account, room_id);
            }
            break;
        }
        case 5:
        {
            result = ChangeAccountEquipments(account);
            break;
        }
        case 0:
            return; // 直接返回，无需返回值
        default:
            printf("无效的选择\n");
            result = False;
            break;
        }

        if (result)
        {
            printf("操作完成\n");
        }
        else
        {
            printf("操作失败\n");
        }

        system("pause");
    }
}


bool ValidAccount(Account* account)
{
	if (!IsValidUsername(account->user_name))
	{
		printf("用户名不合法\n");
		return False;
	}
	if (FindByUsername(account->user_name))
	{
		printf("用户名已存在\n");
		return False;
	}
	if (!IsValidPassword(account->user_password))
	{
		printf("密码不合法\n");
		return False;
	}
	return True;
}

bool IsValidUsername(char* username)
{
	int count = 0;
	while (*username)
	{
		if (!isalnum(*username))
			return False;
		count++;
		if (count > 12)
			return False;
		username++;
	}
	if (count < 4)
		return False;
	return 1;
}

Account* FindByUsername(char* username)
{
	ResourceManager* resource_manager = GetResourceManage();

	Node* temp = resource_manager->account_list->head->next;
	while (temp)
	{
		Account* account = (Account*)temp->data;
		if (strcmp(account->user_name, username) == 0)
			return account;
		temp = temp->next;
	}	
	return NULL;
}
Account* FindById(int id)
{
	ResourceManager* resource_manager = GetResourceManage();
	Node* temp = resource_manager->account_list->head->next;
	while (temp)
	{
		Account* account = (Account*)temp->data;
		if (account->id == id)
			return account;
		temp = temp->next;
	}
	return NULL;
}

bool IsValidPassword(char* password)
{
	int count = 0;
	while (*password)
	{
		if (!(isalnum(*password)||*password=='@'||*password=='+'||*password=='?'))
			return False;
		count++;
		if (count > 20)
			return False;
		password++;
	}
	if (count <= 8)
		return False;
	return True;
}

bool IsCorrectAccount(Account* account)
{
	Account* temp = FindByUsername(account->user_name);
	if (temp == NULL)
	{
		printf("用户名不存在\n");
		return False;
	}
	if (strcmp(temp->user_password, account->user_password) != 0)
	{
		printf("密码错误\n");
		return False;
	}

	account->account_type = temp->account_type;
	return True;
}

