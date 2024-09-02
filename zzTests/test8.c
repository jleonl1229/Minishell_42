#include <stdio.h>
#include <stdlib.h>

int main() {
    // Retrieve the value of the HOME environment variable
    char *home = getenv("HOME");

    // Check if the environment variable exists
    if (home != NULL) {
        printf("The value of $HOME is: %s\n", home);
    } else {
        printf("$HOME is not set.\n");
    }

    return 0;
}
