#ifndef EXPERIMENTAL_EQUIPMENT_H
#define EXPERIMENTAL_EQUIPMENT_H

#include "configs.h"
#include "category.h"
#include "lab_room.h"

enum EquipmentState
{
	Using,     // ����ʹ��
	Idle,      // ����
	Lost,      // ��ʧ
	Damaged,   // �𻵣�δ��ά�ޣ�
	Scrapped,  // ���ϣ�׼��ɾ������
	Repairing  // ����ά��
};

typedef struct _ExperimentalEquipment
{
	int id;                                   // �豸id
	Category* category;                        // �豸���
	char name[EQUIPMENT_LENGTH];              // �豸����
	int room_id;                              // ����ʵ����ID
	int price;                                // �豸�۸�
	char purchase_date[DATE_LENGTH];          // �������� (YYYY-MM-DD)
}ExperimentalEquipment;

ExperimentalEquipment* CreateExperimentalEquipment(Category* category, char* name, int room_id, int price, char* purchase_date);

void DestoryExperimentalEquipment(ExperimentalEquipment* experimental_equipment);

void AddExperimentalEquipment();

#endif // !EXPERIMENTAL_EQUIPMENT_H