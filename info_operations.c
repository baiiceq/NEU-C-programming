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
		DeleteLabRoom();
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
	default:
		break;
	}
}
