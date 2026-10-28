#include <stdio.h>
#include <stdlib.h>

typedef struct poli* poz;
typedef struct poli{
    int k;
    int pot;
    poz next;
}poli;

int sortin(int k, int pot, poz head);
int ispis(poz head);
int zbroji(poz head);
int mnozi(poz prvi, poz drugi, poz rezultat);
void oslobodi_me(poz head);


int main(void)
{
    poli head1 = {0, 0, NULL};
    poli head2 = {0, 0, NULL};
    poli rezultat = {0, 0, NULL};

    char temp[100];
    int k1, pot1, k2, pot2;

    FILE *f = fopen("poli.txt", "r");
    if (f == NULL) {
        printf("NEMA DATOTEKEEE");
        return 1;
    }

    if (fgets(temp, sizeof temp, f) == NULL ||
        sscanf(temp, "%d %d %d %d", &k1, &pot1, &k2, &pot2) != 4) {
        printf("Problem formatiranja");
        fclose(f);
        return 1;
    }

    sortin(k1, pot1, &head1);
    sortin(k2, pot2, &head1);

    if (fgets(temp, sizeof temp, f) == NULL ||
        sscanf(temp, "%d %d %d %d", &k1, &pot1, &k2, &pot2) != 4) {
        printf("Problem formatiranja");
        fclose(f);
        return 1;
    }

    sortin(k1, pot1, &head2);
    sortin(k2, pot2, &head2);

    printf("Prvi polinom:\n");
    ispis(&head1);

    printf("Drugi polinom:\n");
    ispis(&head2);

    mnozi(&head1, &head2, &rezultat);
    ispis(&rezultat);

    fclose(f);
    oslobodi_me(&head1);
    oslobodi_me(&head2);
    oslobodi_me(&rezultat);
    return 0;
}


int sortin(int k, int pot, poz head){
    
    poz temp=malloc(sizeof(poli));

    if(temp==NULL){
        printf("greska u alokaciji :(\n");
        return 1; 
    }


    while(head->next!=NULL && head->next->pot<=pot){
        head=head->next;
    }

    temp->k=k;
    temp->pot=pot;
    temp->next=head->next;
    head->next=temp;

    return 0;
}

int ispis(poz head){
    int i=0;

    poz NextElement=head->next;

    if(NextElement==NULL){
        printf("lista je prazna nema se sta ispisat\n");
        return 0;
    }

    while (NextElement!=NULL) {
        printf("%d. %d %d\n",++i,NextElement->k,NextElement->pot);
        NextElement=NextElement->next;
    }

    return 0;
}

int zbroji(poz head){

    if(head->next==NULL || head->next->next==NULL){
        printf("nema se sta radit");
        return 1;
    }

    poz prev=head;
    head=head->next->next;

    while (head!=NULL) {
        if(prev->next->pot==head->pot){
            poz temp=malloc(sizeof(poli));
            poz temp_p = NULL;

            if(temp==NULL){
                printf("greska u alokaciji :(");
                return 1; 
            }

            temp->pot=head->pot;
            temp->k=prev->next->k+head->k;

            temp_p=prev->next;

            prev->next=temp;
            temp->next=head->next;
            free(temp_p->next);
            free(temp_p);

            head=temp->next;

            continue;
        }
        prev=prev->next;
        head=head->next;
    }
    
    return 0;
}

int mnozi(poz prvi, poz drugi, poz rezultat)
{

    poz a = prvi->next;

    while (a != NULL) {
        poz b = drugi->next;

        while (b != NULL) {
            if (sortin(a->k * b->k, a->pot + b->pot, rezultat) != 0) {
                return 1;
            }
            b = b->next;
        }
        a = a->next;
    }
    if (rezultat->next != NULL && rezultat->next->next != NULL) {
        if (zbroji(rezultat) != 0) {
            return 1;
        }
    }

    return 0;
}

void oslobodi_me(poz head)
{
    poz temp;

    while (head->next != NULL) {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }
}

