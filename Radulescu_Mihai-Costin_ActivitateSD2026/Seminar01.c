#include<stdio.h>
#include<stdlib.h>

struct Produs
{
	int id;
	int stoc;
	char* denumire;
	float pret;
	char categorie;

};

struct Produs initializare(int id, int stoc, char* denumire, float pret, char categorie)
{
	struct Produs s;
	s.id = id;
	s.stoc = stoc;
	s.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1)); //calculam cat imi ocupa un caracter inmultit cu strlen de denumire + 1
	strcpy(s.denumire, denumire);
	s.pret = pret;
	s.categorie = categorie;



	//initializare structura 
	return s;
}

void afisare(struct Produs s)
{
	printf("ID: %d\n", s.id);
	printf("STOC: %d\n", s.stoc);
	printf("DENUMIRE: %s\n", s.denumire);
	printf("PRET: %5.2f\n", s.pret);
	printf("CATEGORIE: %c\n", s.categorie);

	//afisarea tuturor atributelor.
}

void modifica_Atribut(struct Produs* s, char* nouaDenumire)
{
	free((*s).denumire);
	s->denumire = (char*)malloc(sizeof(char) * (strlen(nouaDenumire) + 1));
	strcpy(s->denumire, nouaDenumire);



	//modificarea unui atribut
}

void dezalocare(struct Produs* s)
{
	if (s->denumire != NULL)
	{
		free(s->denumire);
		s->denumire = NULL;
	}


	//dezalocare campuri alocate dinamic
}

float calculeazaTotal(struct Produs s)
{
	return s.stoc * s.pret;
}

int main()
{
	struct Produs s;
	s = initializare(1, 20, "Telefon smart", 300, 'A');
	afisare(s);

	modifica_Atribut(&s, "Mouse");

	afisare(s);
	printf("Valoarea totala pentru %s este %5.2f RON.", s.denumire, calculeazaTotal(s));

	dezalocare(&s);
	return 0;
}