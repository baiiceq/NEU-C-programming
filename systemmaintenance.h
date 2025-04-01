#pragma once
#include "resource_manager.h"
#include "account.h"
#include "configs.h"

// 系统维护主菜单（管理员）
void ASystemMaintenance(Account* account);
// 系统维护主菜单（用户/实验员）
void USystemMaintenance(Account* account);

// 记录系统操作日志
bool LogSystemOperation(const char* operation, int userId);
// 修改自己的用户名
bool ChangeAccountName(Account* account);
// 管理员修改用户的用户名
bool AdminChangeUsername(int adminId, int targetUserId);
// 修改自己的密码
bool ChangePassword(Account* account);
// 重置用户或实验员密码
bool ResetUserPassword(int targetUserId, int adminId);
// 备份系统数据
bool BackupSystemData(int adminId);
// 恢复系统数据
bool RestoreSystemData(int adminId);