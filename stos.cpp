#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stos.h"

void print_student(student* s)
{
	printf("Imie: %s\nNazwisko: %s\nRok urodzenia: %d\n\n", s->imie, s->nazwisko, s->rok_uro);
}

void search_stack(stack* stos, const char* pole, const char* wzorzec) {
	if (!stos || !pole || !wzorzec) {
		printf("Nieprawidlowe dane!\n");
		return;
	}

	student* temp = stos->top;

	while (temp != NULL) {
		if (strcmp(pole, "imie") == 0 && temp->imie && strstr(temp->imie, wzorzec) != NULL) {
			print_student(temp);
		}
		else if (strcmp(pole, "nazwisko") == 0 && temp->nazwisko && strstr(temp->nazwisko, wzorzec) != NULL) {
			print_student(temp);
		}
		else if (strcmp(pole, "rok urodzenia") == 0 && temp->rok_uro == atoi(wzorzec)) {
			print_student(temp);
		}

		temp = temp->n;
	}
}

void free_student(student* s)
{
	if (!s) return;
	if (s->imie) free(s->imie);
	if (s->nazwisko) free(s->nazwisko);
	free(s);
}

stack* create_stack(int size)
{
	stack* new_stack = (stack*)malloc(sizeof(stack));
	if (!new_stack) 
	{ 
		printf("Blad alokacji pamieci!\n");
		return (stack*)NULL;
	}
	new_stack->size = size;
	new_stack->top = (student*)NULL;
	return new_stack;
}

student* create_student(char* imie, char* nazwisko, int rok_uro)
{
	student* new_student = (student*)malloc(sizeof(student));
	if (!new_student) {
		printf("Blad alokacji pamieci!\n");
		return (student*)NULL;
	}
	new_student->imie = (char*)malloc((strlen(imie) + 1) * sizeof(char));
	if (!new_student->imie)
	{
		free_student(new_student);
		printf("Blad alokacji pamieci!\n");
		return (student*)NULL;
	}
	strcpy(new_student->imie, imie);
	new_student->nazwisko = (char*)malloc((strlen(nazwisko) + 1) * sizeof(char));
	if (!new_student->nazwisko)
	{
		free_student(new_student);
		printf("Blad alokacji pamieci!\n");
		return (student*)NULL;
	}
	strcpy(new_student->nazwisko, nazwisko);
	new_student->rok_uro = rok_uro;
	new_student->n = (student*)NULL;
	return new_student;
}

int count(stack* stos)
{
	int n = 0;
	student* temp = stos->top;
	while (temp != NULL)
	{
		temp = temp->n;
		n++;
	}
	return n;
}

int push(stack* stos, char* imie, char* nazwisko, int rok_urodzenia)
{
	if (!stos) return 1;
	if (count(stos) == stos->size) return 2;
	student* new_student = create_student(imie, nazwisko, rok_urodzenia);
	if (!new_student) return 1;
	if (!(stos->top == NULL))
	{
		new_student->n = stos->top;
	}
	stos->top = new_student;
	return 0;

}

int pop(stack* stos)
{
	if (!stos) return 1;
	if (count(stos) == 0) return 2;
	student* temp = stos->top->n;
	print_student(stos->top);
	free_student(stos->top);
	stos->top = temp;
	return 0;
}

void print_stack(stack* stos)
{
	if (!stos) return;
	student* temp = stos->top;
	while (temp != NULL)
	{
		print_student(temp);
		temp = temp->n;
	}
}

void free_stack(stack* stos)
{
	delete_stack(stos);
	free(stos);
}

void delete_stack(stack* stos)
{
	if (!stos) return;
	student* temp1 = stos->top;
	student* temp2 = NULL;
	if (temp1 != NULL)
	{
		temp2 = temp1->n;
	}
	while (temp1 != NULL && temp1->n != NULL)
	{
		free_student(temp1);
		temp1 = temp2;
		if (temp1->n != NULL) temp2 = temp1->n;
	}

	stos->top = NULL;
}