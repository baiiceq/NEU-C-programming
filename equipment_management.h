#ifndef EQUIPMENT_MANAGEMENT
#define EQUIPMENT_MANAGEMENT

#include "configs.h"

typedef enum _CurrentState
{
	Login,       // 登录界面
	Register,    // 注册界面
	Management	 // 管理界面
}CurrentState;

typedef struct _EquipmentManagement
{
	bool running;    // 是否运行
	CurrentState current_state;
} EquipmentManagement;

void ShowMenu(EquipmentManagement* em);

void Run(EquipmentManagement* em);

EquipmentManagement* CreatEquipmentManagement();

void DestoryedEquipmentManagement(EquipmentManagement* em);

#endif // EQUIPMENT_MANAGEMENT