#ifndef EXPERIMENTAL_EQUIPMENT_H
#define EXPERIMENTAL_EQUIPMENT_H

#include "configs.h"
#include "category.h"
#include "lab_room.h"
#include "resource_manager.h"



typedef enum _EquipmentState
{
	Using,     // ����ʹ��
	Idle,      // ����
	Lost,      // ��ʧ
	Damaged,   // �𻵣�δ��ά�ޣ�
	Scrapped,  // ���ϣ�׼��ɾ������
	Repairing  // ����ά��
}EquipmentState;

typedef struct _ExperimentalEquipment
{
	int id;                                   // �豸id
	Category* category;                        // �豸���
	char name[EQUIPMENT_LENGTH];              // �豸����
	int room_id;                              // ����ʵ����ID,-1��ʾδ����
	int price;                                // �豸�۸�
	char purchase_date[DATE_LENGTH];          // �������� (YYYY-MM-DD)
	EquipmentState state;                     // �豸״̬
}ExperimentalEquipment;

ExperimentalEquipment* CreateExperimentalEquipment(Category* category, char* name, int room_id, int price, char* purchase_date);

void DestoryExperimentalEquipment(ExperimentalEquipment* experimental_equipment);

void AddExperimentalEquipment();
void DeleteExperimentalEquipment(ExperimentalEquipment* ee);
void ChangeExperimentalEquipment();

bool ChangeName(ExperimentalEquipment* eq, char* newname);
bool ChangePrice(ExperimentalEquipment* eq, int newprice);
bool ChangeRoom_id(ExperimentalEquipment* eq, char* newroomid);
bool ChangePurchaseDate(ExperimentalEquipment* eq, char* newdate);
bool ChangeExperimentalCategory(ExperimentalEquipment* eq, Category* newcategory);


LinkedList* EFindByName(LinkedList* eqlist, char* name);
LinkedList* EFindById(LinkedList* eqlist, int id);
LinkedList* EFindByRoom_id(LinkedList* eqlist, int roomid);
LinkedList* EFindByCategory(LinkedList* eqlist, int categoryid);
LinkedList* EFindByDate(LinkedList* eqlist, char* start, char* end);
LinkedList* EFindByPrice(LinkedList* eqlist, int min, int max);
#endif // !EXPERIMENTAL_EQUIPMENT_H
