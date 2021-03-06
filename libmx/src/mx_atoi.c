#include "libmx.h"

static bool isdigit(int c) {

    if (c >= '0' && c <= '9') {
        return 1;
    }
    else {
        return 0;
    }
}

int mx_atoi(const char *str) {

    int res = 0;
    int sign = 1;
    int i = 0;

    if(str[0] == '-') {
        sign = -1;
        i++;
    }

    while(str[i] != '\0') {

        if(isdigit(str[i])) {
            res = res * 10 + str[i] - '0';
            i++;
        }
        else {
            break;
        }
    }

    return sign * res;
}

// int main() {
//    char str[] = "-123 456";
//    int val = mx_atoi(str);
//    printf("%d", val);
//    return 0;
// }
