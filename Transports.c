#include <stdlib.h>
#include <string.h>
#include "Transports.h"

#pragma warning(disable:4996)

#pragma region Transports
// Reads from file all transports
Transport* readTransports()
{
	FILE* fp;
	int idTransport, type, rentedCli, status;
	float battery, autonomy, price;
	char geolocation[100];

	Transport* aux = NULL;
	fp = fopen("Transports.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%d;%d;%d;%f;%f;%f;%[^;\n];", &status, &idTransport, &type, &rentedCli, &battery, &autonomy, &price, geolocation);
			aux = insertTransports(aux, idTransport, status, type, rentedCli, battery, autonomy, price, geolocation);
		}

		fclose(fp);
	}
	return(aux);
}

// Insert from file
Transport* insertTransports(Transport* aux, int idTransport, int status, int type, int rentedCli, float battery, float autonomy, float price, char geolocation[])
{
	Transport* new = malloc(sizeof(struct newTransport));
	if (new != NULL)
	{
		new->idTransport = idTransport;
		new->status = status;
		strcpy(new->geolocation, geolocation);
		new->type = type;
		new->rentedCli = rentedCli;
		new->battery = battery;
		new->autonomy = autonomy;
		new->price = price;
		new->next = aux;
		return(new);
	}
	else return(aux);
}

// Lists all the transports
void listTransports(Transport* aux)
{
	printf("---------------------------------------------------------------\n");
	while (aux != NULL)
	{
		printf("ID: %d \n STATUS: %d \n TYPE: %d\n RENTED CLIENT ID: %d \n BATTERY: %.2f \n AUTONOMY: %.2f \n PRICE: %.2f \n GEOLOCATION: %s \n\n\n", aux->idTransport, aux->status, aux->type, aux->rentedCli, aux->battery, aux->autonomy, aux->price, aux->geolocation);
		aux = aux->next;
	}
	printf("---------------------------------------------------------------\n");
}

// Updates transport via transportID

void updateTransport(Transport* original) {
	printf("---------------------------------------------------------------\n");
	int transportID, rentedCli, status, type;
	float battery, autonomy, price;
	char geolocation[100];
	char buffer[5];

	printf("Insert TRANSPORTID to update:\n");
	fgets(buffer, sizeof(buffer), stdin);  // read up to sizeof(buffer) characters from stdin
	transportID = atoi(buffer);  // convert the string to an integer

	printf("Insert the field to update:\n");
	printf("|1 - Status | 2 - Battery | 3 - Autonomy | 4 - Price | 5 - Geolocation |\n");
	fgets(buffer, sizeof(buffer), stdin);  // read up to sizeof(buffer) characters from stdin
	type = atoi(buffer);  // convert the string to an integer

	Transport* current = original;
	while (current != NULL) {
		if (current->idTransport == transportID) {  // assume each client has a unique ID
			// Update the client object based on the given type
			printf("Transport Found!\n");
			printf("Status: %d | ClientID: %d | Geolocation: %s \n", current->status, current->idTransport, current->geolocation);

			if (type == 1) {
				// Update transport status
				printf("Current status: %d\n", current->status);
				printf("|1 - Maintenance | 2 - MIA (Missing in Action) |\n"); //Rented and Available not needed here.
				printf("Insert the status to update:\n");
				scanf("%d", &status);
				current->status = status;
			}
			else if (type == 2) {
				// Update transport battery
				printf("Current battery: %.2f\n", current->battery);
				printf("Insert the battery level to update:\n");
				scanf("%f", &battery);
				current->battery = battery;
			}
			else if (type == 3) {
				// Update transport autonomy
				printf("Current autonomy: %.2f\n", current->autonomy);
				printf("Insert the autonomy to update:\n");
				scanf("%f", &autonomy);
				current->autonomy = autonomy;
			}
			else if (type == 4) {
				// Update transport price
				printf("Current price: %.2f\n", current->price);
				printf("Insert the price to update:\n");
				scanf("%f", &price);
				current->price = price;
			}
			else if (type == 5) {
				// Update transport geolocation
				printf("Current geolocation: %s\n", current->geolocation);
				printf("WARNING! USE WHAT3WORDS.COM TO FIND GEOLOCATION!\n");
				printf("Insert the geolocation to update:\n");
				fgets(geolocation, 100, stdin);
				geolocation[strcspn(geolocation, "\n")] = 0; // remove trailing newline
				strcpy(current->geolocation, geolocation);
			}
			system("cls");
			printf("Transport %d updated.\n", current->idTransport);
			return;  // return the current list after updating
		}
		current = current->next;
	}
	printf("Transport %d not found.\n", transportID);
	printf("---------------------------------------------------------------\n");
}

// Insert unique transport
Transport* insertTransport(Transport* aux)
{
	int type, status;
	float battery, autonomy, price;
	char geolocation[100];

	printf("Type:\n");
	scanf("%d", &type);
	printf("Status:\n");
	scanf("%d", &status);
	printf("Battery:\n");
	scanf("%f", &battery);
	printf("Autonomy:\n");
	scanf("%f", &autonomy);
	printf("Price:\n");
	scanf("%f", &price);
	getchar(); // consume newline character
	printf("Geolocation: ");
	fgets(geolocation, 100, stdin);
	geolocation[strcspn(geolocation, "\n")] = 0; // remove trailing newline




	Transport* new = malloc(sizeof(struct newTransport));
	if (new != NULL)
	{
		new->idTransport = aux->idTransport + 1;
		strcpy(new->geolocation, geolocation);
		new->type = type;
		new->status = status;
		new->battery = battery;
		new->autonomy = autonomy;
		new->price = price;
		new->rentedCli = 0;
		new->next = aux;
		system("cls");
		printf("|------Transport added!------|\n");
		return(new);
	}
	//PREVENT ERRORS, IF FILE IS NOT LOADED AND LIST IS NULL 
	else {
		new->idTransport = 1;
		strcpy(new->geolocation, geolocation);
		new->type = type;
		new->status = status;
		new->battery = battery;
		new->autonomy = autonomy;
		new->price = price;
		new->rentedCli = 0;
		new->next = aux;
		system("cls");
		printf("|------Transport added!------|\n");
		return(new);
	}
}

// Remove transport using idTransport
Transport* removeTransport(Transport* original)
{
	int idTransport;
	char buffer[5];
	printf("Insert TRANSPORT ID to remove:\n");
	fgets(buffer, sizeof(buffer), stdin);  // read up to sizeof(buffer) characters from stdin
	idTransport = atoi(buffer);  // convert the string to an integer

	Transport* before = original, * now = original, * aux;

	if (now == NULL) return(NULL);
	else if (now->idTransport == idTransport)
	{
		aux = now->next;
		free(now);
		system("cls");
		printf("|------Transport removed!------|\n");
		return(aux);
	}
	else
	{
		while ((now != NULL) && (now->idTransport != idTransport))
		{
			before = now;
			now = now->next;
		}
		if (now == NULL) return(original);
		else
		{
			before->next = now->next;
			free(now);
			system("cls");
			printf("|------Transport removed!------|\n");
			return(original);
		}
	}
}
//Save transports in .bin file
void saveTransports(Transport* aux)
{
	char semicolon = ';';
	FILE* fp = fopen("transports.bin", "wb+");
	if (fp == NULL) {
		printf("File doesn't exist. Creating..\n");
	}

	while (aux != NULL) {
		fwrite(&aux->status, sizeof(int), 1, fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(&aux->idTransport, sizeof(int), 1, fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(&aux->type, sizeof(int), 1, fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(&aux->rentedCli, sizeof(int), 1, fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(&aux->battery, sizeof(float), 1, fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(&aux->autonomy, sizeof(float), 1, fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(&aux->price, sizeof(float), 1, fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(aux->geolocation, sizeof(char), sizeof(aux->geolocation), fp);
		fwrite(&semicolon, sizeof(char), 1, fp);

		aux = aux->next;
	}

	fclose(fp);

	system("cls");
	printf("Transport saved!\n");
}
#pragma endregion

#pragma region Categories
// Reads from file all transports
Category* readCategories()
{
	FILE* fp;
	int idCategory, type;
	char desc[100];

	Category* aux = NULL;
	fp = fopen("Categories.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%d;%[^;\n];", &idCategory, &type, desc);
			aux = insertCategories(aux, idCategory, type, desc);
		}

		fclose(fp);
	}
	return(aux);
}

// Insert from file
Category* insertCategories(Category* aux, int idCategory, int type, char desc[])
{
	Category* new = malloc(sizeof(struct newTransport));
	if (new != NULL)
	{
		new->idCategory = idCategory;
		new->type = type;
		strcpy(new->desc, desc);
		new->next = aux;
		return(new);
	}
	else return(aux);
}

// Lists all the categories
void listCategories(Category* aux)
{
	printf("---------------------------------------------------------------\n");
	while (aux != NULL)
	{
		printf("ID: %d\n TYPE: %d \n DESCRIPTION: %s \n\n\n", aux->idCategory, aux->type, aux->desc);
		aux = aux->next;
	}
	printf("---------------------------------------------------------------\n");
}
#pragma endregion

