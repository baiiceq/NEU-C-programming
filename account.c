#include "account.h"
#include <ctype.h>
#include <string.h>
#include "resource_manager.h"


bool IsValidAccount(Account* account)
{
	if (!IsValidUsername(account->user_name))
	{
		printf("用户名不合法\n");
		return 0;
	}
	if (FindByUsername(account->user_name))
	{
		printf("用户名已存在\n");
		return 0;
	}
	if (!IsValidPassword(account->user_password))
	{
		printf("密码不合法\n");
		return 0;
	}
	return 1;
}

bool IsValidUsername(char* username)
{
	int count = 0;
	while (*username)
	{
		if (!isalnum(*username))
			return 0;
		count++;
		if (count > 12)
			return 0;
		username++;
	}
	if (count <= 4)
		return 0;
	return 1;
}

Account* FindByUsername(char* username)
{
	ResourceManager* instance = GetResourceManage();
	Node* temp = instance->account_list->head;
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
			return 0;
		count++;
		if (count > 20)
			return 0;
		password++;
	}
	if (count <= 8)
		return 0;
	return 1;
}
