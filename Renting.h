#include <stdio.h>

void rentTransport(Transport* transport, Client* client, Category* category, int clientID);
void returnTransport(Transport* transport, Client* client, Category* category, int clientID);
int checkClientRental(Client* original, Transport* transport, Category* category, int clientID);
