#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "configs.h"
#include "linked_list.h"

typedef enum _AccountType
{
	Admin,         // ����Ա
	Experimenter,  // ʵ��Ա
	User,          // һ���û�
}AccountType;

typedef struct _Account
{
	AccountType account_type;
	char user_name[USER_NMAE_LENGTH];
	char user_password[USER_PASSWORD_LENGTH];
	int id;  //�˻�ID
	int roomid;   //����ʵ����id
	LinkedList* equipment_id_list;   //ta������豸��id����
} Account;


Account* CreateAccount();

// �����˻�
void DestoryAccount(Account* account);

// �ж��˻��Ƿ���Ч
bool ValidAccount(Account* account);

// �ж��û����Ƿ���Ч
bool IsValidUsername(char* username);

Account* FindByUsername(char* username);

bool IsValidPassword(char* password);

bool IsCorrectAccount(Account* account);

// ....��������
#endif // !ACCOUNT
