#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Carte Carte;
typedef struct Nod Nod;

struct Carte
{
	int id;
	char* nume;
	int nrPagini;
};

struct Nod
{
	Carte info;
	Nod* left;
	Nod* right;
};

Carte initializare(int id, char* nume, int nrPagini) {
	Carte carte;
	carte.id = id;
	carte.nrPagini = nrPagini;
	carte.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(carte.nume, nume);
	return carte;
}

void afisareCarte(Carte carte) {
	printf("\nCartea %s are %d pagini si id-ul %d", carte.nume, carte.nrPagini, carte.id);
}

void inserareInArbore(Nod** radacina, Carte carte) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = carte;
		nou->left = NULL;
		nou->right = NULL;
		*radacina = nou;
	}
	else if (carte.id < (*radacina)->info.id) {
		inserareInArbore(&(*radacina)->left, carte);
	}
	else {
		inserareInArbore(&(*radacina)->right, carte);
	}
}

void parcurgereInordine(Nod* radacina){
	if (radacina) {
		parcurgereInordine(radacina->left);
		afisareCarte(radacina->info);
		parcurgereInordine(radacina->right);
	}
}

void parcurgerePostordine(Nod* radacina) {
	if (radacina) {
		parcurgerePostordine(radacina->left);
		parcurgerePostordine(radacina->right);
		afisareCarte(radacina->info);
	}
}

Carte cautareCarte(Nod* radacina, int idCautat) {
	if (radacina == NULL) {
		return initializare(-1, "NoName", 0);
	}
	else if (idCautat == radacina->info.id) {
		return initializare(radacina->info.id, radacina->info.nume, radacina->info.nrPagini);
	}
	else if (idCautat< radacina->info.id) {
		return cautareCarte(radacina->left, idCautat);
	}
	else {
		return cautareCarte(radacina->right, idCautat);
	}
}

void dezalocare(Nod** radacina) {
	if (*radacina) {
		dezalocare(&(*radacina)->left);
		dezalocare(&(*radacina)->right);
		free((*radacina)->info.nume);
		free((*radacina));
	}
	*radacina = NULL;
}

void main() {
	Nod* radacina = NULL;
	inserareInArbore(&radacina, initializare(12, "Morometii", 260));
	inserareInArbore(&radacina, initializare(10, "Baltagul", 100));
	inserareInArbore(&radacina, initializare(11, "Amintiri din Copilarie", 380));
	inserareInArbore(&radacina, initializare(14, "Ion", 120));
	inserareInArbore(&radacina, initializare(7, "Enigma Otiliei", 300));
	inserareInArbore(&radacina, initializare(8, "Harap-Alb", 54));
	inserareInArbore(&radacina, initializare(13, "Moara cu noroc", 100));

	parcurgereInordine(radacina);
	parcurgerePostordine(radacina);

	Carte carteCautata = cautareCarte(radacina, 11);
	printf("\n Carte cautata: ");
	afisareCarte(carteCautata);
	free(carteCautata.nume);

	dezalocare(&radacina);
}