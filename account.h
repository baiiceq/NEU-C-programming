#ifndef ACCOUNT
#define ACCOUNT

#include "configs.h"

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
} Account;

// �����˻�
Account* CreatAccount();

// �����˻�
void DestoryAccount(Account* account);

// ....��������
#endif // !ACCOUNT
