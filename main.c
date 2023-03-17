#include <stdlib.h>
#include <stdio.h>
#include "Clients.h"
#include "Transports.h"
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
	printf("6 - List Transports\n");
	printf("0 - Exit\n");
	printf("9 - Clear console\n");
	printf("OPTION:\n");
	scanf("%d", &op);
	getchar();
	return(op);
}

int main()
{
	Client* clients = NULL; // Empty linked list
	Transport* transports = NULL;
	clients = readClients(); // Start by reading file
	transports = readTransports();
	int op;

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
		case 6: listTransports(transports); break;
		case 7: updateTransport(transports); break;
		case 9: system("cls"); break;
		}
	} while (op != 0);


	return(0);
}

