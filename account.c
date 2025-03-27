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

// �޸��û���
bool ChangeUsername(Account* account, char* new_username)
{
    // �������Ϊ�գ���ʾ�����޸�
    if (strlen(new_username) == 0)
        return True;

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
    if (strlen(new_password) == 0)
        return True;

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
    // ����ֵ��ʾ����
    if (room_id == -9999) // ʹ��һ����̫���ܳ��ֵ�ֵ��Ϊ"����"���
        return True;

    if (room_id != -1)
    {
        // ��֤ʵ�����Ƿ����
        LabRoom* lab = RoomId_to_LabRoom(room_id);
        if (lab == NULL)
        {
            printf("ָ����ʵ���Ҳ�����\n");
            return False;
        }

        // ���ԭ����������ʵ���ң���Ҫ�Ӿ�ʵ�����Ƴ�
        if (account->roomid != -1 && account->roomid != room_id)
        {
            LabRoom* old_lab = RoomId_to_LabRoom(account->roomid);
            if (old_lab != NULL)
            {
                DeleteTechnician(old_lab, account->id);
            }
        }

        // ��ӵ���ʵ����
        LinkedList_pushback(lab->technician_id_list, &account->id);
    }

    account->roomid = room_id;
    printf("ʵ���ҹ����޸ĳɹ�\n");
    return True;
}



// ��ʾ�˻�������������豸
void DisplayAccountEquipments(Account* account)
{
    if (account->equipment_id_list == NULL || account->equipment_id_list->head->next == NULL)
    {
        printf("���˻���ǰδ�����κ��豸\n");
        return;
    }

    printf("��ǰ������豸ID�б�\n");
    Node* temp = account->equipment_id_list->head->next;
    int count = 0;
    while (temp)
    {
        int* eq_id = (int*)temp->data;
        printf("�豸ID: %d", *eq_id);

        // ���Ի�ȡ�豸����
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
            printf(" (����: %s)\n", eq->name);
        }
        else
        {
            printf(" (�豸��Ϣ������)\n");
        }

        temp = temp->next;
        count++;
    }
    printf("������ %d ̨�豸\n", count);
}

// ���˻���ӹ����豸
bool AddEquipmentToAccount(Account* account, int equipment_id)
{
    // ����豸�Ƿ����
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
        printf("ָ�����豸ID������\n");
        return False;
    }

    // ����Ƿ��Ѿ��ڹ����б���
    Node* temp = account->equipment_id_list->head->next;
    while (temp)
    {
        int* id = (int*)temp->data;
        if (*id == equipment_id)
        {
            printf("���豸���ڹ����б���\n");
            return False;
        }
        temp = temp->next;
    }

    // ����豸ID�������б�
    int* new_id = (int*)malloc(sizeof(int));
    if (new_id == NULL)
    {
        printf("�ڴ����ʧ��\n");
        return False;
    }

    *new_id = equipment_id;
    LinkedList_pushback(account->equipment_id_list, new_id);
    printf("�豸ID: %d ����ӵ������б�\n", equipment_id);
    return True;
}

// ���˻��Ƴ������豸
bool RemoveEquipmentFromAccount(Account* account, int equipment_id)
{
    if (account->equipment_id_list == NULL || account->equipment_id_list->head->next == NULL)
    {
        printf("���˻���ǰδ�����κ��豸\n");
        return False;
    }

    Node* prev = account->equipment_id_list->head;
    Node* current = prev->next;

    while (current)
    {
        int* id = (int*)current->data;
        if (*id == equipment_id)
        {
            // �ҵ��豸ID�����������Ƴ�
            prev->next = current->next;
            free(current->data); // �ͷŴ洢ID���ڴ�
            free(current);       // �ͷŽڵ��ڴ�
            printf("�豸ID: %d �Ѵӹ����б����Ƴ�\n", equipment_id);
            return True;
        }
        prev = current;
        current = current->next;
    }

    printf("���˻��Ĺ����б���δ�ҵ��豸ID: %d\n", equipment_id);
    return False;
}

// �޸��˻�������豸
bool ChangeAccountEquipments(Account* account)
{
    while (1)
    {
        system("cls");
        printf("---          �˻������豸�޸Ĳ˵�       ---\n");
        DisplayAccountEquipments(account);
        printf("\n");
        printf("---          1. ��ӹ����豸            ---\n");
        printf("---          2. �Ƴ������豸            ---\n");
        printf("---          0. �����ϼ��˵�            ---\n");
        printf("--- ѡ��->");

        int option = 0;
        scanf_s("%d", &option);
        getchar(); // ���������

        switch (option)
        {
        case 1:
        {
            printf("������Ҫ��ӵ������б���豸ID (����0ȡ��)��\n");
            char input[10] = "";
            fgets(input, 10, stdin);

            if (input[0] == '\n' || strcmp(input, "0\n") == 0)
            {
                printf("��ȡ�����\n");
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
            printf("������Ҫ�ӹ����б����Ƴ����豸ID (����0ȡ��)��\n");
            char input[10] = "";
            fgets(input, 10, stdin);

            if (input[0] == '\n' || strcmp(input, "0\n") == 0)
            {
                printf("��ȡ���Ƴ�\n");
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
            printf("��Ч��ѡ��\n");
            break;
        }

        system("pause");
    }

    return True;
}

// �޸ĺ�����޸ĺ����������˹����豸��ѡ��
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

    // ȷ��equipment_id_list�ѳ�ʼ��
    if (account->equipment_id_list == NULL)
    {
        account->equipment_id_list = CreateLinkedList();
    }

    while (1)
    {
        system("cls");
        printf("---            �˻���Ϣ�޸Ĳ˵�         ---\n");
        printf("��ǰ�˻���Ϣ��\n");
        printf("ID: %d\n", account->id);
        printf("�û���: %s\n", account->user_name);
        printf("�˻�����: %s\n", account->account_type == Admin ? "����Ա" :
            (account->account_type == Experimenter ? "ʵ��Ա" : "��ͨ�û�"));
        printf("����ʵ����: %d\n", account->roomid);
        printf("\n");
        printf("---            1. �޸��û���               ---\n");
        printf("---            2. �޸�����                 ---\n");
        printf("---            3. �޸��˻�����             ---\n");
        printf("---            4. �޸�����ʵ����           ---\n");
        printf("---            5. �޸Ĺ����豸�б�         ---\n");
        printf("---            0. �˳�                    ---\n");
        printf("--- ѡ��->");

        int option = 0;
        scanf_s("%d", &option);
        getchar(); // ���������

        bool result = False;
        switch (option)
        {
        case 1:
        {
            printf("�������µ��û�����4-12���ַ���ֻ�ܰ�����ĸ�����֣���\n");
            printf("(ֱ�ӻس��������޸�)\n");
            char new_username[USER_NMAE_LENGTH] = "";
            fgets(new_username, USER_NMAE_LENGTH, stdin);

            // �Ƴ����ܵĻ��з�
            int len = strlen(new_username);
            if (len > 0 && new_username[len - 1] == '\n')
                new_username[len - 1] = '\0';

            result = ChangeUsername(account, new_username);
            break;
        }
        case 2:
        {
            printf("�������µ����루8-20���ַ����ɰ�����ĸ�����ֺ�@+?���ţ���\n");
            printf("(ֱ�ӻس��������޸�)\n");
            char new_password[USER_PASSWORD_LENGTH] = "";
            fgets(new_password, USER_PASSWORD_LENGTH, stdin);

            // �Ƴ����ܵĻ��з�
            int len = strlen(new_password);
            if (len > 0 && new_password[len - 1] == '\n')
                new_password[len - 1] = '\0';

            result = ChangePassword(account, new_password);
            break;
        }
        case 3:
        {
            printf("��ѡ���µ��˻����ͣ�\n");
            printf("1. ����Ա\n");
            printf("2. ʵ��Ա\n");
            printf("3. ��ͨ�û�\n");
            printf("(����0�������޸�)\n");
            printf("��ѡ�� -> ");

            char input[10] = "";
            fgets(input, 10, stdin);

            if (input[0] == '\n') {
                result = True; // ֱ�ӻس�����
            }
            else {
                int type = atoi(input);
                result = ChangeAccountType(account, type);
            }
            break;
        }
        case 4:
        {
            printf("��ǰ����ʵ����ID: %d\n", account->roomid);
            printf("�������µ�ʵ����ID������-1��ʾ�������κ�ʵ���ң���\n");
            printf("(ֱ�ӻس��������޸�)\n");

            char input[10] = "";
            fgets(input, 10, stdin);

            if (input[0] == '\n') {
                result = True; // ֱ�ӻس�����
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

