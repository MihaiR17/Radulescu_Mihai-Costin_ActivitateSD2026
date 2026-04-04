//#include<stdio.h>
//#include<malloc.h>
//
//struct Biblioteca {
//	int id;
//	int nrCarti;
//	char* nume;
//	float suprafata;
//	char sector;
//};
//struct Biblioteca initializare(int fid, int fnrCarti, char* fnume, float fsuprafata, char fsector) {
//	struct Biblioteca s;
//	s.id = fid;
//	s.nrCarti = fnrCarti;
//
//	s.nume = (char*)malloc(sizeof(char) * (strlen(fnume) + 1));
//	strcpy(s.nume, fnume);
//
//	s.suprafata = fsuprafata;
//	s.sector = fsector;
//
//	return s;
//}
//
//struct Biblioteca copiazaBiblioteca(struct Biblioteca sursa)
//{
//	return initializare(sursa.id, sursa.nrCarti, sursa.nume, sursa.suprafata, sursa.sector);
//}
//
//void afisare(struct Biblioteca s) {
//	printf("ID: %d\n", s.id);
//	printf("Numar carti: %d\n", s.nrCarti);
//	printf("Nume: %s\n", s.nume);
//	printf("Suprafata: %4.2f\n", s.suprafata);
//	printf("Sector: %d\n", s.sector);
//}
//
//void afisareVector(struct Biblioteca* vector, int nrElemente) {
//	for (int i = 0; i < nrElemente; i++)
//		afisare(vector[i]);
//	return 0;
//}
//
//struct Biblioteca* copiazaPrimeleNElemente(struct Biblioteca* vector, int nrElemente, int nrElementeCopiate) {
//	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
//	struct Biblioteca* vectorNou = NULL;
//	if (nrElementeCopiate > nrElemente)
//	{
//		nrElementeCopiate = nrElemente;
//	}
//	vectorNou = (struct Biblioteca*)malloc(sizeof(struct Biblioteca) * nrElementeCopiate);
//	for (int i = 0; i < nrElementeCopiate; i++)
//	{
//		vectorNou[i] = copiazaBiblioteca(vector[i]);
//	}
//	return vectorNou;
//}
//
//void dezalocare(struct Biblioteca** vector, int* nrElemente) {
//	//dezalocam elementele din vector si vectorul
//	for (int i = 0; i < (*nrElemente); i++)
//	{
//		free((*vector)[i].nume);
//	}
//	free((*vector));
//	*vector = NULL;
//	*nrElemente = 0;
//}
////derefentiere + deplasare + derefentiere + accesare
//
//void copiazaAnumiteElemente(struct Biblioteca* vector, char nrElemente, float prag, struct Biblioteca** vectorNou, int* dimensiune) {
//
//}
//
//struct Biblioteca getPrimulElementConditionat(struct Biblioteca* vector, int nrElemente, const char* conditie) {
//	//trebuie cautat elementul care indeplineste o conditie
//	//dupa atributul de tip char*. Acesta este returnat.
//	struct Biblioteca s;
//	s.id = 1;
//
//	return s;
//}
//void copiazaBibliotecileCuSuprafataMare(struct Biblioteca* vector, char nrElemente, float suprafataMinima, struct Biblioteca** vectorNou, int* dimensiune)
//{
//	*dimensiune = 0;
//	for (int i = 0; i < nrElemente; i++)
//	{
//		if (vector[i].suprafata > suprafataMinima) *dimensiune++;
//	}
//	*vectorNou = (struct Biblioteca*)malloc(sizeof(struct Biblioteca) * (*dimensiune));
//
//	int contor = 0;
//	for (int i = 0; i < nrElemente; i++)
//	{
//		if (vector[i].suprafata > suprafataMinima)
//		{
//			(*vectorNou)[contor++] = copiazaBiblioteca(vector[i]);
//		}
//	}
//}
//
//
//int main() {
//	struct Biblioteca b;
//	b = initializare(129, 1000, "ASE", 129, 3);
//	afisare(b);
//	int numarBiblioteci = 5;
//	struct Biblioteca* vectorB = (struct Biblioteca*)malloc(sizeof(struct Biblioteca) * numarBiblioteci);
//	vectorB[0] = b; //shallowcopy
//	vectorB[1] = initializare(100, 100, "ASE", 120, 5);
//	vectorB[2] = initializare(133, 1212, "POLI", 224, 2);
//	vectorB[3] = initializare(22, 235, "UNIBUC", 334, 1);
//	vectorB[4] = initializare(333, 124, "UTCB", 12, 6);
//
//	printf("Elemente din vector: \n");
//	afisareVector(vectorB, 5);
//	int numarCopiate = 3;
//	struct Biblioteca* copie = copiazaPrimeleNElemente(vectorB, numarBiblioteci, numarCopiate);
//	printf("\nElementele vectorului cu primele %d elemente copiate: \n", numarCopiate);
//	afisareVector(copie, numarCopiate);
//	dezalocare(&copie, &numarCopiate);
//	afisareVector(copie, numarCopiate);
//
//	struct Biblioteca* bibliotecaSuprafataMare = NULL;
//	int numarBiblioteciSuprafataMare = 0;
//	copiazaBibliotecileCuSuprafataMare(vectorB, numarBiblioteci, 100, &bibliotecaSuprafataMare, &numarBiblioteciSuprafataMare);
//	afisareVector(bibliotecaSuprafataMare, numarBiblioteciSuprafataMare);
//	return 0;
//}
//
////[ ] = deplasare + derefentiere;
//// -> = derefentiere + acesar