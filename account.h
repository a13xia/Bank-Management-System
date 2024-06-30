#ifndef ACCOUNT_H_INCLUDED
#define ACCOUNT_H_INCLUDED
#include "fileIO.h"
#include <stdio.h>
#include <string.h>


int validate_iban(const char* filePath, struct account accounts[500], unsigned long int* nr_of_accounts, char *iban);
void change_iban(const char* filePath, struct account accounts[500], unsigned long int* nr_of_accounts, char *old_iban, char *new_iban);
void change_coin(const char* filePath, struct account accounts[500], unsigned long int* nr_of_accounts, char *iban, char *new_coin);
void change_amount(const char* filePath, struct account accounts[500], unsigned long int* nr_of_accounts, char *iban, unsigned long int new_amount);

void createAccount(const char* filePath, struct account accounts[500], unsigned long int* nr_of_accounts, char* FULLNAME, char* IBAN, char* COIN,  long int AMOUNT);
void makeTransaction(const char* filePath, struct account accounts[500], unsigned long int* nr_of_accounts, char* source_iban, char* destination_iban, long int amount);


// NEW FUNCTION

int check_iban(const char* filePath, char* iban);


#endif // ACCOUNT_H_INCLUDED
