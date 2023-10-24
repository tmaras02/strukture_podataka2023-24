#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH (50)
#define ALLOCATION_ERROR (-1)

struct _person;
typedef struct _person* Position;
typedef struct _person
{
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int birthYear;
	Position next;
} person;

Position createPerson();
int addFront(Position p);
Position findLast();
int addBehind(Position p);
int Print(Position p);
int searchPerSurname(Position p);
int Delete(Position p);
int menu();

int main()
{
	person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };

	menu(&Head);

	return EXIT_SUCCESS;
}

Position createPerson() // Creates new element (person) that can be added to list
{
	Position newPerson = NULL;
	char name[MAX_LENGTH] = { 0 };
	char surname[MAX_LENGTH] = { 0 };
	int birthYear = 0;

	newPerson = (Position)malloc(sizeof(person));
	if (!newPerson)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}

	printf("Enter name:\n");
	scanf(" %s", newPerson->name);
	printf("Enter surname:\n");
	scanf(" %s", newPerson->surname);
	printf("Enter birth year:\n");
	scanf(" %d", &newPerson->birthYear);

	return newPerson;
}

int addFront(Position head) // Add element at the front of the list
{
	Position newPerson = NULL;

	newPerson = createPerson();

	if (newPerson)
	{
		newPerson->next = head->next;
		head->next = newPerson;
	}

	return EXIT_SUCCESS;
}

Position findLast(Position head) // Finds last element of the list
{
	while (head->next != NULL)
	{
		head = head->next;
	}
	return head;
}

int addBehind(Position head) // Add element at the end of the list
{
	Position newPerson = NULL;

	newPerson = createPerson();

	if (newPerson)
	{
		newPerson->next = head->next;
		head->next = newPerson;
	}

	return EXIT_SUCCESS;
}

int Print(Position head) // Prints list
{
	while (head != NULL)
	{
		printf("\n%s %s %d \n\n", head->name, head->surname, head->birthYear);
		head = head->next;
	}

	return 0;
}

int searchPerSurname(Position p) // Findes person based on surname and prints memory adress of that person
{
	char sur[MAX_LENGTH];

	printf("\nEnter surname of person you want to find: ");
	scanf("%s", &sur);

	while (p != NULL && strcmp(sur, p->surname) != 0)
	{
		p = p->next;
	}
	if (p == NULL)
		printf("\nPerson wtih surname you entered does not exist!\n\n");
	else
		printf("\nMemory adress of searched person is: %p\n\n", p);

	return EXIT_SUCCESS;
}

int Delete(Position p) // Deletes person based on surname
{
	Position pret = NULL;
	char prez[MAX_LENGTH];

	printf("\nEnter surname of person you want to delete: ");
	scanf("%s", &prez);
	printf("\n");

	while (p->next != NULL && strcmp(prez, p->surname) != 0)
	{
		pret = p;
		p = p->next;
	}

	if (pret != NULL && strcmp(prez, p->surname) == 0)
	{
		p = pret->next;
		pret->next = p->next;
	}

	return EXIT_SUCCESS;
}

int menu(Position Head)
{
	char choice;

	while (1) {
		printf("Enter: F -> Add in front, P -> Print, B -> Add behind, S -> Search per surname, D -> Delete, X -> Exit\n\n");
		printf("Unos: ");
		scanf(" %c", &choice);

		if (choice == 'F' || choice == 'f')
			addFront(Head);
		else if (choice == 'B' || choice == 'b')
			addBehind(Head);
		else if (choice == 'P' || choice == 'p')
			Print(Head->next);
		else if (choice == 'S' || choice == 's')
			searchPerSurname(Head->next);
		else if (choice == 'D' || choice == 'd')
			Delete(&Head);
		else if (choice == 'X' || choice == 'x')
			break;
		else
			printf("\nEntry error, please try again!\n\n");
	}

	return EXIT_SUCCESS;
}