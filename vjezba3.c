#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char ime[20];
    char prezime[20];
    int godina;
}student;

typedef struct cvor* poz;
typedef struct cvor {
    student* val;
    poz next;
}cvor;

int main() {
    cvor head;
    head.val = NULL;
    head.next = NULL;




    return 0;
}

int UnosP(student*, char*, poz);
int UnosN(student*, char*, poz);
int Sort(poz);
int Citaj(poz, char*);
int Pisi(poz, char*);

int UnosP(student* x, char* y, poz h) {
    poz t = (cvor*)malloc(sizeof(cvor));

    if(t == NULL){
        printf("GRESKA U ALOCIRANJU NOVOG CVORA");
        free(t);
        return 1;
    }

    while (h->next != NULL && strcmp(h->next->val->prezime, y) != 0) {
        h = h->next;
    }

    if (h->next == NULL) {
        printf("element nije pronaden");
        free(t);
        return 1;
    }

    t->next = h->next;
    h->next = t;
    t->val = x;

    return 0;
}

int UnosN(student* x, char* y, poz h) {
    poz t = (cvor*)malloc(sizeof(cvor));
    
    if(t == NULL){
        printf("GRESKA U ALOCIRANJU NOVOG CVORA");
        free(t);
        return 1;
    }

    h = h->next;

    while (h != NULL && strcmp(h->val->prezime, y) != 0) {
        h = h->next;
    }

    if (h == NULL) {
        printf("element nije pronaden");
        free(t);
        return 1;
    }

    t->next = h->next;
    h->next = t;
    t->val = x;

    return 0;
}

int Sort(poz h) {
    poz prev_e;
    poz kraj;
    poz e;
    poz temp;

    kraj = NULL;

    while (h->next != kraj) {
        prev_e = h;
        e = h->next;
        
        while (e->next != kraj) {
            if (strcmp(e->val->prezime, e->next->val->prezime) > 0) {
                temp = e->next;
                prev_e->next = temp;
                e->next = temp->next;
                temp->next = e;
                e = temp;
            }

            prev_e = e;
            e = e->next;
        }

        kraj = e;
    }

    return 0;
}

int Citaj(poz head, char* filename) {

	char ime[20];
    char prezime[20];
    int godina;

	FILE* f = fopen(filename, "r");

    if (f == NULL) {
        printf("GRESKA: otvaranje datoteke nije uspjelo");
        return 1;
    }

    while (fscanf(f, "%s %s %d", ime, prezime, &godina) == 3) {
        student* p = (student*)malloc(sizeof(student));
        strcpy(p->ime, ime);
        strcpy(p->prezime, prezime);
        p->godina = godina;

        poz Novi_cvor = (cvor*)malloc(sizeof(cvor));
        Novi_cvor->val = p;
        Novi_cvor->next = NULL;

        poz temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = Novi_cvor;
    }

    fclose(f);
    return 0;
}

int Pisi(poz head, char* filename) {
    FILE* f = fopen(filename, "w");

    if (f == NULL) {
        printf("GRESKA: otvaranje datoteke nije uspjelo");
        return 1;
    }

    poz temp = head->next;
    while (temp != NULL) {
        fprintf(f, "%s %s %d\n", temp->val->ime, temp->val->prezime, temp->val->godina);
        temp = temp->next;
    }

    fclose(f);
    return 0;
}