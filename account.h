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
	Unknow = -1
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
Account* AccountRegister();
void DeleteAccount(Account* account);
void ChangeAccount();
void DestoryAccount(Account* account);


bool ValidAccount(Account* account);// �ж��˻��Ƿ���Ч
bool IsValidUsername(char* username);// �ж��û����Ƿ���Ч
bool IsValidPassword(char* password);
bool IsCorrectAccount(Account* account);

Account* FindByUsername(char* username);
Account* FindById(int id);

bool ChangeAccountLab(Account* account, int room_id);
bool ChangeAccountType(Account* account, int type);
bool ChangeUsername(Account* account, char* new_username);
void DisplayPasswordRules();


// ....��������
#endif // !ACCOUNT
