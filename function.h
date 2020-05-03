//deklaracija svih struktura i funkcija se nalazi u ovom zaglavlju
#ifndef FUNCTION_H
#define FUNCTION_H
typedef struct kupnja {
	char ime_kupljenog_proizvoda[30];
	int stanje;
}KUPNJA;
typedef struct kupac{
	int id;
	char korisnicko_ime[30];
	char lozinka[10];
	KUPNJA kupljeni_proizvod;
}KUPAC;

typedef struct administrator{
	int id_aministrator;
	char user_name[30];
	char lozinka[10];
}ADMINISTRATOR;

typedef struct proizvodi {
	int id;
	char ime_proizvoda[30];
	float cijena;
}PROIZVOD;



KUPAC* ucitavanje_kupaca(KUPAC**);

int odabir_korisnika();

int kraj_programa(void);

void registracija_u_sustav(void);

void kreiranje_datoteke_clanovi(void);
int ucitavanje_broja_korisnika(void);

void glavni_izbornik(void); //glavni izbornik cijeloga sustava->iz njega se sustav grana na manje pod sustave

int prijava_korisnika(KUPAC*);

int prijava_admina(ADMINISTRATOR*);
void admin_izbornik(KUPAC*);

PROIZVOD* ucitavanje_proizvoda(PROIZVOD*);

void kreiranje_datoteke_proizvodi();

int ucitavanje_broja_proizvoda(void);

void unos_novih_proizvoda(void);

int brisanje_proizvoda(PROIZVOD*, int);

void izbornik_korisnici(KUPAC*);

int ispis_proizvoda(int,KUPAC*);
#endif//Header
