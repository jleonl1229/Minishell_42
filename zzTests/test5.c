#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_sh_data {
    char *last_exit_status;
} t_sh_data;

void cmd_return_status(t_sh_data *sh, char **input) {
    int i = 0;
    while (input[i] != NULL) {
        char *current_pos = input[i];
        char *found_pos;
        size_t new_str_len = 0;
        size_t last_exit_status_len = strlen(sh->last_exit_status);

        // Calculate the length of the new string
        while ((found_pos = strstr(current_pos, "_LAST_EXIT_STATUS_")) != NULL) {
            new_str_len += (found_pos - current_pos) + last_exit_status_len;
            current_pos = found_pos + strlen("_LAST_EXIT_STATUS_");
        }
        new_str_len += strlen(current_pos); // Add the length of the remaining part

        // Allocate memory for the new string
        char *new_str = (char *)malloc(new_str_len + 1); // +1 for the null terminator
        if (new_str == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        // Build the new string
        char *new_str_ptr = new_str;
        current_pos = input[i];
        while ((found_pos = strstr(current_pos, "_LAST_EXIT_STATUS_")) != NULL) {
            size_t prefix_len = found_pos - current_pos;

            // Copy the prefix
            strncpy(new_str_ptr, current_pos, prefix_len);
            new_str_ptr += prefix_len;

            // Copy the last exit status
            strcpy(new_str_ptr, sh->last_exit_status);
            new_str_ptr += last_exit_status_len;

            // Move the current position pointer
            current_pos = found_pos + strlen("_LAST_EXIT_STATUS_");
        }

        // Copy the remaining part of the original string
        strcpy(new_str_ptr, current_pos);

        // Free the old string and update the pointer
        free(input[i]);
        input[i] = new_str;

        i++;
    }
}

int main() {
    // Example usage
    t_sh_data sh;
    sh.last_exit_status = "0";

    char *input[] = {
        strdup("cat"),
        strdup("hola_LAST_EXIT_STATUS_"),
        strdup("_LAST_EXIT_STATUS_"),
        strdup("hello_LAST_EXIT_STATUS_HAHA"),
        strdup("_LAST_EXIT_STATUS_ + _LAST_EXIT_STATUS_"),
        NULL
    };

    cmd_return_status(&sh, input);

    for (int i = 0; input[i] != NULL; i++) {
        printf("input[%d] = %s\n", i, input[i]);
        free(input[i]); // Don't forget to free the memory after use
    }

    return 0;
}
