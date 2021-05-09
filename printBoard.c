//
// Created by Hildibjorg on 23.04.2021.
//


#include <stdio.h>
#include <stdbool.h>

struct card{ // we create a struct for a double linked list. This struct represents each card in a deck.
    struct card *last;
    struct card *next;
    char suit;  // A card has a suit and a value. The suit is kept as a char because we only need to compare and print this value.
    // A char is fine for the comparison because we only need to check if two chars are the same
    int value;  // As supposed to the suit we actually need to compare values with operators like "<" and ">=" meaning it's easier to keep it as an integer.
    bool visible;   // The visible variable will be used to find out which cards we should show at the start of a game.
    // It is not strictly needed but it may make programming easier.
};
struct card *cards[7]; //this repressents the different piles in the game

struct card deck[];

int main() {
    int input;
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n"
           "\n"
           "[]\t[]\t[]\t[]\t[]\t[]\t[]\t\t[]\tF1\n"
           "[]\t[]\t[]\t[]\t[]\t[]\t[]\n"
           "[]\t[]\t[]\t[]\t[]\t[]\t[]\t\t[]\tF2\n"
           "[]\t[]\t[]\t[]\t[]\t[]\t[]\n"
           "[]\t[]\t[]\t[]\t[]\t[]\t[]\t\t[]\tF3\n"
           "[]\t[]\t[]\t[]\t[]\t[]\t[]\n"
           "[]\t[]\t[]\t[]\t[]\t[]\t[]\t\t[]\tF4\n"
           "[]\t[]\t[]\n"
           "\n"
           "LAST Command:\n"
           "Message: \n"
           "INPUT >"
    );
    scanf("%d",&input);
}
