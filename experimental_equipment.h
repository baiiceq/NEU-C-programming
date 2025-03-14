#ifndef EXPERIMENTAL_EQUIPMENT_H
#define EXPERIMENTAL_EQUIPMENT_H

#include "configs.h"
#include "category.h"

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
	int id;                         // �豸id(���id+����id)
	Category category;              // �豸���
	char name[EQUIPMENT_LENGTH];    // �豸����
	int room_id;                    // ����ʵ����ID
	int price;                      // �豸�۸�
	char purchase_date[11];         // �������� (YYYY-MM-DD)
}ExperimentalEquipment;
#endif // !EXPERIMENTAL_EQUIPMENT_H

ExperimentalEquipment* CreateExperimentalEquipment();

void DestoryExperimentalEquipment(ExperimentalEquipment* experimental_equipment);