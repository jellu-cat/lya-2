#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//TODO: agregar campo de tipo y de valor

typedef struct TreeExp{
    char* symbol;
    int type;
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

void treePrintNode(TreeExp *tmp){
    printf("%s (%i)\n", tmp->symbol, tmp->type);
}

void treePrintFullNode(TreeExp *tmp){
    printf("%p, \t%s en %p, \t%p\n", tmp->left, tmp->symbol, tmp,
           tmp->right);
}

TreeExp* treeRootFill(TreeExp *tmp, char* symbol, TreeExp** right,
                  TreeExp** left){
    // rellena el nodo
    tmp->symbol = strdup(symbol);
    tmp->left = *left;
    tmp->right = *right;
    return tmp;
}

TreeExp* treeFill(TreeExp *tmp, char* symbol, int type){
    // rellena el nodo
    tmp->symbol = strdup(symbol);
    tmp->type = type;
    /* printf("%i, %i\n", type, tmp->type); */
    tmp->left = NULL;
    tmp->right = NULL;
    /* treePrintNode(tmp); */

    return tmp;
}

int treeRoot(TreeExp **root, TreeExp *tmp){
    // el caso es del primer nodo
    // se crean los enlaces, el nodo es el primero y el
    // último
    *root = tmp;
    return 0;
}

int treeAppend(TreeExp *root, TreeExp **left, TreeExp **right) {
    root->left = *left;
    root->right = *right;
    
    return 0;
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

void treePostOrder(TreeExp *p, int indent){
    if(p != NULL) {
        if (p->left){
            treePostOrder(p->left, indent + 4);
        }
        if (p->right){
            treePostOrder(p->right, indent + 4);
        }
        if (indent) {
            for(int i = 0; i < indent; i++){
                printf(" ");
            }
        }
        printf("%s\n", p->symbol);
    }
}

void treeInOrder(TreeExp *p, int indent){
    if(p != NULL) {
        if (p->left){
            treeInOrder(p->left, indent + 4);
        }
        /* if (indent) { */
        /*     for(int i = 0; i < indent; i++){ */
        /*         printf(" "); */
        /*     } */
        /* } */
        /* printf("%s\n", p->symbol); */
        printf("% s(%i) ", p->symbol, p->type);
        if (p->right){
            treeInOrder(p->right, indent + 4);
        }
    }
}
void treePreOrder(TreeExp *p, int indent){
    if(p != NULL) {
        if (indent) {
            for(int i = 0; i < indent; i++){
                printf(" ");
            }
        }
        printf("%s\n", p->symbol);
        if (p->left){
            treePostOrder(p->left, indent + 4);
        }
        if (p->right){
            treePostOrder(p->right, indent + 4);
        }
    }
}
int nSum(int n) 
{ 
    // base condition to terminate the recursion when N = 0 
    if (n == 0) { 
        return 0; 
    } 
  
    // recursive case / recursive call 
    int res = n + nSum(n - 1); 
  
    return res; 
} 


/* TreeExp *search(TreeExp *beg, char* data){ */
/*     bool finded = false; */
/*     TreeExp *tmp = beg; */
/*     TreeExp *ans = NULL; */

/*     while(tmp != NULL && finded == false){ */
/*         if(strcmp(data, tmp->symbol) == 0){ */
/*             finded = true; */
/*             ans = tmp; */
/*         } */
/*         tmp = tmp->right; */
/*     } */
/*     return ans; */
/* } */

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
