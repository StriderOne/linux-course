// #include "solution.h"
#include <stdio.h>
#include <string.h>

int stringStat(const char *string, size_t multiplier, int *count) {
    *count += 1;
    int len = strlen(string) * multiplier;

    return len;
}