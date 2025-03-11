#ifndef EQUIPMENT_MANAGEMENT
#define EQUIPMENT_MANAGEMENT

#include "configs.h"

typedef enum _CurrentState
{
	Login,       // ��¼����
	Register,    // ע�����
	Management	 // �������
}CurrentState;

typedef struct _EquipmentManagement
{
	bool running;    // �Ƿ�����
	CurrentState current_state;
} EquipmentManagement;

void ShowMenu(EquipmentManagement* em);

void Run(EquipmentManagement* em);

EquipmentManagement* CreatEquipmentManagement();

void DestoryedEquipmentManagement(EquipmentManagement* em);

#endif // EQUIPMENT_MANAGEMENT