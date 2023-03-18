#include <stdlib.h>
#include <string.h>
#include "Transports.h"
#include "Clients.h"

#pragma region RentTransport
void rentTransport(Transport* transport, Client* client, Category* category, int clientID) {

	int transportID;
	char buffer[5];

	// Prints all the available transports
	availableTransports(transport, category);

	printf("Insert TRANSPORTID to rent:\n");
	printf("Or 0 to cancel renting.\n");
	fgets(buffer, sizeof(buffer), stdin);  // read up to sizeof(buffer) characters from stdin
	transportID = atoi(buffer);  // convert the string to an integer


	if (transportID == 0) { 
		return; // Cancel renting
	}
	else {

		if (updateClientRented(clientID, transportID, client, 1) == 0) return; // If client is renting = 0 + last number is 1 because its renting check .h for more info
		if (updateTransportRented(clientID, transportID, transport, 1) == 0) return; // If transport is not available = 0 + last number is 1 because its renting check .h for more info
		
		system("cls");
		getTransportInfo(transport, category, transportID); // Outputs data for renting
		
	}



}
#pragma endregion

#pragma region ReturnTransport
void returnTransport(Transport* transport, Client* client, Category* category, int clientID) {

	int transportID, opt, aux;
	char buffer[5];
	system("cls");
	transportID = checkClientRental(client, transport, category, clientID);
	
	if (transportID == 0) return;
	printf("Are you sure you want to return your rental?\n");
	printf("YES - 1 | NO - 0\n");
	fgets(buffer, sizeof(buffer), stdin);  // read up to sizeof(buffer) characters from stdin
	opt = atoi(buffer);  // convert the string to an integer

	if (opt == 1)
	{
		aux = updateClientRented(clientID, transportID, client, 2);
		aux = updateTransportRented(clientID, transportID, transport, 2);

		system("cls");
		printf("You've stopped renting our vehicle.\n");
		printf("Thank you for choosing us!\n");
		printf("------------------------------------------------------------------------------------------------\n\n\n");

	}
	else {
		system("cls");
		return;
	} 



	
	
	
}
#pragma endregion

