#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

#include "tree.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	int equal = 0;
	btree* root = readTree();
	treeprint(root);
	equal = preOrder(root);
	if (equal != 0)
		printf("\nAt least two identical elements are");
	else
		printf("There are no identical elements");
}