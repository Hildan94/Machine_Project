//
// Created by Hildibjorg on 23.04.2021.
//


#include <stdio.h>

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

void SW();

int main() {

    SW();

}
void SW(){
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n"
           "\n"
    deck[0]"\t"deck[1]"\t"deck[2]"\t"deck[3]"\t"deck[4]"\t"deck[5]"\t"deck[6]"\t\t[]\tF1\n"
    deck[7]"\t"deck[8]"\t"deck[9]"\t"deck[10]"\t"deck[11]"\t"deck[12]"\t"deck[13]"\n"
    deck[14]"\t"deck[15]"\t"deck[16]"\t"deck[17]"\t"deck[18]"\t"deck[19]"\t"deck[20]"\t\t[]\tF2\n"
    deck[21]"\t"deck[22]"\t"deck[23]"\t"deck[24]"\t"deck[25]"\t"deck[26]"\t"deck[27]"\n"
    deck[28]"\t"deck[29]"\t"deck[30]"\t"deck[31]"\t"deck[32]"\t"deck[33]"\t"deck[34]"\t\t[]\tF3\n"
    deck[35]"\t"deck[36]"\t"deck[37]"\t"deck[38]"\t"deck[39]"\t"deck[40]"\t"deck[41]"\n"
    deck[42]"\t"deck[43]"\t"deck[44]"\t"deck[45]"\t"deck[46]"\t"deck[47]"\t"deck[48]"\t\t[]\tF4\n"
    deck[49]"\t"deck[50]"\t"deck[51]"\n"
                                    "\n"
                                    "LAST Command:\n"
                                    "Message: \n"
                                    "INPUT >"
    );
}