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

    while (1)
    {
        system("cls");
        printf("---            账户信息修改菜单         ---\n");
        printf("当前账户信息：\n");
        printf("ID: %d\n", account->id);
        /*printf("用户名: %s\n", account->user_name);*/
        printf("账户类型: %s\n", account->account_type == Admin ? "管理员" :
            (account->account_type == Experimenter ? "实验员" : "普通用户"));
        printf("所属实验室: %d(-1表示无所属实验室)\n", account->roomid);
        printf("\n");
        /*printf("---            1. 修改用户名               ---\n");
        printf("---            2. 修改密码                 ---\n");*/
        printf("---            1. 修改账户类型             ---\n");
        printf("---            2. 修改所属实验室           ---\n");
        printf("---            0. 退出                    ---\n");
        printf("--- 选择->");

        int option = 0;
        scanf_s("%d", &option);
        getchar(); // 清除缓冲区

        bool result = False;
        switch (option)
        {
        /*case 1:
        {
            printf("请输入新的用户名（4-12个字符，只能包含字母和数字）：\n");
            printf("(直接回车可跳过修改)\n");
            char new_username[USER_NMAE_LENGTH] = "";
            fgets(new_username, USER_NMAE_LENGTH, stdin);

            result = ChangeUsername(account, new_username);
            break;
        }
        case 2:
        {
            printf("请输入新的密码（8-20个字符，可包含字母、数字和@+?符号）：\n");
            printf("(直接回车可跳过修改)\n");
            char new_password[USER_PASSWORD_LENGTH] = "";
            fgets(new_password, USER_PASSWORD_LENGTH, stdin);

            result = ChangePassword(account, new_password);
            break;
        }*/
        case 1:
        {
            printf("请选择新的账户类型：\n");
            printf("1. 管理员\n");
            printf("2. 实验员\n");
            printf("3. 普通用户\n");
            printf("(输入0可跳过修改)\n");
            printf("请选择 -> ");

			int type = 0;
			scanf_s("%d", &type);
			getchar(); 
            result = ChangeAccountType(account, type);
            break;
        }
        case 2:
        {
			if (account->account_type !=Experimenter)
			{
				printf("当前账户类型不具有实验室隶属属性\n");
				result = False;
				break;
			}
            printf("请输入新的实验室ID（输入-1表示不属于任何实验室）：\n");
            printf("(直接回车可跳过修改)\n");
			int room_id = 0;
			scanf_s("%d", &room_id);
            getchar();
            result = ChangeAccountLab(account, room_id);
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

// 修改用户名
bool ChangeUsername(Account* account, char* new_username)
{
    // 如果输入为空，表示跳过修改
    if (strcmp(new_username,"\n") == 0)
        return True;

    new_username[strcspn(new_username, "\n")] = '\0';

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
    if (strcmp(new_password, "\n") == 0)
        return True;

    new_password[strcspn(new_password, "\n")] = '\0';

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
    if (room_id == 0)
        return True;

    LabRoom* old_lab = RoomId_to_LabRoom(account->roomid);
    if (old_lab != NULL)
        DeleteTechnician(old_lab, account->id);

    if (room_id != -1)
    {
        LabRoom* lab = RoomId_to_LabRoom(room_id);
        if (lab == NULL)
        {
            printf("指定的实验室不存在\n");
            return False;
        }
        //添加到新实验室
        LinkedList_pushback(lab->technician_id_list, &account->id);

        //同时修改管理的设备链表
        account->equipment_id_list = lab->equipments_list;
    }

    account->roomid = room_id;
    
    printf("实验室归属修改成功\n");
    return True;
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

