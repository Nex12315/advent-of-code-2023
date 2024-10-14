#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 500
#define MAX_COLOR_NAME 20
#define RED_MAX 12
#define GREEN_MAX 13
#define BLUE_MAX 14

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
        char *saveptr1, *saveptr2;
        char *skip_token;

        skip_token = strtok_r(line, ":", &saveptr1);

        char *grab_token = strtok_r(NULL, ";", &saveptr1);
        while (grab_token != NULL) {
            char *color_token = strtok_r(grab_token, ",", &saveptr2);
            while (color_token != NULL) {
                int amount_of_cubes;
                char color_of_cubes[MAX_COLOR_NAME];

                if (sscanf(color_token, " %d %s", &amount_of_cubes, color_of_cubes) == 2) {
                    if ((strcmp(color_of_cubes, "red") == 0 && amount_of_cubes > RED_MAX) ||
                        (strcmp(color_of_cubes, "green") == 0 && amount_of_cubes > GREEN_MAX) ||
                        (strcmp(color_of_cubes, "blue") == 0 && amount_of_cubes > BLUE_MAX)) {
                        error_found++;
                    }
                }

                color_token = strtok_r(NULL, ",", &saveptr2);
            }

            grab_token = strtok_r(NULL, ";", &saveptr1);
        }

        if (error_found == 0) {
            sum += game_id;
        }

        game_id++;
    }

    fclose(file);

    printf("Sum of the IDs is: %d", sum);

    return 0;
}
