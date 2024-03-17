#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
typedef struct Film Film;
typedef struct Nod Nod;

struct Film{
	char* nume;
	int durata;
};

struct Nod {
	Film info;
	Nod* next;
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

void inserareLaInceput(Film film, Nod** cap) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	//shallow copy util
	nou->info = film;
	nou->next = *cap;

	*cap = nou;
}

void parcurgereLista(Nod* cap) {
	while(cap){
		afisareFilm(cap->info);
		cap = cap->next;
	}
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

void dezalocare(Nod** cap) {
	while ((*cap) != NULL) {
		free((*cap)->info.nume);
		Nod* copie = *cap;
		*cap = (*cap)->next;
		free(copie);
	}
}

void main() {
	Nod* cap = NULL;
	inserareLaInceput(initializareFilm("Harry Poter", 400),&cap);
	inserareLaInceput(initializareFilm("Superman", 120),&cap);
	inserareLaInceput(initializareFilm("Batman", 110), &cap);

	parcurgereLista(cap);

	inserareLaFinal(initializareFilm("Robin", 100), &cap);

	parcurgereLista(cap);
	dezalocare(&cap);
}