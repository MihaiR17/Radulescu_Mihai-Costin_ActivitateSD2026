#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Telefon {
	int id;
	int RAM;
	char* producator;
	float pret;
	char serie;
};

struct Telefon initializare(int id , int ram, const char* producator,float pret,char serie) {
	struct Telefon t;
	t.id = id;
	t.RAM = ram;
	t.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(t.producator, producator);
	t.pret = pret;
	t.serie = serie;
	
	return t;
}

void afisare(struct Telefon t) {
	if (t.producator != NULL)
	{
		printf("%d. Telefonul %s seria %c are %d GB RAM si costa %5.2f RON\n ",
			t.id, t.producator, t.serie, t.RAM, t.pret);
	}
	else
	{
		printf("Telefonul nu exista");
	}

	//afisarea tuturor atributelor.
}

void modificaPret(struct Telefon* t,float noulPret) {
	if (noulPret > 0)
	{
		t->pret = noulPret;
	}

	//modificarea unui atribut
}

void dezalocare(struct Telefon *t) {
	if (t->producator != NULL)
	{
		free(t->producator);
		t->producator = NULL;
	}
	//dezalocare campuri alocate dinamic
}

int main() {
	struct Telefon t;
	t = initializare(1, 256, "Samsung", 2000.5, 'A');
	afisare(t);
	modificaPret(&t, 1000);
	afisare(t);

	dezalocare(&t);
	afisare(t);
	return 0;
}