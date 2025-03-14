#ifndef CATEGORY_H
#define CATEGORY_H

#include "configs.h"

typedef struct _Category
{
	int id;                        // ���ID
	char name[CATEGORY_LENGTH];    // �������
	int disposal_years;            // ��������
}Category;

Category* CreateCategory();

void DestoryCategory(Category* category);
#endif // !CATEGORY_H
