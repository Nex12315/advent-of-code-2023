#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 500

struct NumPos {
    int start;
    int end;
};

int sum = 0;

void strip_newline(char *str);
void compare_lines(char *prev, char *curr, char *next, int line_num, int is_first, int is_last);
int find_number(char *line, struct NumPos *num_pos, int start_idx);
char *substring(char *str, struct NumPos *num_pos);

int main() {
    FILE *file = fopen("input", "r");
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

    printf("Sum of all of the part numbers: %d", sum);

    return 0;
}

int find_number(char *line, struct NumPos *num_pos, int start_idx) {
    int i;
    for (i = start_idx; line[i] != '\0'; i++) {
        if (isdigit(line[i]) && num_pos->start == -1) {
            num_pos->start = i;
        }

        if (!isdigit(line[i]) && num_pos->start != -1) {
            num_pos->end = i - 1;
            return 0;
        }
    }

    if (num_pos->start != -1) {
        num_pos->end = i - 1;
        return 0;
    }

    return 1;
}

char *substring(char *str, struct NumPos *num_pos) {
    int start;
    int end;

    if (num_pos->start == 0) {
        start = num_pos->start;
    } else {
        start = num_pos->start - 1;
    }

    if (num_pos->end == (strlen(str) - 1)) {
        end = num_pos->end;
    } else {
        end = num_pos->end + 1;
    }

    int len = end - start + 1;

    char *result = (char *)malloc((len + 1) * sizeof(char)); // +1 for null terminator

    int i, j;
    for (i = start, j = 0; i <= end && str[i] != '\0'; i++, j++) {
        result[j] = str[i];
    }
    result[j] = '\0';

    return result;
}

void strip_newline(char *str) {
    char *pos = strchr(str, '\n');
    if (pos != NULL)
        *pos = '\0';
}

void compare_lines(char *prev, char *curr, char *next, int line_num, int is_first, int is_last) {
    struct NumPos curr_num_pos = {-1, -1};
    int start_idx = 0;

    while (find_number(curr, &curr_num_pos, start_idx) != 1) {
        int adjacent_symbols = 0;
        char *number = substring(curr, &curr_num_pos);

        // Check previous line
        if (strcmp("empty", prev) != 0) {
            for (int i = curr_num_pos.start - 1; i <= curr_num_pos.end + 1; i++) {
                if (i >= 0 && i < strlen(prev) && prev[i] != '.' && !isdigit(prev[i])) {
                    adjacent_symbols++;
                    break;
                }
            }
        }

        // Check next line
        if (strcmp("empty", next) != 0) {
            for (int i = curr_num_pos.start - 1; i <= curr_num_pos.end + 1; i++) {
                if (i >= 0 && i < strlen(next) && next[i] != '.' && !isdigit(next[i])) {
                    adjacent_symbols++;
                    break;
                }
            }
        }

        // Check left
        if (curr_num_pos.start > 0) {
            if (curr[curr_num_pos.start - 1] != '.' && !isdigit(curr[curr_num_pos.start - 1])) {
                adjacent_symbols++;
            }
        }

        // Check right
        if (curr_num_pos.end < strlen(curr) - 1) {
            if (curr[curr_num_pos.end + 1] != '.' && !isdigit(curr[curr_num_pos.end + 1])) {
                adjacent_symbols++;
            }
        }

        if (adjacent_symbols > 0) {
            char *number_str = malloc(strlen(number) + 1);

            int j = 0;
            for (int i = 0; i < strlen(number); i++) {
                if (isdigit(number[i])) {
                    number_str[j] = number[i];
                    j++;
                }
            }
            number_str[j] = '\0';

            int part_number = atoi(number_str);
            sum += part_number;

            free(number_str);
        }

        free(number);
        start_idx = curr_num_pos.end + 1;
        curr_num_pos.start = -1;
        curr_num_pos.end = -1;
    }
}
