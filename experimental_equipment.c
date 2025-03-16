#include "experimental_equipment.h"

ExperimentalEquipment* CreateExperimentalEquipment(Category* category, char* name, int room_id, int price, char* purchase_date)
{
    ExperimentalEquipment* ee = (ExperimentalEquipment*)malloc(sizeof(ExperimentalEquipment));

    if (ee == NULL)
    {
        printf("创建设备失败\n");
        return NULL;
    }

    ee->id = GetNewId(EquipmentID);
    ee->category = category;
    strcpy_s(ee->name, EQUIPMENT_LENGTH, name); 
    ee->price = price;
    ee->room_id = room_id;
    strcpy_s(ee->purchase_date, DATE_LENGTH, purchase_date);

    return ee;

}

void DestoryExperimentalEquipment(ExperimentalEquipment* experimental_equipment)
{

}

void AddExperimentalEquipment()
{
    system("cls");
    ResourceManager* rm = GetResourceManage();
    size_t category_count = rm->category_list->size;
    if (category_count == 0)
    {
        printf("当前无法添加设备\n");
        return; 
    }
    printf("---      选择你要添加的类型        ---\n\n");

    Node* temp = rm->category_list->head;
    for (size_t i = 0; i < category_count; i++)
    {
        temp = temp->next;
        Category* category = (Category*)temp->data;
        printf("--- No%d. %s\n", (int)i + 1, category->name);
    }
    printf("--- 0. 取消\n");
    printf("--- 选择->");
    int select = 0;
    scanf_s("%d", &select);

    if (select == 0)
    {
        return;
    }
    else if (select > category_count)
    {
        printf("非法指令\n");
        system("pause");
        return;
    }
    else
    {
        char name[EQUIPMENT_LENGTH];
        int room_id;
        int price;
        char purchase_date[DATE_LENGTH];

        printf("--- 输入设备名称->   ");
        scanf_s("%s", name, EQUIPMENT_LENGTH);

        printf("--- 输入所属实验室id->  ");
        scanf_s("%d", &room_id);
        LabRoom* labroom = RoomId_to_LabRoom(room_id);
        if (labroom == NULL)
        {
            printf("该实验室不存在\n");
            system("pause");
            return;
        }

        printf("--- 输入设备价格->  ");
        scanf_s("%d", &price);

        printf("--- 输入购买时间（yyyymmdd）->  ");
        scanf_s("%s", purchase_date, DATE_LENGTH);

        Category* category = LinkedList_at(rm->category_list, select - 1);
        ExperimentalEquipment* new_ee = CreateExperimentalEquipment(category, name, room_id, price, purchase_date);
        if (new_ee == NULL)
            return;

        LinkedList_pushback(rm->equipment_list, new_ee);
        LinkedList_pushback(labroom->equipments_list, new_ee->id);

        printf("创建成功！\n设备id: %d\n设备名称: %s\n设备价格: %d 元\n设备购买时间: %s", new_ee->id, name, price,purchase_date);
        system("pause");

    }
}
