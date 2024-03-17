#include<stdio.h>
#include<malloc.h>

typedef struct Angajat Angajat;
typedef struct Nod Nod;

struct Angajat {
    char* nume;
    int varsta;
};

struct Nod {
    Angajat info;
    Nod* next;
};

void afisareAngajat(Angajat angajat) {
    printf("\n Angajatul %s are %d ani.", angajat.nume, angajat.varsta);
}

Angajat initAngajat(const char* nume, int varsta) {
    Angajat angajat;
    angajat.varsta = varsta;
    angajat.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(angajat.nume, nume);

    return angajat;
}

void parcurgereLista(Nod* cap) {
    while (cap) {
        afisareAngajat(cap->info);
        cap = cap->next;
    }
}

void inserareLaInceput(Nod** cap, Angajat info) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = info;
    nou->next = *cap;
    *cap = nou;
}

void inserareLaSfarsit(Nod** cap, Angajat angajat) {
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

void dezalocare(Nod** cap) {
    while ((*cap) != NULL) {
        Nod* temp = *cap;
        *cap = (*cap)->next;
        free(temp->info.nume);
        free(temp);
    }
}

int count(Nod* head, const char* nume) {
    int count = 0;

    while (head) {
        if (strcmp(head->info.nume, nume) == 0) count++;
        head = head->next;
    }

    return count;
}

float calculVarstaMedie(Nod* cap) {
    int contor = 0;
    float medie = 0.0;
    while (cap) {
        medie += cap->info.varsta;
        contor++;
        cap = cap->next;
    }
    if (contor == 0)
        return 0;
    return medie / contor;
}

void main() {
    Nod* cap = NULL;

    inserareLaInceput(&cap, initAngajat("Mihai", 30));
    inserareLaInceput(&cap, initAngajat("Andrei", 28));
    inserareLaInceput(&cap, initAngajat("Ana", 29));
    inserareLaInceput(&cap, initAngajat("Ana", 29));
    inserareLaInceput(&cap, initAngajat("Ana", 29));

    inserareLaSfarsit(&cap, initAngajat("Diana", 27));

    parcurgereLista(cap);

    printf("Numele \"Ana\" apare de %d ori.\n", count(cap, "Ana"));
    printf("\n\n\nMedia varstei angajatilor este %f", calculVarstaMedie(cap));

    dezalocare(&cap);
}