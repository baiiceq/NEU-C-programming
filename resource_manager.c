#include "resource_manager.h"
#include "account.h"
#include <string.h>

static ResourceManager* instance = NULL;

ResourceManager* GetResourceManage()
{
    if (instance == NULL)
    {
        instance = (ResourceManager*)malloc(sizeof(ResourceManager));
        if (instance == NULL)
        {
            printf("资源管理器加载失败");
            exit(-1);
        }
        instance->account_list = CreateLinkedList();
        instance->equipment_list = CreateLinkedList();
        instance->laboratory_list = CreateLinkedList();
    }

    return instance;
}

void DestoryResourceManage()
{
    if (instance == NULL)
        return;

    destoryLinkedList(instance->account_list);
    destoryLinkedList(instance->equipment_list);
    destoryLinkedList(instance->laboratory_list);
}

bool CreateAccountList()
{
	FILE* fp = fopen("account.txt", "r");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		return False;
	}
	while (!feof(fp))
	{
		Account* account = (Account*)malloc(sizeof(Account));
		char str[15]="";
		if (account == NULL)
		{
			printf("内存分配失败\n");
			return False;
		}
		fscanf_s(fp, "%s %s %s\n", str,15, account->user_name, USER_NMAE_LENGTH, account->user_password, USER_PASSWORD_LENGTH);
		str[strlen(str)] = '\0';
		if (strcmp(str, "Admin") == 0)
			account->account_type = Admin;
		else if (strcmp(str, "Experimenter") == 0)
			account->account_type = Experimenter;
		else if (strcmp(str, "user") == 0)
			account->account_type = User;
		LinkedList_pushback(GetResourceManage()->account_list, account);
	}   
	fclose(fp);
	return True;
}

bool SaveAccountList()
{
	FILE* fp = fopen("account.txt", "w");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		return False;
	}
	Node* temp = GetResourceManage()->account_list->head->next;
	char str[15]="";
	while (temp)
	{
		Account* account = (Account*)temp->data;
		if (account->account_type == Admin)
			strcpy_s(str,15, "Admin");
		else if (account->account_type == Experimenter)
			strcpy_s(str, 15,"Experimenter");
		else if (account->account_type == User)
			strcpy_s(str,15, "User");
		fprintf(fp, "%s %s %s\n", str, account->user_name, account->user_password);
		temp = temp->next;
	}
	fclose(fp);
	return True;
}