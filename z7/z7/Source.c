#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define EXIT -1
#define MAX_LINE 1024
#define ERROR -1

struct _folder;
typedef struct _folder* position;
typedef struct _folder {
	char name[MAX_LINE];
	position child;
	position sibling;
}folder;

struct _stack;
typedef  struct _stack* pos;
typedef struct _stack {
	position adress;
	pos next;
}stack;

position makedirectory(position);
position print(position);
position exitdirectory(position);
int push(pos head, position adress);
position pop(pos current);
pos CreateStackElement(position adressa);
int InsertAfter(pos position, pos newElement);
position find(position current, char* name);
position Delete(position);
int deleteStack(pos);

int main() {
	position current = NULL;

	folder C;
	strcpy(C.name, "C");
	C.child = NULL;
	C.sibling = NULL;
	current = &C;

	stack s = { .adress = current,.next = NULL };
	pos sroot = &s;

	position temp;

	char command[MAX_LINE];
	char foldername[MAX_LINE];

	while (1) {
		printf("Upisite naredbu: ");
		scanf("%s", command);
		if (strcmp(command, "md") == 0) {
			current->child = makedirectory(current);
		}
		else if (strcmp(command, "dir") == 0) {
			printf("\nFolder %s:\n", current->name);
			print(current->child);
		}
		else if (strcmp(command, "cd") == 0) {
			printf("\nUnesite ime direktorija: ");
			scanf("%s", foldername);
			temp = find(current, foldername);
			if (temp == NULL)
				printf("\nNepostoji element s takvim imenom! (%s)\n", foldername);
			else {
				push(sroot, temp);
			}
			current = temp;
			printf("Elementi direktorija (%s):\n", foldername);
			print(current->child);
		}
		else if (strcmp(command, "cd..") == 0) {
			current = pop(sroot);
			printf("\n");
		}
		else if (strcmp(command, "exit") == 0) {
			deleteStack(&s);
			Delete(&current);
			break;
		}
		else {
			printf("\nPogresan unos! Pokusajte ponovo!\n\n");
		}
	}
	return 0;
}

position print(position p) {
	if (p == NULL) {
		printf("...\n\n");
		return p;
	}
	printf("%s\n", p->name);
	print(p->sibling);
	return p;
}

position makedirectory(position p) {
	position q, temp;
	q = (position)malloc(sizeof(folder));
	if (!q)
	{
		printf("Can't allocate memory");
		return ERROR;
	}
	printf("\nUpisite naziv direktorija kojeg biste stvorili: ");
	scanf("%s", q->name);
	q->child = NULL;
	q->sibling = NULL;
	q->sibling = p->child;
	p->child = q;
	printf("\nUspjesno napravljen direktorij!\n\n");
	return q;
}

int push(pos head, position adr) {
	pos newElement = NULL;
	newElement = CreateStackElement(adr);
	if (!newElement) {
		return ERROR;
	}

	InsertAfter(head, newElement);

	return 0;
}

position pop(pos current)
{
	pos temp = NULL;
	position top = NULL;

	temp = current->next;
	current->next = temp->next;

	top = temp->adress;
	free(temp);

	return top;
}

pos CreateStackElement(position Adress) {
	pos newElement = NULL;
	newElement = (pos)malloc(sizeof(stack));
	if (!newElement)
	{
		printf("Can't allocate memory");
		return ERROR;
	}

	newElement->adress = Adress;
	newElement->next = NULL;

	return newElement;
}

int InsertAfter(pos position, pos newElement) {

	newElement->next = position->next;
	position->next = newElement;

	return 0;
}

position find(position current, char* name)
{
	position child = current->child;

	if (current == NULL)
		printf("\nDirektorij je prazan\n");

	while (child != NULL && strcmp(child->name, name) != 0)
		child = child->sibling;

	return child;
}

position Delete(position current)
{
	if (current == NULL)
	{
		return NULL;
	}

	Delete(current->sibling);
	Delete(current->child);

	free(current);

	return NULL;
}

int deleteStack(pos head)
{
	position temp = NULL;

	while (head->next != NULL)
	{
		temp = pop(head);
	}

	free(temp);

	printf("\nStog uspjesno obrisan!\n");

	return 1;
}