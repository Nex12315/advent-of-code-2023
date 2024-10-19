#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 500

void strip_newline(char *str) {
    char *pos = strchr(str, '\n');
    if (pos != NULL)
        *pos = '\0';
}

void compare_lines(char *prev, char *curr, char *next, int line_num, int is_first, int is_last) {
    // if (is_first)
    // printf("First line: ");

    // if (is_last)
    // printf("Last line: ");

    // printf("line %d: %s\n", line_num, curr);
    printf("prev line: %s\n", prev);
    printf("curr line: %s\n", curr);
    printf("prev line: %s\n", next);

    printf("--------------\n");
}

int main() {
    FILE *file = fopen("test_input", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return 1;
    }

    char prev_line[MAX_LINE_LENGTH] = "empty";
    char curr_line[MAX_LINE_LENGTH] = "empty";
    char next_line[MAX_LINE_LENGTH] = "empty";
    int line_num = 0;
    int is_first = 1;
    int is_last = 0;

    while (fgets(curr_line, sizeof(curr_line), file) != NULL) {
        strip_newline(curr_line);
        line_num++;

        if (fgets(next_line, sizeof(next_line), file) != NULL) {
            strip_newline(next_line);

            compare_lines(prev_line, curr_line, next_line, line_num, is_first, is_last);
            is_first = 0;

            // Main loop
            while (1) {
                strcpy(prev_line, curr_line);
                strcpy(curr_line, next_line);
                line_num++;

                if (fgets(next_line, sizeof(next_line), file) == NULL) {
                    // This is the last line
                    is_last = 1;
                    compare_lines(prev_line, curr_line, "empty", line_num, is_first, is_last);
                    break;
                }

                strip_newline(next_line);
                compare_lines(prev_line, curr_line, next_line, line_num, is_first, is_last);
            }
        } else {
            // The file has only one line
            is_last = 1;
            compare_lines("empty", curr_line, "empty", line_num, is_first, is_last);
        }
    }

    fclose(file);

    return 0;
}
