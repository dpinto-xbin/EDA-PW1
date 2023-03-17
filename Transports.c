#include <stdlib.h>
#include <string.h>
#include "Transports.h"

#pragma warning(disable:4996)

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
			aux = insertTransports(aux,idTransport, status, type, rentedCli, battery, autonomy, price, geolocation);
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