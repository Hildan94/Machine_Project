#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN(a,b) (((a)<(b)) ? (a) : (b))
void newdeck();
void printdeck();
struct card * findcard(int value, char suit);
int cardtopos(struct card *card); 
void si(int *split);
void sr();
void movecard(int position, struct card *card);
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
int main(int argc, char *argv[]){
    
    newdeck();
    printdeck();
    int a = 26;
    int *split = &a;
    struct card *card = &deck[3];
    movecard(2,card);
    printf("%d%c\n",cards[2]->value, cards[2]->suit);
    card = & deck[1];
    movecard(2,card);
    printf("%d%c\n",cards[2]->value, cards[2]->suit);
    printf("%d%c\n",cards[2]->next->value, cards[2]->next->suit);
    printf("pos = %d\n",cardtopos(findcard(2,C)));
    //sr();//si(split);
    //printdeck();
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
void printdeck(){
    for(int i = 0 ; i <= 51; i++){
        printf("index %d: %c%d \n", i, deck[i].suit, deck[i].value);
    }
}

                    // This function is supposed to mix the card. It takes a pointer to an integer as an input. 
                    // Because this is a pointer it's possible to input a NULL pointer to the function.
                    // If the input is NULL this function will randomly select a valid value for split.

void si(int *split){
    //printf("%d \n", decksize);
    if (split == NULL){// first we check if split is NULL, in which case we select a value for split.
        time_t t;
        srand((unsigned) time(&t));
        int a = (rand()%(decksize-1)) +1; //we want numbers from 1 to decksize.
        split = &a;
        printf("split was not specified, random split %d was chosen\n", *split);
    }
    //printf("%d %d \n", decksize, *split);
    if(*split > decksize || *split <=0){// if the split is either larger than the size of the deck, or smaller than or equal to null we return an error.
        printf("split size error \n");
        return;
    }// now we shuffle the cards into the shuffled pile.
    struct card shuffled[decksize];
    int nextcard = 1;   // next card is used to find the next card in both splits.
    int min = MIN(*split, decksize-*split); //We use min here because by computing this it makes it possible to split the deck without actually creating another array.
                                            // min denotes how far we have to travel down the two splits until there are no more cards in one of them.
    for (int i = decksize-min*2; i<52; i=i+2){ // we use i to find the position we want to shuffle a card to, and we do two cards each loop.
        shuffled[i]=deck[decksize-*split-nextcard]; //The first split starts from the card split down from the top of the deck.
        shuffled[i+1]=deck[decksize-nextcard]; // The second card is chosen from the top of the deck. 
        nextcard++;
    }// when there are no more cards in one of the splits we have to insert the rest of the cards at the bottom of the shuffled pile.
    if(*split<=decksize/2){// The method is different depending on which split has cards left.
        for (int j = 0; j<=decksize-1-min*2;j++){
            shuffled[j]= deck[j];
        }
    }
    else{
        nextcard = 0;
        printf(" min %d decksize-min %d\n",min, decksize-min);
        for (int j = min; j<=decksize-min-1;j++){
            shuffled[nextcard]= deck[j];
            nextcard++;
        }
    }//lastly we have to make the shuffled deck our new deck, we do this by overwriting the deck with the values of the shuffled deck.
    for(int h = 0; h<decksize; h++){
        deck[h] = shuffled[h];
    }
}

void sr(){
    //first we create the shuffled pile. We also initialize our seed for the rand command.
    struct card shuffled[decksize];
    time_t t;
    srand((unsigned) time(&t));
    int randpos;
    //We will now go through each card in the deck and place it in a random position of the shuffled deck.
    for(int j = 0; j<52; j++){
        shuffled[j].suit=NULL;
    }
    for(int i = 0; i<52; i++){
        while(true){ // because we are doing random positions we have no way of knowing whether a random position chosen has alreade been taken.
                     // This means we'll have to continue choosing new positions until we find an available space.
            randpos =(rand()%(decksize));
            if(shuffled[randpos].suit==NULL){ // we check suit because the array doesn't contain pointers, so the best way to check whether it has been taken is by checking the values.
                shuffled[randpos]=deck[i];
                break;
            }
        }
    }// now that we have finished the shuffled pile we want to replace the deck with the new shuffled deck.
    for(int h = 0; h<decksize; h++){
        deck[h] = shuffled[h];
    }
}
// this takes a position 0 indexed value from 0-6 for C1-C7. this position is where we move the card to. it also takes the card you want to move. 
void movecard(int position, struct card *card){
    //we need to dereference the card and the cards connected to it. We do not have to do anything with the next card because we want to move any next cards with it.
    if(card->last!=NULL){
        card->last->next =NULL;
        card->last =NULL;
    }
    //if the position in the cards array is empty we can just add the car to the cards array as the tail.
    if(cards[position]==NULL){
        cards[position] = card;
        return;
    }
    //we create a next pointer which is going to be used to travel from the tail to the head of the linked list.
    struct card *next = cards[position]; 
    while (true){
        if(next->next==NULL){//when we reach the head we connect the card to the head as follows.
            next->next =card;
            card->last = next; 
            return;
        }
        else {
            next = next->next;
        }
    }
}
// this method takes a card and then returns the card's position. Meaning it returns 0-6 depending on which list the card is a part of.
int cardtopos(struct card *card){
    //We can use the double linked list structure to travel in reverse from the card to the tail.
    struct card *prev = card;
    while(true){
        printf("last = %d%c\n", prev->value,prev->suit);
        if(prev->last == NULL){
            break;
        }
        prev = prev->last;
    }
    //we use the cards array to check where prev which is the tail is located.
    for(int i =0; i<7; i++){
        if (cards[i] == prev){
            return i;
        }
    }
}

struct card * findcard(int value, char suit){
    for(int i=0; i<decksize; i++){
        if(deck[i].value==value && deck[i].suit==suit){
            return &deck[i];
        }
    }
}
