#include <stdlib.h>
#include <stdio.h>
#include "Clients.h"
#include "Transports.h"
#include "Renting.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)

int menu()
{
	int op;
	printf("TP PHASE 1\n");
	printf("1 - Insert Client\n");
	printf("2 - List Clients\n");
	printf("3 - Save Clients (.bin)\n");
	printf("4 - Remove Client by ID\n");
	printf("5 - Update Client by ID\n");
	printf("6 - Insert Transport\n");
	printf("7 - List Transports\n");
	printf("8 - Update Transport by ID\n");
	printf("9 - Remove Transport by ID\n");
	printf("10 - Save Transports (.bin)\n");
	printf("11 - List Categories\n");
	printf("12 - Rent Transport\n");
	printf("13 - Clear console\n");
	printf("0 - Exit\n");
	printf("OPTION:\n");
	scanf("%d", &op);
	getchar();
	return(op);
}

int main()
{
	Client* clients = NULL; // Empty linked list
	Transport* transports = NULL;
	Category* categories = NULL;
	clients = readClients(); // Start by reading file
	transports = readTransports();
	categories = readCategories();
	int op, clientID = 1; // Case 12 - direct relation check!

	do
	{
		op = menu();
		switch (op)
		{
		case 1: clients = insertClient(clients); break;
		case 2: listClients(clients); break;
		case 3: saveClients(clients); break;
		case 4: clients = removeClient(clients); break;
		case 5: updateClient(clients); break;
		case 6: transports = insertTransport(transports); break;
		case 7: listTransports(transports); break;
		case 8: updateTransport(transports); break;
		case 9: transports = removeTransport(transports); break;
		case 10: saveTransports(transports); break;
		case 11: listCategories(categories); break;
		case 12: rentTransport(transports, clients, categories, clientID); break; //Dont forget this step is required to have client logged in!
		case 13: system("cls"); break;
		}
	} while (op != 0);


	return(0);
}

