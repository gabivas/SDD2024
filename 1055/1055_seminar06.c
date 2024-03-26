#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
typedef struct Film Film;
typedef struct Nod Nod;

struct Film {
	long id;
	char* nume;
	int durata;
};

struct Nod {
	Film info;
	Nod* next;
};

void afisareFilm(Film film) {
	printf("\n%ld. Filmul %s dureaza %d minute.",film.id, film.nume, film.durata);
}

Film initializareFilm(long id, const char* nume, int durata) {
	Film film;
	film.durata = durata;
	film.id = id;
	film.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(film.nume, nume);

	return film;
}

void push(Film film, Nod** cap) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	//shallow copy util
	nou->info = film;
	nou->next = *cap;

	*cap = nou;
}

void put(Film film, Nod** cap) {
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

Film pop(Nod** varf) {
	Film film;
	film.id = -1;
	film.durata = -1;
	film.nume = NULL;
	if (*varf) {
		film = (*varf)->info;
		Nod* aux = *varf;
		(*varf) = (*varf)->next;
		free(aux);
	}
	return film;
}

Film cautareFilm(Nod** varf, long id) {
	Film film;
	film.id = -1;
	film.durata = -1;
	film.nume = NULL;
	Nod* stivaAux = NULL;
	while ((*varf) != NULL && (*varf)->info.id != id) {
		push(pop(varf), &stivaAux);
	}
	if (*varf) {
		film = pop(varf);
	}
	while (stivaAux) {
		push(pop(&stivaAux), varf);
	}
	return film;
}

void main() {
	Nod* stiva = NULL;
	Film film;
	push(initializareFilm(1, "Harry Poter", 400), &stiva);
	push(initializareFilm(2, "Superman", 120), &stiva);
	push(initializareFilm(3, "Batman", 110), &stiva);

	Film filmCautat = cautareFilm(&stiva, 2);
	afisareFilm(filmCautat);

	printf("\nAfisare stiva: ");
	while (stiva) {
		film = pop(&stiva);
		afisareFilm(film);
		free(film.nume);
	}
	
	Nod* coada = NULL;
	put(initializareFilm(1, "Harry Poter", 400), &coada);
	put(initializareFilm(2, "Superman", 120), &coada);
	put(initializareFilm(3, "Batman", 110), &coada);
	
	printf("\nAfisare coada: ");
	while (coada) {
		film = pop(&coada);
		afisareFilm(film);
		free(film.nume);
	}
}