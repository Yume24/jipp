#pragma once

typedef struct Student {
	char* imie;
	char* nazwisko;
	int rok_uro;
	struct Student* n;
} student;

typedef struct My_Stack {
	int size;
	student* top;
} stack;

stack* create_stack(int size);
student* create_student(char* imie, char* nazwisko, int rok_uro);
int push(stack* stos, char* imie, char* nazwisko, int rok_uro);
int pop(stack* stos);
int count(stack* stos);
void print_stack(stack* stos);
void print_student(student* student);
void search_stack(stack* stos, const char* pole, const char* kryterium);
void free_student(student* student);
void free_stack(stack* stos);
void delete_stack(stack* stos);