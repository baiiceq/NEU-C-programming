#pragma once
#ifndef EQUIPMENT_MANAGEMENT
#define EQUIPMENT_MANAGEMENT

#include <stdio.h>

#include "configs.h"
#include "id_manager.h"
#include "account.h"


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
	Account* current_account;

} EquipmentManagement;

void Run(EquipmentManagement* em);

EquipmentManagement* CreateEquipmentManagement();

void DestoryEquipmentManagement(EquipmentManagement* em);

#endif // EQUIPMENT_MANAGEMENT