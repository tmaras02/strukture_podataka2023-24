#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX_LINE 1024
#define ALLOCATION_ERROR (-1)
#define FILE_OPEN_ERROR (-2)

struct _polinom;
typedef struct _polinom* position;
typedef struct _polinom {
	int coef;
	int exp;
	position next;
}polinom;

int input(char[MAX_LINE], position, position);
int sort(position, position);
int print(position);
int deleteAll(position p);

int main() {
	polinom Head;
	polinom Head2;

	Head.next = NULL;
	Head2.next = NULL;

	char filename[MAX_LINE];

	printf("Enter file name: ");
	scanf("%s", filename);
	printf("\n");

	input(filename, &Head, &Head2);
	print(&Head);
	print(&Head2);

	deleteAll(&Head);
	deleteAll(&Head2);

	return 0;
}

int input(char filename[MAX_LINE], position pos, position pos2) {
	position q = NULL;
	q = (position)malloc(sizeof(polinom));
	if (q == NULL)
	{
		printf("\nCan't allocate memory!\n");
		return ALLOCATION_ERROR;
	}

	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Dear customer, the file %s didn't open! Possible wrong insert!\r\n", filename);
		return FILE_OPEN_ERROR;
	}

	char buffer[MAX_LINE];
	char* p = buffer;
	int n = 0;
	int e = 0;
	int c = 0;

	fgets(buffer, MAX_LINE, fp);

	while (strlen(p) > 0) {
		sscanf(p, "%d %d %n", &c, &e, &n);
		p += n;
		q->coef = c;
		q->exp = e;
		sort(pos, q);
		q = (position)malloc(sizeof(polinom));
		if (q == NULL)
		{
			printf("\nCan't allocate memory!\n");
			return ALLOCATION_ERROR;
		}
	}

	fgets(buffer, MAX_LINE, fp);
	p = buffer;

	while (strlen(p) > 0) {
		sscanf(p, "%d %d %n", &c, &e, &n);
		p += n;
		q->coef = c;
		q->exp = e;
		sort(pos2, q);
		q = (position)malloc(sizeof(polinom));
		if (q == NULL)
		{
			printf("\nCan't allocate memory!\n");
			return ALLOCATION_ERROR;
		}
	}

	return 0;
}

int sort(position pos, position q) {
	while (pos->next != NULL && pos->next->exp < q->exp) {
		pos = pos->next;
	}
	q->next = pos->next;
	pos->next = q;

	return 0;
}

int print(position pos) {
	pos = pos->next;

	while (pos != NULL) {
		if (pos->coef != 0) {
			printf("%dx^%d  ", pos->coef, pos->exp);
			pos = pos->next;
		}
		else
			pos = pos->next;
	}

	printf("\n\n");

	return 0;
}

int deleteAll(position p) {
	position q = NULL;
	while (p->next != 0) {
		q = p->next;
		p->next = q->next;
		free(q);
	}
	return 0;
}