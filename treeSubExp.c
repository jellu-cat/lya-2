#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct TreeExp{
    char* symbol;
    struct TreeExp *left, *right;
} TreeExp;

// Inicializar los punteros
int treeInit(TreeExp *root){
    root = NULL;
    return 0;
}

TreeExp* treeNew(){
    // apuntador temporal para crear el nodo
    TreeExp *tmp;
    tmp = malloc(sizeof(TreeExp));
    return tmp;
}

TreeExp* treeFill(TreeExp *tmp, char* symbol){
    // rellena el nodo
    tmp->symbol = strdup(symbol);
    tmp->left = NULL;
    tmp->right = NULL;

    return tmp;
}

int treeRoot(TreeExp **root, TreeExp *tmp){
    // el caso es del primer nodo
    // se crean los enlaces, el nodo es el primero y el
    // último
    *root = tmp;
    return 0;
}

int treeAppend(TreeExp *root, TreeExp *left, TreeExp *right) {
    root->left = left;
    root->right = right;
    
    return 0;
}

void treePrintFullNode(TreeExp *tmp){
    printf("%p, \t%s en %p, \t%p\n", tmp->left, tmp->symbol, tmp,
           tmp->right);
}

int treeFullPrint(TreeExp *beg){
    // se crea un puntero temporal para recorrer la
    // lista
    TreeExp *tmp;
    tmp = beg;
    while(tmp != NULL){
        treePrintFullNode(tmp);
        tmp = tmp->right;
    }
    
    return 0;
}

void treePrintNode(TreeExp *tmp){
    printf("%s ", tmp->symbol);
}

int treePrint(TreeExp *beg){
    // se crea un puntero temporal para recorrer la
    // lista
    TreeExp *tmp;
    tmp = beg;
    while(tmp != NULL){
        treePrintNode(tmp);
        tmp = tmp->right;
    }
    printf("\n");
    
    return 0;
}
TreeExp *search(TreeExp *beg, char* data){
    bool finded = false;
    TreeExp *tmp = beg;
    TreeExp *ans = NULL;

    while(tmp != NULL && finded == false){
        if(strcmp(data, tmp->symbol) == 0){
            finded = true;
            ans = tmp;
        }
        tmp = tmp->right;
    }
    return ans;
}

int deleteTreeExp(TreeExp *victim){
    return 0;
}

/* int main(void){ */
/*     TreeExp *beg, *end; */
/*     treeInit(&beg, &end); */

/*     for(int i = 0; i < 20; i++){ */
/*         TreeExp *tmp = treeFill(treeNewNode(), "a"); */
/*             if(beg == NULL){ */
/*                 treeFirst(&beg, &end, tmp); */
/*             } else{ */
/*                 treeAppendEnd(&end, tmp); */
/*             } */
/*     } */
/*     treePrint(beg, end); */

/*     TreeExp *ans = search(beg, "b"); */
/*     if(ans != NULL){ */
/*         printf("\n"); */
/*         treePrintNode(ans); */
/*     } */

/*     return 0; */
/* } */
