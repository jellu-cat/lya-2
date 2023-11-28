#include <stdio.h>
#include <string.h>

const char* NUMBER = "0123456789";

int isNumber(char* token){
    int out = -1;
    if(strspn(token, NUMBER) == strlen(token)){
        out = 0;
    }
    return out;
}
