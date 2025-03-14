#ifndef CATEGORY_H
#define CATEGORY_H

#include "configs.h"

typedef struct _Category
{
	int id;                        // 类别ID
	char name[CATEGORY_LENGTH];    // 类别名称
	int disposal_years;            // 报废年限
}Category;

Category* CreateCategory();

void DestoryCategory(Category* category);
#endif // !CATEGORY_H
