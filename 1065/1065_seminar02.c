#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

struct Produs {
	float pret;
	int cod;
	char* denumire;
};

void citireVector(const char* numeFisier, int** vector, int* dimensiune) {
	//dereferentiere
	FILE* streamFisier = NULL;
	streamFisier = fopen(numeFisier, "r");
	if (streamFisier != NULL) {
		fscanf(streamFisier, "%d", dimensiune);
		*vector = (int*)malloc(sizeof(int) * (*dimensiune));
		for (int i = 0; i < *dimensiune; i++) {
			fscanf(streamFisier, "%d", *vector+i);
		}

	}
	fclose(streamFisier);
}

struct Produs preluareProdusDinFisier(FILE* file) {
	struct Produs produs;
	if (file != NULL) {
		char buffer[20];

		fgets(buffer, 10, file);
		produs.pret = atof(buffer);

		fgets(buffer, 10, file);
		produs.cod = atoi(buffer);

		fgets(buffer, 15, file);
		char* denumire = strtok(buffer, "\n");
		produs.denumire = (char*)malloc(sizeof(char)*(strlen(denumire)+1));
		strcpy(produs.denumire, denumire);
	}
	return produs;
}

void afisareProdus(struct Produs produs);

void main() {
	int val1, val2;
	FILE* streamFisier = NULL;
	streamFisier = fopen("Fisier.txt", "r");
	if (streamFisier != NULL) {
		fscanf(streamFisier, "%d", &val1);
		fscanf(streamFisier, "%d", &val2);
	}
	fclose(streamFisier);

	printf("\n Val1= %d, val2= %d", val1, val2);

	int* vector = NULL;
	int dimensiune;
	citireVector("Vector.txt", &vector, &dimensiune);

	for (int i = 0; i < dimensiune; i++) {
		printf("\n vector[%i]= %d", i, vector[i]);
	}
	free(vector);

	FILE* file = NULL;
	file = fopen("Produs.txt", "r");
	struct Produs produs = preluareProdusDinFisier(file);

	afisareProdus(produs);
}

void afisareProdus(struct Produs produs) {
	printf("\nProdusul %s are codul %d si pretul %.2f lei.", produs.denumire, produs.cod, produs.pret);
}