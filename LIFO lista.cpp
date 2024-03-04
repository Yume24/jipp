#include <stdio.h>
#include "plik_bin.h"
#include "stos.h"
#include <string.h>
stack* stos;

void clearBuffer() 
{
    int i = 'a';
    while (i = fgetc(stdin) != '\n' && i != EOF);
}

enum MenuOption {
    DODAJ_ELEMENT = 1,
    POBIERZ_ELEMENT,
    WYSZUKAJ_ELEMENT,
    WYPISZ_WSZYSTKIE,
    SPRAWDZ_LICZBE_ELEMENTOW,
    USUN_STRUKTURE,
    ZAPIS_DO_PLIKU,
    ODCZYT_Z_PLIKU,
    ZAKONCZ_PROGRAM
};

void my_exit()
{
	free_stack(stos);
	exit(0);
}

int main()
{
	stos = create_stack(5);
    enum MenuOption option;
    do {
        char imie[20];
        char nazwisko[20];
        char nazwa_pliku[FILENAME_MAX];
        int rok_urodzenia = 0;
        char pole[20];
        char wartosc[20];
        printf("\nMENU (STOS):\n");
        printf("1. Dodaj element\n");
        printf("2. Pobierz element\n");
        printf("3. Wyszukaj element\n");
        printf("4. Wypisz wszystkie elementy\n");
        printf("5. Sprawdz liczbe elementow\n");
        printf("6. Usun strukture\n");
        printf("7. Zapisz do pliku binarnego\n");
        printf("8. Odczytaj z pliku binarnego\n");
        printf("9. Zakoncz program\n");
        printf("Wybierz opcje: ");
        
        scanf("%d", (int*)&option);
        clearBuffer();
        switch (option) {
        case DODAJ_ELEMENT:
            printf("Podaj imie: ");
            fgets(imie, 19, stdin);
            imie[strcspn(imie, "\n")] = 0;
            
            printf("Podaj nazwisko: ");
            
            fgets(nazwisko, 19, stdin);
            nazwisko[strcspn(nazwisko, "\n")] = 0;
            
            printf("Podaj rok urodzenia: ");
            if (scanf("%d", &rok_urodzenia) == 0) clearBuffer();
            if (push(stos, imie, nazwisko, rok_urodzenia) == 2) printf("Brak miejsca na stosie!\n");
            else printf("Dodano element");
            break;

        case POBIERZ_ELEMENT:
            if (pop(stos) == 2) printf("Brak elementow na stosie!\n");
            else printf("Pobrano element\n");
            break;

        case WYSZUKAJ_ELEMENT:
            printf("Jakie pole chcesz przeszukac?\nimie, nazwisko, rok urodzenia\n");
            fgets(pole, 19, stdin);
            pole[strcspn(pole, "\n")] = 0;
            printf("Jaka wartosc chcesz wyszukac?\n");
            fgets(wartosc, 19, stdin);
            wartosc[strcspn(wartosc, "\n")] = 0;
            printf("Pasujace rekordy:\n\n");
            search_stack(stos, pole, wartosc);
            break;

        case WYPISZ_WSZYSTKIE:
            print_stack(stos);
            break;

        case SPRAWDZ_LICZBE_ELEMENTOW:
            printf("Liczba elementow na stosie to: %d", count(stos));
            break;

        case USUN_STRUKTURE:
            delete_stack(stos);
            printf("Usunieto elementy stosu");
            break;

        case ZAPIS_DO_PLIKU:
            printf("Podaj nazwe pliku do ktorego chcesz zapisac: ");
            scanf("%259s", nazwa_pliku);
            clearBuffer();
            zapis_do_bin(nazwa_pliku, stos);
            break;

        case ODCZYT_Z_PLIKU:
            printf("Podaj nazwe pliku z ktorego chcesz odczytac: ");
            scanf("%259s", nazwa_pliku);
            odczyt_z_bin(nazwa_pliku, stos);
            break;

        case ZAKONCZ_PROGRAM:
            my_exit();
            break;

        default:
            printf("Niepoprawna opcja. Wybierz ponownie.\n");
            clearBuffer();
        }
        printf("\nNacisnij dowolny przycisk");
        _getch();
        system("cls");
    } while (option != ZAKONCZ_PROGRAM);
	
	return 0;
}