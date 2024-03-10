#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Masina Masina;

struct Masina {
	char* marca;
	int anFabricatie;
	float pret;
};

void afisareMasina(Masina masina) {
	printf("\n Masina %s din anul %d a costat %.2f euro.", masina.marca, masina.anFabricatie, masina.pret);
}

Masina citireMasina(FILE* fStream) {
	Masina masina;

	if (fStream != NULL) {

		char buffer[20];
		fgets(buffer, 20, fStream);
		char* sir = strtok(buffer, "\n");
		masina.marca = (char*)malloc(sizeof(char) * (strlen(sir) + 1));
		strcpy(masina.marca, sir);

		fgets(buffer, 6, fStream);
		masina.anFabricatie = atoi(buffer);

		fgets(buffer, 12, fStream);
		masina.pret = atof(buffer);
	}
	return masina;
}

void citireVectorDinFisier(const char* numeFisier, int** vector, int* dimensiune) {
	FILE* fisier = NULL;
	fisier = fopen(numeFisier, "r");
	if (fisier != NULL) {
		fscanf(fisier, "%d", dimensiune);
		*vector = (int*)malloc((*dimensiune) * sizeof(int));
		for (int i = 0; i < *dimensiune; i++) {
			fscanf(fisier, "%d", *vector + i);
		}
	}
	fclose(fisier);
}

void citireMasini(FILE* fisier, Masina** vectorMasini, int* nrMasini) {
	if (fisier != NULL) {
		while (!feof(fisier)) {
			*vectorMasini = (Masina*)realloc(*vectorMasini, (*nrMasini + 1) * sizeof(Masina));
			(*vectorMasini)[*nrMasini] = citireMasina(fisier);
			(*nrMasini)++;
		}
	}
}

void citireMatriceMasiniDeLaTastatura(Masina*** matriceMasini, int nrLinii, int nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {
			(*matriceMasini)[i][j].marca = (char*)malloc(sizeof(char) * 20);

			printf("Marca de pe pozitia(%d, %d): ", i, j);
			scanf("%s", (*matriceMasini)[i][j].marca);

			printf("An fabricatie de pe pozitia(%d, %d): ", i, j);
			scanf("%d", &(*matriceMasini)[i][j].anFabricatie);

			printf("Pret de pe pozitia(%d, %d): ", i, j);
			scanf("%f", &(*matriceMasini)[i][j].pret);
		}
	}
}

void afisareMatriceMasini(Masina** matriceMasini, int nrLinii, int nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {
			afisareMasina(matriceMasini[i][j]);
		}
	}
}

void citireMatriceMasini(Masina*** matriceMasini, int* nrLinii, int* nrColoane ) {
	printf("\n Nr linii: ");
	scanf("%d", nrLinii);
	printf("\n Nr coloane: ");
	scanf("%d", nrColoane);

	*matriceMasini = (Masina**)malloc((*nrLinii) * sizeof(Masina*));
	for (int i = 0; i < (*nrLinii); i++) {
		(*matriceMasini)[i] = (Masina*)malloc((*nrColoane) * sizeof(Masina));
	}
	
	citireMatriceMasiniDeLaTastatura(matriceMasini, *nrLinii, *nrColoane);
}

void main() {
	//FILE* fileStream = NULL;
	//fileStream = fopen("Fisier.txt", "r");
	//int nr1, nr2;
	//if (fileStream != NULL) {
	//	fscanf(fileStream, "%d", &nr1);
	//	fscanf(fileStream, "%d", &nr2);
	//}
	//fclose(fileStream);
	//printf("\n Nr1 = %d, nr2 = %d", nr1, nr2);

	//int* vector;
	//int dimensiune;
	//citireVectorDinFisier("Vector.txt", &vector, &dimensiune);
	//for (int i = 0; i < dimensiune; i++) {
	//	printf("\nvector[%i] = %d", i, vector[i]);
	//}

	//free(vector);

	FILE* streamMasina = NULL;
	streamMasina = fopen("Masina.txt", "r");
	Masina masina = citireMasina(streamMasina);
	afisareMasina(masina);
	fclose(streamMasina);
	free(masina.marca);

	Masina* vectorMasini = NULL;
	int nrMasini = 0; 
	streamMasina = NULL;
	streamMasina = fopen("Masini.txt", "r");
	citireMasini(streamMasina, &vectorMasini, &nrMasini);

	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(vectorMasini[i]);
		free(vectorMasini[i].marca);
	}

	free(vectorMasini);

	Masina** matriceMasini = NULL;
	int nrLinii, nrColoane;
	citireMatriceMasini(&matriceMasini, &nrLinii, &nrColoane);
	afisareMatriceMasini(matriceMasini, nrLinii, nrColoane);
}