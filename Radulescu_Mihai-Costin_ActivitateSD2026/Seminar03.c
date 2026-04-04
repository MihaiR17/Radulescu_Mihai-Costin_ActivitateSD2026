//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrusi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//void afisareMasina(Masina masina) {
//	printf("id ul masinii: %d\n", masina.id);
//	printf("nr ul de usi: %d\n", masina.nrusi);
//	printf("pret: %.2f\n", masina.pret);
//	printf("model: %s\n", masina.model);
//	printf("nume sofer: %s\n", masina.numeSofer);
//	printf("serie: %d\n", masina.serie);
//	printf("\n");
//}
//
//void afisareVectorMasini(Masina* masini, int nrMasini) {
//	for (int i = 0; i < nrMasini; i++) {
//		afisareMasina(masini[i]);
//	}
//}
//
//void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
//
//	Masina* temp = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1));
//
//	for (int i = 0; i < *nrMasini; i++)
//	{
//		temp[i] = (*masini)[i];
//	}
//
//	temp[*nrMasini] = masinaNoua;
//
//	free(masini);
//	*masini = temp;
//
//	(*nrMasini)++;
//}
//
//Masina citireMasinaFisier(FILE* file) {
//	Masina m;
//	char buffer[50];
//	fgets(buffer, 49, file);
//	char var[3] = ",\n";
//	strtok(buffer, var);
//
//	m.id = atoi(strtok(buffer, var));
//	m.nrusi = atoi(strtok(NULL, var));
//	m.pret = atof(strtok(NULL, var));
//
//	char* aux = strtok(NULL, var);
//	m.model = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
//	strcpy(m.model, aux);
//
//	aux = strtok(NULL, var);
//	m.numeSofer = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
//	strcpy(m.numeSofer, aux);
//
//	m.serie = strtok(NULL, var)[0];
//
//	return m;
//
//}
//
//Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
//	FILE* file;
//	file = fopen(numeFisier, "r");
//
//	Masina* masini = NULL;
//	*nrMasiniCitite = 0;
//
//	while (!feof(file))
//	{
//		Masina m = citireMasinaFisier(file);
//		adaugaMasinaInVector(&masini, nrMasiniCitite, m);
//	}
//
//	fclose(file);
//	return masini;
//}
//void dezalocareVectorMasini(Masina** vector, int* nrMasini)
//{
//	for (int i = 0; i < (*nrMasini); i++)
//	{
//		free(vector[i]->model);
//		free(vector[i]->numeSofer);
//	}
//	free(*vector);
//	(*vector) = NULL;
//	(*nrMasini) = 0;
//}
//int main()
//{
//	int nrMasini = 0;
//	Masina* masini = NULL;
//	masini = citireVectorMasiniFisier("masini.txt", &nrMasini);
//	afisareVectorMasini(masini, nrMasini);
//	return 0;
//
//}