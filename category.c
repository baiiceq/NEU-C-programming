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
