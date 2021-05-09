//
// Created by Hildibjorg on 09.05.2021.
//

#include <stdio.h>
#include <stdbool.h>

struct temp{
    char card[52];
};

struct temp cur_card[52];

// declare functions:
bool LD(char *fileName);


//main:
int main (void) {
    char fileName[100] = "C:\\\\Users\\\\Hildibjorg\\\\Desktop\\\\Deck.txt";
    LD(fileName);
}


//functions

bool LD (char *fileName){
    //Currently sets the path from user input but should be changed to given string
    /*
    printf(" Input the filename to be opened : ");
    scanf("%s", fileName);
    */

    //opens the file of given pathname
    FILE *fptr = fopen(fileName, "r");

    //If the file is not found print error
    if (fptr == NULL) {
        printf("Error when opening the file \n");
        return 1;

    }

    //should have a way
    if (fptr == NULL) {
        printf("File does not exist \n");
        return 1;

    }

    //start assigning the deck from file
    else {
        char ch;
        int count = 0;

        do {
            ch = fgetc(fptr);
            if (ch == '\n') count++;
        } while (ch != EOF);

        rewind(fptr);

        int temp;
        fscanf(fptr, "%d", &temp);

        //store the lines from the file in given struct:
        for (int i = 0; i <= count; i++){
            fscanf(fptr,"%s\n", cur_card[i].card);
            //printf("%s\n", cur_card[i].card);
        }

        //There should be a check on whether or not the contents of the file
        //are okay!

        fclose(fptr);
    }
//print out all of the content of the struct:
/*
    for (int i = 0; i < 52; i++){
        printf("%s\n", cur_card[i].card);
    }
  */
    //if the file is read and stored display OK:
    printf("OK");
    return 0;
}