#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    int id;
    char string[50];
} Error;

const Error errors[] = {
    {0, ""},
    {1, ""},
};

const int n_errors = sizeof(errors) / sizeof(errors)[0];

int handleOperations(TreeExp* root){
    int out = 0;
    TreeExp* left = root->left;
    TreeExp* right = root->right;
    if(left->type == right->type){
        out = left->type;
    } else{
        int lsize = getDataSize(left->type);
        int rsize = getDataSize(right->type);
        if(lsize > rsize){
            out = lsize; 
        } else out = rsize;
    } 
    return out;
}

int handleAssign(TreeExp* root){
    int out = -1;
    if(root->left->type == root->right->type){
        out = 0;
    }
    return out;
}

const char* handleError(int index){
    const char* str;
    for(int i = 0; i < n_errors; i++){
        str = errors[index].string;
    }
    return str;
}


// TODO: tipo en el árbol, + i f = f, trucar entero
