#include "category.h"

Category* CreateCategory(char* name, int disposal_years)
{
    Category* new_category = (Category*)malloc(sizeof(Category));
    if (new_category == NULL)
    {
        printf("���ഴ��ʧ��\n");
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
    printf("---          ������豸����          ---\n\n");
    printf("--- ������������->   ");
    scanf_s("%s", name, CATEGORY_LENGTH);
    printf("--- ���뱨������->   ");
    scanf_s("%d", &disposal_years);

    Category* new_category = CreateCategory(name, disposal_years);
    if (new_category == NULL)
        return;

    LinkedList_pushback(GetResourceManage()->category_list, new_category);

    printf("�����ɹ���\n����id: %d\n��������: %s\n��������: %d ��\n", new_category->id, name, disposal_years);
    system("pause");
}

void ChangeCategory()
{
	int id;
	printf("������Ҫ�޸ĵ��豸����ID��\n");
	scanf_s("%d", &id);
	getchar(); // ���������
	Category* category = FindCategoryById(id);
	if (category == NULL)
	{
		printf("���豸���Ͳ�����\n");
		return;
	}
	while (1)
	{
		system("cls");
		printf("---            �豸������Ϣ�޸Ĳ˵�         ---\n");
		printf("��ǰ�豸������Ϣ��\n");
		printf("ID: %d\n", category->id);
		printf("��������: %s\n", category->name);
		printf("��������: %d\n", category->disposal_years);
		printf("\n");
		printf("---            1. �޸���������               ---\n");
		printf("---            2. �޸ı�������                 ---\n");
		printf("---            0. �˳�                    ---\n");
		printf("--- ѡ��->");
		int option = 0;
		scanf_s("%d", &option);
		getchar(); // ���������
		switch (option)
		{
		case 0:
			return;
		case 1:
		{
			char name[CATEGORY_LENGTH];
			printf("�������µ��������ƣ�1-20���ַ�����\n");
			printf("(ֱ�ӻس��������޸�)\n");
			fgets(name, CATEGORY_LENGTH, stdin);
			ChangeCategoryName(category, name);
			break;
		}
		case 2:
		{
			int disposal_years=0;
			printf("�������µı������ޣ�1-20�꣩��\n");
			printf("(ֱ�ӻس��������޸�)\n");
			scanf_s("%d", &disposal_years);
			getchar();
			ChangeCategoryDisposalYears(category,disposal_years);
			break;
		}
		default:
			printf("��Ч��ѡ��\n");
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
	printf("�޸ĳɹ�\n");
}

void ChangeCategoryDisposalYears(Category* category,int disposal_years)
{
	if (disposal_years == 0)
		return;
	category->disposal_years = disposal_years;
	printf("�޸ĳɹ�\n");
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
