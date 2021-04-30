//
// Created by Gülsen on 30-04-2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static char input[50];

//Declared functions
int QQ();

int main() {
    //Used to read the input
    if(fgets(input, 50, stdin) == NULL){
        return 0;
    }
    //puts(input);

    //Sets the last index to 0 in order to compare strings properly
    if(input[strlen(input)-1] == '\n') {
        input[strlen(input)-1] = 0;
    }

    //Commands with only two characters
    if(strcmp(input, "SW") == 0) {
        printf("SW\n");
    }
    if (strcmp(input, "LD") == 0) {
        printf("LD\n");
    }
    if(strcmp(input, "SI") == 0) {
        printf("SI\n");
    }
    if(strcmp(input, "SR") == 0) {
        printf("SR\n");
    }
    if(strcmp(input, "SD") == 0) {
        printf("SD\n");
    }
    if(strcmp(input, "QQ") == 0) {
        QQ();
    }
    if(strcmp(input, "P") == 0) {
        printf("P\n");
    }
    if(strcmp(input, "Q") == 0) {
        printf("Q\n");
    }

    //Command "LD <filename>" where filename is specified (aka. not empty)
    if(input[0] == 'L' && input[1] == 'D' && input[2] == ' '
       && strlen(input) > 4){
        printf("LD filename\n");
    }

    //SI <split> where split is specified
    if(input[0] == 'S' && input[1] == 'I' && input[2] == ' '
       && strlen(input) > 4){
        printf("SI split\n");
    }

    //SD <filename> where filename is specified
    if(input[0] == 'S' && input[1] == 'D' && input[2] == ' '
       && strlen(input) > 4){
        printf("SD filename\n");
    }

    //Missing Game moves

    return 0;
}

int QQ() {
    printf("Are you sure you want to quit the game? (Y/N)\n");

    //Used to read the input
    if(fgets(input, 50, stdin) == NULL){
        return 0;
    }


    //Sets the last index to 0 in order to compare strings properly
    if(input[strlen(input)-1] == '\n') {
        input[strlen(input)-1] = 0;
    }

    //Calls function again if the input is neither 'Y' or 'N'
    if(strcmp(input, "Y") == 0) {
        printf("Y\n");
        exit(0);
    } else if (strcmp(input, "N") == 0) {
        printf("N\n");
        //Should refer to input for commands again
    } else {
        QQ();
    }

}


