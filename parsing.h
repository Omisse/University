#ifndef PARSING_H
#define PARSING_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int flush_to_num_or_spec(char* ch);
int process_input(unsigned long long* amount, double** values);

#endif