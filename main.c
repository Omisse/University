#include <stdio.h>
#include <stdlib.h>

void swap_values(char* ptr1, char* ptr2) {
    char buff = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = buff;
    return;
}

int print_permutations(char* const source, char* const locked_ptr) {
    if (!source || !locked_ptr) {
        return 0;
    }

    if (!*locked_ptr) printf("%s\n",source);
    char* move_ptr = locked_ptr;
    while (*move_ptr) {
        swap_values(locked_ptr, move_ptr);
        print_permutations(source, locked_ptr+1);
        swap_values(locked_ptr, move_ptr);
        move_ptr++;
    }
    return 1;
}

int main() {
    printf("Please, enter any amount of symbols:\n");

    char ch = 'e';
    unsigned long input_size = 1;
    char* usr_input = malloc(input_size*sizeof(char));
    int err = 0;
    for (unsigned long i = 1; ch && ch != '\n' && !err; i++) {
        ch = fgetc(stdin);
        if (input_size < i) {
            input_size*=2;
            char* realloc_result = realloc(usr_input, input_size*sizeof(char));
            if (realloc_result) usr_input = realloc_result;
            else {
                free(usr_input);
                err = 1;
            }
        }     
        if (!err) usr_input[i-1] = ch != '\n' && ch != EOF ? ch : 0;
    }
    if (!err) {       
        err = !print_permutations(usr_input, usr_input);
        free(usr_input);
    } else {
        printf("Memory allocation error: looks like we're exceeded the limits!\n");
    }
    return err;
}