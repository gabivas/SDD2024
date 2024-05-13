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

int calculInaltimeArbore(Nod* radacina) {
	if (radacina != NULL) {
		int inaltimeSubArboreSt = calculInaltimeArbore(radacina->copilStanga);
		int inaltimeSubArboreDr = calculInaltimeArbore(radacina->copilDreapta);
		if (inaltimeSubArboreSt > inaltimeSubArboreDr) {
			return inaltimeSubArboreSt + 1;
		}
		else {
			return inaltimeSubArboreDr + 1;
		}
	}
	else {
		return 0;
	}
}

int diferentaInaltimi(Nod* radacina) {
	if (radacina != NULL) {
		return calculInaltimeArbore(radacina->copilStanga) - calculInaltimeArbore(radacina->copilDreapta);
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

void inserareInArboreAVL(Prajitura prajitura, Nod** radacina) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->prajitura = prajitura;
		nou->copilStanga = NULL;
		nou->copilDreapta = NULL;
		*radacina = nou;
	}
	else if (prajitura.id < (*radacina)->prajitura.id) {
		inserareInArboreAVL(prajitura, &(*radacina)->copilStanga);
	}
	else {
		inserareInArboreAVL(prajitura, &(*radacina)->copilDreapta);
	}

	int diferentaInaltimiSubarbori = diferentaInaltimi(*radacina);

	if (diferentaInaltimiSubarbori == 2) {
		//dezechilibru pe partea stanga
		if (diferentaInaltimi((*radacina)->copilStanga) == -1) {
			rotireLaStanga(&(*radacina)->copilStanga);
		}
		rotireLaDreapta(radacina);
	}
	if (diferentaInaltimiSubarbori == -2) {
		//dezechilibru pe partea dreapta
		if (diferentaInaltimi((*radacina)->copilDreapta) == 1) {
			rotireLaDreapta(&(*radacina)->copilDreapta);
		}
		rotireLaStanga(radacina);
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

int nrFrunze(Nod* radacina) {
	if (!radacina) {
		return 0;
	}
	if (radacina->copilStanga == NULL && radacina->copilDreapta == NULL) {
		return 1;
	}
	return nrFrunze(radacina->copilStanga) + nrFrunze(radacina->copilDreapta);
}

void main() {
	Nod* radacina = NULL;
	inserareInArboreAVL(initPrajitura(1, "Profiterol", 20), &radacina);
	inserareInArboreAVL(initPrajitura(2, "Amandina", 21.5), &radacina);
	inserareInArboreAVL(initPrajitura(3, "Cheesecake", 30), &radacina);
	inserareInArboreAVL(initPrajitura(4, "Ecler", 16), &radacina);
	inserareInArboreAVL(initPrajitura(5, "Lavacake", 30), &radacina);
	/*inserareInArboreAVL(initPrajitura(6, "Negresa", 21), &radacina);*/

	parcurgerePostordine(radacina);
	printf("\n Nr noduri frunza: %d", nrFrunze(radacina));

	dezalocare(&radacina);
}