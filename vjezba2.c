#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char ime[20];
    char prezime[20];
    int datum;
}student;

typedef struct cvor * poz;
typedef struct cvor{
    student* val;
    poz next;
}cvor;

int UnosP(student*,poz);
int UnosK(student*,poz);
int ispis(poz);
int trazi(char *,poz);
int brisi(int,poz);
void oslobodi_me(poz);

int main(){
    int choice=0;
    int datum=0;
    char buffer[40];
    char ime[20];
    char prezime[20];

    /*Inicializacija i deklaracija head elementa*/
    cvor head;
    head.next=NULL;
    head.val=NULL;

    printf("add or delete.... make your choice: ");
    scanf("%d",&choice);
    getc(stdin);
    while(choice!=6){
        switch (choice) {
            case 1:{
                printf("FORMAT: ime prezime datum\nUnesite elemente:\n");
                while (fgets(buffer, sizeof(buffer), stdin)!=NULL && buffer[0]!='\n') {
                    if(buffer[strlen(buffer)-1] != '\n'){
                        printf("GRESKA : PREVISE ZNAKOVA");
                        oslobodi_me(&head);
                        return 1;}
                    
                    if(sscanf(buffer,"%s %s %d",ime,prezime,&datum)!=3){
                        printf("GRESKA : NEPRAVILAN FORMAT");
                        oslobodi_me(&head);
                        return 1;
                    }
                    
                    student *stud=(student*)malloc(sizeof(student));

                    if(stud==NULL){
                        printf("GRESKA : NEUSPJESNA ALOCIRANJA");
                        oslobodi_me(&head);
                        return 1;
                    }

                    strcpy(stud->ime,ime);
                    strcpy(stud->prezime,prezime);
                    stud->datum=datum;

                    UnosP(stud, &head);
                    printf("\n");
                    ispis(&head);
                }
                break;
            }       

            case 2:{
                ispis(&head);
                break;
            }

            case 3:{
                printf("FORMAT: ime prezime datum\nUnesite elemente:\n");
                while (fgets(buffer, sizeof(buffer), stdin)!=NULL && buffer[0]!='\n') {
                    if(buffer[strlen(buffer)-1] != '\n'){
                        printf("GRESKA : PREVISE ZNAKOVA");
                        oslobodi_me(&head);
                        return 1;}
                    
                    if(sscanf(buffer,"%s %s %d",ime,prezime,&datum)!=3){
                        printf("GRESKA : NEPRAVILAN FORMAT");
                        oslobodi_me(&head);
                        return 1;
                    }
                    
                    student *stud=(student*)malloc(sizeof(student));

                    if(stud==NULL){
                        printf("GRESKA : NEUSPJESNA ALOCIRANJA");
                        oslobodi_me(&head);
                        return 1;
                    }

                    strcpy(stud->ime,ime);
                    strcpy(stud->prezime,prezime);
                    stud->datum=datum;

                    UnosK(stud, &head);
                    printf("\n");
                    ispis(&head);
                }
                break;
            }

            case 4:{
                printf("Unesi prezime za potrazit:\n");
                scanf("%s",prezime);
                trazi(prezime,&head);
                break;
            }

            case 5:{
                printf("Unesi element za brisat(prezime):\n");
                scanf("%s",prezime);
                brisi(trazi(prezime, &head),&head);
                break;
            }

            default:{
                printf("pokusajte ponovo");
                break;
            }
        }
        printf("make your choice :");
        scanf(" %d",&choice);
        getc(stdin);
    }   
    
    oslobodi_me(&head);
    return 0;
}

int UnosP(student *data,poz head){

    /*allociranje novog cvora*/
    cvor *Novi_cvor=(cvor *)malloc(sizeof(cvor));

    if(Novi_cvor==NULL){
        printf("GRESKA U ALOCIRANJU NOVOG CVORA");
        oslobodi_me(head);
        return 1;
    }

    /*ucitavanje podataka u novi element*/
    Novi_cvor->val=data;

    /*provjera jeli lista prazna te dodavanje elementa*/
    if(head->next==NULL){
        head->next=Novi_cvor;
        Novi_cvor->next=NULL;
        return 0;
    }

    /*dodavanje elementa*/
    Novi_cvor->next=head->next;
    head->next=Novi_cvor;

    return 0;
}

int ispis(poz head){
    int i=0;

    poz NextElement=head->next;

    if(NextElement==NULL){
        printf("lista je prazna nema se sta ispisat");
        return 0;
    }

    while (NextElement!=NULL) {
        printf("%d. %s %s %d\n",++i,NextElement->val->ime,NextElement->val->prezime,NextElement->val->datum);
        NextElement=NextElement->next;
    }

    return 0;
}

int UnosK(student* data,poz head){

    /*allociranje novog cvora*/
    poz Novi_cvor=(cvor *)malloc(sizeof(cvor));

    if(Novi_cvor==NULL){
        printf("GRESKA U ALOCIRANJU NOVOG CVORA");
        oslobodi_me(head);
        return 1;
    }

    Novi_cvor->val = data;
    cvor *temp=head->next;

    if(head->next == NULL){
        head->next = Novi_cvor;
        Novi_cvor->next = NULL;
        return 0;
    }

    while (temp->next!=NULL) {
        temp=temp->next;
    }

    Novi_cvor->next=NULL;

    temp->next=Novi_cvor;

    return 0;

}

int trazi(char *prezime,poz head){
    poz temp=head->next;
    int i=0;

    if (temp==NULL) {
        printf("list je prazna\n");
        return 0;
    }

    while (temp!=NULL) {
        ++i;
        if(strcmp(temp->val->prezime, prezime)==0){
            printf("Element uspjesno pronaden index:%d\n",i);
            return i;
        }
        temp=temp->next;
    }
    printf("sve smo pretrazili... nema elementa\n");
    return -1;
}

int brisi(int n, poz head){
    if(n == -1){
        printf("sve smo pretrazili... nema elementa za brisanje\n");
        return 1;
    }

    poz temp = head;
    
    for(int i = 0; i < n-1 && temp->next != NULL; i++){
        temp = temp->next;
    }
    
    if(temp->next == NULL){
        printf("Element ne postoji\n");
        return 1;
    }
    
    poz doomed = temp->next;
    temp->next = doomed->next;
    
    free(doomed->val);
    free(doomed);
    printf("Element obrisan uspjesno\n");
    return 0;
}

void oslobodi_me(poz head){
    poz temp;
    while(head->next != NULL){
        temp = head->next;
        head->next = temp->next;
        free(temp->val);
        free(temp);
    }
}
