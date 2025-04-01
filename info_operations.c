#include "info_operations.h"

int ManageMenu()
{
	system("cls");

	printf("---         ѡ��Ҫ���еĲ���         ---\n");
	printf("---            1. ���               ---\n");
	printf("---            2. ɾ��               ---\n");
	printf("---            3. �޸�               ---\n");
	printf("---            0. ȡ��               ---\n");
	printf("--- ѡ��->");

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
		printf("������Ҫɾ�����豸ID��\n");
		int id;
		scanf_s("%d", &id);
		getchar();
		ExperimentalEquipment* ee = (ExperimentalEquipment*)EFindById(GetResourceManage()->equipment_list, id)->head->next->data;
		system("cls");
		printf("=== ɾ���豸ȷ�� ===\n");
		printf("ID: %d\n", ee->id);
		printf("����: %s\n", ee->name);
		printf("���: %s\n", ee->category->name);
		printf("�۸�: %d\n", ee->price);
		printf("����ʵ����ID: %d\n", ee->room_id);
		printf("��������: %s\n", ee->purchase_date);
		printf("\n����: ɾ������������! ȷ��ɾ��? (Y/N): ");

		char confirm;
		scanf_s("%c", &confirm, 1);
		fflush(stdin);

		if (confirm != 'Y' && confirm != 'y') {
			printf("��ȡ��ɾ������\n");
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
			printf("ע��ʧ��\n");
			system("pause");
			return;
		}

		// �������˻�
		ResourceManager* resource_manager = GetResourceManage();
		LinkedList_pushback(resource_manager->account_list, account);
		printf("ע��ɹ�\n");
		break;
	}
	case 2:
		printf("������Ҫɾ�����˻�ID��\n");
		int id;
		scanf_s("%d", &id);
		getchar();
		Account* account = FindById(id);
		// ��ӡ�˻���Ϣ��Ҫ��ȷ��
		printf("\n=== ɾ���˻�ȷ�� ===\n");
		printf("�˻�ID: %d\n", account->id);
		printf("�û���: %s\n", account->user_name);
		printf("�˻�����: %s\n",
			account->account_type == Admin ? "����Ա" :
			account->account_type == Experimenter ? "ʵ��Ա" : "��ͨ�û�");
		printf("����ʵ����: %d\n", account->roomid);
		char confirm;
		printf("\n����: ɾ���˻�����������! ȷ��ɾ��? (Y/N): ");
		scanf_s("%c", &confirm, 1);
		fflush(stdin);

		if (confirm != 'Y' && confirm != 'y')
		{
			printf("��ȡ��ɾ������\n");
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
		printf("������Ҫɾ����ʵ����ID��\n");
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
		printf("������Ҫɾ�����豸����ID��\n");
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
