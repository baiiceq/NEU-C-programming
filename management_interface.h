#pragma once
#ifndef MANAGEMENT_INTERFACE
#define MANAGEMENT_INTERFACE

#include "linked_list.h"
#include "equipment_management.h"
#include "id_manager.h"
#include "info_operations.h"


int ShowManagementMenu(AccountType account_type);

void RunManagementInterface(int option, EquipmentManagement* em, AccountType account_type);

// 信息查询函数
void QueryInformation();

// 信息排序函数
void SortInformation();

// 信息统计
void Statistics();

// 系统维护
void SystemMaintenance(AccountType account_type);

// 基本信息维护
void BasicInformationManagement();

// 信息调整管理
void AdjustmentInformation();

// 设备管理
void EquipmentsManagement();
#endif // !MANAGEMENT_INTERFACE
