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
		printf("�˻�����ʧ�ܣ�\n");
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
    printf("������Ҫ�޸ĵ��˻�ID��\n");
    scanf_s("%d", &account_id);
    getchar(); // ���������

    Account* account = FindById(account_id);
    if (account == NULL)
    {
        printf("���˻�������\n");
        return;
    }

    while (1)
    {
        system("cls");
        printf("---            �˻���Ϣ�޸Ĳ˵�         ---\n");
        printf("��ǰ�˻���Ϣ��\n");
        printf("ID: %d\n", account->id);
        /*printf("�û���: %s\n", account->user_name);*/
        printf("�˻�����: %s\n", account->account_type == Admin ? "����Ա" :
            (account->account_type == Experimenter ? "ʵ��Ա" : "��ͨ�û�"));
        printf("����ʵ����: %d(-1��ʾ������ʵ����)\n", account->roomid);
        printf("\n");
        /*printf("---            1. �޸��û���               ---\n");
        printf("---            2. �޸�����                 ---\n");*/
        printf("---            1. �޸��˻�����             ---\n");
        printf("---            2. �޸�����ʵ����           ---\n");
        printf("---            0. �˳�                    ---\n");
        printf("--- ѡ��->");

        int option = 0;
        scanf_s("%d", &option);
        getchar(); // ���������

        bool result = False;
        switch (option)
        {
        /*case 1:
        {
            printf("�������µ��û�����4-12���ַ���ֻ�ܰ�����ĸ�����֣���\n");
            printf("(ֱ�ӻس��������޸�)\n");
            char new_username[USER_NMAE_LENGTH] = "";
            fgets(new_username, USER_NMAE_LENGTH, stdin);

            result = ChangeUsername(account, new_username);
            break;
        }
        case 2:
        {
            printf("�������µ����루8-20���ַ����ɰ�����ĸ�����ֺ�@+?���ţ���\n");
            printf("(ֱ�ӻس��������޸�)\n");
            char new_password[USER_PASSWORD_LENGTH] = "";
            fgets(new_password, USER_PASSWORD_LENGTH, stdin);

            result = ChangePassword(account, new_password);
            break;
        }*/
        case 1:
        {
            printf("��ѡ���µ��˻����ͣ�\n");
            printf("1. ����Ա\n");
            printf("2. ʵ��Ա\n");
            printf("3. ��ͨ�û�\n");
            printf("(����0�������޸�)\n");
            printf("��ѡ�� -> ");

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
				printf("��ǰ�˻����Ͳ�����ʵ������������\n");
				result = False;
				break;
			}
            printf("�������µ�ʵ����ID������-1��ʾ�������κ�ʵ���ң���\n");
            printf("(ֱ�ӻس��������޸�)\n");
			int room_id = 0;
			scanf_s("%d", &room_id);
            getchar();
            result = ChangeAccountLab(account, room_id);
            break;
        }
        case 0:
            return; // ֱ�ӷ��أ����践��ֵ
        default:
            printf("��Ч��ѡ��\n");
            result = False;
            break;
        }

        if (result)
        {
            printf("�������\n");
        }
        else
        {
            printf("����ʧ��\n");
        }

        system("pause");
    }
}

// �޸��û���
bool ChangeUsername(Account* account, char* new_username)
{
    // �������Ϊ�գ���ʾ�����޸�
    if (strcmp(new_username,"\n") == 0)
        return True;

    new_username[strcspn(new_username, "\n")] = '\0';

    if (!IsValidUsername(new_username))
    {
        printf("�û������Ϸ�\n");
        return False;
    }

    Account* existing = FindByUsername(new_username);
    if (existing != NULL && existing != account)
    {
        printf("�û����Ѵ���\n");
        return False;
    }

    strcpy_s(account->user_name, USER_NMAE_LENGTH, new_username);
    printf("�û����޸ĳɹ�\n");
    return True;
}

// �޸�����
bool ChangePassword(Account* account, char* new_password)
{
    // �������Ϊ�գ���ʾ�����޸�
    if (strcmp(new_password, "\n") == 0)
        return True;

    new_password[strcspn(new_password, "\n")] = '\0';

    if (!IsValidPassword(new_password))
    {
        printf("���벻�Ϸ�\n");
        return False;
    }

    strcpy_s(account->user_password, USER_PASSWORD_LENGTH, new_password);
    printf("�����޸ĳɹ�\n");
    return True;
}

// �޸��˻�����
bool ChangeAccountType(Account* account, int type)
{
    // �������Ϊ0����ʾ�����޸�
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
        printf("��Ч���˻�����\n");
        return False;
    }

    printf("�˻������޸ĳɹ�\n");
    return True;
}

// �޸��˻�����ʵ����
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
            printf("ָ����ʵ���Ҳ�����\n");
            return False;
        }
        //��ӵ���ʵ����
        LinkedList_pushback(lab->technician_id_list, &account->id);

        //ͬʱ�޸Ĺ�����豸����
        account->equipment_id_list = lab->equipments_list;
    }

    account->roomid = room_id;
    
    printf("ʵ���ҹ����޸ĳɹ�\n");
    return True;
}


bool ValidAccount(Account* account)
{
	if (!IsValidUsername(account->user_name))
	{
		printf("�û������Ϸ�\n");
		return False;
	}
	if (FindByUsername(account->user_name))
	{
		printf("�û����Ѵ���\n");
		return False;
	}
	if (!IsValidPassword(account->user_password))
	{
		printf("���벻�Ϸ�\n");
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
		printf("�û���������\n");
		return False;
	}
	if (strcmp(temp->user_password, account->user_password) != 0)
	{
		printf("�������\n");
		return False;
	}

	account->account_type = temp->account_type;
	return True;
}

