#ifndef ACCOUNT
#define ACCOUNT

#include "configs.h"

typedef enum _AccountType
{
	Admin,         // 管理员
	Experimenter,  // 实验员
	User,          // 一般用户
}AccountType;

typedef struct _Account
{
	AccountType account_type;
	char user_name[USER_NMAE_LENGTH];
	char user_password[USER_PASSWORD_LENGTH];
} Account;


// 销毁账户
void DestoryAccount(Account* account);

bool IsValidAccount(Account* account);
bool IsValidUsername(char* username);
Account* FindByUsername(char* username);
bool IsValidPassword(char* password);
bool IsCorrectAccount(Account* account);

// ....其他函数
#endif // !ACCOUNT
