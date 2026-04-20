//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//struct Telefon {
//	int id;
//	int RAM;
//	char* producator;
//	float pret;
//	char serie;
//};
//
//struct Telefon initializare(int id , int ram, const char* producator,float pret,char serie) {
//	struct Telefon t;
//	t.id = id;
//	t.RAM = ram;
//	t.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
//	strcpy(t.producator, producator);
//	t.pret = pret;
//	t.serie = serie;
//	
//	return t;
//}
//
//void afisare(struct Telefon t) {
//	if (t.producator != NULL)
//	{
//		printf("%d. Telefonul %s seria %c are %d GB RAM si costa %5.2f RON\n ",
//			t.id, t.producator, t.serie, t.RAM, t.pret);
//	}
//	else
//	{
//		printf("Telefonul nu exista");
//	}
//
//	//afisarea tuturor atributelor.
//}
//
//void modificaPret(struct Telefon* t,float noulPret) {
//	if (noulPret > 0)
//	{
//		t->pret = noulPret;
//	}
//
//	//modificarea unui atribut
//}
//
//void dezalocare(struct Telefon *t) {
//	if (t->producator != NULL)
//	{
//		free(t->producator);
//		t->producator = NULL;
//	}
//	//dezalocare campuri alocate dinamic
//}
//
//int main() {
//	struct Telefon t;
//	t = initializare(1, 256, "Samsung", 2000.5, 'A');
//	afisare(t);
//	modificaPret(&t, 1000);
//	afisare(t);
//
//	dezalocare(&t);
//	afisare(t);
//	return 0;
//}






#include<stdio.h>
#include<malloc.h>

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

void afisareVector(struct Telefon* vector, int nrElemente) {
	for (int i = 0;i < nrElemente;i++)
	{
		afisare(vector[i]);
	}


	//afisarea elementelor din vector apeland functia afisare
}

struct Sablon* copiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Telefon *vectorNou=NULL;
	vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * nrElementeCopiate);
	for (int i = 0;i < nrElementeCopiate;i++)
	{
		vectorNou[i] = vector[i];
		vectorNou[i].producator = (char*)malloc(strlen(vector[i].producator) + 1);
		strcpy(vectorNou[i].producator, vector[i].producator);

	}

	return vectorNou;
}

void dezalocare(struct Telefon** vector, int* nrElemente) {

	for (int i = 0;i < *nrElemente;i++)
	{
		if (((*vector)[i]).producator != NULL)
		{
			free((*vector)[i].producator);
		}
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;

	//dezalocam elementele din vector si vectorul
}

void copiazaTelefoaneScumpe(struct Telefon* vector, char nrElemente, float pretMinim, struct Telefon** vectorNou, int* dimensiune) {

	*dimensiune = 0;
	for (int i = 0;i < nrElemente;i++)
	{
		if (vector[i].pret >= pretMinim)
		{
			(*dimensiune)++;
		}
	}
	if ((*vectorNou) != NULL)
	{
		free(*vectorNou);
	}
	*vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * (*dimensiune));
	int k = 0;
	for (int i = 0;i < nrElemente;i++)
	{
		if (vector[i].pret >= pretMinim)
		{
			(*vectorNou)[k] = vector[i];
			(*vectorNou)[k].producator = (char*)malloc(strlen(vector[i].producator) + 1);
			strcpy_s((*vectorNou)[k].producator, strlen(vector[i].producator) + 1, vector[i].producator);
			k++;
		}

	}
		//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
}

struct Telefon getPrimulTelefonByProducator(struct Telefon* vector, int nrElemente, const char* producator) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Telefon t;
	t.producator = NULL;
	for (int i = 0;i < nrElemente;i++)
	{
		if (strcmp(vector[i].producator, producator) == 0)
		{
			t = vector[i];
			t.producator = (char*)malloc(strlen(vector[i].producator + 1));
			strcpy(t.producator,vector[i].producator);

		}
	}

	return t;
}
	


int main() {

	struct Telefon* telefoane = NULL;
	int nrTelefoane = 3;
	telefoane = (struct Telefon*)malloc(sizeof(struct Telefon) * nrTelefoane);
	telefoane[0] = initializare(1, 256, "Samsung", 2000, 'S');
	telefoane[1] = initializare(2, 256, "Motorola", 1500, 'M');
	telefoane[2] = initializare(3, 256, "Apple", 2200, 'A');


	afisareVector(telefoane, 3);

	struct Telefon* primeleTelefoane = NULL;
	int nrPrimeleTelefoane = 1;
	primeleTelefoane = copiazaPrimeleNElemente(telefoane, nrTelefoane, nrPrimeleTelefoane);
	printf("\n\n Primele telefoane : \n");
	afisareVector(primeleTelefoane, nrPrimeleTelefoane);

	dezalocare(&primeleTelefoane, &nrPrimeleTelefoane);

	afisareVector(primeleTelefoane, nrPrimeleTelefoane);


	// copiaza telefoane scumpe

	struct Telefon* telefoaneScumpe = NULL;
	int nrTelefoaneScumpe = 0;
	copiazaTelefoaneScumpe(telefoane, nrTelefoane, 1000, &telefoaneScumpe, &nrTelefoaneScumpe);
	printf("\n\n Telefoane scumpe: \n");
	afisareVector(telefoaneScumpe, nrTelefoaneScumpe);

	dezalocare(&telefoaneScumpe, &nrTelefoaneScumpe);

	struct Telefon telefon = getPrimulTelefonByProducator(telefoane, nrTelefoane, "Motorola");
	printf("\n\n Telefonul gasit: \n");
	afisare(telefon);
	if (telefon.producator != NULL)
	{
		free(telefon.producator);
		telefon.producator = NULL;
	}

	dezalocare(&telefoane, &nrTelefoane);
	return 0;
}