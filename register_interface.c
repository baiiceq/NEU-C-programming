#include "register_interface.h"
#include "account.h"

int ShowRegisterMenu()
{
    system("cls");

    int option = 0;
    printf("---   注册界面   ---\n\n");
    printf("---   1. 注册    ---\n");
    printf("---   2. 登录    ---\n");
    printf("---   0. 退出    ---\n");
    printf("--- 请输入选项->");

    scanf_s("%d", &option);
    while (getchar() != '\n');

    system("pause");
    return option;
}

void RunRegisterInterface(int option, EquipmentManagement* em)
{
    switch (option)
    {
    case 0:
        em->running = False;
        break;
    case 1:
    {
        Account* account = AccountRegister();
        if (account == NULL)
        {
            printf("注册失败\n");
            system("pause");
            return;
        }
        
        // 储存新账户
        ResourceManager* resource_manager = GetResourceManage();
        LinkedList_pushback(resource_manager->account_list, account);
		printf("注册成功\n");
    }
    break;
    case 2:
        em->current_state = Login;
        break;
    default:
        printf("操作非法！\n");
        break;
    }
    system("pause");
}

Account* AccountRegister()
{
    Account* account = CreateAccount();
    int a = 0;
    printf("请输入用户类型1.管理员2.实验员3.一般用户\n");
    scanf_s("%d",&a);
    while (getchar() != '\n');
    switch (a) 
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
		printf("用户类型不合法\n");
		return NULL;
    }
    printf("请输入用户名(长度在4-12位，且只能包含字母和数字）\n");
	fgets(account->user_name, USER_NMAE_LENGTH, stdin);
    account->user_name[strcspn(account->user_name, "\n")] = '\0';
    printf("请输入用户密码（长度在8-20位，且只能包含字母数字以及@+？）\n");
    fgets(account->user_password, sizeof(account->user_password), stdin);
    account->user_password[strcspn(account->user_password, "\n")] = '\0';

    if (!ValidAccount(account))
    {
		free(account);
		return NULL;
    }
	account->id = GetNewId(AccountID);
    account->roomid = -1;
    return account;
}
