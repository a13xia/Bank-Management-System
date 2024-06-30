#include "fileIO.h"


void deleteFromCSV(const char* filePath, struct account accounts[500], unsigned long int* nr_of_accounts, char *iban)
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
                    accounts[i].amount = atoi(col_data);
            }

            if( j == 3 && ok == 1){
                ok = 0;
                i--;
            }
            j++;
            col_data = strtok(NULL, ",");
        }

        i++;
    }

    *nr_of_accounts = i;

    fclose(file);
}



void readFromFile(const char* filePath, int* output)
{
	FILE* file = openFile(filePath, "r");

	if (file == NULL)
		return;

	fscanf_s(file, "%d", output);
	fclose(file);
}



void findInCSV(const char* filePath, char* full_name, char matrix_of_characters[][3][40], int* length_strings, unsigned long int amount[], int* length_amount){
    FILE* file = openFile(filePath, "r");



	if (file == NULL)
		return;

    char header[200];
	char data[200];

	char* col_data;
	int line_index_strings = 0, col_index_strings, line_index_amount=0;

	fgets(header, 200, file);


	// For MSVC Compiler: fopen_s / fscanf_s / strtok_s ( ..., &next_col);
	// For GCC Compiler (Code::Blocks / etc): fopen / fscanf / strtok ( ... );

	while (!feof(file))
	{

		fgets(data, 200, file);
		col_data = strtok(data, ",");

		col_index_strings = 0;
		if(strcmp(col_data, full_name) == 0)
        {
            while (col_data != NULL)
            {

                if(col_index_strings == 3){

                    amount[line_index_amount] = atoi(col_data);
                    line_index_amount++;
                }
                else{

                    strcpy(matrix_of_characters[line_index_strings][col_index_strings], col_data);
                    col_index_strings++;
                }

                col_data = strtok(NULL, ",");
            }
            line_index_strings++;

        }

	}

	// printf("\nprima valoare a lui amount este: %d", amount[0]);

	*length_amount = line_index_amount;
	*length_strings =  line_index_strings;


/*
    for(int i = 0;i<(line_index_strings-1); i++)
            {
                for(int j=0;j<3; j++){
                    printf("%s ", strings[i][j]);
                }
            }
            printf("\n");
            for(int i = 0;i<(line_index_amount-1); i++){
                printf("%s ", amount[i]);
            }
*/

	fclose(file);
}


void writeToCSV(const char* filePath, struct account accounts[], unsigned long int nr_of_accounts)
{

	FILE* file = openFile(filePath, "w");

	if (file == NULL)
		return;

    fprintf(file, "%s\n", "Name,IBAN,Coin,Amount");

    for(int i=0;i<nr_of_accounts;i++)
        fprintf(file, "%s,%s,%s,%d\n", accounts[i].owner, accounts[i].iban, accounts[i].coin, accounts[i].amount);
	fclose(file);
}

void writeToFile(const char* filePath, const char* message)
{

	if (message == NULL || strlen(message) == 0)
		return;

	FILE* file = openFile(filePath, "w");

	if (file == NULL)
		return;

	fprintf(file, "%s", message);
	fclose(file);
}

FILE* openFile(const char* filePath, const char* mode)
{
	// IF GUARD
	if (filePath == NULL || strlen(filePath) == 0 ||
		mode == NULL || strlen(mode) == 0)
		return NULL;

	FILE* file = NULL;

	fopen_s(&file, filePath, mode);

	return file;
}



