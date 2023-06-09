#include <stdlib.h>
#include <string.h>
#include "Transports.h"

#pragma warning(disable:4996)



#pragma region Transports

#pragma region ReadAndInsertTransportsFromFile
/**
 * \Function Name readTransports
 * \Function Type Transport *
 * 
 * \Brief: Reads from file all transports
 * 
 * 
 */
Transport* readTransports()
{
	FILE* fp;
	int idTransport, type, rentedCli, status;
	float battery, autonomy, price;
	char geolocation[100];

	Transport* aux = NULL;
	fp = fopen("Transports.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%d;%d;%d;%f;%f;%f;%[^;\n];", &status, &idTransport, &type, &rentedCli, &battery, &autonomy, &price, geolocation);
			aux = insertTransports(aux, idTransport, status, type, rentedCli, battery, autonomy, price, geolocation);
		}

		fclose(fp);
	}
	return(aux);
}


/**
 * \Function Name insertTransports
 * \Function Type Transport *
 * 
 * \Brief: Insert from file
 * 
 * \param aux
 * \param idTransport
 * \param status
 * \param type
 * \param rentedCli
 * \param battery
 * \param autonomy
 * \param price
 * \param geolocation
 * 
 * \return 
 */
Transport* insertTransports(Transport* aux, int idTransport, int status, int type, int rentedCli, float battery, float autonomy, float price, char geolocation[])
{
	Transport* new = malloc(sizeof(struct newTransport));
	if (new != NULL)
	{
		new->idTransport = idTransport;
		new->status = status;
		strcpy(new->geolocation, geolocation);
		new->type = type;
		new->rentedCli = rentedCli;
		new->battery = battery;
		new->autonomy = autonomy;
		new->price = price;
		new->next = aux;
		return(new);
	}
	else return(aux);
}
#pragma endregion


#pragma region ListTransportsOptions

/**
 * \Function Name listTransports
 * \Function Type void
 * 
 * \Brief: Lists all the transports
 * 
 * \param aux
 * 
 */
void listTransports(Transport* aux)
{
	system("cls");
	printf("---------------------------------------------------------------\n");
	printf("ALL TRANSPORTS\n\n");
	while (aux != NULL)
	{
		printf("ID: %d - STATUS: %d - TYPE: %d - RENTED CLIENT ID: %d - BATTERY: %.2f - AUTONOMY: %.2f - PRICE: %.2f - GEOLOCATION: %s \n\n\n", aux->idTransport, aux->status, aux->type, aux->rentedCli, aux->battery, aux->autonomy, aux->price, aux->geolocation);
		aux = aux->next;
	}
	printf("---------------------------------------------------------------\n");
}


/**
 * \Function Name availableTransports
 * \Function Type void
 * 
 * \Brief: List all the available transports
 * 
 * \param aux
 * \param aux2
 * 
 */
void availableTransports(Transport* aux, Category* aux2)
{
	system("cls");
	printf("---------------------------------------------------------------\n");
	printf("AVAILABLE TRANSPORTS\n\n");
	while (aux != NULL)
	{
		if (aux->status == 4) {
			printf("ID: %d - TYPE: %s - BATTERY: %.2f - AUTONOMY: %.2f - PRICE: %.2f - GEOLOCATION: %s \n\n\n", aux->idTransport, typeCategories(aux2, aux->type), aux->battery, aux->autonomy, aux->price, aux->geolocation);
		}
		aux = aux->next;
	}
	printf("---------------------------------------------------------------\n");
}
#pragma endregion


#pragma region UpdateUniqueTransport

/**
 * \Function Name updateTransport
 * \Function Type void
 * 
 * \Brief: Updates transport via transportID
 * 
 * \param original
 * 
 */
void updateTransport(Transport* original) {
	printf("---------------------------------------------------------------\n");
	int transportID, rentedCli, status, type;
	float battery, autonomy, price;
	char geolocation[100];
	char buffer[5];

	printf("Insert TRANSPORTID to update:\n");
	fgets(buffer, sizeof(buffer), stdin);  // read up to sizeof(buffer) characters from stdin
	transportID = atoi(buffer);  // convert the string to an integer

	printf("Insert the field to update:\n");
	printf("|1 - Status | 2 - Battery | 3 - Autonomy | 4 - Price | 5 - Geolocation |\n");
	fgets(buffer, sizeof(buffer), stdin);  // read up to sizeof(buffer) characters from stdin
	type = atoi(buffer);  // convert the string to an integer

	Transport* current = original;
	while (current != NULL) {
		if (current->idTransport == transportID) {  // assume each client has a unique ID
			// Update the client object based on the given type
			printf("Transport Found!\n");
			printf("Status: %d | ClientID: %d | Geolocation: %s \n", current->status, current->idTransport, current->geolocation);

			if (type == 1) {
				// Update transport status
				printf("Current status: %d\n", current->status);
				printf("| 1 - Maintenance | 2 - MIA (Missing in Action) | 3 - Rented | 4 - Available |\n");
				printf("Insert the status to update:\n");
				scanf("%d", &status);
				current->status = status;
			}
			else if (type == 2) {
				// Update transport battery
				printf("Current battery: %.2f\n", current->battery);
				printf("Insert the battery level to update:\n");
				scanf("%f", &battery);
				current->battery = battery;
			}
			else if (type == 3) {
				// Update transport autonomy
				printf("Current autonomy: %.2f\n", current->autonomy);
				printf("Insert the autonomy to update:\n");
				scanf("%f", &autonomy);
				current->autonomy = autonomy;
			}
			else if (type == 4) {
				// Update transport price
				printf("Current price: %.2f\n", current->price);
				printf("Insert the price to update:\n");
				scanf("%f", &price);
				current->price = price;
			}
			else if (type == 5) {
				// Update transport geolocation
				printf("Current geolocation: %s\n", current->geolocation);
				printf("WARNING! USE WHAT3WORDS.COM TO FIND GEOLOCATION!\n");
				printf("Insert the geolocation to update:\n");
				fgets(geolocation, 100, stdin);
				geolocation[strcspn(geolocation, "\n")] = 0; // remove trailing newline
				strcpy(current->geolocation, geolocation);
			}
			system("cls");
			printf("Transport %d updated.\n", current->idTransport);
			return;  // return the current list after updating
		}
		current = current->next;
	}
	printf("Transport %d not found.\n", transportID);
	printf("---------------------------------------------------------------\n");
}
#pragma endregion


#pragma region UpdateTransportsOptions
/**
 * \Function Name updateTransportRented
 * \Function Type int
 * 
 * \Brief: Updates transport status to rented or available
 * 
 * \param clientID
 * \param transportID
 * \param original
 * \param opt
 * 
 */
int updateTransportRented(int clientID,int transportID, Transport* original, int opt){

	Transport* current = original;

	while (current != NULL) {
		if (current->idTransport == transportID) { 
			if (current->status != 4) {
				if (opt == 2)
				{
					current->rentedCli = 0;
					current->status = AVAILABLE;
				}else{
					system("cls");
					printf("The transport you chose is not available! \n");
					printf("Going back to menu... \n");
					return 0;  // return without updating
				}
				
			}
			else {
				current->rentedCli = clientID;
				current->status = RENTED;
				return 1;  // return the current list after updating
			}
		}
		current = current->next;
	}

}

#pragma endregion

#pragma region InsertAndRemoveUniqueTransport

/**
 * \Function Name insertTransport
 * \Function Type Transport *
 * 
 * \Brief: Insert unique transport
 * 
 * \param aux
 * 
 */
Transport* insertTransport(Transport* aux)
{
	int type, status;
	float battery, autonomy, price;
	char geolocation[100];

	printf("Type:\n");
	scanf("%d", &type);
	printf("Status:\n");
	scanf("%d", &status);
	printf("Battery:\n");
	scanf("%f", &battery);
	printf("Autonomy:\n");
	scanf("%f", &autonomy);
	printf("Price:\n");
	scanf("%f", &price);
	getchar(); // consume newline character
	printf("Geolocation: ");
	fgets(geolocation, 100, stdin);
	geolocation[strcspn(geolocation, "\n")] = 0; // remove trailing newline




	Transport* new = malloc(sizeof(struct newTransport));
	if (new != NULL)
	{
		new->idTransport = aux->idTransport + 1;
		strcpy(new->geolocation, geolocation);
		new->type = type;
		new->status = status;
		new->battery = battery;
		new->autonomy = autonomy;
		new->price = price;
		new->rentedCli = 0;
		new->next = aux;
		system("cls");
		printf("|------Transport added!------|\n");
		return(new);
	}
	//PREVENT ERRORS, IF FILE IS NOT LOADED AND LIST IS NULL 
	else {
		new->idTransport = 1;
		strcpy(new->geolocation, geolocation);
		new->type = type;
		new->status = status;
		new->battery = battery;
		new->autonomy = autonomy;
		new->price = price;
		new->rentedCli = 0;
		new->next = aux;
		system("cls");
		printf("|------Transport added!------|\n");
		return(new);
	}
}


/**
 * \Function Name removeTransport
 * \Function Type Transport *
 * 
 * \Brief: Remove transport using idTransport
 * 
 * \param original
 * 
 * \return 
 */
Transport* removeTransport(Transport* original)
{
	int idTransport;
	char buffer[5];
	printf("Insert TRANSPORT ID to remove:\n");
	fgets(buffer, sizeof(buffer), stdin);  // read up to sizeof(buffer) characters from stdin
	idTransport = atoi(buffer);  // convert the string to an integer

	Transport* before = original, * now = original, * aux;

	if (now == NULL) return(NULL);
	else if (now->idTransport == idTransport)
	{
		aux = now->next;
		free(now);
		system("cls");
		printf("|------Transport removed!------|\n");
		return(aux);
	}
	else
	{
		while ((now != NULL) && (now->idTransport != idTransport))
		{
			before = now;
			now = now->next;
		}
		if (now == NULL) return(original);
		else
		{
			before->next = now->next;
			free(now);
			system("cls");
			printf("|------Transport removed!------|\n");
			return(original);
		}
	}
}
#pragma endregion


#pragma region SaveTransportsFiles

/**
 * \Function Name saveTransports
 * \Function Type void
 * 
 * \Brief: Save transports in .bin file
 * 
 * \param aux
 * 
 */
void saveTransports(Transport* aux)
{
	char semicolon = ';';
	FILE* fp = fopen("transports.bin", "wb+");
	if (fp == NULL) {
		printf("File doesn't exist. Creating..\n");
	}

	while (aux != NULL) {
		fwrite(&aux->status, sizeof(int), 1, fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(&aux->idTransport, sizeof(int), 1, fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(&aux->type, sizeof(int), 1, fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(&aux->rentedCli, sizeof(int), 1, fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(&aux->battery, sizeof(float), 1, fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(&aux->autonomy, sizeof(float), 1, fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(&aux->price, sizeof(float), 1, fp);
		fwrite(&semicolon, sizeof(char), 1, fp);
		fwrite(aux->geolocation, sizeof(char), sizeof(aux->geolocation), fp);
		fwrite(&semicolon, sizeof(char), 1, fp);

		aux = aux->next;
	}

	fclose(fp);

	system("cls");
	printf("Transport saved!\n");
}
#pragma endregion


#pragma region TransportGetFunctions
/**
 * \Function Name getTransportInfo
 * \Function Type void
 * 
 * \Brief: Prints transport info
 * 
 * \param aux
 * \param aux2
 * \param transportID
 * 
 */
void getTransportInfo(Transport* aux, Category* aux2, int transportID)
{
	while (aux != NULL)
	{
		if (aux->idTransport == transportID) {
			printf("------------------------------------------------------------------------------------------------\n");
			printf("You chose %s!\n", typeCategories(aux2, aux->type));
			printf("So your vehicle ID is %d and is located in: %s\n",
				aux->idTransport, aux->geolocation);
			printf("The battery level is %.2f and you have at least %.2f kms of autonomy.\n", 
				aux->battery, aux->autonomy);
			printf("Dont forget the price is %.2f EUR!\n", 
				aux->price);
			printf("Thank you for renting our vehicles! \n");
			printf("------------------------------------------------------------------------------------------------\n\n\n");
			break;
		}
		aux = aux->next;
	}
}
#pragma endregion


#pragma region SortList

/**
 * \Function Name insertionSortDescendingAutonomy
 * \Function Type Transport *
 * 
 * \Brief: Sorts list by descending autonomy
 * 
 * \param head
 * 
 */
Transport* insertionSortDescendingAutonomy(Transport* head) {
	if (head == NULL || head->next == NULL) {
		return head;
	}

	Transport* sorted = head, * unsorted = head->next;
	sorted->next = NULL;

	while (unsorted != NULL) {
		Transport* node = unsorted;
		unsorted = unsorted->next;

		if (node->autonomy > sorted->autonomy) {
			node->next = sorted;
			sorted = node;
		}
		else {
			Transport* current = sorted;
			while (current->next != NULL && current->next->autonomy > node->autonomy) {
				current = current->next;
			}
			node->next = current->next;
			current->next = node;
		}
	}

	return sorted;
}


/**
 * \Function Name checkTransportbyGeolocation
 * \Function Type void
 * 
 * \Brief: Checks what transport is available in a certain geolocation
 * 
 * \param original
 * \param categories
 * 
 */
void checkTransportbyGeolocation(Transport* original, Category* categories) {

	char geolocation[100];
	printf("Please insert your geolocation:\n");
	scanf("%99s", geolocation);

	system("cls");
	while (original != NULL) {
		if (strcmp(original->geolocation, geolocation) == 0) {
			printf("Transport ID: %d - Type: %s - Battery: %.2f - Autonomy: %.2f \n\n\n", original->idTransport, typeCategories(categories, original->type), original->battery, original->autonomy);
		}
		original = original->next;
	}
	return 0;

}


#pragma endregion


#pragma endregion

#pragma region Categories

#pragma region ReadAndInsertCategoriesFromFile

/**
 * \Function Name readCategories
 * \Function Type Category *
 * 
 * \Brief: Reads from file all transports
 * 
 */
Category* readCategories()
{
	FILE* fp;
	int idCategory, type;
	char desc[100];

	Category* aux = NULL;
	fp = fopen("Categories.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%d;%[^;\n];", &idCategory, &type, desc);
			aux = insertCategories(aux, idCategory, type, desc);
		}

		fclose(fp);
	}
	return(aux);
}


/**
 * \Function Name insertCategories
 * \Function Type Category *
 * 
 * \Brief: Insert from file
 * 
 * \param aux
 * \param idCategory
 * \param type
 * \param desc
 * 
 */
Category* insertCategories(Category* aux, int idCategory, int type, char desc[])
{
	Category* new = malloc(sizeof(struct newTransport));
	if (new != NULL)
	{
		new->idCategory = idCategory;
		new->type = type;
		strcpy(new->desc, desc);
		new->next = aux;
		return(new);
	}
	else return(aux);
}
#pragma endregion

#pragma region ListCategoriesOptions

/**
 * \Function Name listCategories
 * \Function Type void
 * 
 * \Brief: Lists all the categories
 * 
 * \param aux
 * 
 */
void listCategories(Category* aux)
{
	printf("---------------------------------------------------------------\n");
	while (aux != NULL)
	{
		printf("ID: %d - TYPE: %d - DESCRIPTION: %s \n\n\n", aux->idCategory, aux->type, aux->desc);
		aux = aux->next;
	}
	printf("---------------------------------------------------------------\n");
}


/**
 * \Function Name typeCategories
 * \Function Type char *
 * 
 * \Brief: Get category type description
 * 
 * \param aux
 * \param type
 * 
 */
char* typeCategories(Category* aux, int type)
{
	while (aux != NULL)
	{
		if (aux->type == type) return aux->desc;
		aux = aux->next;
	}
}


/**
 * \Function Name getType
 * \Function Type int
 * 
 * \Brief: Get type via transportID
 * 
 * \param aux
 * \param transportID
 * 
 */
int getType(Transport* aux, int transportID)
{
	while (aux != NULL)
	{
		if (aux->idTransport == transportID) return aux->type;
		aux = aux->next;
	}
}

#pragma endregion

#pragma endregion

