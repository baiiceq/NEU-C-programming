#include "service.h"
#include <time.h>

Service* CreateService(int equipment_id, char* equipment_name, char* user_id,char* data, Service_type type, char* reason)
{
	Service* service = (Service*)malloc(sizeof(Service));
	if (service == NULL)
	{
		printf("内存分配失败\n");
		exit(-1);
	}
	service->service_id = GetNewId(ServiceID);
	service->equipment_id = equipment_id;
	strcpy_s(service->equipment_name, EQUIPMENT_LENGTH, equipment_name);
	strcpy_s(service->user_id, USER_NMAE_LENGTH, user_id);
	strcpy_s(service->data, DATE_LENGTH, data);
	service->type = type;
	strcpy_s(service->reason, NOTE_LENGTH, reason);
	return service;
}

void DestoryService(Service* service)
{
	if (service)
		free(service);
}

void AddService(Account* account)
{
	ResourceManager* rm = GetResourceManage();
	Service* service = (Service*)malloc(sizeof(Service));
	if (service == NULL)
	{
		printf("内存分配失败\n");
		return;
	}
	printf("请输入设备ID->");
	scanf_s("%d", &service->equipment_id);
	getchar();
	ExperimentalEquipment* ee = (ExperimentalEquipment*)EFindById(rm->equipment_list, service->equipment_id)->head->next->data;
	printf("ID对应的设备名为%s\n", ee->name);
	strcpy_s(service->equipment_name, EQUIPMENT_LENGTH, ee->name);
	//获取时间
	time_t now;
	time(&now);
	char formattedTime[30];
	struct tm timeinfo;
	localtime_s(&timeinfo, &now);
	strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d_%H-%M-%S", &timeinfo);
	formattedTime[10] = 0;
	strcpy_s(service->data, DATE_LENGTH, formattedTime);
	printf("请输入维修类型(0:遗失登记 1:损坏登记 2:维修登记 3:维修完成 4:报废登记)->");
	int type;
	scanf_s("%d", &type);
	getchar();
	switch (type)
	{
	case 0:
		service->type = LostRegister;
		ee->state = Lost;
		break;
	case 1:
		service->type = DamagedRegister;
		ee->state = Damaged;
		break;
	case 2:
		service->type = ServiceRegister;
		ee->state = Repairing;
		ee->service_times++;
		break;
	case 3:
		service->type = ServiceFinish;
		ee->state = Idle;
		break;
	case 4:
		service->type = ScrapRegister;
		ee->state = Scrapped;
		break;
	default:
		printf("非法指令\n");
		free(service);
		return;
	}
	printf("如有备注请输入->");
	fgets(service->reason, NOTE_LENGTH, stdin);
	if (strcmp(service->reason, "\n") == 0)
		strcpy_s(service->reason, sizeof(service->reason), "nothing");
	else
		service->reason[strlen(service->reason) - 1] = '\0';
	service->user_id = account->id;
	service->service_id = GetNewId(ServiceID);
	LinkedList_pushback(rm->service_list, service);
	printf("维修成功\n");
}

void DeleteService(Service* service)
{
	ResourceManager* rm = GetResourceManage();
	Node* temp = rm->service_list->head;
	while (temp->next)
	{
		Service* temp_service = (Service*)temp->next->data;
		if (temp_service == service)
		{
			temp->next = temp->next->next;
			DestoryService(service);
			rm->service_list->size--;
			break;
		}
		temp = temp->next;
	}
}