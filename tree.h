#pragma once
#include <stdio.h>
#include <conio.h>

struct btree
{
	char data;
	btree* left, *right;
};

struct dstack
{
	btree* data;
	dstack* next;
};

void create(dstack** st)
{
	*st = NULL;
}

int empty(dstack* st)					
{
	if (!st)
		return 1;
	else
		return 0;
}

dstack* pushdstack(btree *x, dstack *st)			
{
	dstack* r;
	r = new dstack;
	r->data = x;
	r->next = st;

	return r;
}
int popdstack(btree** x, dstack** st)			
{
	dstack* r;
	if (*st)
	{
		r = *st;
		*x = (*st)->data;
		*st = (*st)->next;
		delete r;
		return 1;
	}
	return 0;
}

btree *buildTree(FILE *in)
{
	btree *d = NULL;  
	char symb;  

	fscanf(in, "%c", &symb);

	switch (symb) 
	{
		case '(':   
			d = new btree;
			fscanf(in, "%c", &symb);
			d->data = symb;   
			d->left = buildTree(in);   
			d->right = buildTree(in);   
			fscanf(in, "%c", &symb);   
			break;

		case ',': 
			d = buildTree(in); 
			break;

		case '0': break;
	}

	return d;
}

btree *readTree()
{
	btree *root = NULL;

	FILE *in = fopen("in.txt", "r");  
	if (!in) 
	{ 
		printf("Error opening file"); 
		_getch(); 
	
	}
	else 
		root = buildTree(in);
	
	fclose(in);  
	return root;
}

int isHaveEqual(btree *d, char elem)			
{
	int equal = 0;					// Yes or no
	btree q, q1;
	dstack* s;
	create(&s);

	while (d != NULL && !equal)
	{
		if (d->left != NULL && d->right != NULL)				// direct detour
		{
			q = *d;
			s = pushdstack(d->right, s);
			q1 = *d;

			if (q.data != q1.data) 
				d = q.left;		
			else
				d = d->left;
		}
		else
			if (d->left == NULL && d->right == NULL)
				if (!empty(s)) 
					popdstack(&d, &s);
				else 
					d = NULL;
			else
				if (d->left != NULL) 
					d = d->left;
				else 
					d = d->right;

				if (d != NULL)
					if (q->data == elem) 
						equal = 1;			
	}

	return equal;
}

int find(btree *d)					
{
	btree q, q1;					
	int equal = 0;	
	dstack* s;
	create(&s);

	while (d && !equal)
	{
		
		equal = isHaveEqual(d, d->data);	// Is there something similar to this element?

		if (d->left != NULL && d->right != NULL)				// direct detour
		{
			q = *d;
			s = pushdstack(d->right, s);
			q1 = *d;

			if (q.data != q1.data)
				d = q.left;
			else
				d = d->left;
		}
		else
			if (d->left == NULL && !d->right == NULL)
				if (!empty(s))
					popdstack(&d, &s);
				else 
					d = NULL;
			else
				if (d->left != NULL) 
					d = d->left;
				else 
					d = d->right;
	}

	return equal;
}

void treeprint(btree *p)
{
	if (p != NULL)
	{
		treeprint(p->left);
		printf("%c ", p->data);
		treeprint(p->right);
	}
}
