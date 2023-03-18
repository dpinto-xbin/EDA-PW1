/*****************************************************************//**
 * \file   Managers.c
 * 
 * \author Diogo Pinto & Ricardo Cruz
 * \date   March 2023
 *********************************************************************/
#include <stdlib.h>
#include <string.h>
#include "Managers.h"
#pragma warning(disable:4996)


#pragma region ReadAndInsertManagersFromFile
Manager* readManagers()
{
	FILE* fp;
	char nif[15], name[30], password[30];

	Manager* aux = NULL;
	fp = fopen("Managers.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%[^;\n];%[^;\n];%[^;\n];", nif, name, password);
			aux = insertManagers(aux, nif, name, password);
		}

		fclose(fp);
	}
	return(aux);
}

// Insert from file
Manager* insertManagers(Manager* aux, char nif[], char name[], char password[])
{
	Manager* new = malloc(sizeof(struct newManager));
	if (new != NULL)
	{
		strcpy(new->nif, nif);
		strcpy(new->name, name);
		strcpy(new->password, password);
		new->next = aux;
		return(new);
	}
	else return(aux);
}
#pragma endregion

#pragma region Login

int verifyLogin(Manager* original) {

	char nif[15], password[30];

	printf("Please insert your NIF:\n");
	scanf("%14s", nif);
	printf("Please insert your password:\n");
	scanf("%29s", password);

	if (checkNIF(original, nif) == 0) {
		printf("NIF DOES NOT EXIST!\n");
		return 0; // nif does not exist
	}

	if (checkAuth(original, nif, password) == 0) {
		printf("PASSWORD DOES NOT MATCH!\n");
		return 0; // password doesnt match
	} 
	
	return 1; // return 1 means nif and password match!

}

int checkNIF(Manager* original, char nif[]) {
	while (original != NULL) {
		if (strcmp(original->nif, nif) == 0) {
			return 1;
		}
		original = original->next;
	}
	return 0;
}

/**
 * .
 * 
 * \function name checkAuth
 * \function type int
 * \param original
 * \param nif
 * \param password
 * \return 
 */
int checkAuth(Manager* original, char nif[], char password[]) {
	while (original != NULL) {
		if (strcmp(original->nif, nif) == 0 && strcmp(original->password, password) == 0) {
			return 1;
		}
		original = original->next;
	}
	return 0;
}


#pragma endregion

