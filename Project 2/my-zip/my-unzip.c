#include <stdio.h>
#include <stdlib.h>
void deRLEcompress(const char *source, const char *dest){
    // read the source file in BINARY mode
    FILE *sourceFile = fopen(source, "rb");
    // Write in the destination file
    FILE *destFile = fopen(dest, "w");
    // File could not be opened
    if (!sourceFile || !destFile) {
        perror("The files could not be opened");
        exit(1);
    }
    int count;
    char current;
    // Reading compressed data from the source file
    while (fread(&count, sizeof(int), 1, sourceFile) == 1) {
        fread(&current, 1, 1, sourceFile);
        // Repeat the character count times and write to the destination file
        for (int i = 0; i < count; i++) {
            fprintf(destFile, "%c", current);
        }
    }
    // Closing the files
    fclose(sourceFile);
    fclose(destFile);
}

int main(int argc, char *argv[]) {
    // Check command line arguments
    if (argc != 3) {
        fprintf(stderr, "Something bad happened with the command\n", argv[0]);
        return 1;
    }
    // decompression
    deRLEcompress(argv[1], argv[2]);
    printf("Decompression done.\n");
    return 0;
}
