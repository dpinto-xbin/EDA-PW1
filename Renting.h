/*****************************************************************//**
 * \Filename Renting.h
 * 
 * 
 * \author Ricardo Cruz && Diogo Pinto
 * \date   March 2023
 *********************************************************************/
#include <stdio.h>


//Function to rent a transport
void rentTransport(Transport* transport, Client* client, Category* category, int clientID);

//Function to return a transport
void returnTransport(Transport* transport, Client* client, Category* category, int clientID);

//Checks if client has a rental at that time
int checkClientRental(Client* original, Transport* transport, Category* category, int clientID);