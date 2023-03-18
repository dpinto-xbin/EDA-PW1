/*****************************************************************//**
 * \file   main.c
 * 
 * \author Diogo Pinto & Ricardo Cruz
 * \date   March 2023
 *********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "Clients.h"
#include "Transports.h"
#include "Renting.h"
#include "Managers.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)

int menu()
{
	int op;
	printf("TP PHASE 1\n");
	printf("1 - Rent Transport\n");
	printf("2 - Return Transport\n");
	printf("0 - Exit\n");
	printf("OPTION:\n");
	scanf("%d", &op);
	getchar();
	return(op);
}

int menuManager()
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
	printf("12 - List Transports by Geolocation\n");
	printf("14 - Transports by descending order of autonomy\n");
	printf("15 - Clear console\n");
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
	Transport* sortedList = NULL;
	Manager* managers = NULL;
	clients = readClients(); // Start by reading file
	transports = readTransports();
	categories = readCategories();
	managers = readManagers();
	int op, clientID;// Case 12 - direct relation check!
	int login, loginAuth;
	char nif[15], password[30];

	printf("User - 1 | Manager - 2\n");
	printf("Welcome. Login as user or manager?\n");
	scanf("%d", &login);

	if (login == 1) {
		printf("Please insert your clientID:\n");
		scanf("%d", &clientID);
		do
		{
			op = menu();
			switch (op)
			{
			case 1: rentTransport(transports, clients, categories, clientID); break; 
			case 2: returnTransport(transports, clients, categories, clientID); break;
			}

		} while (op != 0);
	}
	else {
		loginAuth = verifyLogin(managers);
		if (loginAuth == 0) return 0;
		
		do
		{
			op = menuManager();
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
			case 12: checkTransportbyGeolocation(transports, categories); break;
			case 14: sortedList = insertionSortDescendingAutonomy(transports); listTransports(sortedList); break;
			case 15: system("cls"); break;
			}
		} while (op != 0);
	}

	


	return(0);
}

