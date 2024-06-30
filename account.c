#include "account.h"


int validate_iban(const char* filePath, struct account accounts[500], unsigned long int* nr_of_accounts, char *iban)
{
    FILE* file = fopen(filePath, "r");

    if (file == NULL)
        return;

    long int i = 0;

    char header[200];
    char data[200];

    char* col_data;
    fgets(header, 200, file);

    while (fgets(data, 200, file) != NULL) {
        col_data = strtok(data, ",");

        int j = 0;
        while (col_data != NULL) {
            if (j == 0)
                strcpy(accounts[i].owner, col_data);
            else if (j == 1) {
                if (strcmp(col_data, iban) == 0)
                    return 1;
                else
                    strcpy(accounts[i].iban, col_data);
            } else if (j == 2)
                strcpy(accounts[i].coin, col_data);
            else
                accounts[i].amount = atoi(col_data);

            j++;
            col_data = strtok(NULL, ",");
        }
        i++;
    }

    *nr_of_accounts = i;

    fclose(file);
    return 0;
}

void change_iban(const char* filePath, struct account accounts[500], unsigned long int* nr_of_accounts, char *old_iban, char *new_iban) {
    FILE* file = fopen(filePath, "r");

    if (file == NULL)
        return;

    long int i = 0;

    char header[200];
    char data[200];

    char* col_data;
    fgets(header, 200, file);

    while (fgets(data, 200, file) != NULL) {
        col_data = strtok(data, ",");

        int j = 0;
        while (col_data != NULL) {
            if (j == 0)
                strcpy(accounts[i].owner, col_data);
            else if (j == 1) {
                if (strcmp(col_data, old_iban) == 0)
                    strcpy(accounts[i].iban, new_iban);
                else
                    strcpy(accounts[i].iban, col_data);
            } else if (j == 2)
                strcpy(accounts[i].coin, col_data);
            else
                accounts[i].amount = atoi(col_data);

            j++;
            col_data = strtok(NULL, ",");
        }
        i++;
    }

    *nr_of_accounts = i;

    fclose(file);
}


void change_coin(const char* filePath, struct account accounts[500], unsigned long int* nr_of_accounts, char *iban, char *new_coin)
 {
    FILE* file = fopen(filePath, "r");

    if (file == NULL)
        return;

    unsigned long int i = 0;

    char header[200];
    char data[200];

    char* col_data;
    fgets(header, 200, file);
    int ok = 0;

    while (fgets(data, 200, file) != NULL) {
        col_data = strtok(data, ",");

        int j = 0;
        while (col_data != NULL) {
            if (j == 0)
                strcpy(accounts[i].owner, col_data);
            else if (j == 1) {
                if (strcmp(col_data, iban) == 0)
                    ok = 1;
                strcpy(accounts[i].iban, col_data);

            } else if (j == 2){
                if(ok == 1){
                    ok = 0;
                    strcpy(accounts[i].coin, new_coin);
                }
                else
                    strcpy(accounts[i].coin, col_data);
            }
            else
                accounts[i].amount = atoi(col_data);

            j++;
            col_data = strtok(NULL, ",");
        }

        i++;
    }

    *nr_of_accounts = i;

    fclose(file);
}



void change_amount(const char* filePath, struct account accounts[500], unsigned long int* nr_of_accounts, char *iban, unsigned long int new_amount)
 {
    FILE* file = fopen(filePath, "r");

    if (file == NULL)
        return;

    unsigned long int i = 0;

    char header[200];
    char data[200];

    char* col_data;
    fgets(header, 200, file);
    int ok = 0;

    while (fgets(data, 200, file) != NULL) {
        col_data = strtok(data, ",");

        int j = 0;
        while (col_data != NULL) {
            if (j == 0)
                strcpy(accounts[i].owner, col_data);
            else if (j == 1) {
                if (strcmp(col_data, iban) == 0)
                    ok = 1;
                strcpy(accounts[i].iban, col_data);

            } else if (j == 2){
                    strcpy(accounts[i].coin, col_data);
            }
            else{
                if(ok == 1){
                    ok = 0;
                    accounts[i].amount = new_amount;
                }
                else
                    accounts[i].amount = atoi(col_data);
            }


            j++;
            col_data = strtok(NULL, ",");
        }

        i++;
    }

    *nr_of_accounts = i;

    fclose(file);
}



void createAccount(const char* filePath, struct account accounts[500], unsigned long int* nr_of_accounts, char* FULLNAME, char* IBAN, char* COIN,  long int AMOUNT){
    FILE* file = fopen(filePath, "r");

    if (file == NULL)
        return;

    unsigned long int i = 0;

    char header[200];
    char data[200];

    char* col_data;
    fgets(header, 200, file);

    while (fgets(data, 200, file) != NULL) {
        col_data = strtok(data, ",");

        int j = 0;
        while (col_data != NULL) {
            if (j == 0)
                strcpy(accounts[i].owner, col_data);
            else if (j == 1) {
                strcpy(accounts[i].iban, col_data);

            } else if (j == 2){
                    strcpy(accounts[i].coin, col_data);
            }
            else{
                    accounts[i].amount = atoi(col_data);
            }

            j++;
            col_data = strtok(NULL, ",");
        }

        i++;
    }

    strcpy(accounts[i].owner, FULLNAME);
    strcpy(accounts[i].iban, IBAN);
    strcpy(accounts[i].coin, COIN);
    accounts[i].amount = AMOUNT;

    i++;

    *nr_of_accounts = i;

    fclose(file);
}


void makeTransaction(const char* filePath, struct account accounts[500], unsigned long int* nr_of_accounts, char* source_iban, char* destination_iban, long int amount)
{
    FILE* file = fopen(filePath, "r");

    if (file == NULL)
        return;

    unsigned long int i = 0;

    char header[200];
    char data[200];

    char* col_data;
    fgets(header, 200, file);
    int ok=0;

    while (fgets(data, 200, file) != NULL) {
        col_data = strtok(data, ",");

        int j = 0;
        while (col_data != NULL) {
            if (j == 0)
                strcpy(accounts[i].owner, col_data);
            else if (j == 1) {
                    if (strcmp(col_data, source_iban) == 0){
                        ok = 1;

                    }

                    else if(strcmp(col_data, destination_iban) == 0)
                    {
                        ok = 2;
                    }

                strcpy(accounts[i].iban, col_data);

            }
            else if (j == 2){
                    strcpy(accounts[i].coin, col_data);
            }
            else{
                    if(ok == 1){
                        accounts[i].amount = atoi(col_data);
                        if(accounts[i].amount - amount <0)
                            accounts[i].amount= 0;
                        else
                            accounts[i].amount -= amount;
                        ok = 0;
                    }
                    else if(ok ==2){
                        accounts[i].amount = atoi(col_data);
                        accounts[i].amount += amount;

                        ok = 0;
                    }
                    else{

                        accounts[i].amount = atoi(col_data);
                    }



            }

            j++;
            col_data = strtok(NULL, ",");
        }

        i++;
    }


    *nr_of_accounts = i;

    fclose(file);
}




    // NEW
    // CHECK IF THE IBAN ALREADY EXISTS, WHEN CREATING AN ACCOUNT


int check_iban(const char* filePath, char* iban){


    FILE* file = fopen(filePath, "r");

    if (file == NULL)
        return;


    char header[200];
    char data[200];

    char* col_data;
    fgets(header, 200, file);

    while (fgets(data, 200, file) != NULL) {
        col_data = strtok(data, ",");

        int j = 0;
        while (col_data != NULL) {
            if (j == 1) {    // Because the IBAN is on the second column

                if (strcmp(col_data, iban) == 0){
                    fclose(file);
                    return 1;
                }
            }

            j++;
            col_data = strtok(NULL, ",");
        }
    }

    fclose(file);
    return 0;

}

