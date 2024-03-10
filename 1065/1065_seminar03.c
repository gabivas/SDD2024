#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

typedef struct Produs Produs;

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
			fscanf(streamFisier, "%d", *vector + i);
		}
	}
	fclose(streamFisier);
}

Produs preluareProdusDinFisier(FILE* file) {
	Produs produs;
	if (file != NULL) {
		char buffer[20];

		fgets(buffer, 10, file);
		produs.pret = atof(buffer);

		fgets(buffer, 10, file);
		produs.cod = atoi(buffer);

		fgets(buffer, 15, file);
		char* denumire = strtok(buffer, "\n");
		produs.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
		strcpy(produs.denumire, denumire);
	}
	return produs;
}

void afisareProdus(Produs produs);

void citireProduseDinFisier(FILE* file, Produs** vectorProduse, int* nrProduse) {
	if(file != NULL){
	while(!feof(file)){
		*vectorProduse = (Produs*)realloc((*vectorProduse), (1 + (*nrProduse)) * sizeof(Produs));
		(*vectorProduse)[*nrProduse] = preluareProdusDinFisier(file);
		(*nrProduse)++;
	}
	}
}

void citireMatriceProduse(Produs*** matriceProduse, int nrLinii, int nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {
			printf("Pretul pentru pozitia(%d,%d): ", i, j);
			scanf("%f", &(*matriceProduse)[i][j].pret);

			printf("Codul pentru pozitia(%d,%d): ", i, j);
			scanf("%d", &(*matriceProduse)[i][j].cod);

			printf("Denumirea pentru pozitia(%d,%d): ", i, j);
			(*matriceProduse)[i][j].denumire = (char*)malloc(sizeof(char) * 20);
			scanf("%s", (*matriceProduse)[i][j].denumire);
		}
	}
}

void citireMatriceDeLaTastatura(Produs*** matriceProduse, int* nrLinii,
	int* nrColoane) {
	printf("\n Nr linii: ");
	scanf("%d", nrLinii);
	printf("\n Nr coloane: ");
	scanf("%d", nrColoane);

	*matriceProduse = (Produs**)malloc(sizeof(Produs*) * (*nrLinii));
	for (int i = 0; i < (*nrLinii); i++) {
		(*matriceProduse)[i] = (Produs*)malloc(sizeof(Produs) * (*nrColoane));
	}

	citireMatriceProduse(matriceProduse, *nrLinii, *nrColoane);
}

void afisareMatriceProduse(Produs** matriceProduse, int nrLinii,
	int nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {
			afisareProdus(matriceProduse[i][j]);
		}
	}
}

void main() {
	/*int val1, val2;
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
	free(vector);*/

	FILE* file = NULL;
	file = fopen("Produs.txt", "r");
	Produs produs = preluareProdusDinFisier(file);

	afisareProdus(produs);

	Produs* vectorProduse = NULL;
	int nrProduse = 0;
	file = NULL;
	file = fopen("Produse.txt", "r");

	citireProduseDinFisier(file, &vectorProduse, &nrProduse);

	for (int i = 0; i < nrProduse; i++) {
		afisareProdus(vectorProduse[i]);
		free(vectorProduse[i].denumire);
	}

	free(vectorProduse);

	Produs** matriceProduse = NULL;
	int nrLinii, nrColoane;
	citireMatriceDeLaTastatura(&matriceProduse, &nrLinii, 
		&nrColoane);
	afisareMatriceProduse(matriceProduse, nrLinii, nrColoane);
}

void afisareProdus(struct Produs produs) {
	printf("\nProdusul %s are codul %d si pretul %.2f lei.", produs.denumire, produs.cod, produs.pret);
}