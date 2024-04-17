#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Carte Carte;
typedef struct MaxHeap MaxHeap;

struct Carte {
	int prioritate;
	char* titlu;
	float pret;
};

struct MaxHeap {
	Carte* vector;
	int dimensiune;
};

Carte initCarte(int prioritate, char* titlu, float pret) {
	Carte carte;
	carte.prioritate = prioritate;
	carte.pret = pret;
	carte.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(carte.titlu, titlu);

	return carte;
}

void afisareCarte(Carte carte) {
	printf("\n%d. Cartea cu titlul %s costa %.2f lei.", carte.prioritate, carte.titlu, carte.pret);
}

void afisareHeap(MaxHeap maxHeap) {
	for (int i = 0; i < maxHeap.dimensiune; i++) {
		afisareCarte(maxHeap.vector[i]);
	}
}

void filtrare(MaxHeap maxHeap, int index) {
	if (maxHeap.dimensiune > 0) {
		int pozStanga = 2 * index + 1;
		int pozDreapa = 2 * index + 2;
		int pozitieMaxim = index;

		if (pozStanga < maxHeap.dimensiune && maxHeap.vector[pozitieMaxim].prioritate < maxHeap.vector[pozStanga].prioritate) {
			pozitieMaxim = pozStanga;
		}
		if (pozDreapa < maxHeap.dimensiune && maxHeap.vector[pozitieMaxim].prioritate < maxHeap.vector[pozDreapa].prioritate) {
			pozitieMaxim = pozDreapa;
		}

		if (pozitieMaxim != index) {
			Carte aux = maxHeap.vector[pozitieMaxim];
			maxHeap.vector[pozitieMaxim] = maxHeap.vector[index];
			maxHeap.vector[index] = aux;
			if (pozitieMaxim <= maxHeap.dimensiune / 2 - 1) {
				filtrare(maxHeap, pozitieMaxim);
			}
		}
	}
}

void extragere(MaxHeap* heap, Carte* carte) {
	*carte = initCarte(heap->vector[0].prioritate, heap->vector[0].titlu, heap->vector[0].pret);
	Carte aux = heap->vector[0];
	heap->vector[0] = heap->vector[heap->dimensiune - 1];
	heap->vector[heap->dimensiune - 1] = aux;
	(heap->dimensiune)--;
	filtrare(*heap, 0);
}

void main() {
	MaxHeap maxHeap;
	maxHeap.dimensiune = 6;
	maxHeap.vector = (Carte*)malloc(sizeof(Carte) * maxHeap.dimensiune);

	maxHeap.vector[0] = initCarte(1, "Heidi", 27);
	maxHeap.vector[1] = initCarte(2, "AlbaCaZapada", 33);
	maxHeap.vector[2] = initCarte(3, "Cenusareasa", 33);
	maxHeap.vector[3] = initCarte(4, "Iliada", 43);
	maxHeap.vector[4] = initCarte(5, "Rapunzel", 28);
	maxHeap.vector[5] = initCarte(6, "Ion", 23);

	//afisare initiala
	afisareHeap(maxHeap);

	for (int i = maxHeap.dimensiune / 2 - 1; i >= 0; i--) {
		filtrare(maxHeap, i);
	}

	//afisare MaxHeap
	printf("\n");
	afisareHeap(maxHeap);

	printf("\n");
	Carte carte;
	while (maxHeap.dimensiune != 0) {
		extragere(&maxHeap, &carte);
		afisareCarte(carte);
		free(carte.titlu);
	}
}