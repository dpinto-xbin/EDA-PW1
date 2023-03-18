#include <stdio.h>

typedef struct newClient
{
    int idClient;
    char name[50];
    float balance;
    char nif[15];
    char address[50];
    char phone[12];
    char email[50];
    int rentedT;
    struct newClient* next;
} Client;


//Read file and insert list at start
Client* insertClients(Client* aux, int idClient, char name[], float balance, char nif[], char address[], char phone[], char email[], int rentedT);

//Insert single client
Client* insertClient(Client* aux);

//Checks if idClient exists
int existClient(Client* aux, int idClient);

//Reads the file clients.txt and insert on a list
Client* readClients();

//List all the clients in the list
void listClients(Client* aux);

//Saves the list on a .bin file
void saveClients(Client* aux);

//Removes client via idClient reorganizes list and returns list
Client* removeClient(Client* original);

//Updates client via idClient via pointer
void updateClient(Client* original);

//Updates the rented transport on client
int updateClientRented(int clientID, int transportID, Client* client);

