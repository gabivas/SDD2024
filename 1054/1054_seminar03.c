#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Animal Animal;

struct Animal {
	char* specie;
	int varsta;
	float greutate;
};

void afisareAnimal(Animal animal) {
	printf("\nAnimalul de rasa %s are %d ani si %.2f kg.", animal.specie, animal.varsta, animal.greutate);
}

void citireVectorDinFisier(const char* numeFisier, int** vector, int* dimensiune) {
	//dereferentiere
	FILE* streamFisier = NULL;
	streamFisier = fopen(numeFisier, "r");
	if (streamFisier != NULL) {
		fscanf(streamFisier, "%d", dimensiune);
		*vector = (int*)malloc(sizeof(int) * (*dimensiune));
		for (int i = 0; i < *dimensiune; i++) {
			fscanf(streamFisier, "%d", &(*vector)[i]);
			//fscanf(streamFisier, "%d", *vector + i);
		}
		fclose(streamFisier);
	}
}

Animal citireAnimal(FILE* streamFisier) {
	//fgets
	Animal animal;
	char buffer[10];
	fgets(buffer, 10, streamFisier);
	//buffer="Caine\n"
	char* sir = strtok(buffer, "\n");
	//sir="Caine"

	animal.specie = (char*)malloc(sizeof(char) * (strlen(sir) + 1));
	strcpy(animal.specie, sir);

	fgets(buffer, 5, streamFisier);
	animal.varsta = atoi(buffer);

	fgets(buffer, 8, streamFisier);
	animal.greutate = atof(buffer);

	return animal;
}

void citireVectorAnimale(FILE* file, Animal** vectorAnimale, int* nrAnimale) {
	if (file == NULL) {
		return;
	}
		while (!feof(file)) {
			*vectorAnimale = (Animal*)realloc(*vectorAnimale, ((*nrAnimale) + 1) * sizeof(Animal));
			(*vectorAnimale)[*nrAnimale] = citireAnimal(file);
			(*nrAnimale)++;
		}
}

void citireMatriceDeLaTastatura(Animal*** matriceAnimale, int nrColoane, int nrLinii) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {
			printf("Specia pentru pozitia(%d,%d)", i, j);
			(*matriceAnimale)[i][j].specie = (char*)malloc(sizeof(char) * 30);
			scanf("%s", (*matriceAnimale)[i][j].specie);

			printf("Varsta pentru pozitia(%d,%d)", i, j);
			scanf("%d", &(*matriceAnimale)[i][j].varsta);

			printf("Greutatea pentru pozitia(%d,%d)", i, j);
			scanf("%f", &(*matriceAnimale)[i][j].greutate);
		}
	}
}

void citireMatriceAnimale(int* nrLinii, int* nrColoane, Animal*** matriceAnimale) {
	printf("\n Nr linii:");
	scanf("%d", nrLinii);
	printf("\n Nr coloane:");
	scanf("%d", nrColoane);

	*matriceAnimale = (Animal**)malloc(sizeof(Animal*) * (*nrLinii));
	for (int i = 0; i < (*nrLinii); i++) {
		(*matriceAnimale)[i] = (Animal*)malloc(sizeof(Animal) * (*nrColoane));
	}

	citireMatriceDeLaTastatura(matriceAnimale, *nrColoane, *nrLinii);
}

void afisareMatriceAnimale(int nrLinii, int nrColoane, Animal** matriceAnimale) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {
			afisareAnimal(matriceAnimale[i][j]);
		}
	}
}

void main() {
	//FILE* streamFile = NULL;
	//int a, b;

	//streamFile = fopen("Date.txt", "r");
	//if (streamFile != NULL) {
	//	//fscanf - citeste linia si se deplaseaza pe urmatoarea linie
	//	//fgets - citeste linia cu tot cu "\n", "Mere\n"
	//	fscanf(streamFile, "%d", &a);
	//	fscanf(streamFile, "%d", &b);
	//}

	//fclose(streamFile);

	//printf("\n a=%d, b=%d", a, b);

	//int* vector = NULL;
	//int dimensiune;
	//citireVectorDinFisier("Vector.txt", &vector, &dimensiune);

	//for (int i = 0; i < dimensiune; i++) {
	//	printf("\n vector[%i] = %d", i, vector[i]);
	//}

	//free(vector);

	Animal caine;
	FILE* streamFisier = NULL;
	streamFisier = fopen("Animal.txt", "r");
	if (streamFisier != NULL) {
		caine = citireAnimal(streamFisier);
	}
	fclose(streamFisier);
	afisareAnimal(caine);

	free(caine.specie);

	Animal* vectorAnimale = NULL;
	int nrAnimale = 0;
	streamFisier = NULL;
	streamFisier = fopen("Animale.txt", "r");
	citireVectorAnimale(streamFisier, &vectorAnimale, &nrAnimale);
	if(streamFisier!=NULL)
	fclose(streamFisier);
	if (vectorAnimale != NULL) {
		for (int i = 0; i < nrAnimale; i++) {
			afisareAnimal(vectorAnimale[i]);
			free(vectorAnimale[i].specie);
		}
		free(vectorAnimale);
	}

	int nrLinii, nrColoane;
	Animal** matriceAnimale = NULL;
	citireMatriceAnimale(&nrLinii, &nrColoane, &matriceAnimale);
	afisareMatriceAnimale(nrLinii, nrColoane, matriceAnimale);
}