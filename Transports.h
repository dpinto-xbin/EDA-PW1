#include <stdio.h>

#pragma region Transports

typedef struct newTransport {
    int idTransport;
    int type;
    float battery;
    float autonomy;
    float price; //price per km
    int rentedCli;
    int status;
    char geolocation[100];

    struct newTransport* next;
} Transport;


// Reads the file Transports.txt and insert on a linked list
Transport* readTransports();

// Used at program start to insert data obtained from file
Transport* insertTransports(Transport* aux, int idTransport, int status, int type, int rentedCli, float battery, float autonomy, float price, char geolocation[]);

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

#pragma region Categories
typedef struct newCategory {
    int idCategory;
    int type;
    char desc[100];

    struct newCategory* next;
} Category;

// Reads the file Categories.txt and insert on a linked list
Category* readCategories();

// Used at program start to insert data obtained from file
Category* insertCategories(Category* aux, int idCategory, int type, char desc[]);

// List all transports categories
void listCategories(Category* aux);

#pragma endregion




