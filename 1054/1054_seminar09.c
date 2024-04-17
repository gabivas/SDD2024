#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Carte Carte;
typedef struct MaxHeap MaxHeap;

struct Carte
{
	int prioritate;
	char* nume;
	int nrPagini;
};

struct MaxHeap
{
	Carte* vector;
	int dim;
};

Carte initializare(int prioritate, char* nume, int nrPagini) {
	Carte carte;
	carte.prioritate = prioritate;
	carte.nrPagini = nrPagini;
	carte.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(carte.nume, nume);
	return carte;
}

void afisareCarte(Carte carte) {
	printf("\nCartea %s are %d pagini si prioritatea %d", carte.nume, carte.nrPagini, carte.prioritate);
}

void afisareMaxHeap(MaxHeap maxHeap) {
	for (int i = 0; i < maxHeap.dim; i++) {
		afisareCarte(maxHeap.vector[i]);
	}
}

void filtrare(MaxHeap maxHeap, int index) {
	if (maxHeap.dim > 0) {
		int pozMaxim = index;
		int pozSt = 2 * index + 1;
		int pozDr = 2 * index + 2;
		if (pozSt < maxHeap.dim && maxHeap.vector[pozMaxim].prioritate < maxHeap.vector[pozSt].prioritate) {
			pozMaxim = pozSt;

		}
		if (pozDr < maxHeap.dim && maxHeap.vector[pozMaxim].prioritate < maxHeap.vector[pozDr].prioritate) {
			pozMaxim = pozDr;
		}
		if (pozMaxim != index) {
			Carte aux = maxHeap.vector[index];
			maxHeap.vector[index] = maxHeap.vector[pozMaxim];
			maxHeap.vector[pozMaxim] = aux;
			if (pozMaxim <= maxHeap.dim / 2 - 1) {
				filtrare(maxHeap, pozMaxim);
			}
		}
	}
}

void extragere(MaxHeap* maxHeap, Carte* carte) {
	*carte = initializare(maxHeap->vector[0].prioritate, maxHeap->vector[0].nume, maxHeap->vector[0].nrPagini);
	Carte aux = maxHeap->vector[0];
	maxHeap->vector[0] = maxHeap->vector[maxHeap->dim-1];
	maxHeap->vector[maxHeap->dim - 1] = aux;
	maxHeap->dim--;
	filtrare(*maxHeap, 0);
}

void main() {

	MaxHeap maxHeap;
	maxHeap.dim = 6;

	maxHeap.vector = (Carte*)malloc(sizeof(Carte) * maxHeap.dim);

	maxHeap.vector[0] = initializare(1, "Morometii", 260);
	maxHeap.vector[1] = initializare(2, "Baltagul", 100);
	maxHeap.vector[2] = initializare(3, "Amintiri din Copilarie", 380);
	maxHeap.vector[3] = initializare(4, "Ion", 120);
	maxHeap.vector[4] = initializare(5, "Enigma Otiliei", 300);
	maxHeap.vector[5] = initializare(6, "Harap-Alb", 54);

	afisareMaxHeap(maxHeap);

	for (int i = maxHeap.dim / 2 - 1; i >= 0; i--) {
		filtrare(maxHeap, i);
	}
	printf("\n");
	afisareMaxHeap(maxHeap);

	printf("\n");
	Carte carte;
	while (maxHeap.dim != 0) {
		extragere(&maxHeap, &carte);
		afisareCarte(carte);
		free(carte.nume);
	}
	printf("\n");
	for (int i = 0; i < 6; i++) {
		afisareCarte(maxHeap.vector[i]);
		free(maxHeap.vector[i].nume);
	}
	free(maxHeap.vector);
}