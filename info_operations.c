#include "info_operations.h"

int ManageMenu()
{
	system("cls");

	printf("---         选择要进行的操作         ---\n");
	printf("---            1. 添加               ---\n");
	printf("---            2. 删除               ---\n");
	printf("---            3. 修改               ---\n");
	printf("---            0. 取消               ---\n");
	printf("--- 选择->");

	int option = 0;
	scanf_s("%d", &option);

	system("pause");

	return option;
}

void ManageExperimentalEquipment()
{
	int option = ManageMenu();
	switch (option)
	{
	case 0:
		return;
	case 1:
		AddExperimentalEquipment();
		break;
	case 2:
		printf("请输入要删除的设备ID：\n");
		int id;
		scanf_s("%d", &id);
		getchar();
		ExperimentalEquipment* ee = (ExperimentalEquipment*)EFindById(GetResourceManage()->equipment_list, id)->head->next->data;
		system("cls");
		printf("=== 删除设备确认 ===\n");
		printf("ID: %d\n", ee->id);
		printf("名称: %s\n", ee->name);
		printf("类别: %s\n", ee->category->name);
		printf("价格: %d\n", ee->price);
		printf("所属实验室ID: %d\n", ee->room_id);
		printf("购买日期: %s\n", ee->purchase_date);
		printf("\n警告: 删除操作不可逆! 确认删除? (Y/N): ");

		char confirm;
		scanf_s("%c", &confirm, 1);
		fflush(stdin);

		if (confirm != 'Y' && confirm != 'y') {
			printf("已取消删除操作\n");
			return ;
		}
		DeleteExperimentalEquipment(ee);
		break;
	case 3:
		ChangeExperimentalEquipment();
	default:
		break;
	}
}

void ManageAccount()
{
	int option = ManageMenu();
	switch (option)
	{
	case 0:
		return;
	case 1:
	{
		Account* account = AccountRegister();
		if (account == NULL)
		{
			printf("注册失败\n");
			system("pause");
			return;
		}

		// 储存新账户
		ResourceManager* resource_manager = GetResourceManage();
		LinkedList_pushback(resource_manager->account_list, account);
		printf("注册成功\n");
		break;
	}
	case 2:
		printf("请输入要删除的账户ID：\n");
		int id;
		scanf_s("%d", &id);
		getchar();
		Account* account = FindById(id);
		// 打印账户信息，要求确认
		printf("\n=== 删除账户确认 ===\n");
		printf("账户ID: %d\n", account->id);
		printf("用户名: %s\n", account->user_name);
		printf("账户类型: %s\n",
			account->account_type == Admin ? "管理员" :
			account->account_type == Experimenter ? "实验员" : "普通用户");
		printf("所属实验室: %d\n", account->roomid);
		char confirm;
		printf("\n警告: 删除账户操作不可逆! 确认删除? (Y/N): ");
		scanf_s("%c", &confirm, 1);
		fflush(stdin);

		if (confirm != 'Y' && confirm != 'y')
		{
			printf("已取消删除操作\n");
			return False;
		}
		DeleteAccount(account);
		break;
	case 3:
		ChangeAccount();
		break;
	default:
		break;
	}
}

void ManageLabRoom()
{
	int option = ManageMenu();
	switch (option)
	{
	case 0:
		break;
	case 1:
		AddLabRoom();
		break;
	case 2:
		printf("请输入要删除的实验室ID：\n");
		int id;
		scanf_s("%d", &id);
		fflush(stdin);
		DeleteLabRoom(id);
		break;
	case 3:
		ChangeLabRoom();
		break;
	default:
		break;
	}
}

void ManageCategory()
{
	int option = ManageMenu();
	switch (option)
	{
	case 0:
		return;
	case 1:
		AddCategory();
		break;
	case 2:
		printf("请输入要删除的设备类型ID：\n");
		int id;
		scanf_s("%d", &id);
		fflush(stdin);
		DeleteCategory(id);
	case 3:
		ChangeCategory();
		break;
	default:
		break;
	}
}
