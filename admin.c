//ovdje se nalazi sustav za prijavu admina 
//te izbornik za admin dio sustava
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "function.h"
#include <string.h>
#include <stdlib.h>

//admin dio funkcije
int prijava_admina(ADMINISTRATOR* pok_admin) {
	int flag = 0;
	int i = 0;
	int j = 0;
	int br_admina = 1;
	ADMINISTRATOR pomoc;
	printf("Za prijavu imate 3 pokusaja\n");
	for (j = 0; j < 3; j++) {
		for (i = 0; i < br_admina; i++) {
			printf("Unesite korinicko ime:\n");
			scanf(" %29s", &pomoc.user_name);
			printf("Unesite lozinku:\n");
			scanf(" %9s", &pomoc.lozinka);
			if (strcmp(pomoc.user_name, pok_admin->user_name) == 0 && strcmp(pomoc.lozinka, pok_admin->lozinka) == 0) {
				printf("Uspjesno logiranje u sustav.\n");
				flag = 1;
				break;
			}
			else {
				printf("Pogrijesno unesen username ili lozinka pokusajte opet \n");
			}
		}
		if (strcmp(pomoc.user_name, pok_admin->user_name) == 0 && strcmp(pomoc.lozinka, pok_admin->lozinka) == 0) {
			break;
		}
	}
	return flag;
}

void admin_izbornik(KUPAC*ime) {
	FILE* datoteka_kupci = NULL;
	char *ime_dat_kupci = "kupci.bin";
	int odabir = 0;
	int pomoc = 0;
	int admin = 1;
	int stanje = 3;
	int i = 0;
	int kupnja_flag = 1;
	int br_korisnika = ucitavanje_broja_korisnika();
	KUPAC* kupci = NULL;
	KUPAC pretraga;
	int br_proizvoda = ucitavanje_broja_proizvoda();

	PROIZVOD* proizvodi = NULL;
	do {
		system("cls"); // brisanje konzolnog ekrana
		printf("Unesite koju radnju zelite da se izvrsi:\n");
		printf("1)dodavanje proizvoda\n");
		printf("2)brisanje proizvoda\n");
		printf("3)ispis svih proizvoda\n");
		printf("4)pregled narudzbi\n");
		printf("0)izlaz iz programa\n");
		do {
			scanf(" %d", &odabir);
			if (odabir < 0 || odabir>4) {
				printf("Krivi odabir molim vas unesite ponovno\nPazite da taj odabir bude 1 ili 2 ili 3.\n");
			}
		} while (odabir < 0 || odabir>4);
		switch (odabir)
		{
		case 1:
			unos_novih_proizvoda();
			break;
		case 2:
			//brisanjeproizvoda
			br_proizvoda = ucitavanje_broja_proizvoda();
			stanje = brisanje_proizvoda(proizvodi, br_proizvoda);
			if (stanje == 1) {
				printf("Uspjesno izbrisan trazeni proizvid\n");
			}
			if(stanje==0) {
				printf("Neuspjesno obrisan proizvod");
			}
			break;
		case 3:
			pomoc = ispis_proizvoda(admin,ime);
			break;
		case 4:
			//todo pregled narudzbi i njihova obrada
			kupci = ucitavanje_kupaca(kupci);
			if (kupci != NULL) {
				for (i = 0; i < br_korisnika; i++) {
					if ((kupci + i)->kupljeni_proizvod.stanje == 1) {
						printf("Ime kupca koji ima narudzbu je %s\n", (kupci + i)->korisnicko_ime);
					}
				}
				printf("Unesite ime kupca od kojega zelite procesuirati narudzbu\n");
				scanf(" %29s", pretraga.korisnicko_ime);
				for (i = 0; i < br_korisnika; i++) {
					if (strcmp(pretraga.korisnicko_ime, (kupci + i)->korisnicko_ime) == 0) {
						if ((kupci + i)->kupljeni_proizvod.stanje == 1) {
							printf("Ovaj korisnik je narucio %s\n", (kupci + i)->kupljeni_proizvod.ime_kupljenog_proizvoda);
							printf("Ako ce te isporuciti ovu narudzbu unesite 2 ako necete unesite 0 i obradite ju kasnije.\n");
							do {
								scanf(" %d", &kupnja_flag);

								if (kupnja_flag == 2) {
									(kupci + i)->kupljeni_proizvod.stanje == 2;
									printf("Narudzba poslana. \n");
									break;
									//todo zasto izade van 
								}

							} while (kupnja_flag != 0);
						}
					}
				}
				datoteka_kupci = fopen(ime_dat_kupci, "rb+");
				if (datoteka_kupci != NULL) {
					rewind(datoteka_kupci);
					fseek(datoteka_kupci, 4, SEEK_SET);
					fwrite(kupci, sizeof(KUPAC), br_korisnika, datoteka_kupci);
					fclose(datoteka_kupci);
				}
				free(kupci);
			}
			else {
				exit(EXIT_FAILURE);
			}
			break;
		case 0: 
			odabir = kraj_programa();
			if (odabir == 0) {
				printf("Kraj programa, stisnite bilo koju tipku za povratak u glavni izbornik\n");
				_getch();
				free(proizvodi);
				glavni_izbornik();
			}
			else {
				printf("Pritisnite bilo koju tipku za nastavak programa\n");
			}
			break;
		}
		_getch();
	} while (odabir = !0);
}
