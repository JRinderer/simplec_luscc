#include <stdio.h>
#include "scanner.h"

int main(void) {
    FILE *file = fopen("main.luscc", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }
    start_scanner(file);
    fclose(file);
    return 0;
}