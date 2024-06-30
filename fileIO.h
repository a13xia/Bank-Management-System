#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED
#include <stdio.h>
#include <string.h>

struct account {
    char owner[50];
    char iban[50];
    char coin[10];
    unsigned long int amount;
};

void readFromFile(const char* filePath, int* output);
void writeToFile(const char* filePath, const char* message);

FILE* openFile(const char* filePath, const char* mode);
void findInCSV(const char* filePath, char *full_name, char matrix_of_characters[][3][40], int* length_strings, unsigned long int amount[], int* length_amount);
void writeToCSV(const char* filePath, struct account accounts[], unsigned long int nr_of_accounts);
void deleteFromCSV(const char* filePath, struct account accounts[500], unsigned long int* nr_of_accounts, char *iban);



#endif // FILEIO_H_INCLUDED
