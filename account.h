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

// 创建账户(检验用户名，密码合法性）
//Account* CreatAccount(Account* account);

// 销毁账户
void DestoryAccount(Account* account);

bool* IsValidAccount(Account* account);
bool IsValidUsername(char* username);
Account* FindByUsername(char* username);
bool IsValidPassword(char* password);


// ....其他函数
#endif // !ACCOUNT
