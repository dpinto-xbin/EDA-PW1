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
		return;
	}
	else {

		if (updateClientRented(clientID, transportID, client) == 0) return;
		if (updateTransportRented(clientID, transportID, transport) == 0) return;
		
		system("cls");
		getTransportInfo(transport, category, transportID);
		
	}



}
#pragma endregion


