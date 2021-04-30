//
// Created by Hildibjorg on 23.04.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *filename = "Deck.txt";
    char input[41];
    printf("Enter a file name:\n");
    /*
     * C:\\Users\\Hildibjorg\\Desktop\\Deck.txt
     */

    fgets(input,sizeof(input),stdin);
    printf("%s \n",input);


    FILE *infile = fopen(input, "r");
    struct stat sb;
    stat(filename, &sb);

    char *file_contents = malloc(sb.st_size);
    while (fscanf(infile, "%[^\n] ", file_contents) != EOF){
        printf("> %s\n", file_contents);
    }

    fclose(infile);
    exit(EXIT_SUCCESS);
}