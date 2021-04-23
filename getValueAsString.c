//
// Created by Hildibjorg on 23.04.2021.
//

#include <stdio.h>
String getValueAsString(int value);

int main() {
    getValueAsString(10)
}

String getValueAsString(int value){
    char result;
    if value < 0 || value > 12){
    return printf("The value of the number is not correct!")
}
    switch (value){
        case '0':
            result = 'A';
            break;
        case '9':
            result = 'T';
            break;
        case '10':
            result = 'J';
            break;
        case '11':
            result = 'D';
            break;
        case '12':
            result = 'K';
            break;
        default:
            result = 'value';
            break;
    }

    return result;
}