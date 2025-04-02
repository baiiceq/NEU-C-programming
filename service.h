#pragma once
#include "configs.h"
#include "id_manager.h"
#include "resource_manager.h"
#include "account.h"
#include "experimental_equipment.h"
#include "linked_list.h"

//维修类型
typedef enum _Service_type 
{
	LostRegister,      // 遗失登记
	DamagedRegister,   // 损坏登记
	ServiceRegister,   // 维修登记
	ServiceFinish,     // 维修完成
	ScrapRegister              // 报废
} Service_type;
// 维修记录结构
typedef struct _Service 
{
    int service_id;              // 记录ID
    int equipment_id;           // 设备ID
	char equipment_name[EQUIPMENT_LENGTH]; // 设备名
    int user_id;                // 操作人员ID
    char data[DATE_LENGTH];                  // 维修时间
	Service_type type;          // 维修类型
    char reason[NOTE_LENGTH];           // 备注
} Service;

Service* CreateService(int equipment_id, char* equipment_name, int user_id, char* time, Service_type type, char* reason);
void DestoryService(Service* service);
void AddService(Account*);
void DeleteService(Service* service);
