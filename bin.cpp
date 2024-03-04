#include "plik_bin.h"
#include "stos.h"
#include <stdio.h>
// nowy komentarz
void zapis_do_bin(char* nazwa_pliku, stack* stos)
{
    FILE* plik = fopen(nazwa_pliku, "wb");
    if (!plik)
    {
        printf("Blad otwierania pliku!\n");
        return;
    }

    student* temp = stos->top;
    for (int i = 0; i < count(stos) && temp != NULL; i++)
    {
        student* temp = stos->top;
        for (int j = 0; j < count(stos) - i - 1; j++)
        {
            temp = temp->n;
        }
        fwrite(temp->imie, sizeof(char), 20, plik);
        fwrite(temp->nazwisko, sizeof(char), 20, plik);
        fwrite(&(temp->rok_uro), sizeof(int), 1, plik);

    }

    fclose(plik);
    printf("Zapisano do pliku\n");
}

void odczyt_z_bin(char* nazwa_pliku, stack* stos)
{
    FILE* plik = fopen(nazwa_pliku, "rb");
    if (!plik)
    {
        printf("Blad otwierania pliku!\n");
        return;
    }
    delete_stack(stos);

    char imie[20];
    char nazwisko[20];
    int rok_uro;

    while (fread(imie, sizeof(char), 20, plik) == 20 &&
        fread(nazwisko, sizeof(char), 20, plik) == 20 &&
        fread(&rok_uro, sizeof(int), 1, plik) == 1)
    {
        push(stos, imie, nazwisko, rok_uro);
    }

    fclose(plik);
    printf("Odczytano dane\n");
}

