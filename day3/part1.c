#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 500

int main() {
    FILE *file;
    char line[MAX_LINE_LENGTH];

    file = fopen("input", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
    }

    fclose(file);

    return 0;
}
