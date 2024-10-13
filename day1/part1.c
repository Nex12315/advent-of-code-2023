#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int main() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    int sum = 0;

    file = fopen("input", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char digits[MAX_LINE_LENGTH];
        int digit_index = 0;
        for (int i = 0; i < strlen(line) - 1; i++) {
            if (isdigit(line[i]) != 0) {
                digits[digit_index] = line[i];
                digit_index++;
            }
        }

        char num_to_sum[3] = {digits[0], digits[digit_index - 1], '\0'};
        int num = atoi(num_to_sum);

        sum += num;
    }

    fclose(file);

    printf("Sum of all of the calibration values: %d", sum);

    return 0;
}
