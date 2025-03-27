#include "category.h"

Category* CreateCategory(char* name, int disposal_years)
{
    Category* new_category = (Category*)malloc(sizeof(Category));
    if (new_category == NULL)
    {
        printf("分类创建失败\n");
        return NULL;
    }

    strcpy_s(new_category->name, CATEGORY_LENGTH, name);
    new_category->disposal_years = disposal_years;
    new_category->id = GetNewId(CategoryID);

    return new_category;
}

void DestoryCategory(Category* category)
{
}

void AddCategory()
{
    char name[CATEGORY_LENGTH];
    int disposal_years;
    system("cls");
    printf("---          添加新设备类型          ---\n\n");
    printf("--- 输入类型名称->   ");
    scanf_s("%s", name, CATEGORY_LENGTH);
    printf("--- 输入报废年限->   ");
    scanf_s("%d", &disposal_years);

    Category* new_category = CreateCategory(name, disposal_years);
    if (new_category == NULL)
        return;

    LinkedList_pushback(GetResourceManage()->category_list, new_category);

    printf("创建成功！\n类型id: %d\n类型名称: %s\n报废年限: %d 年\n", new_category->id, name, disposal_years);
    system("pause");
}

void ChangeCategory()
{
	int id;
	printf("请输入要修改的设备类型ID：\n");
	scanf_s("%d", &id);
	getchar(); // 清除缓冲区
	Category* category = FindCategoryById(id);
	if (category == NULL)
	{
		printf("该设备类型不存在\n");
		return;
	}
	while (1)
	{
		system("cls");
		printf("---            设备类型信息修改菜单         ---\n");
		printf("当前设备类型信息：\n");
		printf("ID: %d\n", category->id);
		printf("类型名称: %s\n", category->name);
		printf("报废年限: %d\n", category->disposal_years);
		printf("\n");
		printf("---            1. 修改类型名称               ---\n");
		printf("---            2. 修改报废年限                 ---\n");
		printf("---            0. 退出                    ---\n");
		printf("--- 选择->");
		int option = 0;
		scanf_s("%d", &option);
		getchar(); // 清除缓冲区
		switch (option)
		{
		case 0:
			return;
		case 1:
		{
			char name[CATEGORY_LENGTH];
			printf("请输入新的类型名称（1-20个字符）：\n");
			printf("(直接回车可跳过修改)\n");
			fgets(name, CATEGORY_LENGTH, stdin);
			ChangeCategoryName(category, name);
			break;
		}
		case 2:
		{
			int disposal_years=0;
			printf("请输入新的报废年限（1-20年）：\n");
			printf("(直接回车可跳过修改)\n");
			scanf_s("%d", &disposal_years);
			getchar();
			ChangeCategoryDisposalYears(category,disposal_years);
			break;
		}
		default:
			printf("无效的选择\n");
			break;
		}
	}
}

void ChangeCategoryName(Category* category,char* name)
{
	if (strcmp(name, "\n") == 0)
		return;
	name[strcspn(name, "\n")] = '\0';
	strcpy_s(category->name, CATEGORY_LENGTH, name);
	printf("修改成功\n");
}

void ChangeCategoryDisposalYears(Category* category,int disposal_years)
{
	if (disposal_years == 0)
		return;
	category->disposal_years = disposal_years;
	printf("修改成功\n");
}

Category* FindCategoryById(int id)
{
	Node* temp = GetResourceManage()->category_list->head->next;
	while (temp)
	{
		Category* category = (Category*)temp->data;
		if (category->id == id)
			return category;
		temp = temp->next;
	}
	return NULL;
}
