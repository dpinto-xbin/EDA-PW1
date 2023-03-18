#include <stdlib.h>
#include <string.h>
#include "Clients.h"

#pragma warning(disable:4996)

#pragma region ReadAndInsertClientsFromFile
// Reads from file all clients
Client* readClients()
{
	FILE* fp;
	int idClient, rentedT;
	float balance;
	char name[50], nif[15], address[50], phone[12], email[50];

	Client* aux = NULL;
	fp = fopen("Clients.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%[^;\n];%f;%[^;\n];%[^;\n];%[^;\n];%[^;\n];%d\n",
				&idClient, name, &balance, nif, address, phone, email, &rentedT);
			aux = insertClients(aux, idClient, name, balance, nif, address, phone, email, rentedT);
		}

		fclose(fp);
	}
	return(aux);
}

// Insert new client
Client* insertClients(Client* aux, int idClient, char name[], float balance, char nif[], char address[], char phone[], char email[], int rentedT)
{
	if (!existClient(aux, idClient))
	{
		Client* new = malloc(sizeof(struct newClient));
		if (new != NULL)
		{
			new->idClient = idClient;
			strcpy(new->name, name);
			strcpy(new->nif, nif);
			strcpy(new->address, address);
			strcpy(new->phone, phone);
			strcpy(new->email, email);
			new->balance = balance;
			new->rentedT = rentedT;
			new->next = aux;
			return(new);
		}
	}
	else return(aux);
}
#pragma endregion

#pragma region InsertAndRemoveUniqueClient
Client* insertClient(Client* aux)
{
	int idClient, rentedT;
	float balance;
	char name[50], nif[15], address[50], phone[15], email[50];

	printf("Name: ");
	fgets(name, 50, stdin);
	name[strcspn(name, "\n")] = 0; // remove trailing newline
	printf("NIF: ");
	fgets(nif, 15, stdin);
	nif[strcspn(nif, "\n")] = 0; // remove trailing newline
	printf("Address: ");
	fgets(address, 50, stdin);
	address[strcspn(address, "\n")] = 0; // remove trailing newline
	printf("Phone: ");
	fgets(phone, 12, stdin);
	phone[strcspn(phone, "\n")] = 0; // remove trailing newline
	printf("Email: ");
	fgets(email, 50, stdin);
	email[strcspn(email, "\n")] = 0; // remove trailing newline

	Client* new = malloc(sizeof(struct newClient));
	if (new != NULL)
	{
		new->idClient = aux->idClient + 1;
		strcpy(new->name, name);
		strcpy(new->nif, nif);
		strcpy(new->address, address);
		strcpy(new->phone, phone);
		strcpy(new->email, email);
		new->balance = 0;
		new->rentedT = 0;
		new->next = aux;
		system("cls");
		printf("|------Client added!------|\n");
		return(new);
	}
	//PREVENT ERRORS, IF FILE IS NOT LOADED AND LIST IS NULL 
	else {
		new->idClient = 1;
		strcpy(new->name, name);
		strcpy(new->nif, nif);
		strcpy(new->address, address);
		strcpy(new->phone, phone);
		strcpy(new->email, email);
		new->balance = 0;
		new->rentedT = 0;
		new->next = aux;
		system("cls");
		printf("|------Client added!------|\n");
		return(new);
	}
}

// Remove client using idClient
Client* removeClient(Client* original)
{
	int idClient;
	char buffer[5];
	printf("Insert CLIENTID to remove:\n");
	fgets(buffer, sizeof(buffer), stdin);  // read up to sizeof(buffer) characters from stdin
	idClient = atoi(buffer);  // convert the string to an integer

	Client* before = original, * now = original, * aux;

	if (now == NULL) return(NULL);
	else if (now->idClient == idClient)
	{
		aux = now->next;
		free(now);
		system("cls");
		printf("|------Client removed!------|\n");
		return(aux);
	}
	else
	{
		while ((now != NULL) && (now->idClient != idClient))
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
			printf("|------Client removed!------|\n");
			return(original);
		}
	}
}
#pragma endregion

#pragma region UpdateUniqueClient
void updateClient(Client* original) {
	printf("---------------------------------------------------------------\n");
	char address[50];
	char phone[12];
	char email[50];
	int clientID, type;
	char buffer[5];

	printf("Insert CLIENTID to update:\n");
	fgets(buffer, sizeof(buffer), stdin);  // read up to sizeof(buffer) characters from stdin
	clientID = atoi(buffer);  // convert the string to an integer

	printf("Insert the field to update:\n");
	printf("|1 - Email | 2 - Phone | 3 - Address|\n");
	fgets(buffer, sizeof(buffer), stdin);  // read up to sizeof(buffer) characters from stdin
	type = atoi(buffer);  // convert the string to an integer

	Client* current = original;
	while (current != NULL) {
		if (current->idClient == clientID) {  // assume each client has a unique ID
			// Update the client object based on the given type
			printf("Client Found!\n");
			printf("Name: %s | ClientID: %d \n", current->name, current->idClient);

			if (type == 1) {
				// Update client's email
				printf("Current email: %s\n", current->email);
				printf("Insert the email to update:\n");
				fgets(email, 50, stdin);
				email[strcspn(email, "\n")] = 0; // remove trailing newline
				strcpy(current->email, email);
			}
			else if (type == 2) {
				// Update client's phone
				printf("Current phone: %s\n", current->phone);
				printf("Insert the phone to update:\n");
				fgets(phone, 12, stdin);
				phone[strcspn(phone, "\n")] = 0; // remove trailing newline
				strcpy(current->phone, phone);
			}
			else if (type == 3) {
				// Update client's address
				printf("Current address: %s\n", current->address);
				printf("Insert the address to update:\n");
				fgets(address, 50, stdin);
				address[strcspn(address, "\n")] = 0; // remove trailing newline
				strcpy(current->address, address);
			}
			system("cls");
			printf("Client %s updated.\n", current->name);
			return;  // return the current list after updating
		}
		current = current->next;
	}
	printf("Client %d not found.\n", clientID);
	printf("---------------------------------------------------------------\n");
}
#pragma endregion

#pragma region ListClientsOptions
// Lists all the clients
void listClients(Client* aux)
{
	printf("---------------------------------------------------------------\n");
	while (aux != NULL)
	{
		printf("NAME: %s \n ID: %d\n BALANCE: %.2f \n NIF: %s \n ADDRESS: %s \n PHONE: %s \n EMAIL: %s \n RENTED ID: %d \n\n\n", aux->name, aux->idClient, aux->balance, aux->nif, aux->address, aux->phone, aux->email, aux->rentedT);
		aux = aux->next;
	}
	printf("---------------------------------------------------------------\n");
}
#pragma endregion

#pragma region ClientCheckFunctions
// Checks if client is already on the list
// Returns 1 if exists, 0 if doesnt exist
int existClient(Client* aux, int idClient)
{
	while (aux != NULL)
	{
		if (aux->idClient == idClient) return(1);
		aux = aux->next;
	}
	return(0);
}

#pragma endregion

#pragma region SaveClientsFiles
void saveClients(Client* aux)
{
	char semicolon = ';';
	FILE* fp = fopen("clients.bin", "wb+");
	if (fp == NULL) {
		printf("File doesn't exist. Creating..\n");
	}

	while (aux != NULL) {
		fwrite(&aux->idClient, sizeof(int), 1, fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(aux->name, sizeof(char), sizeof(aux->name), fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(&aux->balance, sizeof(float), 1, fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(aux->nif, sizeof(char), sizeof(aux->nif), fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(aux->address, sizeof(char), sizeof(aux->address), fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(aux->phone, sizeof(char), sizeof(aux->phone), fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(aux->email, sizeof(char), sizeof(aux->email), fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(&aux->rentedT, sizeof(int), 1, fp);

		aux = aux->next;
	}

	fclose(fp);
}
#pragma endregion

#pragma region UpdateClientsOptions
int updateClientRented(int clientID, int transportID, Client* original) {

	Client* current = original;

	while (current != NULL) {
		if (current->idClient == clientID) {
			if (current->rentedT != 0) {
				system("cls");
				printf("You're already renting! \n");
				printf("Going back to menu... \n");
				return 0;  // return without updating
			}
			else {
				current->rentedT = transportID;
				return 1;  // return the current list after updating
			}
		}
		current = current->next;
	}
}
#pragma endregion











