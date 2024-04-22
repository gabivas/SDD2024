#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Prajitura Prajitura;
typedef struct Nod Nod;

struct Prajitura {
	int id;
	char* denumire;
	float pret;
};

struct Nod {
	Prajitura prajitura;
	Nod* copilStanga;
	Nod* copilDreapta;
};

void afisarePrajitura(Prajitura prajitura) {
	printf("\n %d. Prajitura %s costa %f lei.", prajitura.id, prajitura.denumire, prajitura.pret);
}

Prajitura initPrajitura(int id, char* denumire, float pret) {
	Prajitura prajitura;
	prajitura.pret = pret;
	prajitura.id = id;
	prajitura.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(prajitura.denumire, denumire);

	return prajitura;
}

void inserareInArbore(Prajitura prajitura, Nod** radacina) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->prajitura = prajitura;
		nou->copilStanga = NULL;
		nou->copilDreapta = NULL;
		*radacina = nou;
	}
	else if (prajitura.id < (*radacina)->prajitura.id) {
		inserareInArbore(prajitura, &(*radacina)->copilStanga);
	}
	else {
		inserareInArbore(prajitura, &(*radacina)->copilDreapta);
	}
}

void parcurgereInordine(Nod* radacina) {
	if (radacina) {
		parcurgereInordine(radacina->copilStanga);
		afisarePrajitura(radacina->prajitura);
		parcurgereInordine(radacina->copilDreapta);
	}
}

void parcurgerePostordine(Nod* radacina) {
	if (radacina) {
		parcurgerePostordine(radacina->copilStanga);
		parcurgerePostordine(radacina->copilDreapta);
		afisarePrajitura(radacina->prajitura);
	}
}

Prajitura cautarePrajitura(int id, Nod* radacina) {
	if (!radacina) {
		return initPrajitura(-1, "Neinitializat", 0.0f);
	}
	else if (radacina->prajitura.id == id) {
		return initPrajitura(radacina->prajitura.id, radacina->prajitura.denumire, radacina->prajitura.pret);
	}
	else if (id < radacina->prajitura.id) {
		return cautarePrajitura(id, radacina->copilStanga);
	}
	else {
		return cautarePrajitura(id, radacina->copilDreapta);
	}
}

void dezalocare(Nod** radacina) {
	if (*radacina) {
		dezalocare(&(*radacina)->copilStanga);
		dezalocare(&(*radacina)->copilDreapta);
		free((*radacina)->prajitura.denumire);
		free(*radacina);
	}
}

void main() {
	Nod* radacina = NULL;
	inserareInArbore(initPrajitura(5, "Profiterol", 20), &radacina);
	inserareInArbore(initPrajitura(2, "Amandina", 21.5), &radacina);
	inserareInArbore(initPrajitura(7, "Cheesecake", 30), &radacina);
	inserareInArbore(initPrajitura(4, "Ecler", 16), &radacina);
	inserareInArbore(initPrajitura(8, "Lavacake", 30), &radacina);
	inserareInArbore(initPrajitura(6, "Negresa", 21), &radacina);

	parcurgereInordine(radacina);
	printf("\n Parcurgere postordine: ");
	parcurgerePostordine(radacina);

	Prajitura prajituraCautata = cautarePrajitura(6, radacina);
	printf("\n Prajitura cautata: ");
	afisarePrajitura(prajituraCautata);
	free(prajituraCautata.denumire);

	dezalocare(&radacina);
}