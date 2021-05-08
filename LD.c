//
// Created by Hildibjorg on 23.04.2021.
//

#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

// Defined variables:
#define SIZE 20

 // Function declarations

 //
 bool LD();




int main() {

    LD();


}

bool LD (){
    FILE *infile;
    char input[100] = "";

    printf("Enter a file name:\n");
    // Test path: C:\\Users\\Hildibjorg\\Desktop\\Deck.txt

    //scans and saves the given filepath
    scanf("%s",&input);

    //opens and reads the file
    infile = fopen(input, "r");

    //if no filepath is given assign the standard deck
    if(&infile == NULL){
        //find ud af hvordan man assigner decket
        //*infile = *deck;
    }

    //if given filepath is wrong/not assigned assign the standard deck pile and display OK to console
    if(infile == NULL){
        printf("Error in opening file");
    }


    // check if all cards are present in the deck




    // prints the content of the given file:
    /*
    while(1) {
        c = fgetc(infile);
        if(feof(infile)){
            break;
        }
        printf("%c",c);
    }
*/

    fclose(infile);
    printf("OK");
    return(0);
}