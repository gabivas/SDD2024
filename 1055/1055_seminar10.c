#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Carte Carte;
typedef struct Nod Nod;

struct Carte {
	int id;
	char* titlu;
	float pret;
};

struct Nod {
	Carte info;
	Nod* copilStanga;
	Nod* copilDreapta;
};

Carte initCarte(int id, char* titlu, float pret) {
	Carte carte;
	carte.id = id;
	carte.pret = pret;
	carte.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(carte.titlu, titlu);

	return carte;
}

void afisareCarte(Carte carte) {
	printf("\n%d. Cartea cu titlul %s costa %.2f lei.", carte.id, carte.titlu, carte.pret);
}

void inserareBST(Carte carte, Nod** radacina) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = carte;
		nou->copilStanga = NULL;
		nou->copilDreapta = NULL;
		*radacina = nou;
	}
	else if (carte.id < (*radacina)->info.id) {
		inserareBST(carte, &(*radacina)->copilStanga);
	}
	else {
		inserareBST(carte, &(*radacina)->copilDreapta);
	}
}

void parcurgereInordine(Nod* radacina) {
	if (radacina) {
		parcurgereInordine(radacina->copilStanga);
		afisareCarte(radacina->info);
		parcurgereInordine(radacina->copilDreapta);
}
}

void parcurgerePreordine(Nod* radacina) {
	if (radacina) {
		afisareCarte(radacina->info);
		parcurgerePreordine(radacina->copilStanga);
		parcurgerePreordine(radacina->copilDreapta);
	}
}

Carte cautareDupaId(Nod* radacina, int id) {
	if (!radacina) {
		return initCarte(-1, "Negasit", 0.0f);
	}
	else if (id == radacina->info.id) {
		return initCarte(radacina->info.id, radacina->info.titlu, radacina->info.pret);
	}
	else if (id < radacina->info.id) {
		return cautareDupaId(radacina->copilStanga, id);
	}
	else {
		return cautareDupaId(radacina->copilDreapta, id);
	}
}

void main() {
	Nod* radacina = NULL;
	inserareBST(initCarte(10, "Heidi", 27), &radacina);
	inserareBST(initCarte(7, "AlbaCaZapada", 33), &radacina);
	inserareBST(initCarte(11, "Cenusareasa", 33), &radacina);
	inserareBST(initCarte(5, "Iliada", 43), &radacina);
	inserareBST(initCarte(8, "Rapunzel", 28), &radacina);
	inserareBST(initCarte(100, "Ion", 23), &radacina);
	inserareBST(initCarte(6, "Maitreyi", 40), &radacina);
	inserareBST(initCarte(75, "Moara cu Noroc", 33), &radacina);
	inserareBST(initCarte(12, "Enigma Otiliei", 25), &radacina);

	parcurgereInordine(radacina);

	parcurgerePreordine(radacina);

	Carte carteCautata = cautareDupaId(radacina, 8);
	printf("\n Cartea cu id-ul 8: ");
	afisareCarte(carteCautata);
}