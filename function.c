//ovdje se nalazi glavni izbornik,odabir za glavni izbornik , te funckija za kraj programa koja se koristi u vise razlicitih dijelova sustava
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "function.h"
#include <string.h>
#include <stdlib.h>

//odabir za izbornik
int odabir_korisnika () {
	int odabir=0;

	printf("Dobrodosli u trgovinu.\n\n");
	printf("Odaberite sto zelite:\n");
	printf("1)Login-u sustav\n");
	printf("2)Registracija-u sustav\n");
	printf("3)Administratorski-pristup\n");
	printf("0)Izlazak iz programa;\n");

	do {
		scanf(" %d", &odabir);
		if (odabir < 0 || odabir>3) {
			printf("Krivi odabir molim vas unesite ponovno\nPazite da taj odabir bude 1 ili 2 ili 3.\n");
		}
	} while (odabir < 0 || odabir>3);

	return odabir;
}

//glavni izbornik

void glavni_izbornik() {
	int odabir;
	int stanje_prijave = 0;
	ADMINISTRATOR admin1 = { 0, "Polanc","Doki" };
	ADMINISTRATOR* pok_admin = &admin1;
	KUPAC ime;//skladisti se korisnicko ime logiranog korisnika
	int login=1;
	do {
		system("cls"); // brisanje konzolnog ekrana
		odabir = odabir_korisnika();
		//vraca broj koji kazuje koji je korisnik odabran te kako ce sustav dalje funkcionirati 
		switch (odabir) {
		case 1:
			//Kupac s postojecim podatcima 
			login = prijava_korisnika(&ime);
			if (login == 0) {
				//printf("ime logiranog korisnika je %s", ime.korisnicko_ime);
				//_getch();
				izbornik_korisnici(&ime);
			}
			else {
				printf("Prijava u sustav nije uspjela pokusajte opet s ispravnim podatcima\n");
			}
			
			break;
		case 2:
			//Kupac s ne postojecim podatcima ->Potrebna registracija
			registracija_u_sustav();//dovrsiti funckiju registracija 
			break;
		case 3:
			//Administrator sustava-> Nadzor podataka, obavljanje naloga kupnje 
			stanje_prijave = prijava_admina(pok_admin);
			if (stanje_prijave == 1) {
				system("cls");
				admin_izbornik(&ime);
			}
			else {
				printf("Neuspjesna prijava admina u sustav. \n");
			}
			break;
		case 0:
			odabir = kraj_programa();
			if (odabir == 0) {
				printf("Kraj programa, stisnite bilo koju tipku za zavrsetak\n");
				_getch();
				exit(EXIT_SUCCESS);
			}
			else {
				printf("Pritisnite bilo koju tipku za nastavak programa\n");
			}
			break;
		}
		_getch();
	} while (odabir != 0);
}

int kraj_programa(void) {
	int kraj;
	char* nastavak = "ne";
	char* zavrsetak = "da";
	char unos[3];
	printf("\nJeste li sigurni da zelite izaci iz programa?\n");
	printf("Ako ste sigurni onda unesite 'da' \nako zelite i dalje nastaviti koristiti program unesite 'ne' i biti ce te vraceni u glavni izbornik\n");
	do {
		scanf(" %2s", &unos);
		if (strcmp(zavrsetak, unos) == 0) {
			kraj = 0;
			break;
		}
		if (strcmp(nastavak, unos) == 0) {
			kraj = 1;
			break;
		}
		if (strcmp(nastavak, unos) != 0 || strcmp(zavrsetak, unos) != 0) {
			printf("Krivi unos, trebate unjeti 'da' ili 'ne'\n");
		}
	} while (1);
	return kraj;
}
