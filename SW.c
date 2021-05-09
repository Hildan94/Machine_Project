//
// Created by Hildibjorg on 23.04.2021.
//


#include <stdio.h>
#include <stdbool.h>
void newdeck();
char getValueAsString(int number);
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

struct card deck[52];

void SW();

int main() {
    newdeck();
    SW();

}
int decksize = 0;
void newdeck(){
    // to initialize we first want to create all cards. We'll be storing them in the array deck.
    char suits[] = {'C','D','H','S'};
    decksize =52;
    int k = 0;
    for(int i=0; i<=3; i++){
        for(int j=1; j<=13; j++){
            struct card tempcard;
            tempcard.suit = suits[i];
            tempcard.value = j;
            deck[k]= tempcard;
            k++;
        }
    }
}

void SW(){
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n"
           "\n");

    printf("%c%c",getValueAsString(deck[0].value), deck[0].suit);printf("\t");printf("%c%c",getValueAsString(deck[1].value), deck[1].suit);printf("\t");printf("%c%c",getValueAsString(deck[2].value), deck[2].suit);printf("\t");printf("%c%c",getValueAsString(deck[3].value), deck[3].suit);printf("\t");
    printf("%c%c",getValueAsString(deck[4].value), deck[4].suit);printf("\t");printf("%c%c",getValueAsString(deck[5].value), deck[5].suit);printf("\t");printf("%c%c",getValueAsString(deck[6].value), deck[6].suit);printf("\t\t[]\tC1\n");

    printf("%c%c",getValueAsString(deck[7].value), deck[7].suit);printf("\t");printf("%c%c",getValueAsString(deck[8].value), deck[8].suit);printf("\t");printf("%c%c",getValueAsString(deck[9].value), deck[9].suit);printf("\t");printf("%c%c",getValueAsString(deck[10].value), deck[10].suit);printf("\t");printf("%c%c",getValueAsString(deck[11].value), deck[11].suit);printf("\t");
    printf("%c%c",getValueAsString(deck[13].value), deck[13].suit);printf("\t");printf("%c%c",getValueAsString(deck[14].value), deck[14].suit);printf("\n");

    printf("%c%c",getValueAsString(deck[15].value), deck[15].suit);printf("\t");printf("%c%c",getValueAsString(deck[16].value), deck[16].suit);printf("\t");printf("%c%c",getValueAsString(deck[17].value), deck[17].suit);printf("\t");printf("%c%c",getValueAsString(deck[18].value), deck[18].suit);printf("\t");
    printf("%c%c",getValueAsString(deck[19].value), deck[19].suit);printf("\t");printf("%c%c",getValueAsString(deck[20].value), deck[20].suit);printf("\t");printf("%c%c",getValueAsString(deck[21].value), deck[21].suit);printf("\t\t[]\tC2\n");

    printf("%c%c",getValueAsString(deck[21].value), deck[21].suit);printf("\t");printf("%c%c",getValueAsString(deck[22].value), deck[22].suit);printf("\t");printf("%c%c",getValueAsString(deck[23].value), deck[23].suit);printf("\t");printf("%c%c",getValueAsString(deck[24].value), deck[24].suit);printf("\t");
    printf("%c%c",getValueAsString(deck[25].value), deck[25].suit);printf("\t");printf("%c%c",getValueAsString(deck[26].value), deck[26].suit);printf("\t");printf("%c%c",getValueAsString(deck[27].value), deck[27].suit);printf("\n");


    /*deck[2]"\t"deck[3]"\t"deck[4]"\t"deck[5]"\t"deck[6]"\t\t[]\tF1\n"
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
    );*/
}

char getValueAsString(int number) {
    char result='b';

    switch (number) {
        case 0:
            result = 'A';
            break;
        case 9:
            result = 'T';
            break;
        case 10:
            result = 'J';
            break;
        case 11:
            result = 'D';
            break;
        case 12:
            result = 'K';
            break;
        default:
            result = (number+1)+'0';
            break;
    }

    return result;
}