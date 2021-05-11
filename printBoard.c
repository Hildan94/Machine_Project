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

}
void printboard(){
int cpile[7] = {8,8,8,7,7,7,7};

printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n"
"\n");
int linenr = 0;
int pile = 0;
int fcount = 1;

for (int i = 0; i < decksize; i++) {
while (1) {
//goes here there should not be a card
if (cpile[pile] == linenr || cpile[pile] < linenr) {
printf("\t");
pile = (pile + 1) % 7;
if (pile == 0 ) {
//check whether F-pile should be printed which is at the end of line 0, 2, 4 and 6
if (linenr % 2 == 0){
printf("\t\t");

//check if card is set to being visible or not
if(!deck[i].visible){
printf("[]\t");
printf("%c%d" ,'F',fcount);
fcount++;
}
else{
printf("[]\t");
printf("\t");
printf("%c%d" ,'F',fcount);
fcount++;
}
}
//reached end of line so print new line
printf("\n");
linenr = (linenr + 1);
}
}
//goes here if there is space
else {
if(!deck[i].visible){
printf("[]\t");
}
else{
printf("%c%c",getValueAsString(deck[i].value),deck[i].suit);
printf("\t");
}
pile = (pile + 1) % 7;
if (pile == 0) {
//check whether F-pile should be printed which is at the end of line 0, 2, 4 and 6
if (linenr % 2 == 0){

//check if card is set to being visible or not
printf("\t\t");
if(!deck[i].visible){
printf("[]\t");
printf("%c%d" ,'F',fcount);
printf("\t");
fcount++;
}
else{
printf("[]\t");
printf("\t");
printf("%c%d" ,'F',fcount);
fcount++;
}
}
//reached end of line so print new line
printf("\n");
linenr = (linenr + 1);
}
break;
}
}
}
printf("\n\n"
"LAST Command: LD\n"
"Message: OK\n"
"INPUT >");

}

}

