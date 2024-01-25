#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    // Get command line arguments
    if (argc < 2){
        // No command line arguments --> exit
        exit(0);
    }
    // Do the catting for the given files
    for (int i = 1; i < argc; i++){
        // Open file
        FILE *file = fopen(argv[i], "r");
        // Check
        if (file == NULL){
            // File could not be opened --> exit
            fprintf(stderr, "Something bad happened.\n");
            exit(1);
        }
        // Print out the files
        int ch;
        while ((ch = fgetc(file)) != EOF){
        // Cast to unsigned char (otherwise there is warnings when using -Wall)
        putchar((unsigned char)ch);
        }
        // Closing the file
        fclose(file);
    }
    // Exit
    exit(0);
}
