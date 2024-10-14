#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 500
#define RED_MAX 12
#define GREEN_MAX 13
#define BLUE_MAX 14

int main() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    int sum = 0;
    int game_id = 1;

    file = fopen("test_input", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char *token;
        token = strtok(line, ":");

        token = strtok(NULL, ";");
        while (token != NULL) {
            printf("%s\n", token);
            token = strtok(NULL, ";");
        }

        game_id++;
        printf("-------------\n");
    }

    fclose(file);

    // printf("Sum of the IDs is: %d", sum);

    return 0;
}
