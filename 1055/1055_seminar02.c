#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct Masina {
	char* marca;
	int anFabricatie;
	float pret;
};

void afisareMasina(struct Masina masina) {
	printf("\n Masina %s din anul %d a costat %.2f euro.", masina.marca, masina.anFabricatie, masina.pret);
}

struct Masina citireMasina(FILE* fStream) {
	struct Masina masina;

	if(fStream != NULL){
	
		char buffer[20];
		fgets(buffer, 20, fStream);
		char* sir = strtok(buffer, "\n");
		masina.marca = (char*)malloc(sizeof(char) * (strlen(sir) + 1));
		strcpy(masina.marca, sir);

		fgets(buffer, 6, fStream);
		fgets()
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

void main() {
	FILE* fileStream = NULL;
	fileStream = fopen("Fisier.txt", "r");
	int nr1, nr2;
	if (fileStream != NULL) {
		fscanf(fileStream, "%d", &nr1);
		fscanf(fileStream, "%d", &nr2);
	}
	fclose(fileStream);
	printf("\n Nr1 = %d, nr2 = %d", nr1, nr2);

	int* vector;
	int dimensiune;
	citireVectorDinFisier("Vector.txt", &vector, &dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		printf("\nvector[%i] = %d", i, vector[i]);
	}

	free(vector);

	FILE* streamMasina = NULL;
	streamMasina = fopen("masina.txt", "r");
	struct Masina masina = citireMasina(streamMasina);
	afisareMasina(masina);
	fclose(streamMasina);
	free(masina.marca);
}