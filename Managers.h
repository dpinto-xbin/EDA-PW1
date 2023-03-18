#include <stdio.h>

typedef struct newManager {
    char nif[15];
    char name[30];
    char password[30];

    struct newManager* next;
} Manager;

Manager* readManagers();
Manager* insertManagers(Manager* aux, char nif[], char name[], char password[]);
int verifyLogin(Manager* original);
int checkNIF(Manager* original, char nif[]);
int checkAuth(Manager* original, char nif[], char password[]);
