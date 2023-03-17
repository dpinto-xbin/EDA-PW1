typedef struct newTransport {
    int idTransport;
    int type;
    float battery;
    float autonomy;
    float price;
    int rentedCli;
    char geolocation[100];

    struct newTransport* next;
} Transport;

typedef struct newCategory {
    int idCategory;
    int type;
    char desc[100];

    struct newCategory* next;
} Category;


