#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct _student{
	char ime[20];
	char prezime[20];
	int bodovi;
}stud;

float relativniBr(int bod, int max);

int main() {
	
	FILE *f;
	char buffer[50] = {0};
	int brStud = 0;
	int Struct_size=0;
	stud *student;


	f = fopen("studenti.txt", "r");

	if (f == NULL) {
		printf("GRESKA!");
		return -1;
	}

	while (!feof(f)) {
		fgets(buffer,50,f);
		brStud++;
	}

	Struct_size=brStud * sizeof(stud);
	student = (stud *)malloc(Struct_size);
	brStud = 0;

	if (!student) {
		printf("GRESKA U ALLOCIRANJU");
		free(student);
		return -1;
	}

	rewind(f);

	while (fscanf(f,"%s %s %d",student[brStud].ime,student[brStud].prezime,&student[brStud].bodovi)==3) {
		brStud++;
	}

	if (brStud != Struct_size / sizeof(stud)) {
		printf("GRESKA U FORMATIRANJU");
		free(student);
		return -1;
	}

	fclose(f);

	printf("\tBROJ STUDENATA %d\n", brStud);
	for (int i = 0; i < brStud; i++) {
		printf("%s %s %d %.2f\n", student[i].ime, student[i].prezime, student[i].bodovi,relativniBr(student[i].bodovi,MAX));
	}

	printf("Allocirano memorije: %dB\n",Struct_size);

	free(student);/*be free!*/

}

float relativniBr(int bod,int max) {
	return (float)bod / max * 100;
}