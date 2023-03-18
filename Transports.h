/*****************************************************************//**
 * \Filename Transports.h
 * 
 * 
 * \author Ricardo Cruz && Diogo Pinto
 * \date   March 2023
 *********************************************************************/
#include <stdio.h>
#define RENTED 3
#define AVAILABLE 4
#define MIA 2
#define MAINTENANCE 1

#pragma region Structs
typedef struct newTransport {
    int idTransport;
    int type;
    float battery;
    float autonomy;
    float price; // Price per km
    int rentedCli;
    int status; // 1 - Maintenance | 2 - MIA (Missing in Action) | 3 - Rented | 4 - Available |
    char geolocation[100];

    struct newTransport* next;
} Transport;

typedef struct newCategory {
    int idCategory;
    int type;
    char desc[100];

    struct newCategory* next;
} Category;
#pragma endregion

#pragma region Transports

#pragma region TransportFunctionsManager
// List all transports
void listTransports(Transport* aux);

// Update transport via ID
void updateTransport(Transport* original);

//Insert unique transport
Transport* insertTransport(Transport* aux);

//Removes transport by ID
Transport* removeTransport(Transport* original);

//Saves bin file of linked list Transport
void saveTransports(Transport* aux);
#pragma endregion

#pragma region TransportFunctionsGlobal
// List availables transports
void availableTransports(Transport* aux, Category* aux2);
#pragma endregion

#pragma region TransportFunctionsSupport
// Reads the file Transports.txt and insert on a linked list
Transport* readTransports();

// Used at program start to insert data obtained from file
Transport* insertTransports(Transport* aux, int idTransport, int status, int type, int rentedCli, float battery, float autonomy, float price, char geolocation[]);

// Updates Transport to RENTED after client renting it.
int updateTransportRented(int clientID, int transportID, Transport* original, int opt);

// Gets all transport info when renting
void getTransportInfo(Transport* aux, Category* aux2, int transportID);

// Check for type via TRANSPORTID
int getType(Transport* aux, int transportID);

// To sort the linked list into descending by autonomy
Transport* insertionSortDescendingAutonomy(Transport* head);

// List all the vehicles in that geolocation
void checkTransportbyGeolocation(Transport* original, Category* categories);

#pragma endregion


#pragma endregion

#pragma region Categories

// Reads the file Categories.txt and insert on a linked list
Category* readCategories();

// Used at program start to insert data obtained from file
Category* insertCategories(Category* aux, int idCategory, int type, char desc[]);

// List all transports categories
void listCategories(Category* aux);

// Gets description of type
char* typeCategories(Category* aux, int type);

#pragma endregion




