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

int inaltimeArbore(Nod* radacina) {
	if (radacina != NULL) {
		int inaltimeStanga = inaltimeArbore(radacina->copilStanga);
		int inaltimeDreapta = inaltimeArbore(radacina->copilDreapta);
		if (inaltimeStanga > inaltimeDreapta) {
			return inaltimeStanga + 1;
		}
		else {
			return inaltimeDreapta + 1;
		}
	}
	else {
		return 0;
	}
}

int diferentaInaltimi(Nod* radacina) {
	if (radacina != NULL) {
		return inaltimeArbore(radacina->copilStanga) - inaltimeArbore(radacina->copilDreapta);
	}
	else {
		return 0;
	}
}

void rotireLaDreapta(Nod** radacina) {
	Nod* aux = (*radacina)->copilStanga;
	(*radacina)->copilStanga = aux->copilDreapta;
	aux->copilDreapta = *radacina;
	*radacina = aux;
}

void rotireLaStanga(Nod** radacina) {
	Nod* aux = (*radacina)->copilDreapta;
	(*radacina)->copilDreapta = aux->copilStanga;
	aux->copilStanga = *radacina;
	*radacina = aux;
}

void inserareAVL(Carte carte, Nod** radacina) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = carte;
		nou->copilStanga = NULL;
		nou->copilDreapta = NULL;
		*radacina = nou;
	}
	else if (carte.id < (*radacina)->info.id) {
		inserareAVL(carte, &(*radacina)->copilStanga);
	}
	else {
		inserareAVL(carte, &(*radacina)->copilDreapta);
	}

	int diferentaH = diferentaInaltimi(*radacina);
	if (diferentaH == 2) {
		//dezechilibru pe stanga
		if (diferentaInaltimi((*radacina)->copilStanga) == -1) {
			rotireLaStanga(&(*radacina)->copilStanga);
		}
		rotireLaDreapta(radacina);
	}
	if (diferentaH == -2) {
		//dezechilibru pe dreapta
		if (diferentaInaltimi((*radacina)->copilDreapta) == 1) {
			rotireLaDreapta(&(*radacina)->copilDreapta);
		}
		rotireLaStanga(radacina);
	}
}

void main() {
	Nod* radacina = NULL;
	inserareAVL(initCarte(1, "Heidi", 27), &radacina);
	inserareAVL(initCarte(2, "AlbaCaZapada", 33), &radacina);
	inserareAVL(initCarte(3, "Cenusareasa", 33), &radacina);
	inserareAVL(initCarte(4, "Iliada", 43), &radacina);
	inserareAVL(initCarte(5, "Rapunzel", 28), &radacina);
	/*inserareAVL(initCarte(100, "Ion", 23), &radacina);
	inserareAVL(initCarte(6, "Maitreyi", 40), &radacina);
	inserareAVL(initCarte(75, "Moara cu Noroc", 33), &radacina);
	inserareAVL(initCarte(12, "Enigma Otiliei", 25), &radacina);*/

	parcurgerePreordine(radacina);
}