//
// Created by Hildibjorg on 23.04.2021.
//


#include <stdio.h>
#include <stdbool.h>

void newdeck();

char getValueAsString(int number);

void printdeck();

struct card *findcard(int value, char suit);

int cardtopos(struct card *card);

void movecard(int position, struct card *card);

void setToDeck(int number[]);

struct card { // we create a struct for a double linked list. This struct represents each card in a deck.
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

struct card fdeck[4];

void SW();
//


int main() {
    newdeck();
    SW();
}

//

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

void printdeck() {
    for (int i = 0; i <= 51; i++) {
        printf("index %d: %c%d \n", i, deck[i].suit, deck[i].value);
    }
}
//giver kun de første 6, start med at indsætte c1 til c7, skal der flere i
//hav en counter for
void setToDeck(int number[]) {

    //sæt alle cards[] points til null
    for (int i = 0; i < 6; i++) {
        cards[i] = NULL;
    }

    //sæt alle deck, last og next points til null
    for (int i = 0; i < decksize; i++) {
        deck[i].next = NULL;
        deck[i].last = NULL;
    }


// check if sum of array > 52
    int sum = 0;
    for (int k = 0; k <= 5; k++) {
        sum = sum + number[k];

    }
    if (sum > 52) {
        printf("error");
        return;
    }

//find the 7'th pile:
// 52 - sum(array)
    int cpile[7];

    for (int g = 0; g <= 6; g++) {
        //sets the 7'th pile
        if (g == 6) {
            cpile[g] = (52 - sum);
            break;
        }
        cpile[g] = number[g];
    }

    int linenr = 0;
    int pile = 0;

    for (int i = 0; i < decksize; i++) {
//check if pile has space for a card
// if there is space, then insert card i that pile and continue to next card
//if not then go to the next pile
//use while loop to find next available pile
        while (1) {
            //goes here if there is not space
            if (cpile[pile] == linenr || cpile[pile] < linenr) {
                /*
                printf("\n not space");
                */
                pile = (pile + 1) % 7;
                if (pile == 0) {
                    linenr = (linenr + 1);
                }
            }
                //goes here if there is space
            else {
                movecard(pile, findcard(deck[i].value, deck[i].suit));
                /*
                printf("\n is space ");
                printf("%d%c", deck[i].value, deck[i].suit);
                printf("\t");
                printf("%d",pile);
                 */
                pile = (pile + 1) % 7;
                if (pile == 0) {
                    linenr = (linenr + 1);
                }
                break;
            }
        }
    }
}

void SW() {

    int number[6] = {8, 8, 8, 7, 7, 7};
    setToDeck(number);

    //should check if a card deck is assigned:

    for (int i = 0; i < 4; i++){
        fdeck[i].visible = false;
    }

    for (int i = 0; i < 52; i++){
        deck[i].visible = true;
    }

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

// this takes a position 0 indexed value from 0-6 for C1-C7. this position is where we move the card to. it also takes the card you want to move.
void movecard(int position, struct card *card) {
    //we need to dereference the card and the cards connected to it. We do not have to do anything with the next card because we want to move any next cards with it.
    if (card->last != NULL) {
        card->last->next = NULL;
        card->last = NULL;
    }
    //if the position in the cards array is empty we can just add the car to the cards array as the tail.
    if (cards[position] == NULL) {
        cards[position] = card;
        return;
    }
    //we create a next pointer which is going to be used to travel from the tail to the head of the linked list.
    struct card *next = cards[position];
    while (true) {
        if (next->next == NULL) {//when we reach the head we connect the card to the head as follows.
            next->next = card;
            card->last = next;
            return;
        } else {
            next = next->next;
        }
    }
}

// this method takes a card and then returns the card's position. Meaning it returns 0-6 depending on which list the card is a part of.
int cardtopos(struct card *card) {
    //We can use the double linked list structure to travel in reverse from the card to the tail.
    struct card *prev = card;
    while (true) {
        printf("last = %d%c\n", prev->value, prev->suit);
        if (prev->last == NULL) {
            break;
        }
        prev = prev->last;
    }
    //we use the cards array to check where prev which is the tail is located.
    for (int i = 0; i < 7; i++) {
        if (cards[i] == prev) {
            return i;
        }
    }
}

struct card *findcard(int value, char suit) {
    for (int i = 0; i < decksize; i++) {
        if (deck[i].value == value && deck[i].suit == suit) {
            return &deck[i];
        }
    }
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