/*Ovdje se nalaze sljedece funkcije :
			1)kreiranje datoteke proizvodi
			2)ucitavanje broja proizvoda iz dateke proizvodi.bin
			3)dinamicki zauzimanje memorije za sve proizvode 
			4)unos novih proizvoda u datoteku proizvodi.bin
			5)ispis proizvoda se nalazi u ovoj datoteci 
			6)funkcija za brisanje proizvoda 
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "function.h"
#include <string.h>
#include <stdlib.h>

PROIZVOD* ucitavanje_proizvoda(PROIZVOD* proizvod) {
	FILE* datoteka = NULL;
	char* ime_dat = "proizvodi.bin";
	int broj_proizvoda = ucitavanje_broja_proizvoda();//ucitavanje kupaca todo
	proizvod = (PROIZVOD*)calloc(broj_proizvoda, sizeof(PROIZVOD));
	if (proizvod != NULL) {
		datoteka = fopen(ime_dat, "rb");
		if (datoteka == NULL) {
			printf("Neuspjesno otvaranje datoteke za citanje\n");
		}
		else {
			rewind(datoteka);
			fseek(datoteka, 4, SEEK_SET);
			fread(proizvod, sizeof(PROIZVOD), broj_proizvoda, datoteka);
			fclose(datoteka);
		}
	}
	return proizvod;
}
int ucitavanje_broja_proizvoda(void) {
	int br_proizvoda = 0;
	FILE* datoteka = NULL;
	char* ime_dat = "proizvodi.bin";
	datoteka = fopen(ime_dat, "rb");
	if (datoteka != NULL) {
		rewind(datoteka);
		fread(&br_proizvoda, sizeof(int), 1, datoteka);
		fclose(datoteka);
	}
	else {
		printf("Nemoguce je saznati koliki je broj proizvoda u datoteci!\n");
		perror("error report:");
		printf("\nKraj programa\n");
		exit(EXIT_FAILURE);
	}
	return br_proizvoda;
}
void kreiranje_datoteke_proizvodi() {
	FILE* dat_proizvodi = NULL;
	char* ime_dat = "proizvodi.bin";
	dat_proizvodi = fopen(ime_dat, "rb");
	if (dat_proizvodi == NULL) {
		dat_proizvodi = fopen(ime_dat, "wb");
		if (dat_proizvodi == NULL) {
			printf("Ne mogucnost kreiranja datoteke proizvodi.bin\n ");
			perror("Kreiranje:");
			printf("\nKraj programa\n");
			exit(EXIT_FAILURE);
		}
		else {
			printf("Uspjesno kreirana datoteka proizvodi.bin\n");
			fclose(dat_proizvodi);
		}
	}
	else {
		fclose(dat_proizvodi);
	}
}
void unos_novih_proizvoda() {
	PROIZVOD novi_proizvod= { 0 };
	PROIZVOD* svi_proizvodi = NULL;
	FILE* datoteka = NULL;
	int flag = 1;
	int i = 0;
	char* ime_dat = "proizvodi.bin";
	int broj_proizvoda = ucitavanje_broja_proizvoda();
	//printf("%d-br kor", broj_proizvoda);
	
	if (broj_proizvoda == 0) {
		datoteka = fopen(ime_dat, "rb+");
		if (datoteka != NULL) {
			//todo ucitavanje novog proizvoda

			if (datoteka == NULL) {
				printf("Ne mogucnost kreiranja datoteke proizvodi.bin\n ");
				perror("Kreiranje:\n");
				printf("\nKraj programa\n");
				exit(EXIT_FAILURE);
			}
			else {
				printf("Unesite ime proizvoda\n");
				scanf(" %29s", &novi_proizvod.ime_proizvoda);
				printf("Unesite cijenu proizvoda\n");
				scanf(" %f", &novi_proizvod.cijena);
				printf("Unesite id proizvoda\n");
				scanf(" %d", &novi_proizvod.id);
				broj_proizvoda += 1;
				//printf("br%d", broj_proizvoda);
				fwrite(&broj_proizvoda, sizeof(int), 1, datoteka);
				rewind(datoteka);
				fseek(datoteka, 0, SEEK_END);
				fwrite(&novi_proizvod, sizeof(PROIZVOD), 1, datoteka);
				fclose(datoteka);
			}
		}
	}
	else {
		svi_proizvodi = ucitavanje_proizvoda(svi_proizvodi);
		if (svi_proizvodi == NULL) {
			printf("Ne mogucnost zauzimanja memorije\n ");
			perror("Zauzimanja memorije:\n");
			printf("\nKraj programa\n");
			exit(EXIT_FAILURE);
		}
		else {
			datoteka = fopen(ime_dat, "rb+");
			if (datoteka == NULL) {
				printf("Ne mogucnost otvaranja datoteke proizvodi.bin\n ");
				perror("Kreiranje:\n");
				printf("\nKraj programa\n");
				exit(EXIT_FAILURE);
			}
			else {
				do {
					flag = 1;
					printf("Unesite ime koje je razlicito od ostalih:\n");
					scanf(" %29s", &novi_proizvod.ime_proizvoda);
					for (i = 0; i < broj_proizvoda; i++) {
						if (strcmp((novi_proizvod.ime_proizvoda), (svi_proizvodi[i].ime_proizvoda)) == 0) {
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
				printf("Unesite cijenu proizvoda:\n");
				scanf(" %f", &novi_proizvod.cijena);
				do {
					flag = 1;
					printf("Unesite id koje je razlicit od ostalih:\n");
					scanf(" %d", &novi_proizvod.id);
					for (i = 0; i < broj_proizvoda; i++) {
						if (novi_proizvod.id==svi_proizvodi[i].id) {
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
			}
		}
		broj_proizvoda += 1;
		//printf("br%d", broj_proizvoda);
		fwrite(&broj_proizvoda, sizeof(int), 1, datoteka);
		rewind(datoteka);
		fseek(datoteka, 0, SEEK_END);
		fwrite(&novi_proizvod, sizeof(PROIZVOD), 1, datoteka);
		fclose(datoteka);
		//todo ucitavanje proizvoda novog ako nije 0 proizvoda
		//printf("else");
	}
	//_getch();
	free(svi_proizvodi);
}
int ispis_proizvoda(int korisnik,KUPAC*ime) {
	PROIZVOD* proizvodi = NULL;
	PROIZVOD pomoc = { 0 };
	PROIZVOD temp = { 0 };
	FILE *datoteka = NULL;
	int br_kupaca = ucitavanje_broja_korisnika();
	char* ime_dat = "proizvodi.txt";
	int odabir_ispisa ;
	int i = 0,j=0;
	int flag = 0;
	char nema_narudzbe = "0";
	char ima_narudzbe = "1";
	int indeks_korisnika = 0;
	KUPAC* kupci=NULL;
	FILE* datoteka_kupci;
	char* ime_dat_kupci = "kupci.bin";
	int br_proizvoda = ucitavanje_broja_proizvoda();

	proizvodi = ucitavanje_proizvoda(proizvodi);

	if (proizvodi == NULL) {
		printf("Ne mogucnost zauzimanja memorije  za proizvode.\n ");
		perror("Zauzimanja memorije:\n");
		printf("\nKraj programa\n");
		exit(EXIT_FAILURE);
	}
	else {
		do {
			flag = 0;
			system("cls"); // brisanje konzolnog ekrana
			printf("Odaberite po kojim kriterijima zelite ispisati i pretraziti proizvode.\n");
			printf("1)Ispis svih proizvoda i svih podataka o njemu\n");
			printf("2)Pretraga proizvoda po imenu i ispis podataka o proizvodu ako postoji\n");
			printf("3)Ispis svih proizvoda s trazenom cijenom\n");
			printf("4)Pretraga proizvoda po imenu i cijieni te ispis ako ga ima \n");
			printf("5)Ispis svih proizvoda u datoteku proizvodi.txt\n");
			printf("6)Sortiranje proizvoda od najjeftinijeg prema najskupljem\n");
			printf("7)Sortiranje proizvoda od najskupljeg prema najjeftinijem \n");
			printf("8)Narudzba novih proizvoda\n");
			if (korisnik == 1) {
				printf("9)ispis proizvoda s njegovim id-jem\n");
			}
			printf("0)izlazak iz izbornika i povratak u vas glavni izbornik\n");
			if (korisnik == 0) {//za korisnika
				do {
					scanf("%d", &odabir_ispisa);
					if (odabir_ispisa < 0 || odabir_ispisa>8)
						printf("Krivi unos pokusajte opet:\n");
				} while (odabir_ispisa < 0 || odabir_ispisa>8);
			}
			if (korisnik == 1) {//za admina 
				do {
					scanf("%d", &odabir_ispisa);
					if (odabir_ispisa < 0 || odabir_ispisa>9)
						printf("Krivi unos pokusajte opet:\n");
				} while (odabir_ispisa < 0 || odabir_ispisa>9);
			}
			switch (odabir_ispisa)
			{
			case 1:
				for (i = 0; i < br_proizvoda; i++) {
					printf("Ime:%s \t Cijena:%f kn \n", (proizvodi + i)->ime_proizvoda, (proizvodi + i)->cijena);
				}
				break;
			case 2:
				printf("Printf unesite ime proizvoda kojeg zelite:\n");
				scanf(" %29s", &pomoc.ime_proizvoda);
				for (i = 0; i < br_proizvoda; i++) {
					if (strcmp(pomoc.ime_proizvoda, (proizvodi + i)->ime_proizvoda) == 0) {
						printf("Ime:%s \t Cijena:%f kn \n", (proizvodi + i)->ime_proizvoda, (proizvodi + i)->cijena);
						flag = 1;
					}
					if (flag == 0 && i == br_proizvoda - 1) {
						printf("Proizvod s tim imenom ne postoji u trgovini.\n");
					}
				}
				break;
			case 3:
				printf("Printf unesite cijenu proizvoda:\n");
				scanf(" %f", &pomoc.cijena);
				for (i = 0; i < br_proizvoda; i++) {
					if (pomoc.cijena==(proizvodi+i)->cijena) {
						printf("Ime:%s \t Cijena:%f kn  \n", (proizvodi + i)->ime_proizvoda, (proizvodi + i)->cijena);
						flag = 1;
					}
					if (flag == 0 && i == br_proizvoda - 1) {
						printf("Proizvod s tom cijenom ne postoji u trgovini.\n");
					}
				}
				break;
			case 4:
				printf("Unesite ime trazenog proizvoda:\n");
				scanf(" %29s", &pomoc.ime_proizvoda);
				printf("Printf unesite cijenu proizvoda:\n");
				scanf(" %f", &pomoc.cijena);
				for (i = 0; i < br_proizvoda; i++) {
					if (strcmp(pomoc.ime_proizvoda, (proizvodi + i)->ime_proizvoda) == 0) {
						if (pomoc.cijena == (proizvodi + i)->cijena) {
							printf("Ime:%s \t Cijena:%f kn\n", (proizvodi + i)->ime_proizvoda, (proizvodi + i)->cijena);
							flag = 1;
						}
					}
				}
				if (flag == 0 && i == br_proizvoda - 1) {
					printf("Proizvod s tim imenom i cijenom ne postoji u trgovini.\n");
				}
				break;
			case 5:
				datoteka=fopen(ime_dat, "w");
				if (datoteka == NULL) {
					printf("Ne mogucnost otvaranja datoteke proizvodi.bin\n ");
					perror("Kreiranje:\n");
					printf("\nKraj programa\n");
					exit(EXIT_FAILURE);
				}
				else {
					for(i=0;i<br_proizvoda;i++)
					fprintf(datoteka, "Ime:%s \t Cijena:%f kn \n", (proizvodi + i)->ime_proizvoda, (proizvodi + i)->cijena);
					printf("Preuzmite datoeku s zeljenim podatcima(proizvodi.txt).\n");
					fclose(datoteka);
				}
				break;
			case 6:
				// sortiranje uzlazno
				for (i = 0; i < br_proizvoda - 1; i++) {
					for( j = 0; j < br_proizvoda - 1 - i; j++) {
						if ((proizvodi + j + 1)->cijena < (proizvodi + j)->cijena) {
							strcpy(temp.ime_proizvoda, (proizvodi + j)->ime_proizvoda);
							temp.id = (proizvodi + j)->id;
							temp.cijena = (proizvodi + j)->cijena;
							strcpy((proizvodi + j)->ime_proizvoda, (proizvodi + j + 1)->ime_proizvoda);
							(proizvodi + j)->id = (proizvodi + j + 1)->id;
							(proizvodi + j)->cijena = (proizvodi + j + 1)->cijena;
							strcpy((proizvodi + j + 1)->ime_proizvoda, temp.ime_proizvoda);
							(proizvodi + j + 1)->id = temp.id;
							(proizvodi + j + 1)->cijena = temp.cijena;
						}
					}
				}
				printf("Popis je sortiran od manje cijene prema vecoj\n");
				for (i = 0; i < br_proizvoda; i++) {
					printf("Ime:%s \t Cijena:%f kn \n", (proizvodi + i)->ime_proizvoda, (proizvodi + i)->cijena);
				}
				break;
			case 7:
				//sortiranje silazno 
				for (i = 0; i < br_proizvoda - 1; i++) {
					for (j = 0; j < br_proizvoda - 1 - i; j++) {
						if ((proizvodi + j + 1)->cijena > (proizvodi + j)->cijena) {
							strcpy(temp.ime_proizvoda, (proizvodi + j)->ime_proizvoda);
							temp.id = (proizvodi + j)->id;
							temp.cijena = (proizvodi + j)->cijena;
							strcpy((proizvodi + j)->ime_proizvoda, (proizvodi + j + 1)->ime_proizvoda);
							(proizvodi + j)->id = (proizvodi + j + 1)->id;
							(proizvodi + j)->cijena = (proizvodi + j + 1)->cijena;
							strcpy((proizvodi + j + 1)->ime_proizvoda, temp.ime_proizvoda);
							(proizvodi + j + 1)->id = temp.id;
							(proizvodi + j + 1)->cijena = temp.cijena;
						}
					}
				}
				printf("Popis je sortiran od vece cijene prema manjoj\n");
				for (i = 0; i < br_proizvoda; i++) {
					printf("Ime:%s \t Cijena:%f kn \n", (proizvodi + i)->ime_proizvoda, (proizvodi + i)->cijena);
				}
				break;
			case 8:
				kupci = ucitavanje_kupaca(kupci);
				if (kupci != NULL) {
					for (i = 0; i < br_kupaca; i++) {
						if (strcmp(ime->korisnicko_ime, kupci->korisnicko_ime) == 0) {
							indeks_korisnika = i;
						}
					}
					printf("Svi proizvodi u trgovini su:\n");
					for (i = 0; i < br_proizvoda; i++) {
						printf("Ime:%s \t Cijena:%f kn \n", (proizvodi + i)->ime_proizvoda, (proizvodi + i)->cijena);
					}
					(kupci + indeks_korisnika)->kupljeni_proizvod.stanje = 0;
					printf("Unesite ime proizvoda koji zelite kupiti\n");
					scanf(" %29s", &pomoc.ime_proizvoda);
					for (i = 0; i < br_proizvoda; i++) {
						if (strcmp(pomoc.ime_proizvoda, (proizvodi + i)->ime_proizvoda) == 0) {
							strcpy(((kupci + indeks_korisnika)->kupljeni_proizvod.ime_kupljenog_proizvoda), pomoc.ime_proizvoda);
							//printf("\n%s", ((kupci + indeks_korisnika)->kupljeni_proizvod.ime_kupljenog_proizvoda));
							(kupci + indeks_korisnika)->kupljeni_proizvod.stanje = 1;
							printf("Uspjesno poslana narudzba\n");
							flag = 1;
						}
						if (flag == 0 && i == br_proizvoda - 1) {
							printf("Proizvod s tim imenom ne postoji u trgovini.\n");
						}
					}
					datoteka_kupci=fopen(ime_dat_kupci, "rb+");
					if (datoteka_kupci != NULL) {
						rewind(datoteka_kupci);
						fseek(datoteka_kupci, 4, SEEK_SET);
						fwrite(kupci, sizeof(KUPAC),br_kupaca, datoteka_kupci);
						fclose(datoteka_kupci);
					}
					free(kupci);
				}
				break;
			case 9:
				for (i = 0; i < br_proizvoda; i++) {
					printf("Ime:%s \t Cijena:%f kn \t Id:%d \n", (proizvodi + i)->ime_proizvoda, (proizvodi + i)->cijena, (proizvodi + i)->id);
				}
				break;
			case 0:
				odabir_ispisa = kraj_programa();
				if (korisnik == 1 && odabir_ispisa==0) {
					return 0;
					free(proizvodi);
					
					admin_izbornik(ime);
				}
				if (korisnik == 0 && odabir_ispisa == 0) {
					free(proizvodi);
					izbornik_korisnici(ime);
				}
				break;
			}
			_getch();
		} while (odabir_ispisa != 0);
	}
}

int brisanje_proizvoda(PROIZVOD* proizvodi, int br_proizvoda) {
	int i = 0;
	int j = 0;
	int flag = 0;
	PROIZVOD brisanje = { 0 };
	PROIZVOD temp;
	FILE* datoteka = NULL;
	char* dat_ime = "proizvodi.bin";
	PROIZVOD* Pomoc;
	if (br_proizvoda == 0) {
		printf("Ne postoji ni jedan proizvod u datoteci te se ova funkcija ne može izvršiti.\n");
		return 0;
	}
	else {
		proizvodi = ucitavanje_proizvoda(proizvodi);
		if (proizvodi == NULL) {
			printf("Nemoguce je procitati proizovde iz datoteke\n");
			_getch();
			exit(EXIT_FAILURE);
		}
		else {
			printf("Unesite ime  proizvoda kojega zelite obrisati\n ");
			scanf(" %29s", &brisanje.ime_proizvoda);
			printf("Unesite id proizvoda\n");
			scanf(" %d", &brisanje.id);
			for (i = 0; i < br_proizvoda; i++) {
				if (strcmp(brisanje.ime_proizvoda, (proizvodi + i)->ime_proizvoda) == 0 && brisanje.id==(proizvodi + i)->id) {
					flag = 1;
					for (j = i; j < br_proizvoda; j++) {
						if (j + 1 == br_proizvoda) {
							break;
						}
						//printf("Ulazak\n");
						strcpy(temp.ime_proizvoda, (proizvodi + j)->ime_proizvoda);
						//printf("temp ime-%s\n",temp.ime_proizvoda);
						temp.id = (proizvodi + j)->id;
						temp.cijena = (proizvodi + j)->cijena;
						strcpy((proizvodi + j)->ime_proizvoda, (proizvodi + j+1)->ime_proizvoda);
						//printf("proizvod j-%s\n", (proizvodi + j)->ime_proizvoda);
						(proizvodi + j)->id = (proizvodi + j + 1)->id;
						(proizvodi + j)->cijena = (proizvodi + j + 1)->cijena;
						strcpy((proizvodi + j + 1)->ime_proizvoda, temp.ime_proizvoda);
						(proizvodi + j + 1)->id = temp.id;
						(proizvodi + j + 1)->cijena = temp.cijena;
						//printf("proizvod j+1-%s\n", (proizvodi + j+1)->ime_proizvoda);

					}
				}
			}
			Pomoc= (PROIZVOD*)calloc(br_proizvoda-1, sizeof(PROIZVOD));
			if (Pomoc != NULL) {
				for (i = 0; i < br_proizvoda - 1; i++) {
					strcpy((Pomoc + i)->ime_proizvoda, (proizvodi + i)->ime_proizvoda);
					(Pomoc + i)->cijena = (proizvodi + i)->cijena;
					(Pomoc + i)->id = (proizvodi + i)->id;
				}
			}
			else {
				flag = 0;
				exit(EXIT_FAILURE);
			}
			if (flag == 1) {
				datoteka = fopen(dat_ime, "rb+");
				if (datoteka != NULL) {
					br_proizvoda = br_proizvoda - 1;
					fwrite(&br_proizvoda, sizeof(int), 1, datoteka);
					rewind(datoteka);
					fseek(datoteka, 4, SEEK_SET);
					fwrite(Pomoc, sizeof(PROIZVOD), br_proizvoda, datoteka);
					fclose(datoteka);
				}
			}
			free(Pomoc);
			free(proizvodi);
			_getch();
		}
	}
	return flag;
}