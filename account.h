#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "configs.h"
#include "linked_list.h"

typedef enum _AccountType
{
	Admin,         // 管理员
	Experimenter,  // 实验员
	User,          // 一般用户
	Unknow = -1
}AccountType;

typedef struct _Account
{
	AccountType account_type;
	char user_name[USER_NMAE_LENGTH];
	char user_password[USER_PASSWORD_LENGTH];
	int id;  //账户ID
	int roomid;   //所属实验室id
	LinkedList* equipment_id_list;   //ta管理的设备的id链表
} Account;


Account* CreateAccount();
Account* AccountRegister();
void DeleteAccount(Account* account);
void ChangeAccount();
void DestoryAccount(Account* account);


bool ValidAccount(Account* account);// 判断账户是否有效
bool IsValidUsername(char* username);// 判断用户名是否有效
bool IsValidPassword(char* password);
bool IsCorrectAccount(Account* account);

Account* FindByUsername(char* username);
Account* FindById(int id);

bool ChangeAccountLab(Account* account, int room_id);
bool ChangeAccountType(Account* account, int type);
bool ChangeUsername(Account* account, char* new_username);
void DisplayPasswordRules();


// ....其他函数
#endif // !ACCOUNT
