#include "equipment_management.h"

int main()
{
	EquipmentManagement* em = CreatEquipmentManagement();

	while (em->running)
	{
		ShowMenu(em);
		Run(em);
	}

	DestoryedEquipmentManagement(em);
}