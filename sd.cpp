//
// Created by Gülsen on 10-05-2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void sd();
char getValueAsString(int number);
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

int main() {


    newdeck();
    sd();

    return 0;
}
int decksize = 0;

void sd() {
    char cardsString[157];

    char *fileName = "cards.txt"; //pathname

    //Saves the deck as a string[] consisting of value + suit + newline
    int count = 0;
    for (int i = 0; i < 155; i++) {
        if (i % 3 == 0) {
            cardsString[i] = getValueAsString(deck[count].value);
        } else if (i % 3 == 1) {
            cardsString[i] = deck[count].suit;
            count++;
        } else {
            cardsString[i] = '\n';
        }


    }

    cardsString[155] = 0; //Nullpointer so it isn't displayed in cards.txt
    FILE *fptr;
    fptr = fopen(fileName, "w");
    if (fptr == NULL) {
        printf("File doesn't exist");
    }
    fprintf(fptr, "%s", cardsString);
    fclose(fptr);

}

char getValueAsString(int number) {
    char result = 'b';

    switch (number) {
        case 1:
            result = 'A';
            break;
        case 10:
            result = 'T';
            break;
        case 11:
            result = 'J';
            break;
        case 12:
            result = 'D';
            break;
        case 13:
            result = 'K';
            break;
        default:
            result = (number) + '0';
            break;
    }

    return result;
}

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

