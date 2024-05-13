#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
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

void parcurgereInordine(Nod* radacina) {
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
	else if (idCautat < radacina->info.id) {
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

int inaltimeArbore(Nod* radacina) {
	if (radacina != NULL) {
		int inaltimeSt = inaltimeArbore(radacina->left);
		int inaltimeDr = inaltimeArbore(radacina->right);
		if (inaltimeSt > inaltimeDr) {
			return 1 + inaltimeSt;
		}
		else {
			return 1 + inaltimeDr;
		}
	}
	else {
		return 0;
	}
}

int diferentaInaltimi(Nod* radacina) {
	if (radacina != NULL) {
		return inaltimeArbore(radacina->left) - inaltimeArbore(radacina->right);
	}
	else {
		return 0;
	}
}

void rotireLaStanga(Nod** radacina) {
	Nod* aux = (*radacina)->right;
	(*radacina)->right = aux->left;
	aux->left = *radacina;
	*radacina = aux;
}

void rotireLaDreapta(Nod** radacina) {
	Nod* aux = (*radacina)->left;
	(*radacina)->left = aux->right;
	aux->right = *radacina;
	*radacina = aux;
}

void inserareInArboreAVL(Nod** radacina, Carte carte) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = carte;
		nou->left = NULL;
		nou->right = NULL;
		*radacina = nou;
	}
	else if (carte.id < (*radacina)->info.id) {
		inserareInArboreAVL(&(*radacina)->left, carte);
	}
	else {
		inserareInArboreAVL(&(*radacina)->right, carte);
	}

	int diferentaInaltimiSubarbori = diferentaInaltimi(*radacina);
	if (diferentaInaltimiSubarbori == 2) {
		//dezechilibru pe stanga
		if (diferentaInaltimi((*radacina)->left) == -1) {
			rotireLaStanga(&(*radacina)->left);
		}
		rotireLaDreapta(radacina);
	}
	if (diferentaInaltimiSubarbori == -2) {
		//dezechilibru pe dreapta
		if (diferentaInaltimi((*radacina)->right) == 1) {
			rotireLaDreapta(&(*radacina)->right);
		}
		rotireLaStanga(radacina);
	}
}

bool esteFrunza(Nod* radacina, int id) {
	if (!radacina) {
		return false;
	}
	if (radacina->info.id == id && radacina->left == NULL && radacina->right == NULL) {
		return true;
	}
	else if (id < radacina->info.id) {
		return esteFrunza(radacina->left, id);
	}
	else {
		return esteFrunza(radacina->right, id);
	}
}

void main() {
	Nod* radacina = NULL;
	inserareInArboreAVL(&radacina, initializare(1, "Morometii", 260));
	inserareInArboreAVL(&radacina, initializare(2, "Baltagul", 100));
	inserareInArboreAVL(&radacina, initializare(3, "Amintiri din Copilarie", 380));
	inserareInArboreAVL(&radacina, initializare(4, "Ion", 120));
	inserareInArboreAVL(&radacina, initializare(5, "Enigma Otiliei", 300));
	//inserareInArboreAVL(&radacina, initializare(8, "Harap-Alb", 54));
	//inserareInArboreAVL(&radacina, initializare(13, "Moara cu noroc", 100));

	parcurgerePostordine(radacina);

	if (esteFrunza(radacina, 1)) {
		printf("\n Este nod frunza!");
	}

	dezalocare(&radacina);
}