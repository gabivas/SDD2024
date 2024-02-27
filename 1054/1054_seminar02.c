#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct Animal{
	char* specie;
	int varsta;
	float greutate;
};

void afisareAnimal(struct Animal animal) {
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

struct Animal citireAnimal(FILE* streamFisier) {
	//fgets
	struct Animal animal;
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

void main() {
	FILE* streamFile = NULL;
	int a, b;

	streamFile = fopen("Date.txt", "r");
	if (streamFile != NULL) {
		//fscanf - citeste linia si se deplaseaza pe urmatoarea linie
		//fgets - citeste linia cu tot cu "\n", "Mere\n"
		fscanf(streamFile, "%d", &a);
		fscanf(streamFile, "%d", &b);
	}

	fclose(streamFile);

	printf("\n a=%d, b=%d", a, b);

	int* vector = NULL;
	int dimensiune;
	citireVectorDinFisier("Vector.txt", &vector, &dimensiune);

	for (int i = 0; i < dimensiune; i++) {
		printf("\n vector[%i] = %d", i, vector[i]);
	}

	free(vector);

	struct Animal caine;
	FILE* streamFisier = NULL;
	streamFisier = fopen("Animal.txt", "r");
	if (streamFisier != NULL) {
		caine = citireAnimal(streamFisier);
	}
	fclose(streamFisier);
	afisareAnimal(caine);

	free(caine.specie);
}