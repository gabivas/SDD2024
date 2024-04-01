#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
typedef struct Film Film;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Film {
	char* nume;
	int durata;
};

struct Nod {
	Film info;
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int dimensiune;
};

void afisareFilm(Film film) {
	printf("\n Filmul %s dureaza %d minute.", film.nume, film.durata);
}

Film initializareFilm(const char* nume, int durata) {
	Film film;
	film.durata = durata;
	film.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(film.nume, nume);

	return film;
}

void inserareLaFinal(Film film, Nod** cap) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	//shallow copy util
	nou->info = film;
	nou->next = NULL;

	if ((*cap) == NULL) {
		*cap = nou;
	}
	else {
		Nod* copie = *cap;
		while (copie->next) {
			copie = copie->next;
		}
		copie->next = nou;
	}
}

int functieHash(int durata, int dim) {
	return durata % dim;
}

HashTable initializareHashTable(int dim) {
		HashTable hashTable;
		hashTable.dimensiune = dim;
		hashTable.vector = (Nod**)malloc(sizeof(Nod*) * dim);
		for (int i = 0; i < dim; i++) {
			hashTable.vector[i] = NULL;
		}
		return hashTable;
}

void inserareInHashTable(Film film, HashTable hashTable) {
	if (hashTable.dimensiune > 0) {
		int pozitie = functieHash(film.durata, hashTable.dimensiune);
		if (pozitie < hashTable.dimensiune && pozitie >= 0) {
			inserareLaFinal(film, &(hashTable.vector[pozitie]));
		}
	}
}

void traversareHashTable(HashTable hashT) {
	for (int i = 0; i < hashT.dimensiune; i++) {
		printf("\n Pozitie = %d", i
		);
		Nod* copie = hashT.vector[i];
		while (copie) {
			afisareFilm(copie->info);
			copie = copie->next;
		}
	}
}

void main() {
	HashTable hashTable = initializareHashTable(10);
	inserareInHashTable(initializareFilm("Harry Poter", 407), hashTable);
	inserareInHashTable(initializareFilm("Superman", 125), hashTable);
	inserareInHashTable(initializareFilm("Batman", 113), hashTable);
	inserareInHashTable(initializareFilm("Robin", 101), hashTable);
	traversareHashTable(hashTable);
	traversareHashTable(hashTable);
}