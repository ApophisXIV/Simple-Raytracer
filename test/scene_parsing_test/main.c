#include <stdio.h>

int main(int argc, char **argv) {

    FILE *f = fopen("scene.txt", "wt");
    if (f == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
    }

    fclose(f);

    return 0;
}