#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct DataType{
    int identifier;
    char* token;
    int size;
} DataType;

static const DataType data_types[] = {
    {1, "int", 4},
    {2, "float", 8},
    {3, "boolean", 1},
};

const int n_datatypes = sizeof(data_types) / sizeof(data_types)[0];

int mapTypeNumber(char *type){
    int map = -1;
    for (int i = 0; i < n_datatypes; i++) {
        if(strcmp(type, data_types[i].token) == 0){
            map = data_types[i].identifier;
            break;
        }
    }
    return map;
}



// TODO: char* symbol, son left y right necesarios? se puede
// poner otro campo indicando si son binarios o unarios
typedef struct {
    char* symbol;
    int left;
    int right;
    int result;
    int level;
} Operator;


const int MAX_OP = 3;

// símbolo | tipo op1 | tipo op2 | tipo resultado | nivel
static const Operator operators[] = {
    {"*", 1, 1, 1, 1}, {"*", 2, 2, 2, 1},
    {"/", 1, 1, 1, 1}, {"/", 2, 2, 2, 1},
    {"+", 1, 1, 1, 2}, {"+", 2, 2, 2, 2},
    {"-", 1, 1, 1, 2}, {"-", 2, 2, 2, 2},
    {"=", 1, 1, 1, 3}, {"=", 2, 2, 2, 3},
};

const int n_operators = sizeof(operators) / sizeof(operators)[0];

void print_op(const Operator* operator){
    printf("%c | Op1 = %i, Op2 = %i | Resultado = %i\n",
           operator->symbol, operator->left,
           operator->right, operator->result);
}

int getDataSize(int type){
    int size = -1;
    const DataType* ans = NULL;
    Operator* tmp = NULL;
    for(int i = 0; i < n_operators; i++){
        if(type == data_types[i].size){
            ans = &data_types[i];
            size = ans->size;
            break;
        }
    }
    return size;
}

int getOpLevel(char* token){
    int level = -1;
    const Operator* ans = NULL;
    Operator* tmp = NULL;
    for(int i = 0; i < n_operators; i++){
        if(strcmp(token, operators[i].symbol) == 0){
            ans = &operators[i];
            level = ans->level;
            break;
        }
    }
    return level;
}

int opSearch(char* symbol){
    int finded = -1;

    for(int i = 0; i < n_operators; i++){
        if(strcmp(symbol, operators[i].symbol) == 0){
            finded = 0;
            break;
        }
    }
    return finded;
}

const Operator* consult_op(char* symbol, int right, int left){
    const Operator* column = NULL; 
    for(int i = 0; i < sizeof(operators); i++){
        if(strcmp(symbol, operators[i].symbol) == 0 &&
           right == operators[i].right &&
           left == operators[i].left){
           column = &operators[i];
        } 
    }
    return column;
}
