#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 500
#define MAX_COLOR_NAME 20

int main() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    int sum = 0;
    int game_id = 1;

    file = fopen("input", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        int error_found = 0;
        int green_max = 0;
        int blue_max = 0;
        int red_max = 0;
        char *saveptr1, *saveptr2;
        char *skip_token;

        skip_token = strtok_r(line, ":", &saveptr1);

        char *grab_token = strtok_r(NULL, ";", &saveptr1);
        while (grab_token != NULL) {
            printf("%s\n", grab_token);

            char *color_token = strtok_r(grab_token, ",", &saveptr2);
            while (color_token != NULL) {
                int amount;
                char color[MAX_COLOR_NAME];

                if (sscanf(color_token, " %d %s", &amount, color) == 2) {
                    if (strcmp(color, "green") == 0) {
                        if (amount > green_max)
                            green_max = amount;
                    } else if (strcmp(color, "blue") == 0) {
                        if (amount > blue_max)
                            blue_max = amount;
                    } else if (strcmp(color, "red") == 0) {
                        if (amount > red_max)
                            red_max = amount;
                    }
                }

                color_token = strtok_r(NULL, ",", &saveptr2);
            }

            grab_token = strtok_r(NULL, ";", &saveptr1);
        }

        printf("Game %d required at least %d red, %d green, %d blue cubes.\n", game_id, red_max,
               green_max, blue_max);

        printf("---------\n");

        sum += red_max * green_max * blue_max;

        game_id++;
    }

    fclose(file);

    printf("The sum of the power of all sets: %d", sum);

    return 0;
}
