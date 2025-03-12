#ifndef LOGIN_INTERFACE
#define LOGIN_INTERFACE

#include "configs.h"
#include "account.h"
#include "linked_list.h"
#include "equipment_management.h"

struct _EquipmentManagement;
typedef struct _EquipmentManagement EquipmentManagement;

typedef struct _LoginInterface 
{
    LinkedList* account_list;
} LoginInterface;

// 销毁登录界面
void destoryLoginInterface();

// 获取登录界面
LoginInterface* GetLoginInterface();

int ShowLoginMenu();

void RunLoginInterface(int option, EquipmentManagement* em);

// 登录函数（包括输入账号和密码，检查账号合法性等操作）, 返回账号
Account* AccountLogin();

#endif // !LOGIN_INTERFACE