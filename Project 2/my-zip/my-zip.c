#include <stdio.h>
#include <stdlib.h>
void RLEcompress(const char *source, const char *dest){
    // read source file in text mode
    FILE *sourceFile = fopen(source, "r");
    // write destination file in binary form
    FILE *destFile = fopen(dest, "wb");
    // File could not be opened
    if (!sourceFile || !destFile) {
        perror("Files could not be opened");
        exit(1);
    }
    int count = 1;
    char current, next;
    // Get first character from the source file
    fread(&current, 1, 1, sourceFile);
    // Read the file
    while (fread(&next, 1, 1, sourceFile) == 1){
        // increment count whenever the next character is the same as current
        if (next == current){
            count++;
        } else{
            // When the next character is different, map it to the destination file
            fwrite(&count, sizeof(int), 1, destFile);
            fwrite(&current, 1, 1, destFile);
            // Reset count and move on to the next character
            count = 1;
            current = next;
        }
    }
    // Finish writing the destination file (compressed file)
    fwrite(&count, sizeof(int), 1, destFile);
    fwrite(&current, 1, 1, destFile);
    // Closing the files
    fclose(sourceFile);
    fclose(destFile);
}

int main(int argc, char *argv[]){
    // Check command line arguments
    if (argc != 3){
        fprintf(stderr, "Something bad happened with the command\n", argv[0]);
        return 1;
    }
    // compression function call
    RLEcompress(argv[1], argv[2]);
    printf("Compression done.\n");
    // Return success status
    return 0;
}
