#pragma once

typedef struct _EquipmentManagement
{
	int running;
} EquipmentManagement;

void ShowMenu(EquipmentManagement* em);

void Run(EquipmentManagement* em);

EquipmentManagement* CreatEquipmentManagement();

void DestoryedEquipmentManagement(EquipmentManagement* em);