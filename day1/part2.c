#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

struct num {
    char digit;
    char *pdigit_in_line;
};

int find_start_or_end(struct num digits[], int length, char *option);

int main() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    int sum = 0;
    char *number_words[] = {"zero", "one", "two",   "three", "four",
                            "five", "six", "seven", "eight", "nine"};
    int number_words_len = sizeof(number_words) / sizeof(number_words[0]);

    file = fopen("input", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        struct num digits[MAX_LINE_LENGTH];
        int digit_index = 0;

        for (int i = 0; i < strlen(line) - 1; i++) {
            if (isdigit(line[i]) != 0) {
                digits[digit_index].digit = line[i];
                digits[digit_index].pdigit_in_line = &line[i];
                digit_index++;
            }
        }

        for (int i = 1; i < number_words_len; i++) {
            char *pline = line;
            while ((pline = strstr(pline, number_words[i])) != NULL) {
                digits[digit_index].digit = i + '0';
                digits[digit_index].pdigit_in_line = pline;
                digit_index++;
                pline++;
            }
        }

        if (digit_index > 0) {
            int start = digits[find_start_or_end(digits, digit_index, "start")].digit;
            int end = digits[find_start_or_end(digits, digit_index, "end")].digit;
            char num_to_sum[3] = {start, end, '\0'};
            int num = atoi(num_to_sum);
            sum += num;
        }
    }

    fclose(file);

    printf("Sum of all of the calibration values: %d", sum);

    return 0;
}

int find_start_or_end(struct num digits[], int length, char *option) {
    int result_index = 0;

    if (strcmp(option, "start") == 0) {
        for (int i = 1; i < length; i++) {
            if (digits[i].pdigit_in_line < digits[result_index].pdigit_in_line) {
                result_index = i;
            }
        }
    } else if (strcmp(option, "end") == 0) {
        for (int i = 1; i < length; i++) {
            if (digits[i].pdigit_in_line > digits[result_index].pdigit_in_line) {
                result_index = i;
            }
        }
    }

    return result_index;
}
