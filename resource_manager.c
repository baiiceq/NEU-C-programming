#include "resource_manager.h"
#include "account.h"
#include "category.h"
#include "experimental_equipment.h"
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
		instance->category_list = CreateLinkedList();
    }

    return instance;
}

void LoadResource()
{
	LoadAccountList();
	LoadCategoryList();
	LoadEquipmentList();
	LoadLaboratoryList();
	reLordAccountList();
}

void SaveResource()
{
	char path[100];
	strcpy_s(path,100, "account.txt");
	SaveAccountList(path);
	strcpy_s(path,100, "category.txt");
	SaveCategoryList(path);
	strcpy_s(path, 100, "equipment.txt");
	SaveEquipmentList(path);
	strcpy_s(path, 100,"laboratory.txt");
	SaveLaboratoryList(path);
}

void DestoryResourceManage()
{
    if (instance == NULL)
        return;

    destoryLinkedList(instance->account_list);
    destoryLinkedList(instance->equipment_list);
    destoryLinkedList(instance->laboratory_list);
}

bool LoadAccountList()
{
	FILE* fp = fopen("account.txt", "r");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		return False;
	}
	ResourceManager* resource_manager = GetResourceManage();
	while (!feof(fp))
	{
		Account* account = CreateAccount();
		char str[15]="";
		if (account == NULL)
		{
			printf("内存分配失败\n");
			return False;
		}
		fscanf_s(fp, "%d %s %s %s %d\n",&account->id, str,15, account->user_name, 
			USER_NMAE_LENGTH, account->user_password, USER_PASSWORD_LENGTH,&account->roomid);

		str[strlen(str)] = '\0';
		account->user_name[strlen(account->user_name)] = '\0';
		account->user_password[strlen(account->user_password)] = '\0';

		if (strcmp(str, "Admin") == 0)
			account->account_type = Admin;
		else if (strcmp(str, "Experimenter") == 0)
			account->account_type = Experimenter;
		else if (strcmp(str, "User") == 0)
			account->account_type = User;

		LinkedList_pushback(resource_manager->account_list, account);
	}   
	fclose(fp);
	return True;
}

bool SaveAccountList(char* path)
{
	FILE* fp = fopen(path, "w");
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
		fprintf(fp, "%d %s %s %s %d\n", account->id,str, account->user_name,
			account->user_password,account->roomid);
		temp = temp->next;
	}
	fclose(fp);
	return True;
}

bool LoadEquipmentList()
{
	FILE* fp = fopen("equipment.txt", "r");
	if (fp == NULL) 
	{
		printf("打开文件失败\n");
		return False;
	}
	ResourceManager* resource_manager = GetResourceManage();
	int category_id = 0;

	//此处如果是用feof读取空文件将会非常危险，后面相似的地方也是
	while (!feof(fp))
	{
		ExperimentalEquipment* eq = (ExperimentalEquipment*)malloc(sizeof(ExperimentalEquipment));
		if (eq == NULL)
		{
			printf("内存分配失败\n");
			fclose(fp);
			return False;
		}
		char str[15] = "";
		fscanf_s(fp, "%d %d ", &eq->id, &category_id);
		fscanf_s(fp, "%s ", eq->name, EQUIPMENT_LENGTH);
		fscanf_s(fp, "%d %d ", &eq->room_id, &eq->price);
		fscanf_s(fp, "%s ", eq->purchase_date, DATE_LENGTH);
		fscanf_s(fp, "%s\n", str, 15);
		eq->name[strlen(eq->name)] = '\0';
		eq->purchase_date[strlen(eq->purchase_date)] = '\0';

		if (category_id == -1)
			eq->category = NULL;
		else
			eq->category = FindCategoryById(category_id);

		if (strcmp(str, "Using") == 0)
			eq->state = Using;
		else if (strcmp(str, "Idle") == 0)
			eq->state = Idle;
		else if (strcmp(str, "Scrapped") == 0)
			eq->state = Scrapped;
		else if (strcmp(str, "Damaged") == 0)
			eq->state = Damaged;
		else if (strcmp(str, "Lost") == 0)
			eq->state = Lost;
		else if (strcmp(str, "Repairing") == 0)
			eq->state = Repairing;

		LinkedList_pushback(resource_manager->equipment_list, eq);
	}
	fclose(fp);
	return False;
}

bool SaveEquipmentList(char* path)
{
	FILE* fp = fopen(path, "w");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		return False;
	}
	Node* temp = GetResourceManage()->equipment_list->head->next;
	while (temp)
	{
		ExperimentalEquipment* eq = (ExperimentalEquipment*)temp->data;
		fprintf(fp, "%d %d %s %d %d %s ", eq->id, eq->category->id, eq->name,
			eq->room_id, eq->price, eq->purchase_date);
		char str[15] = "";
		if (eq->state == Using)
			strcpy_s(str, 15, "Using");
		else if (eq->state == Idle)
			strcpy_s(str, 15, "Idle");
		else if (eq->state == Scrapped)
			strcpy_s(str, 15, "Scrapped");
		else if (eq->state == Damaged)
			strcpy_s(str, 15, "Damaged");
		else if (eq->state == Lost)
			strcpy_s(str, 15, "Lost");
		else if (eq->state == Repairing)
			strcpy_s(str, 15, "Repairing");
		fprintf(fp, "%s\n", str);
		temp = temp->next;
	}
	fclose(fp);
	return False;
}

bool LoadCategoryList()
{
	FILE* fp = fopen("category.txt", "r");
	if (fp == NULL)
	{
		perror("文件打开失败\n");
		return False;
	}
	ResourceManager* resource_manager = GetResourceManage();
	while (!feof(fp))
	{
		Category* category = (Category*)malloc(sizeof(Category));
		if (category == NULL)
		{
			printf("内存分配失败\n");
			fclose(fp);
			return False;
		}
		fscanf_s(fp, "%d %s %d\n", &category->id,  category->name,CATEGORY_LENGTH, 
			&category->disposal_years);
		category->name[strlen(category->name)] = '\0';
		LinkedList_pushback(resource_manager->category_list, category);
	}
	fclose(fp);
	return False;
}

bool SaveCategoryList(char* path)
{
	FILE* fp = fopen(path, "w");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		return False;
	}
	Node* temp = GetResourceManage()->category_list->head->next;
	while (temp)
	{
		Category* category = (Category*)temp->data;
		fprintf(fp, "%d %s %d\n", category->id, category->name, category->disposal_years);
		temp = temp->next;
	}
	fclose(fp);
	return False;
}

bool LoadLaboratoryList()
{
	FILE* fp = fopen("laboratory.txt", "r");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		return False;
	}
	ResourceManager* resource_manager = GetResourceManage();
	char delim[] = ",";
	while (!feof(fp))
	{
		LabRoom* laboratory = (LabRoom*)malloc(sizeof(LabRoom));
		if (laboratory == NULL)
		{
			printf("内存分配失败\n");
			fclose(fp);
			return False;
		}
		char str1[LABROOM_LENGTH] = "";
		char str2[LABRROM_LINKEDLIST_LENGTH] = "";
		fscanf_s(fp, "%d %s %s %s\n", &laboratory->id, laboratory->name, LABROOM_LENGTH,
			str1, LABROOM_LENGTH, str2, LABRROM_LINKEDLIST_LENGTH);
		laboratory->name[strlen(laboratory->name)] = '\0';
		//按逗号分割字符串
		
		laboratory->technician_id_list = CreateLinkedList();
		char* token=NULL;
		char* context = NULL;
		if (!strcmp(str1, "-1,") == 0)
		{
			token = strtok_s(str1, delim, &context);
			while (token)
			{
				int id = atoi(token);
				Account* tech = FindById(id);
				LinkedList_pushback(laboratory->technician_id_list, &tech->id);
				token = strtok_s(NULL, delim, &context);
			}
		}
		laboratory->equipments_list = CreateLinkedList();
		if (!strcmp(str2, "-1,") == 0)
		{
			context = NULL;
			token = strtok_s(str2, delim, &context);
			while (token)
			{
				int id = atoi(token);
				ExperimentalEquipment* eq = (ExperimentalEquipment*)(EFindById(GetResourceManage()->equipment_list, id)
					->head->next->data);
				LinkedList_pushback(laboratory->equipments_list, &eq->id);
				token = strtok_s(NULL, delim, &context);
			}
		}
		LinkedList_pushback(resource_manager->laboratory_list, laboratory);
	}
	fclose(fp);
	return False;
}

bool SaveLaboratoryList(char* path)
{
	FILE* fp = fopen(path, "w");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		return False;
	}
	Node* temp = GetResourceManage()->laboratory_list->head->next;
	while (temp)
	{
		LabRoom* laboratory = (LabRoom*)temp->data;
		fprintf(fp, "%d %s ", laboratory->id, laboratory->name);
		Node* temp1 = laboratory->technician_id_list->head->next;
		if (temp1 == NULL)
			fprintf(fp,"-1,");
		else
		{
			while (temp1)
			{
				int* id = (int*)temp1->data;
				fprintf(fp, "%d,", *id);
				temp1 = temp1->next;
			}
		}
		fprintf(fp, " ");
		temp1 = laboratory->equipments_list->head->next;
		if(temp1==NULL)
			fprintf(fp, "-1,");
		else 
		{
			while (temp1)
			{
				int* id = (int*)temp1->data;
				fprintf(fp, "%d,", *id);
				temp1 = temp1->next;
			}
		}
		fprintf(fp, "\n");
		temp = temp->next;
	}
	fclose(fp);
	return False;
}

//加载account中的equipment_id_list
bool reLordAccountList()
{
	Node* temp = GetResourceManage()->account_list->head->next;
	while (temp)
	{
		Account* account = (Account*)temp->data;
		if (account->roomid == -1)
		{
			account->equipment_id_list = CreateLinkedList();
		}
		else
		{
			LabRoom* labroom = RoomId_to_LabRoom(account->roomid);
			account->equipment_id_list = labroom->equipments_list;
		}
		temp = temp->next;
	}
}

//备份文件
bool SaveBackUp(char* time,char* formattedTime)
{
	char str[100];
	snprintf(str, 100, "backups/%s/readme.txt", formattedTime);
	FILE* fp = fopen(str, "w");
	if(fp==NULL)
	{
		printf("文件打开失败\n");
		return False;
	}
	fprintf(fp, "=== 系统备份信息 ===\n");
	fprintf(fp, "备份时间%s\n",time);
	ResourceManager* rm = GetResourceManage();
	fprintf(fp, "账户数据备份共 %zu 条记录\n", rm->account_list->size);
	fprintf(fp, "设备数据备份共 %zu 条记录\n", rm->equipment_list->size);
	fprintf(fp, "设备类别数据备份共 %zu 条记录\n",rm->category_list->size);
	fprintf(fp, "实验室数据备份共 %zu 条记录\n", rm->laboratory_list->size);
	fclose(fp);
}