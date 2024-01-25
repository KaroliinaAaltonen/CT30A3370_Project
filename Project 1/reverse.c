#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_lines(char **lines, size_t line_count, FILE *output) {
    // Reverse lines and print
    for (ssize_t i = line_count - 1; i >= 0; i--) {
        fprintf(output, "%s\n", lines[i]);
    }
}

int main(int argc, char *argv[]) {
    FILE *input = stdin;
    FILE *output = stdout;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **lines = NULL;
    size_t line_count = 0;

    // Check if too many arguments
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    }

     // Check if input and output files are same
    if (argc == 3 && strcmp(argv[1], argv[2]) == 0) {
        fprintf(stderr, "Input and output file must differ\n");
        return 1;
    }

    // Opens input file
    if (argc == 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            return 1;
        }
    }

    // Opens output file
    else if (argc == 3) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            return 1;
        }
        output = fopen(argv[2], "w");
        if (output == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            fclose(input);
            return 1;
        }
    }

    // Read input file and store in array
    while ((read = getline(&line, &len, input)) != -1) {
        // Delete new lines
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        // Realloc lines for array
        lines = realloc(lines, (line_count + 1) * sizeof(char *));
        if (lines == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }

        // strdup() allocates memory for new line
        // and copies pointer of line to lines
        lines[line_count] = strdup(line);
        if (lines[line_count] == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }

        line_count++;
    }

    free(line);

    reverse_lines(lines, line_count, output);

    // Free memory
    for (size_t i = 0; i < line_count; i++) {
        free(lines[i]);
    }
    free(lines);

    // Close files
    if (input != stdin)
        fclose(input);
    if (output != stdout)
        fclose(output);

    return 0;
}
