#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Prajitura Prajitura;
typedef struct MaxHeap MaxHeap;

struct Prajitura {
	int prioritate;
	char* denumire;
	float pret;
};

struct MaxHeap {
	int dimensiune;
	Prajitura* vector;
};

void afisarePrajitura(Prajitura prajitura) {
	printf("\n %d. Prajitura %s costa %f lei.", prajitura.prioritate, prajitura.denumire, prajitura.pret);
}

Prajitura initPrajitura(int prioritate, char* denumire, float pret) {
	Prajitura prajitura;
	prajitura.pret = pret;
	prajitura.prioritate = prioritate;
	prajitura.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(prajitura.denumire, denumire);

	return prajitura;
}

void afisareMaxHeap(MaxHeap maxHeap) {
	for (int i = 0; i < maxHeap.dimensiune; i++) {
		afisarePrajitura(maxHeap.vector[i]);
	}
}

void filtrare(MaxHeap maxHeap, int index) {
	if (maxHeap.dimensiune > 0) {
		int pozSt = 2 * index + 1;
		int pozDr = 2 * index + 2;
		int pozitieMaxim = index;
		if (pozSt < maxHeap.dimensiune && maxHeap.vector[pozitieMaxim].prioritate < maxHeap.vector[pozSt].prioritate) {
			pozitieMaxim = pozSt;
		}
		if (pozDr < maxHeap.dimensiune && maxHeap.vector[pozitieMaxim].prioritate < maxHeap.vector[pozDr].prioritate) {
			pozitieMaxim = pozDr;
		}
		if (pozitieMaxim != index) {
			Prajitura aux = maxHeap.vector[pozitieMaxim];
			maxHeap.vector[pozitieMaxim] = maxHeap.vector[index];
			maxHeap.vector[index] = aux;
			if (pozitieMaxim <= maxHeap.dimensiune / 2 - 1) {
				filtrare(maxHeap, pozitieMaxim);
			}
		}
	}
}

void extragere(MaxHeap* maxHeap, Prajitura* prajitura) {
	*prajitura = initPrajitura(maxHeap->vector[0].prioritate, maxHeap->vector[0].denumire, maxHeap->vector[0].pret);
	Prajitura aux = maxHeap->vector[0];
	maxHeap->vector[0] = maxHeap->vector[maxHeap->dimensiune - 1];
	maxHeap->vector[maxHeap->dimensiune - 1] = aux;
	maxHeap->dimensiune--;
	filtrare(*maxHeap, 0);
}

void main() {
	MaxHeap maxHeap;
	maxHeap.dimensiune = 6;
	maxHeap.vector = (Prajitura*)malloc(sizeof(Prajitura)*maxHeap.dimensiune);
	maxHeap.vector[0] = initPrajitura(10, "Profiterol", 20);
	maxHeap.vector[1] = initPrajitura(11, "Amandina", 21.5);
	maxHeap.vector[2] = initPrajitura(15, "Cheesecake", 30);
	maxHeap.vector[3] = initPrajitura(17, "Ecler", 16);
	maxHeap.vector[4] = initPrajitura(20, "Lavacake", 30);
	maxHeap.vector[5] = initPrajitura(12, "Negresa", 21);

	afisareMaxHeap(maxHeap);

	for (int i = maxHeap.dimensiune / 2 - 1; i >= 0; i--) {
		filtrare(maxHeap, i);
	}
	printf("\n");
	afisareMaxHeap(maxHeap);

	printf("\n");
	Prajitura prajitura;
	while (maxHeap.dimensiune != 0) {
		extragere(&maxHeap, &prajitura);
		afisarePrajitura(prajitura);
		free(prajitura.denumire);
	}

	printf("\n");
	for (int i = 0; i < 6; i++) {
		afisarePrajitura(maxHeap.vector[i]);
		free(maxHeap.vector[i].denumire);
	}
	free(maxHeap.vector);
}