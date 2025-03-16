#pragma once
#ifndef CATEGORY_H
#define CATEGORY_H

#include <stdio.h>
#include <string.h>

#include "configs.h"
#include "id_manager.h"

typedef struct _Category
{
	int id;                        // ���ID
	char name[CATEGORY_LENGTH];    // �������
	int disposal_years;            // ��������
}Category;

Category* CreateCategory(char* name, int disposal_years);

void DestoryCategory(Category* category);
#endif // !CATEGORY_H
