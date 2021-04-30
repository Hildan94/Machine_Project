#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN(a,b) (((a)<(b)) ? (a) : (b))
void newdeck();
void printdeck();
struct card{
    struct card *last;
    struct card *next;
    char suit;
    int value;
    bool visible;
};

int main(int argc, char *argv[]){
    
    newdeck();
    printdeck();
    int a = 26;
    int *split = &a;

    sr();//si(split);
    printdeck();
}
struct card *cards[7];

struct card deck[];

int decksize = 0;
void newdeck(){
    // to initialize we first want to create all cards. We'll be storing them in the array temp.
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

void si(int *split);

void si(int *split){
    //printf("%d \n", decksize);
    if (split == NULL){
        time_t t;
        srand((unsigned) time(&t));
        int a = (rand()%(decksize-1)) +1;
        split = &a;
        printf("split was not specified, random split %d was chosen\n", *split);
    }
    //printf("%d %d \n", decksize, *split);
    if(*split > decksize || *split <=0){
        printf("split size error \n");
        return;
    }
    struct card shuffled[decksize];
    int nextcard = 1;
    int min = MIN(*split, decksize-*split);
    for (int i = decksize-min*2; i<52; i=i+2){
        shuffled[i]=deck[decksize-*split-nextcard];
        shuffled[i+1]=deck[decksize-nextcard];
        nextcard++;
    }
    if(*split<=decksize/2){
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
    }
    for(int h = 0; h<decksize; h++){
        deck[h] = shuffled[h];
    }
}

void sr();

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
void movecard();
// this takes a position 0 indexed value from 0-6 for C1-C7. this position is where we move the card to. it also takes the card you want to move. 
void movecard(int position, struct card card){
    //we need to dereference the card 

}
