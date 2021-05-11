#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MIN(a,b) (((a)<(b)) ? (a) : (b))
void newdeck();
void printdeck();
int CommandInput();
static char input[50]; //Used for CommandInput
struct card * findcard(int value, char suit);
int cardtopos(struct card *card);
void game();
int valueFromChar(char value);
void si(int *split);
void LD(char *fileName);
void sr();
void sd();
void movecard(int position, struct card *card);
void movefromfound(int position, int found);
void movetofound(int position, struct card *card);
void P();
void setToDeck(int number[]);
char getValueAsString(int number);
struct card * getPileCard(int pile, int pilenr);
void printboard();
void SW();
void srTest();
void siTest();
void sdTest();

struct card * getBottomCard(int pile);
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
struct card *foundation[4];// This repressants the foundation piles.

struct card deck[52];//this represents the deck.
int main(int argc, char *argv[]){

    game();
    //newdeck();
    //printdeck();
    //int a = 26;
    //int *split = &a;
    //struct card *card = &deck[3];
    //movecard(2,card);
    //printf("%d%c\n",cards[2]->value, cards[2]->suit);
    //card = & deck[1];
    //movecard(2,card);
    //printf("%d%c\n",cards[2]->value, cards[2]->suit);
    //printf("%d%c\n",cards[2]->next->value, cards[2]->next->suit);
    //printf("pos = %d\n",cardtopos(findcard(2,C)));
    //sr();//si(split);
    //printdeck();
}

void game(){//This method is used to contain the gameloop.
    while(true){
        CommandInput();
    }
}

int decksize = 0;// we use decksize to go through cards in the game, and to find out if the game is finished.
void newdeck(){//this method is called when you want a new deck. It'll create an unshuffled deck. AC->KS
    // to initialize we first want to create all cards. We'll be storing them in the array deck.
    char suits[] = {'C','D','H','S'};
    decksize =52;
    int k = 0;
    for(int i=0; i<=3; i++){
        for(int j=1; j<=13; j++){
            struct card tempcard;
            tempcard.suit = suits[i];
            tempcard.value = j;
            tempcard.visible = false;
            deck[k]= tempcard;
            k++;
        }
    }
}
void printdeck(){//this method prints each card in the deck.
    for(int i = 0 ; i <= 51; i++){
        printf("index %d: %c%d \n", i, deck[i].suit, deck[i].value);
    }
}

// This function is supposed to mix the deck. It takes a pointer to an integer as an input.
// Because this is a pointer it's possible to input a NULL pointer to the function.
// If the input is NULL this function will randomly select a valid value for split.

void si(int *split){
    //printf("%d \n", decksize);
    if (split == NULL){// first we check if split is NULL, in which case we select a value for split.
        time_t t;
        srand((unsigned) time(&t));
        int a = (rand()%(52-1)) +1; //we want numbers from 1 to decksize.
        split = &a;
        printf("split was not specified, random split %d was chosen\n", *split);
    }
    //printf("%d %d \n", decksize, *split);
    if(*split > 52 || *split <=0){// if the split is either larger than the size of the deck, or smaller than or equal to null we return an error.
        printf("split size error \n");
        return;
    }// now we shuffle the cards into the shuffled pile.
    struct card shuffled[52];
    int nextcard = 1;   // next card is used to find the next card in both splits.
    int min = MIN(*split, 52-*split); //We use min here because by computing this it makes it possible to split the deck without actually creating another array.
    // min denotes how far we have to travel down the two splits until there are no more cards in one of them.
    for (int i = 52-min*2; i<52; i=i+2){ // we use i to find the position we want to shuffle a card to, and we do two cards each loop.
        shuffled[i]=deck[52-*split-nextcard]; //The first split starts from the card split down from the top of the deck.
        shuffled[i+1]=deck[52-nextcard]; // The second card is chosen from the top of the deck.
        nextcard++;
    }// when there are no more cards in one of the splits we have to insert the rest of the cards at the bottom of the shuffled pile.
    if(*split<=52/2){// The method is different depending on which split has cards left.
        for (int j = 0; j<=52-1-min*2;j++){
            shuffled[j]= deck[j];
        }
    }
    else{
        nextcard = 0;
        //printf(" min %d decksize-min %d\n",min, 52-min);
        for (int j = min; j<=52-min-1;j++){
            shuffled[nextcard]= deck[j];
            nextcard++;
        }
    }//lastly we have to make the shuffled deck our new deck, we do this by overwriting the deck with the values of the shuffled deck.
    for(int h = 0; h<52; h++){
        deck[h] = shuffled[h];
    }
}

//this function goes through each card in the deck and tries to place it in a random position of the shuffled pile. It does this through brute force.
void sr(){
    //first we create the shuffled pile. We also initialize our seed for the rand command.
    struct card shuffled[52];
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
            randpos =(rand()%(52));
            if(shuffled[randpos].suit==NULL){ // we check suit because the array doesn't contain pointers, so the best way to check whether it has been taken is by checking the values.
                shuffled[randpos]=deck[i];
                break;
            }
        }
    }// now that we have finished the shuffled pile we want to replace the deck with the new shuffled deck.
    for(int h = 0; h<52; h++){
        deck[h] = shuffled[h];
    }
}
// this takes a position 0 indexed value from 0-6 for C1-C7. this position is where we move the card to. it also takes the card you want to move.
void movecard(int position, struct card *card){
    //we need to dereference the card and the cards connected to it. We do not have to do anything with the next card because we want to move any next cards with it.
    if(card->last!=NULL){
        card->last->visible = true;
        card->last->next =NULL;
        card->last =NULL;
    }
    else{
        cards[cardtopos(card)] == NULL;
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
//this method goes through the deck and returns the card which matches the value and suit you input.
struct card * findcard(int value, char suit){
    for(int i=0; i<52; i++){
        if(deck[i].value==value && deck[i].suit==suit){
            return &deck[i];
        }
    }
}

//this method gets an input from the user using the commandline. It then compares the input with a few premade commands, and depending on the input a function is called.
int CommandInput() {
    //Used to read the input
    if(fgets(input, 50, stdin) == NULL){
        return 0;
    }
    //Sets the last index to 0 in order to compare strings properly
    if(input[strlen(input)-1] == '\n') {
        input[strlen(input)-1] = 0;
    }
    //Commands with only two characters
    if(strcmp(input, "SW") == 0) {
        SW();
    }
    else if(strcmp(input, "SR") == 0) {
        sr();
        //printf("SR\n");
    }
    else if(strcmp(input, "QQ") == 0) {
        exit(0);
    }
    else if(strcmp(input, "P") == 0) {
        P();
    }

        //Command "LD <filename>" where filename is specified (aka. not empty)
    else if(input[0] == 'L' && input[1] == 'D'){
        char filename[47];
        for (int j = 0; j< 47; j++){
            filename[j]=NULL;
        }
        char *ptr = NULL;
        int ctr = 0;
        for(int i = 3 ;i<strlen(input);i++){
            filename[ctr] = input[i];
            ctr++;
        }
        if(strlen(input)>3){
            ptr = &filename;
        }
        LD(ptr);
        int piles[6] = {8,8,8,7,7,7};
        setToDeck(piles);
        printboard();

        //printf("LD filename\n");
    }

    //SI <split> where split is specified
    if(input[0] == 'S' && input[1] == 'I'){
        char filename[47];
        for (int j = 0; j< 47; j++){
            filename[j]=NULL;
        }
        char *ptr = NULL;
        int ctr = 0;
        for(int i = 3 ;i<strlen(input);i++){
            filename[ctr] = input[i];
            ctr++;
        }
        if(strlen(input)>3){
            int a = atoi(filename);
            ptr = &a;
        }
        si(ptr);
        //printf("SI split\n");
    }

    //SD <filename> where filename is specified
    if(input[0] == 'S' && input[1] == 'D'){
        sd();
    }

    //Missing Game moves

    return 0;
}
//LD takes a pointer to a filename. This filename variable needs to be the complete path to the file, or NULL if you would like to start a new deck.
//If the filename is not valid an error message is printed.
void LD(char *fileName) {
    int size = 0;


    if (fileName == NULL )
    {
        newdeck();
        return;
    }
    //opens the file of given pathname
    FILE *fptr = fopen(fileName, "r");

    //should have a way
    if (fptr == NULL) {
        printf("File does not exist \n");
        return;
    }

        //start assigning the deck from file
    else {
        char klo;
        int i = 0;
        int count = 1;
        while ((klo = fgetc(fptr)) != EOF) {

            if (klo == '\n') {
                count = 1;
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
                    case 'J':
                        deck[i].value = 11;
                        break;
                    case 'Q':
                        deck[i].value = 12;
                        break;
                    case 'K':
                        deck[i].value = 13;
                        break;
                    default:
                        deck[i].value = klo - '0';
                }
            } else {
                deck[i].suit = klo;
                deck[i].visible = false;
                deck[i].next = NULL;
                deck[i].last = NULL;
                size++;
            }

        }

        fclose(fptr);
    }
    //Set the decksize of the given deck:
    decksize = size;

//check if all cards are present
    int countDeckSize = 0;
    for (int i = 0; i < size; i++)
    {
        countDeckSize = countDeckSize++;
//    printf("%d \n",count);
    }
    if (countDeckSize < 52){
        printf("The file does not contain 52 cards! \n");
        return;
    }

    //printf("\nOK");
    return;
}
//SORRY. This is a very bad implementation of P. It is  over 300 lines long, and very complex, and likely riddled with bugs.
//We had a big timecrunch because members of the group spend much longer than agreed upon on some of the methods I wanted to use for testing purposes.
//I had also expected to be able to delegate parts of the method for other people to finnish, but I had to make it alone.

//There is a brief description of the method in the report, it says the following:
/*"There are 3 main parts in the function. The first - before the while loop which contains the actual game - is the initialization part.
  In this part we start by distributing the cards onto the board, and setting the visibility of the individual cards.
  The next part is the input handling. Here we first check whether the input is 'Q' in which case we break the while loop.
  Otherwise we split the message in a \textit{from}, and \textit{to} string.
  These messages are split when they encounter the '->' arrow symbol, which is a part of the game move format.
  Everything left of the arrow is added to the \textit{from} string, and everything right of it is likewise added to the \textit{to} string. \
  The last part is where the complexity increases. The purpose of this part is to check the validity of moves, and do the moves if they are valid.
  Here we have three sections. Moves from the foundation pile to the columns, moves from the columns to the foundation pile, and moves from the columns to other columns.
  Each of these types of moves have different validation criteria."*/
//just to specify. The function returns nothing, and handles all the game logic and setup.

void P(){
    //First we initialize the game board
    int piles[6] = {1,6,7,8,9,10};
    for (int i = 0; i < 52; i++){
        deck[i].last =NULL;
        deck[i].next =NULL;
        deck[i].visible = true;
    }
    setToDeck(piles);
    foundation[0]= NULL;
    foundation[1]= NULL;
    foundation[2]= NULL;
    foundation[3]= NULL;

    //We want to fix which cards are visible at start of game.
    cards[1]->visible=false;
    cards[2]->visible=false;
    cards[3]->visible=false;
    cards[4]->visible=false;
    cards[5]->visible=false;
    cards[6]->visible=false;
    cards[2]->next->visible=false;
    cards[3]->next->visible=false;
    cards[4]->next->visible=false;
    cards[5]->next->visible=false;
    cards[6]->next->visible=false;
    cards[3]->next->next->visible=false;
    cards[4]->next->next->visible=false;
    cards[5]->next->next->visible=false;
    cards[6]->next->next->visible=false;
    cards[4]->next->next->next->visible=false;
    cards[5]->next->next->next->visible=false;
    cards[6]->next->next->next->visible=false;
    cards[5]->next->next->next->next->visible=false;
    cards[6]->next->next->next->next->visible=false;
    cards[6]->next->next->next->next->next->visible=false;
    while(true){//this is the main loop.
        if(decksize<=0){//if all the cards are in the foundation piles decksize should be 1 because we degate it by 1 each time.
            printf("\n You have won\n");
            decksize = 52;
            for(int i =0; i<4;i++){
                foundation[i]=NULL;
            }
            break;
        }
        printboard(); // printboard();
        if(fgets(input, 50, stdin) == NULL){
            return;
        }

        //Sets the last index to 0 in order to compare strings properly
        if(input[strlen(input)-1] == '\n') {
            input[strlen(input)-1] = 0;
        }

        //Commands with only two characters
        if(strcmp(input, "Q") == 0) {
            decksize = 52;
            for(int i =0; i<4;i++){
                foundation[i]=NULL;
            }
            break;
        }
        else {
            //first we split the string into from, and to.
            char from[6];
            char to[3];
            for(int i=0; i < 6;i++){
                from[i]=NULL;
            }
            for(int i=0; i < 3;i++){
                to[i]=NULL;
            }
            int j = 0;
            for(; j < 6;j++){
                if(input[j] == '-'){
                    break;
                }
                if(input[j]==NULL){
                    break;
                }
                from[j] = input[j];
            }
            if(input[j]!='-' || input[j+1]!='>'){
                printf("The input has to be in the format <pile>:<card>-><pile> or <pile>-><pile>\n");
                continue;
            }
            j=j+2;
            for(int h=0;h<3;h++){
                to[h]=input[j];
                j++;
            }

            //if from len is 2 then it should represent a pile, if it is 5 then it should represent a pile followed by the card that has to be moved.
            int fromlen = strlen(from);
            int tolen = strlen(to);
            int cardvalue = valueFromChar(from[3]);
            int pile1;
            int pile2;
            if(fromlen==5){
                if(from[0]!='C' || from[2]!=':'){
                    printf("The input has to be in the format <pile>:<card>-><pile> or <pile>-><pile>\n");
                    continue;
                }
                else if(from[4]=='C'|| from[4]=='S'|| from[4]=='H' || from[4]=='D'){
                    //convert chars to integers
                    int pile1 = (int) from[1]-'0'-1;

                    if(cardvalue==0){
                        printf("cards can have values A,T,J,Q,K and 2-9\n");
                        continue;
                    }
                    if(from[0]=='C'){
                        if(pile1>6 || pile1<0){
                            printf("columns can have values 1-7\n");
                            continue;
                        }
                    }
                    else{
                        if(pile1>3 || pile1<0){
                            printf("Foundation piles can have values 1-4\n");
                            continue;
                        }
                    }
                }
                else{
                    printf("The input has to be in the format <pile>:<card>-><pile> or <pile>-><pile>\n");
                    continue;
                }
            }
            else if(fromlen==2){
                if(from[0]!='C'&& from[0]!='F'){
                    printf("The input has to be in the format <pile>:<card>-><pile> or <pile>-><pile>\n");
                    continue;
                }
                pile1 = (int) from[1]-'0'-1;
                if(from[0]=='C'){
                    if(pile1>6 || pile1<0){
                        printf("columns can have values 1-7\n");
                        continue;
                    }
                }
                else{
                    if(pile1>3 || pile1<0){
                        printf("Foundation piles can have values 1-4\n");
                        continue;
                    }
                }
            }
            else{
                printf("The input has to be in the format <pile>:<card>-><pile> or <pile>-><pile>\n");
                continue;
            }
            if(tolen==2){
                if(to[0]!='C' && to[0]!='F'){
                    printf("The input has to be in the format <pile>:<card>-><pile> or <pile>-><pile>\n");
                    continue;
                }
                pile2 = (int) to[1]-'0'-1;
                if(to[0]=='C'){
                    if(pile2>6 || pile2<0){
                        printf("columns can have values 1-7\n");
                        continue;
                    }
                }
                else{
                    if(pile2>3 || pile2<0){
                        printf("Foundation piles can have values 1-4\n");
                        continue;
                    }
                }
            }
            else{
                printf("The input has to be in the format <pile>:<card>-><pile> or <pile>-><pile>\n");
                continue;
            }
            //now we know the input is a valid format. We now want to check whether the move follows the rules.
            //first we check if the referenced card is visible
            if(from[0]=='C' && to[0]=='C'){
                struct card* tempfrom = NULL;
                if(fromlen == 5){
                    tempfrom = findcard(cardvalue, from[4]);
                    if(!tempfrom->visible){
                        printf("you are referencing an invisible card\n");
                        continue;
                    }
                    int cardpos =cardtopos(tempfrom);
                    pile1 = (int) from[1]-'0'-1;
                    if(cardpos != pile1){// now we check if the card you are referencing is in the pile you are referencing.
                        printf("you are referencing a card in the wrong pile\n");
                        //printf("1 %d %d\n",cardpos, pile1);
                        continue;
                    }
                }//now we check if you are moving a card into the same pile. we do this for all formats of from.
                if(pile1 == pile2){
                    printf("you are moving a card into the same pile %d %d\n",pile1,pile2);
                    continue;
                }
                if(tempfrom == NULL){
                    tempfrom = getBottomCard(pile1);
                    if(tempfrom == NULL){
                        printf("There are no cards to move in that pile\n");
                        continue;
                    }
                }
                struct card* tempto = getBottomCard(pile2);
                if(tempto == NULL && tempfrom->value!=13){
                    printf("You have to move a king to an empty pile\n");
                    continue;
                }
                if(tempto ==NULL){
                    movecard(pile2,tempfrom);
                    continue;
                }
                if(tempto->suit == tempfrom->suit){
                    printf("you have to move cards onto cards of a different suit\n");
                    continue;
                }
                if(tempfrom->value+1!=tempto->value){
                    printf("you have to move cards onto cards with a value which is 1 larger\n");
                    continue;
                }
                //printf("%d%c\n",tempfrom->value,tempfrom->suit);
                movecard(pile2,tempfrom);
            }
            else if(from[0]=='F' && to[0]=='F'){
                printf("you cannot move cards from one foundation pile to another\n");
                continue;
            }
            else if(from[0]=='F' && to[0]=='C'){
                struct card* tempfrom = NULL;
                if (foundation[pile1]!=NULL){
                    tempfrom = foundation[pile1];
                }
                if(tempfrom == NULL){
                    printf("the foundation pile is empty\n");
                    continue;
                }
                struct card* tempto = getBottomCard(pile2);
                if(tempto == NULL && tempfrom->value!=13){
                    printf("You have to move a king to an empty pile\n");
                    continue;
                }
                if(tempto->suit == tempfrom->suit){
                    printf("you have to move cards onto cards of a different suit\n");
                    continue;
                }
                if(tempfrom->value+1!=tempto->value){
                    printf("you have to move cards onto cards with a value which is 1 larger\n");
                    continue;
                }

                movefromfound(pile1,pile2);
            }
            else {
                pile1 = (int) from[1]-'0'-1;
                pile2 = (int) to[1]-'0'-1;
                struct card* tempfrom = NULL;
                if(fromlen == 5){
                    tempfrom = findcard(cardvalue, from[4]);
                    if(!tempfrom->visible){
                        printf("you are referencing an invisible card\n");
                        continue;
                    }
                    int cardpos = cardtopos(tempfrom);

                    if(cardpos != pile1){// now we check if the card you are referencing is in the pile you are referencing.
                        printf("you are referencing a card in the wrong pile\n");
                        continue;
                    }
                    if(tempfrom->next!=NULL){
                        printf("you cannot move more than one card to a foundation\n");
                        continue;
                    }
                }
                if(tempfrom == NULL){
                    tempfrom = getBottomCard(pile1);
                    if(tempfrom == NULL){
                        printf("There are no cards to move in that pile\n");
                        continue;
                    }
                }
                struct card* tempto = NULL;
                if (foundation[pile2]!=NULL){
                    tempto = foundation[pile2];
                }
                if(tempto == NULL && tempfrom->value!=1){
                    printf("You have to move an ace to an empty foundation pile\n");
                    continue;
                }
                else if(tempto==NULL){
                    movetofound(pile2,tempfrom);
                    continue;
                }
                if(tempto->suit != tempfrom->suit){
                    printf("You have to move cards onto the foundation pile with the same suit\n");
                    continue;
                }
                if(tempfrom->value-1!=tempto->value){
                    printf("You have to move cards onto the foundation tile with a value which is 1 smaller\n");
                    continue;
                }
                movetofound(pile2,tempfrom);
            }
        }
    }
}
// This method takes a char which represents the card's value, such as 'A' or '2'and returns an integer that represents the card's value.
int valueFromChar(char value){
    if(value=='A')
        return 1;
    else if(value=='T')
        return 10;
    else if(value=='J')
        return 11;
    else if(value=='Q')
        return 12;
    else if(value=='K')
        return 13;
    int v = (int) value - '0';
    if(v>1 && v<10){
        return v;
    }
    return 0;
}
//This method goes through a column pile specified by "int pile" 0-6 representing C1-C7. When it reaches the bottom it returns the buttom card.
//If the pile has no cards, it returns NULL
struct card * getBottomCard(int pile){
//we need to dereference the card and the cards connected to it. We do not have to do anything with the next card because we want to move any next cards with it.

    //if the position in the cards array is empty we can just add the car to the cards array as the tail.
    if(cards[pile]==NULL){
        return NULL;
    }
    //we create a next pointer which is going to be used to travel from the tail to the head of the linked list.
    struct card *next = cards[pile];
    while (true){
        if(next->next==NULL){//when we reach the head we connect the card to the head as follows.
            return next;
        }
        else {
            next = next->next;
        }
    }
}
//Because we implemented P late I 3 individual methods that would move cards. This one moves cards from foundations into the column piles.
//You give the method a position which signifies the column: 0-6 -> C1-C7. And an integer found: 0-3 -> F1-F4.
//It then moves the top card from the foundation to the bottom of the column.
void movefromfound(int position, int found){
    //we need to dereference the card and the cards connected to it. We do not have to do anything with the next card because we want to move any next cards with it.
    struct card* card = foundation[found];
    if(card->next!=NULL){
        foundation[found] = card->next;
        card->next->last = NULL;
    }
    else{
        foundation[found] = NULL;
    }
    card->next =NULL;
    card->last =NULL;
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
    decksize++;
}
//This one moves cards from column piles into the foundation piles.
//You give the method a position which signifies the foundation: 0-3 -> F1-F4. And the card you want to have moved to the foundation.
//It then moves the card into the foundation. I didn't have time to think about checking for errors. That is done in the method P();
void movetofound(int position, struct card* card){
    //we need to dereference the card and the cards connected to it. We do not have to do anything with the next card because we want to move any next cards with it.
    if(card->last!=NULL){
        card->last->visible = true;
        card->last->next = NULL;
        card->last = NULL;
    }
    else{
        cards[cardtopos(card)] = NULL;
    }
    //if the position in the cards array is empty we can just add the car to the cards array as the tail.
    if(foundation[position]!=NULL){
        foundation[position]->last =card;
        card->next = foundation[position];
        foundation[position] = card;
    }
    else{
        foundation[position] = card;
    }
    decksize--;
}
//Set to deck reinitialize all cards so they do not reference each other, afterwards it places the cards into the 7 columns depending on your specifications.
//the integer array number is used to describe how many cards are to be placed in each pile. The first 6 elements of number correspond to the first six columns C1-C6.
//The rest of the cards not specified in the array are placed in column 7.
// we only check if the total for the first six rows of the number array is more than 52 in which case we return an error.

void setToDeck(int number[]) {

    //sæt alle cards[] points til null
    for (int i = 0; i < 7; i++) {
        cards[i] = NULL;
    }

    //sæt alle deck, last og next points til null
    for (int i = 0; i < 52; i++) {
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

    for (int i = 0; i < 52; i++) {
//check if pile has space for a card
//if there is space, then insert card i that pile and continue to next card
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
//The SW method specifies a format for the cards using the settodeck method, and then sets all cards to visible and prints the board using the printboard() method.
void SW() {
    int number[6] = {8, 8, 8, 7, 7, 7};
    setToDeck(number);

    //should check if a card deck is assigned:

    for (int i = 0; i < 52; i++){
        deck[i].visible = true;
    }
    printboard();
}
//The print board method is used to print the board state. It's not ideal, but the method uses "cpile" to find out how many cards are in each pile. then it prints each card
//cpile is initialized at the start by traversing the columns. Again it would be better to just do this at runtime but allas. The method prints "[]" if a card is invisible.
void printboard(){
    int cpile[7] = {0,0,0,0,0,0,0};
    //We need to find cpile[] even though this isn't the best way to do it.
    for(int pile = 0; pile <7; pile++){
        if(cards[pile]==NULL){
            continue;
        }
        //we create a next pointer which is going to be used to travel from the tail to the head of the linked list.
        struct card *next = cards[pile];
        cpile[pile]++;
        while (true){
            if(next->next==NULL){//when we reach the head we connect the card to the head as follows.
                break;
            }
            else {
                next = next->next;
                cpile[pile]++;
            }
        }
    }
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n"
           "\n");
    int linenr = 0;
    int pile = 0;
    int fcount = 1;

    for (int i = 0; i < decksize; i++) { //this is the reason why we need to keep track of how many cards are in the foundation pile. If we do not we get an error here.
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
                        if(linenr<7){
                            if(foundation[linenr/2]!=NULL){
                                printf("%c%c",getValueAsString(foundation[linenr/2]->value),foundation[linenr/2]->suit);
                                printf("\t");
                                printf("\t");
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
                    }
                    //reached end of line so print new line
                    printf("\n");
                    linenr = (linenr + 1);
                }
            }
                //goes here if there is space
            else {
                if(!getPileCard(pile,linenr)->visible){
                    printf("[]\t");
                }
                else{
                    printf("%c%c",getValueAsString(getPileCard(pile,linenr)->value),getPileCard(pile,linenr)->suit);
                    printf("\t");
                }
                pile = (pile + 1) % 7;
                if (pile == 0) {
                    //check whether F-pile should be printed which is at the end of line 0, 2, 4 and 6
                    if (linenr % 2 == 0){

                        //check if card is set to being visible or not
                        printf("\t\t");
                        if(linenr<7){
                            if(foundation[linenr/2]!=NULL){
                                printf("%c%c",getValueAsString(foundation[linenr/2]->value),foundation[linenr/2]->suit);
                                printf("\t");
                                printf("\t");
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
    /*if(foundation[0]!=NULL){
        printf("1 %d%c\n",foundation[0]->value,foundation[0]->suit);
    }
    if(foundation[1]!=NULL){
        printf("2 %d%c\n",foundation[1]->value,foundation[1]->suit);
    }
    if(foundation[2]!=NULL){
        printf("3 %d%c\n",foundation[2]->value,foundation[2]->suit);
    }
    if(foundation[3]!=NULL){
        printf("4 %d%c\n",foundation[3]->value,foundation[3]->suit);
    }*/
}
//This method returns the corresponding character which represents each value. Such as 'A' -> 1 or '7'->7
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
            result = 'Q';
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
//gets the pilenr'th card from a column pile specified by the integer pile. pile should be an integer between 0-6 corresponding to the columns C1-C7.
//pilenr denotes how far we should go down the pile.
struct card * getPileCard(int pile, int pilenr){
    //if the position in the cards array is empty we can just add the car to the cards array as the tail.
    if(cards[pile]==NULL){
        return NULL;
    }
    //we create a next pointer which is going to be used to travel from the tail to the head of the linked list.
    struct card *next = cards[pile];
    while (true){
        if(pilenr==0 || next->next==NULL){//when we reach the head we connect the card to the head as follows.
            return next;
        }
        else {
            next = next->next;
            pilenr--;
        }
    }
}
//SD cannot take a file name. It just stores the current deck into the file named "cards.txt".
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
void srTest() {
    newdeck();
    printf("before shuffle \n");
    printdeck();
    printf("\n");
    sr();
    printf("after shuffle \n");
    printdeck();
}

void siTest() {
    newdeck();
    printf("Before split \n");
    printdeck();
    printf("\n");
    int a = 13;
    int *split = &a;
    si(split);
    printf("After split \n");
    printdeck();
}

void sdTest() {
    newdeck();
    sr();
    printf("Expected to be under cards.txt with value + suit \n");
    printdeck();
    sd();
}
