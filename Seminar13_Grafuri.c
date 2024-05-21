#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>
#include<string.h>

typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;
typedef struct Autostrada Autostrada;

typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Nod {
	int ID;
	Nod* next;
	Nod* prev;
};

struct ListaDubla {
	Nod* first;
	Nod* last;
};

struct Autostrada {
	int id;
	char* denumire;
	int nrKm;
};

struct NodPrincipal {
	Autostrada info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar {
	NodPrincipal* info;
	NodSecundar* next;
};

void push(ListaDubla* ld, int ID) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = ld->first;
	nou->prev = NULL;
	nou->ID = ID;

	if (ld->first == NULL) {
		ld->first = ld->last = nou;
	}
	else {
		ld->first->prev = nou;
		ld->first = nou;
	}
}

void put(ListaDubla* ld, int ID) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->prev = ld->last;
	nou->ID = ID;

	if (ld->last == NULL) {
		ld->first = ld->last = nou;
	}
	else {
		ld->last->next = nou;
		ld->last = nou;
	}
}

int pop(ListaDubla* ld) {
	int ID = -1;
	if (ld->first) {
		ID = ld->first->ID;
		Nod* aux = ld->first;
		ld->first = ld->first->next;
		if (ld->first == NULL) {
			ld->last = NULL;
		}
		free(aux);
	}
	return ID;
}

Autostrada initAutostrada(int id, const char* denumire, int nrKm)
{
	Autostrada autostrada;
	autostrada.id = id;
	autostrada.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(autostrada.denumire, denumire);
	autostrada.nrKm = nrKm;

	return autostrada;
}

void inserareListaPrincipala(NodPrincipal** cap, Autostrada autostrada) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = autostrada;
	nou->next = NULL;
	nou->vecini = NULL;
	NodPrincipal* aux = *cap;
	if (*cap) {
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*cap = nou;
	}
}

void inserareListaSecundara(NodSecundar** cap, NodPrincipal* info)
{
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->info = info;
	nou->next = NULL;
	if (*cap)
	{
		NodSecundar* aux = *cap;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
	else
	{
		*cap = nou;
	}
}

void afisareAutostrada(Autostrada a) {
	printf("\nAutostrada %s cu id-ul %d are %d km", a.denumire, a.id, a.nrKm);
}

NodPrincipal* cautareNodDupaId(NodPrincipal* graf, int id) {
	while (graf !=NULL && id != graf->info.id) {
		graf = graf->next;
	}
	return graf;
}

void inserareMuchie(NodPrincipal* graf, int id1, int id2) {
	NodPrincipal* nod1 = cautareNodDupaId(graf, id1);
	NodPrincipal* nod2 = cautareNodDupaId(graf, id2);
	if (nod1 != NULL && nod2 != NULL) {
		inserareListaSecundara(&nod1->vecini, nod2);
		inserareListaSecundara(&nod2->vecini, nod1);
	}
}

void afisareGraf(NodPrincipal* graf) {
	while (graf != NULL) {
		afisareAutostrada(graf->info);
		NodSecundar* vecini = graf->vecini;
		printf("\n Vecinii:");
		while (vecini) {
			afisareAutostrada(vecini->info->info);
			vecini = vecini->next;
		}
		printf("\n");
		graf = graf->next;
	}
}

void parcurgereInAdancime(NodPrincipal* graf, int idStart) {
	int dimensiune = 6;
	int* vectorNoduriVizitate = (int*)malloc(6 * sizeof(int));
	for (int i = 0; i < dimensiune; i++) {
		vectorNoduriVizitate[i] = 0;
	}
	ListaDubla stiva;
	stiva.first = stiva.last = NULL;
	push(&stiva, idStart);
	vectorNoduriVizitate[idStart-1] = 1;
	while (stiva.first) {
		int idExtras = pop(&stiva);
		NodPrincipal* nodExtras = cautareNodDupaId(graf, idExtras);
		afisareAutostrada(nodExtras->info);
		NodSecundar* vecini = nodExtras->vecini;
		while (vecini) {
			if (vectorNoduriVizitate[vecini->info->info.id - 1] == 0) {
				push(&stiva, vecini->info->info.id);
				vectorNoduriVizitate[vecini->info->info.id - 1] = 1;
			}
			vecini = vecini->next;
		}
	}
}

void main() {
	NodPrincipal* graf = NULL;
	inserareListaPrincipala(&graf, initAutostrada(1, "A1", 100));
	inserareListaPrincipala(&graf, initAutostrada(2, "A2", 200));
	inserareListaPrincipala(&graf, initAutostrada(3, "A3", 300));
	inserareListaPrincipala(&graf, initAutostrada(4, "A4", 400));
	inserareListaPrincipala(&graf, initAutostrada(5, "A5", 500));
	inserareListaPrincipala(&graf, initAutostrada(6, "A6", 600));

	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 1, 3);
	inserareMuchie(graf, 2, 4);
	inserareMuchie(graf, 3, 5);
	inserareMuchie(graf, 4, 6);
	inserareMuchie(graf, 5, 6);

	afisareGraf(graf);
	printf("\nParcurgere in adancime:");
	parcurgereInAdancime(graf, 1);
}