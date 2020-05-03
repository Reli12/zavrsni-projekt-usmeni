//izbornik za korisnike 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "function.h"
#include <string.h>
#include <stdlib.h>
void izbornik_korisnici(KUPAC*ime) {
	int odabir_clanovi;
	int korisnici = 0;
	int br_kupaca = ucitavanje_broja_korisnika();
	KUPAC* kupci = NULL;
	kupci=ucitavanje_kupaca(kupci);
	int pom = 1;
	int i = 0;
	int indeks_korisnika=0;
	if (kupci != NULL) {
		for (i = 0; i < br_kupaca; i++) {
			if (strcmp(ime->korisnicko_ime, kupci->korisnicko_ime) == 0) {
				indeks_korisnika = i;
			}
		}
	}

	do{
		system("cls"); // brisanje konzolnog ekrana
		printf("Unesite koju radnju zelite da se obavi\n");
		printf("1)Izbornik proizvoda i kupnja proizvoda");
		if (pom == 0)
			printf("(*)\n");
		else
			printf("\n");
		printf("2)Stanje narudzbe\n");
		printf("0)Izlazak iz izbornika i povratak u glavni izbornik\n");
		do {
			scanf("%d", &odabir_clanovi);
			if (odabir_clanovi < 0 || odabir_clanovi>2)
				printf("Krivi unos pokusajte opet \n");
		} while (odabir_clanovi < 0 || odabir_clanovi>2);
		switch (odabir_clanovi)
		{	
		case 1:
			free(kupci);
			pom = ispis_proizvoda(korisnici,ime);
			break;
		case 2:
			if ((kupci + indeks_korisnika)->kupljeni_proizvod.stanje == 0) {
				printf("Nema narucenih proizvoda .\n");
			}
			if ((kupci + indeks_korisnika)->kupljeni_proizvod.stanje == 1) {
				printf("Imate narucen proizvod-narudzba je u obradi. \n");
			}
			if ((kupci + indeks_korisnika)->kupljeni_proizvod.stanje == 2) {
				printf("Narudzba je poslana.\n");
			}
			break;
		case 0: 
			odabir_clanovi = kraj_programa();
			if (odabir_clanovi == 0) {
				free(kupci);
				glavni_izbornik();
				break;
			}
			break;
		}
		_getch();
	} while (odabir_clanovi!=0);
}