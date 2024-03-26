#include<stdio.h>
#include<malloc.h>

typedef struct Angajat Angajat;
typedef struct Nod Nod;

struct Angajat {
    long id;
    char* nume;
    int varsta;
};

struct Nod {
    Angajat info;
    Nod* next;
};

void afisareAngajat(Angajat angajat) {
    printf("\n%ld. Angajatul %s are %d ani.", angajat.id, angajat.nume, angajat.varsta);
}

Angajat initAngajat(long id, const char* nume, int varsta) {
    Angajat angajat;
    angajat.varsta = varsta;
    angajat.id = id;
    angajat.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(angajat.nume, nume);

    return angajat;
}

void push(Nod** cap, Angajat info) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = info;
    nou->next = *cap;
    *cap = nou;
}

void put(Nod** cap, Angajat angajat) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = angajat;
    nou->next = NULL;

    if ((*cap) == NULL) {
        *cap = nou;
    }
    else {
        Nod* temp = *cap;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = nou;
    }
}

Angajat pop(Nod** varf) {
    Angajat angajat;
    angajat.id = -1;
    angajat.varsta = -1;
    angajat.nume = NULL;

    if (*varf) {
        angajat = (*varf)->info;
        Nod* copie = *varf;
        (*varf) = (*varf)->next;
        free(copie);
    }
    return angajat;
}

Angajat cautareDupaId(Nod** stiva, long id) {
    Angajat angajat;
    angajat.id = -1;
    angajat.varsta = -1;
    angajat.nume = NULL;
    Nod* stivaAuxiliara = NULL;

    while ((*stiva)!=NULL && id!= (*stiva)->info.id)
    {
        push(&stivaAuxiliara, pop(stiva));
    }
    if (*stiva) {
        angajat = pop(stiva);
    }

    while (stivaAuxiliara) {
        push(stiva, pop(&stivaAuxiliara));
    }

    return angajat;
}

void main() {
    Nod* stiva = NULL;
    Angajat angajat;
    push(&stiva, initAngajat(1, "Mihai", 30));
    push(&stiva, initAngajat(2, "Andrei", 28));
    push(&stiva, initAngajat(3, "Ana", 29));
    push(&stiva, initAngajat(4, "Ana", 29));
    push(&stiva, initAngajat(5, "Ana", 29));

    Angajat angajatCautat = cautareDupaId(&stiva, 3);
    afisareAngajat(angajatCautat);
    free(angajatCautat.nume);

    printf("\n Stiva:");
    while (stiva) {
        angajat = pop(&stiva);
        afisareAngajat(angajat);
        free(angajat.nume);
    }

    Nod* coada = NULL;
    put(&coada, initAngajat(1, "Mihai", 30));
    put(&coada, initAngajat(2, "Andrei", 28));
    put(&coada, initAngajat(3, "Ana", 29));
    put(&coada, initAngajat(4, "Ana", 29));
    put(&coada, initAngajat(5, "Ana", 29));

    printf("\n Coada:");
    while (coada) {
        angajat = pop(&coada);
        afisareAngajat(angajat);
        free(angajat.nume);
    }
}