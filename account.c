#include <ctype.h>
#include <string.h>
#include "resource_manager.h"
#include "account.h"



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

