//
// Created by Hildibjorg on 09.05.2021.
//

#include <stdio.h>
#include <stdbool.h>

void newdeck();

struct card { // we create a struct for a double linked list. This struct represents each card in a deck.
    struct card *last;
    struct card *next;
    char suit;  // A card has a suit and a value. The suit is kept as a char because we only need to compare and print this value.
    // A char is fine for the comparison because we only need to check if two chars are the same
    int value;  // As supposed to the suit we actually need to compare values with operators like "<" and ">=" meaning it's easier to keep it as an integer.
    bool visible;   // The visible variable will be used to find out which cards we should show at the start of a game.
    // It is not strictly needed but it may make programming easier.
};
struct card deck[52];

// declare functions:
void LD(char *fileName);


//main:
int main(void) {
    char fileName[100] = "";
    LD(fileName);
}


//functions
int decksize = 0;
void newdeck() {
    // to initialize we first want to create all cards. We'll be storing them in the array deck.
    char suits[] = {'C', 'D', 'H', 'S'};
    decksize = 52;
    int k = 0;
    for (int i = 0; i <= 3; i++) {
        for (int j = 1; j <= 13; j++) {
            struct card tempcard;
            tempcard.suit = suits[i];
            tempcard.value = j;
            tempcard.last = NULL;
            tempcard.next = NULL;
            tempcard.visible = false;
            deck[k] = tempcard;
            k++;
        }
    }
}

void LD(char *fileName) {

    //opens the file of given pathname
    FILE *fptr = fopen(fileName, "r");

    if (fileName[0] == '\0' )
    {
        newdeck();
        return;
    }

    //should have a way
    if (fptr == NULL) {
        printf("File does not exist \n");
        return;
    }

        //start assigning the deck from file
    else {
        char ch;
        char klo;
        int i = 0;
        int count = 1;
        while ((klo = fgetc(fptr)) != EOF) {

            if (klo == '\n') {
                count = 1;
                if (i != 0){
                    deck[i].last = &deck[i-1];
                }
                if (i != 51){
                    deck[i].next = &deck[i+1];
                }
                i++;
                continue;
            }
            count++;
            //printf("%c", klo);
            if (count % 2 == 0) {
                switch (klo) {
                    case 'A':
                        deck[i].value = 1;
                        break;
                    case 'T':
                        deck[i].value = 10;
                        break;
                    case 'D':
                        deck[i].value = 11;
                        break;
                    case 'K':
                        deck[i].value = 12;
                        break;
                    default:
                        deck[i].value = klo - '0';
                }
            } else {
                deck[i].suit = klo;
            }

        }

        fclose(fptr);
    }

//check if all cards are present

  printf("\nOK");
    return;
}