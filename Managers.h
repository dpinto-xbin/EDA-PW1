/*****************************************************************//**
 * \Filename Managers.h
 * 
 * 
 * \author Ricardo Cruz && Diogo Pinto
 * \date   March 2023
 *********************************************************************/
#include <stdio.h>

typedef struct newManager {
    char nif[15];
    char name[30];
    char password[30];

    struct newManager* next;
} Manager;

//Reads the file Managers.txt and insert on a list
Manager* readManagers();

//Insert single manager
Manager* insertManagers(Manager* aux, char nif[], char name[], char password[]);

//Initialize AUTH proccess
int verifyLogin(Manager* original);

//Compares nif for AUTH proccess
int checkNIF(Manager* original, char nif[]);

//Verifys if password and nif match
int checkAuth(Manager* original, char nif[], char password[]);
