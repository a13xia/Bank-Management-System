#include <stdlib.h>
#include "fileIO.h"
#include "account.h"


//  NEW
//  HERE I ADDED THESE DECLARATIONS GLOBALLY, IN ORDER TO BE ABLE TO USE THE MENUS



unsigned char matrix_of_characters[500][3][40], *name, *surname;
unsigned long int amount[500];
int length_strings, length_amount;


unsigned long int nr_of_accounts;
struct account accounts[500];




//  NEW
// FUNCTIONS WITH ALL THE MENUS


void start_menu(){
    printf("\n\t~ Happy Savings Bank ~\n\n\n");
    printf("  Menu\n\n 1. EDIT ACCOUNT  2. DELETE ACCOUNT  3. CREATE ACCOUNT  4. VIEW ACCOUNT  5. PERFORM TRANSACTIONS\n\n\n");
    printf("   Please choose an option from 1 to 5: ");

}

void edit_menu(unsigned char matrix_of_characters[][3][40], unsigned long int amount[], int length_amount){
    printf("\n  Welcome to the edit section! These are your accounts: \n\n");

            for(int i = 0;i<(length_amount); i++)
            {
                printf(" %d. ", i+1);
                for(int j=0;j<3; j++){
                    printf("%s ", matrix_of_characters[i][j]);
                }
                printf("%d", amount[i]);
                printf("\n");
            }
            printf("\n   Please enter the account number you want to edit: ");
            int account_number;
            scanf("%d", &account_number);
            printf("\n\n      ");
            if(account_number >= 1 && account_number<=length_amount){
                account_number-=1;

                    //printf("    Name\t  IBAN\t\t \t      Coin Amount\n\n    ");

                for(int j=0;j<3; j++){
                    printf("%s ", matrix_of_characters[account_number][j]);
                }
                printf("%d\n\n", amount[account_number]);
                printf("  What would you like to change from this account? (IBAN / Amount / Coin) :  ");
                char change[10];



                scanf("%s", change);
                if(strcmp(change, "IBAN")!=0 && strcmp(change, "Amount")!=0 && strcmp(change, "Coin")!=0){
                    printf("\n  Incorrect option! Try again: ");
                    scanf("%s", change);
                    while(strcmp(change, "IBAN")!=0 && strcmp(change, "Amount")!=0 && strcmp(change, "Coin")!=0){
                        printf("\n  Try again: ");
                        scanf("%s", change);
                    }

                }
                    if(strcmp(change, "IBAN")==0){
                        printf("   Please introduce the new IBAN:  ");
                        char new_iban[50];
                        scanf("%*c"); // Consume newline character from the buffer
                        scanf("%[^\n]%*c", new_iban); // Read input string with spaces


                        // NEW
                        // CHECK IF THE NEW IBAN ALREADY EXISTS

                        if( check_iban("accounts2.csv", new_iban) == 1){
                            printf("\n Sorry, you can't use this IBAN because it already exists!\n Try another one: ");
                            scanf("%[^\n]%*c", new_iban);

                            while(check_iban("accounts2.csv", new_iban) == 1){
                                printf("\n Try again: ");
                                scanf("%[^\n]%*c", new_iban);
                            }

                        }


                        char old_iban[30];
                        strcpy(old_iban, matrix_of_characters[account_number][1]);
                        change_iban("accounts2.csv", accounts, &nr_of_accounts, old_iban, new_iban);
                        writeToCSV("accounts2.csv", accounts, nr_of_accounts);

                        printf("\n  You successfully changed the IBAN!");

                    }
                    if(strcmp(change, "Amount")==0){
                        printf("   Please introduce the new Amount:  ");
                        long int new_amount;
                        scanf("%d", &new_amount);
                        if(new_amount < 0){
                            printf("\n   The amount must be a positive number!");
                            scanf("%d", &new_amount);
                            while(new_amount < 0){
                                printf("\n  This is still negative. Try again: ");
                                scanf("%d", &new_amount);
                            }
                        }
                            char iban[30];
                            strcpy(iban, matrix_of_characters[account_number][1]);
                            change_amount("accounts2.csv", accounts, &nr_of_accounts, iban, new_amount);
                            writeToCSV("accounts2.csv", accounts, nr_of_accounts);

                            printf("\n  You successfully changed the Amount!");


                    }
                    if(strcmp(change, "Coin")==0){
                        printf("   Please introduce the new Coin (RON/EUR/USD) :  ");
                        char new_coin[10];
                        scanf("%s", new_coin);

                        if(strcmp(new_coin, "RON")!= 0 && strcmp(new_coin, "EUR")!= 0 && strcmp(new_coin, "USD")!= 0){
                            printf("\n  The coin you introduced is not valid. Try again: ");
                            scanf("%s", new_coin);
                            while(strcmp(new_coin, "RON")!= 0 && strcmp(new_coin, "EUR")!= 0 && strcmp(new_coin, "USD")!= 0){
                                printf("  This is not a valid coin, try again: ");
                                scanf("%s", new_coin);
                            }
                        }
                            char iban[30];
                            strcpy(iban, matrix_of_characters[account_number][1]);
                            change_coin("accounts2.csv", accounts, &nr_of_accounts, iban, new_coin);
                            writeToCSV("accounts2.csv", accounts, nr_of_accounts);
                            printf("\n  You successfully changed the Coin!");

                    }
            }
            else{
//  NEW
// I added this possibility to go back to the edit menu and insert a correct acc nr this time

                system("CLS");
                printf("\n  Sorry, this is an invalid account number!\n");
                edit_menu(matrix_of_characters, amount, length_amount);
            }
}

void delete_menu(unsigned char matrix_of_characters[][3][40], unsigned long int amount[], int length_amount){

    printf("\n  Welcome to the delete section! These are your accounts: \n\n");

            for(int i = 0;i<(length_amount); i++)
            {
                printf(" %d. ", i+1);
                for(int j=0;j<3; j++){
                    printf("%s ", matrix_of_characters[i][j]);
                }
                printf("%d", amount[i]);
                printf("\n");
            }
            printf("\n   Please enter the account number you want to delete: ");

            int account_number;
            scanf("%d", &account_number);

            if(account_number >= 1 && account_number<=length_amount){
                    account_number-=1;

                    printf("\n    Name\t  IBAN\t\t\t       Coin Amount\n\n    ");

                for(int j=0;j<3; j++){
                    printf("%s ", matrix_of_characters[account_number][j]);
                }
                printf("%d\n\n", amount[account_number]);

                char iban[30];
                strcpy(iban, matrix_of_characters[account_number][1]);
                deleteFromCSV("accounts2.csv", accounts, &nr_of_accounts, iban);
                writeToCSV("accounts2.csv", accounts, nr_of_accounts);


                printf("This account is now deleted!");
            }
            else{
//  NEW
// I added this possibility to go back to the delete menu and insert a correct acc nr this time

                    system("CLS");
                    printf("\n  Sorry, this is an invalid account number!\n");
                    delete_menu(matrix_of_characters, amount, length_amount);
            }

}

void create_menu(){

    printf("\n  Welcome to the create section! \n\n  Please enter the necessary info to open an account: \n\n");
    printf("  Name and surname: ");
    char FULLNAME[50];
    scanf("%*c");
    scanf("%[^\n]%*c", FULLNAME);

    printf("\n");
    printf("  IBAN: ");
    char IBAN[30];
    scanf("%[^\n]%*c", IBAN);

            // NEW
            // CHECK IF THE IBAN ALREADY EXISTS


    if( check_iban("accounts2.csv", IBAN) == 1){
        printf("\n Sorry, you can't use this IBAN because it already exists!\n Try another one: ");
        scanf("%[^\n]%*c", IBAN);

        while(check_iban("accounts2.csv", IBAN) == 1){
            printf("\n Try again: ");
            scanf("%[^\n]%*c", IBAN);
        }

    }


    printf("\n");
    printf("  Coin (RON/EUR/USD): ");
    char COIN[10];
    scanf("%s", COIN);
    if(strcmp(COIN, "RON")!= 0 && strcmp(COIN, "EUR")!= 0 && strcmp(COIN, "USD")!= 0){
        printf("  This is not a valid coin, try again: ");
        scanf("%s", COIN);
        while(strcmp(COIN, "RON")!= 0 && strcmp(COIN, "EUR")!= 0 && strcmp(COIN, "USD")!= 0){
            printf("  This is not a valid coin, try again: ");
            scanf("%s", COIN);
        }
    }

        printf("\n");
        printf("  Amount: ");
        long int AMOUNT;
        scanf("%d", &AMOUNT);
        if(AMOUNT<0){
            printf("\n  You need to introduce a positive number here!");
            scanf("%d", &AMOUNT);
            while(AMOUNT < 0){
                printf("\n  This is still negative. Try again: ");
                scanf("%d", &AMOUNT);
            }
        }
            createAccount("accounts2.csv", accounts, &nr_of_accounts, FULLNAME, IBAN, COIN, AMOUNT);
            writeToCSV("accounts2.csv", accounts, nr_of_accounts);
            printf("\n  You successfully created a new account:\n\n");
            printf("    Name: %s\t   IBAN: %s\t     Coin: %s    Amount: %d\n\n", FULLNAME, IBAN, COIN, AMOUNT);





}

void view_menu(unsigned char matrix_of_characters[][3][40], unsigned long int amount[], int length_amount){
    printf("\nWelcome to the view section! These are your accounts: \n\n");
    printf("    Name\t  IBAN\t\t\t       Coin Amount\n\n");

    for(int i = 0;i<(length_amount); i++)
    {
        printf(" %d. ", i+1);
        for(int j=0;j<3; j++){
            printf("%s ", matrix_of_characters[i][j]);
        }
        printf("%d", amount[i]);
        printf("\n");
    }
}

void transaction_menu(unsigned char matrix_of_characters[][3][40], unsigned long int amount[], int length_amount){

            printf("\n  Welcome to the transactions section!  ");
            printf("\n   These are your accounts: \n\n");
            printf("    Name\t  IBAN\t\t\t       Coin Amount\n\n");

                for(int i = 0;i<(length_amount); i++)
                {
                    printf(" %d. ", i+1);
                    for(int j=0;j<3; j++){
                        printf("%s ", matrix_of_characters[i][j]);
                }
                printf("%d", amount[i]);
                printf("\n");
            }

            printf("\n\n   In order to make a transaction, you need to introduce both the the Source IBAN and the Destination IBAN.\n");


            char source_iban[30], destination_iban[30];
            long int am;

            printf("Please enter your Source IBAN: ");
            scanf("%*c");
            scanf("%[^\n]%*c", source_iban);

            printf("\nPlease enter the Destination IBAN: ");
            scanf("%[^\n]%*c", destination_iban);

            printf("\nPlease enter the amount you want to transfer: ");
            scanf("%d", &am);

            if(amount < 0){
                printf("  You need to introduce a positive number of money! ");
            }
            else if(strcmp(source_iban, destination_iban) == 0)
                printf("  The IBANs need to be different!");
            else{
                makeTransaction("accounts2.csv", accounts, &nr_of_accounts, source_iban, destination_iban, am);
                writeToCSV("accounts2.csv", accounts, nr_of_accounts);
                printf("   You successfully sent the money!");
            }

}






int main(int argc, char *argv[])
{

    if(strcmp(argv[1], "login") == 0 && argv[2]  && argv[3]){

        name = argv[2];
        surname = argv[3];

        char full_name[strlen(name) + strlen(surname) + 1];
        strcpy(full_name, name);
        strcat(full_name, " ");
        strcat(full_name, surname);

//  NEW
//  menu added

        start_menu();
        int option;
        scanf("%d", &option);
        if(option>=1 && option<=5){

        if(option == 1){

            findInCSV("accounts2.csv", &full_name, matrix_of_characters, &length_strings, amount, &length_amount);

            if(length_amount == 0){

//  NEW
// I added this possibility to go back to the main and perform other operations

                system("CLS");
                printf("\n   We are sorry, but you don't have an account...Maybe you would like to create one first!\n");
                main(argc, argv);
            }
            else{
//  NEW
//   menu added

                edit_menu(matrix_of_characters, amount, length_amount);
            }

        }

        else if(option == 2){

            findInCSV("accounts2.csv", &full_name, matrix_of_characters, &length_strings, amount, &length_amount);

            if(length_amount == 0){

//  NEW
//  I added this possibility to go back to the main again to do other operations

                system("CLS");
                printf("\n   We are sorry, but you don't have an account...Maybe you would like to create one first!\n");
                main(argc, argv);
            }
            else{

//  NEW
//  menu added
                delete_menu(matrix_of_characters, amount, length_amount);
            }
        }


        else if(option == 3){

//  NEW
//  menu added
            findInCSV("accounts2.csv", &full_name, matrix_of_characters, &length_strings, amount, &length_amount);
            create_menu();

        }


        else if(option == 4){

            findInCSV("accounts2.csv", &full_name, matrix_of_characters, &length_strings, amount, &length_amount);

            if(length_amount == 0){
//  NEW
//  I added this possibility to go back to the main again to do other operations

                system("CLS");
                printf("\n   We are sorry, but you don't have an account...Maybe you would like to create one first!\n");
                main(argc, argv);
            }

            else{
//  NEW
//  menu added
                view_menu(matrix_of_characters, amount, length_amount);
            }
        }


        else if(option == 5){

            findInCSV("accounts2.csv", &full_name, matrix_of_characters, &length_strings, amount, &length_amount);

            if(length_amount == 0){
//  NEW
// I added this possibility to go back to the main and perform other operations
                system("CLS");
                printf("\n   We are sorry, but you can't perform any transaction because you don't have an account......Maybe you would like to create one first!\n");
                main(argc, argv);
            }
            else
                transaction_menu(matrix_of_characters, amount, length_amount);
    }
        }
        else{

//  NEW
// I added this possibility to go back to the main and perform other operations

            system("CLS");
            printf("\n  You introduced an invalid option!\n");
            main(argc, argv);
        }
}
        else
            printf("To perform any action related to your bank account, please log in first! Write 'login ', your name and then your surname.");

        printf("\n");


    return 0;
}
