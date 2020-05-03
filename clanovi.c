/*ovdje se nalaze sljedece funcije :
			1)kreiranje datoteke clanovi.bin
			2)prijava korisnika u sustav
			3)registracija novih korisnika u sustav
			4)Funcija koja dohvaca broj korisnika koji su uneseni u datoteku
			5)Funcija koja dinamicki zauzima memoriju za sve korisnike zbog registracije i prijave korisnika je potrebna
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "function.h"
#include <string.h>
#include <stdlib.h>
//clanovi dio funkcije

void kreiranje_datoteke_clanovi() {
	FILE* dat_clanovi = NULL;
	char* ime_dat = "kupci.bin";
	dat_clanovi = fopen(ime_dat, "rb");
	if (dat_clanovi == NULL) {
		dat_clanovi = fopen(ime_dat, "wb");
		if (dat_clanovi == NULL) {
			printf("Ne mogucnost kreiranja datoteke clanovi.bin\n ");
			perror("Kreiranje:");
			printf("\nKraj programa\n");
			exit(EXIT_FAILURE);
		}
		else {
			printf("Uspjesno kreirana datoteka clanovi.bin\n");
			fclose(dat_clanovi);
		}
	}
	else {
		fclose(dat_clanovi);
	}
}

//funkcija provjerava koliko je upisanih korisnika u sustavu te vraca ukupan broj korisnika toga sustava
int ucitavanje_broja_korisnika(void) {
	int br_korisnika = 0;
	FILE* datoteka = NULL;
	char* ime_dat = "kupci.bin";
	datoteka = fopen(ime_dat, "rb");
	if (datoteka != NULL) {
		rewind(datoteka);
		fread(&br_korisnika, sizeof(int), 1, datoteka);
		fclose(datoteka);
	}
	else {
		printf("Nemoguce je saznati koliki je broj korisnika iz datoteke!\n");
		perror("error report:");
		printf("\nKraj programa\n");
		exit(EXIT_FAILURE);
	}
	return br_korisnika;
}

void registracija_u_sustav() {
	FILE* datoteka = NULL;
	char* ime_dat = "kupci.bin";
	KUPAC novi_korisnik = {0};
	int duljina_lozinke = 0;
	int br_korisnika = ucitavanje_broja_korisnika();
	int* broj_korisnika=& br_korisnika;
	int pom_br = *broj_korisnika;
	KUPAC* kupci=NULL;
	int flag = 1;
	int i = 0;
	int pom = 0;
	
	if (*broj_korisnika == 0) {
		datoteka = fopen(ime_dat, "wb");
		if (datoteka != NULL) {
			//printf("prvi ");
			printf("Unesite korisnicko ime:\n");
			scanf(" %29s", &novi_korisnik.korisnicko_ime);
			printf("Unesite lozinku\n");
			printf("Lozinka mora biti minimalno 4 znaka duljine:\n");
			do {
				scanf(" %9s", &novi_korisnik.lozinka);
				duljina_lozinke = strlen(novi_korisnik.lozinka, 10);
				//printf("%d\n", duljina_lozinke);
				if (duljina_lozinke < 5) {
					printf("Lozinka je prekratka morate biti duza od 4 znaka, ponovite unos:\n");
				}
				if (duljina_lozinke > 9) {
					printf("Lozinka je predugacka mora biti kraca od 10 znakova:\n");
				}
			} while (duljina_lozinke < 5 || duljina_lozinke> 9);
			printf("Unesite id novog korisnika:\n");
			scanf(" %d", &novi_korisnik.id);
			//izmjena stanja kupnje
			novi_korisnik.kupljeni_proizvod.stanje=0;
			*broj_korisnika += 1;
			pom_br = *broj_korisnika;
			//printf("br%d", *broj_korisnika);
			fwrite(&pom_br, sizeof(int), 1, datoteka);
			rewind(datoteka);
			fseek(datoteka, 0, SEEK_END);
			fwrite(&novi_korisnik, sizeof(KUPAC), 1, datoteka);
			fclose(datoteka);
		}
		else {
			printf("Datoteka za zapisivanje korisnika nije se u mogucnosti otvoriti!\n");
			perror("Otvaranje(error report):");
			printf("\nKraj programa\n");
			exit(EXIT_FAILURE);
		}
	}
	else {
		//printf("drugi ");
		datoteka = fopen(ime_dat, "rb+");
		if (datoteka != NULL) {
			//kupci = (KUPAC*)calloc(pom_br, sizeof(KUPAC));
			kupci = ucitavanje_kupaca(&kupci);
			if (kupci == NULL) {
				printf("nemoguce zauzeti memoriju za kupce\n");
			}
			//printf("BROJ KORISNIKA %d\n", *broj_korisnika);
			/*for (i = 0; i < *broj_korisnika; i++) {
				printf("%s\n", (kupci + i)->korisnicko_ime);
			}*/
			do {
				flag = 1;
				printf("Unesite ime koje je razlicito od ostalih\n");
				scanf("%s", &novi_korisnik.korisnicko_ime);
				for (i = 0; i < *broj_korisnika; i++) {
					if (strcmp((novi_korisnik.korisnicko_ime),( kupci[i].korisnicko_ime)) == 0 ) {
						flag= 0;
						break;
					}
				}
				if (flag == 1) {
					//printf("strging are not equal");
					break;
				}
				i = 0;
			} while (flag == 0);
			
			printf("Unesite lozinku\n");
			printf("Lozinka mora biti minimalno 4 znaka duljine a maksimalno 9:\n");
			do {
				scanf(" %9s", &novi_korisnik.lozinka);
				duljina_lozinke = strlen(novi_korisnik.lozinka, 10);
				//printf("%d\n", duljina_lozinke);
				if (duljina_lozinke < 5) {
					printf("Lozinka je prekratka morate biti duza od 4 znaka, ponovite unos:\n");
				}
				if (duljina_lozinke > 9) {
					printf("Lozinka je predugacka mora biti kraca od 10 znakova:\n");
				}
			} while (duljina_lozinke < 5 || duljina_lozinke> 9);

			do {
				flag = 1;
				printf("Unesite id korisnika koji je razlicit od ostalih:\n");
				scanf(" %d", &novi_korisnik.id);
				for (i = 0; i < *broj_korisnika; i++) {
					if (novi_korisnik.id==kupci[i].id) {
						flag = 0;
						break;
					}
				}
				if (flag == 1) {
					//printf("strging are not equal");
					break;
				}
				i = 0;
			} while (flag == 0);

			*broj_korisnika += 1;
			
			pom_br = *broj_korisnika;
			//izmjena
			novi_korisnik.kupljeni_proizvod.stanje = 0;
			//printf("%d-pom", pom_br);
			//printf("br%d", *broj_korisnika);
			fwrite(&pom_br, sizeof(int), 1, datoteka);
			rewind(datoteka);
			fseek(datoteka, 0, SEEK_END);
			fwrite(&novi_korisnik, sizeof(KUPAC), 1, datoteka);
			fclose(datoteka);
		}
		else {
			printf("Datoteka za zapisivanje korisnika nije se u mogucnosti otvoriti!\n");
			perror("Otvaranje(error report):");
			printf("\nKraj programa\n");
			exit(EXIT_FAILURE);
		}
	}
	free(kupci);
}
KUPAC* ucitavanje_kupaca(KUPAC* kupci) {
	FILE* datoteka = NULL;
	char* ime_dat = "kupci.bin";
	int broj_kupaca = 0;
	broj_kupaca = ucitavanje_broja_korisnika();
	kupci = (KUPAC*)calloc(broj_kupaca, sizeof(KUPAC));
	if (kupci != NULL) {
		datoteka = fopen(ime_dat, "rb");
		if (datoteka == NULL) {
			printf("neuspjesno otvaranje datoteke za citanje\n");
		}
		else {
			rewind(datoteka);
			fseek(datoteka, 4, SEEK_SET);
			fread(kupci, sizeof(KUPAC), broj_kupaca, datoteka);
			fclose(datoteka);
		}
		return kupci;
	}
	return kupci;
}

int prijava_korisnika(KUPAC*ime) {
	int br_korisnika = ucitavanje_broja_korisnika();
	FILE* datoteka;
	char* ime_datoteke = "kuoci.bin";
	KUPAC korisnik;
	int brojac = 0;
	KUPAC* kupci = NULL;
	int flag = 0,i=0,j=0;
	
	kupci = ucitavanje_kupaca(&kupci);

	if (kupci == NULL) {
		printf("Nemoguce zauzeti memoriju\n");
		exit(EXIT_FAILURE);
	}
	else {
		printf("Molim vas unesite trazene podatke kako bi ste se prijavili u sustav.\n");
		printf("Imate za to tri pokusaja.\n");
		do {
			flag = 0;
			printf("Unesite korisnicko ime\n");
			scanf(" %s", &korisnik.korisnicko_ime);
			for (i = 0; i < br_korisnika; i++) {
				if (strcmp((korisnik.korisnicko_ime), (kupci[i].korisnicko_ime)) == 0) {
					printf("Unesite lozinku\n");
					scanf(" %s", &korisnik.lozinka);
					for (j = 0; j < br_korisnika; j++) {
						if (strcmp((korisnik.lozinka), (kupci[j].lozinka)) == 0) {
							printf("Uspjesna prijava u sustav\n");
							printf("Za nastavak stisnite bilokuju tipku\n");
							strcpy(ime->korisnicko_ime, korisnik.korisnicko_ime);
							_getch();
							flag = 1;
							//printf("%d-flag-unos\n", flag);
							break;
						}
						if (flag == 0 && j==br_korisnika-1) {
							printf("Kriva lozinka\n");
							flag = 0;
						}
						//printf("%d-flag\n", flag);
					}
					//printf("%d-flag-unos-izlaz\n", flag);
					if (flag == 1) {
						break;
					}
				}
			}
			brojac++;
			//printf("%d-flag-kraj\n",flag);
			if (flag == 1||brojac==3) {
				if (flag == 1) {
					free(kupci);
					return 0;
				}
				break;
			}

		} while (flag == 0);	
	}
	free(kupci);
	return 1;
}