#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// Disclaimer for wimplicit crashing
void RLEcompress(const char *source, const char *dest);

typedef struct{
    const char *source;
    const char *dest;
}CompressionParams;

void *RLEcompressThread(void *arg){
    CompressionParams *params = (CompressionParams *)arg;
    RLEcompress(params->source, params->dest);
    printf("%s compressed.\n", params->source);
    return NULL;
}

void RLEcompress(const char *source, const char *dest){
    // (r) Open source file in TEXT MODE
    FILE *sourceFile = fopen(source, "r");
    // (w) Open destination file in BINARY MODE
    FILE *destFile = fopen(dest, "wb");

    // Could not open file(s)
    if (!sourceFile || !destFile){
        perror("Files could not be opened");
        exit(1);
    }

    int count = 1;
    char current, next;
    // The first character from the source file
    fread(&current, 1, 1, sourceFile);
    // Reading file
    while (fread(&next, 1, 1, sourceFile) == 1){
        if (next == current) {
            count++;
        } else{
            // Compressed data to the destination file
            fwrite(&count, sizeof(int), 1, destFile);
            fwrite(&current, 1, 1, destFile);
            // Move to the next character and reset count
            count = 1;
            current = next;
        }
    }
    // Finish writing the destination file (compressed file)
    fwrite(&count, sizeof(int), 1, destFile);
    fwrite(&current, 1, 1, destFile);
    // Close the files
    fclose(sourceFile);
    fclose(destFile);
}

int main(int argc, char *argv[]){
    // Check command line arguments
    if (argc % 2 != 1 || argc < 3){
        fprintf(stderr, "Usage: <file1> <compressed_file1> <file2> <compressed_file2>... \n", argv[0]);
        return 1;
    }
    // Get the number of file pairs (must be divisible by 2 or someone has committed a bad)
    int numFilePairs = (argc - 1) / 2;
    // Create an array of pthread_t to store thread IDs
    pthread_t *threads = (pthread_t *)malloc(numFilePairs * sizeof(pthread_t));
    // Loop through the file pairs and create threads for each compression
    for (int i = 0; i < numFilePairs; i++) {
        CompressionParams *params = (CompressionParams *)malloc(sizeof(CompressionParams));
        // Set the source and destination file
        params->source = argv[i * 2 + 1];
        params->dest = argv[i * 2 + 2];
        // Create a thread for the compression
        if (pthread_create(&threads[i], NULL, RLEcompressThread, params) != 0) {
            fprintf(stderr, "Error creating thread for %s\n", params->source);
            return 1;
        }
    }
    // Wait for all threads to finish
    for (int i = 0; i < numFilePairs; i++) {
        pthread_join(threads[i], NULL);
    }
    // Free allocated memory
    free(threads);
    printf("All done.\n");
    return 0;
}
