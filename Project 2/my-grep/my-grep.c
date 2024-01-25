#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Max size for character array storing each line
#define MAX_LINE_SIZE 2048
int main(int argc, char *argv[]){
    // Check if there is a search term
    if (argc < 2){
        fprintf(stderr, "Something bad happened with the command\n");
        exit(1);
    }
    // Search term from command line
    const char *searchTerm = argv[1];
    // Go through the command line files
    for (int i = 2; i < argc; i++){
        // Opening the file
        FILE *file = fopen(argv[i], "r");
        // File could not be opened
        if (file == NULL) {
            // Print error message and exit
            fprintf(stderr, "Something bad happened with the file\n");
            exit(1);
        }
        // Go over each line in the file
        char line[MAX_LINE_SIZE];
        while (fgets(line, sizeof(line), file) != NULL){
            // Find the search term in the file
            if (strstr(line, searchTerm) != NULL) {
                // Get the line where the search term is in
                printf("%s", line);
            }
        }
        // Closing the file
        fclose(file);
    }
    // No file was specified --> read from input
    if (argc == 2) {
        char line[MAX_LINE_SIZE];
        while (fgets(line, sizeof(line), stdin) != NULL) {
            if (strstr(line, searchTerm) != NULL) {
                printf("%s", line);
            }
        }
    }
    // Exit
    exit(0);
}
