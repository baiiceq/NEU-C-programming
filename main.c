#include "equipment_management.h"

int main()
{
	EquipmentManagement* em = CreateEquipmentManagement();

	while (em->running)
	{
		Run(em);
	}

	DestoryEquipmentManagement(em);
}