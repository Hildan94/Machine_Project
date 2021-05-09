//
// Created by Hildibjorg on 23.04.2021.
//

#include <stdio.h>

char getValueAsString(int number);

int main() {
    int input;
    printf("Enter a number (0-12):\n");
    scanf("%d",&input);
    char a = getValueAsString(input);
}

char getValueAsString(int number) {
    char result='b';

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