#include <stdio.h>

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

typedef struct newCategory {
    int idCategory;
    int type;
    char desc[100];

    struct newCategory* next;
} Category;


// Reads the file Transports.txt and insert on a list
Transport* readTransports();

// Read file and insert list at start
Transport* insertTransports(Transport* aux, int idTransport, int status, int type, int rentedCli, float battery, float autonomy, float price, char geolocation[]);

// List all transports
void listTransports(Transport* aux);

// Update transport via ID
void updateTransport(Transport* original);
