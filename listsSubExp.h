#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct SubExp{
    char* symbol;
    TreeExp* link;
    struct SubExp *left, *right;
} SubExp;

// Inicializar los punteros
int dlistInit(SubExp **beg, SubExp **end){
    // El puntero principal para localizar y recorrer la lista
    *beg = NULL;
    *end = NULL;
    return 0;
}

SubExp* dlistNewNode(){
    // apuntador temporal para crear el nodo
    SubExp *tmp;
    SubExp *p = malloc(sizeof(SubExp));
    tmp = malloc(sizeof(SubExp));
    return tmp;
}

SubExp* dlistFill(SubExp *tmp, char* symbol){
    // rellena el nodo
    tmp->symbol = strdup(symbol);
    tmp->link = NULL;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

// enlazar un campo de la lista con su subárbol
void dlistChangeLink(SubExp **tmp, TreeExp *tree){
    (*tmp)->link = tree;
}

int dlistFirst(SubExp **beg, SubExp **end, SubExp *tmp){
    // el caso es del primer nodo
    // se crean los enlaces, el nodo es el primero y el
    // último
    *beg = tmp;
    *end = tmp;
    return 0;
}

int dlistAppendEnd(SubExp **end, SubExp *tmp) {
    // se crea una copia del último noodo, que va a terminar siendo
    // el penúltimo
    SubExp *last = *end;
    
    // se liga el nuevo nodo a la lista
    tmp->left = *end;
    tmp->right = NULL;
    last->right = tmp;

    // se actualizan los punteros de la lista
    *end = tmp;
    
    return 0;
}

void dlistDeleteFirst(SubExp **first){
    /* printf("\t\ttengo esto: %p\n", *first); */
    if((*first) == NULL) return;
    SubExp *node = *first;

    // una alternativa a crear una variable extra *first
    *first = (*first)->right;
    (*first)->left = NULL;
    /* printf("\t\tahora es esto: %p\n", *first); */
    node->right = NULL;
}

void dlistDeleteNode(SubExp **first, SubExp *node){ 
    if(node == *first){
        dlistDeleteFirst(first);
        return;
    }
    
    SubExp *prev = node->left;
    SubExp *next = node->right;

    node->left->right = next;
    if(next != NULL){
        next->left = prev; 
    }

    node->left = NULL;
    node->right = NULL;
    free(node);
}

void dlistPrintFullNode(SubExp *tmp){
    printf("%p, \t%s en %p, \t%p", tmp->left, tmp->symbol, tmp,
           tmp->right);
    if(tmp->link != NULL){
        printf(" **\n");
    } else printf("\n");
}

int dlistFullPrint(SubExp *beg){
    // se crea un puntero temporal para recorrer la
    // lista
    SubExp *tmp;
    tmp = beg;
    while(tmp != NULL){
        dlistPrintFullNode(tmp);
        tmp = tmp->right;
    }
    
    return 0;
}

void dlistPrintNode(SubExp *tmp){
    printf("%s ", tmp->symbol);
}

int dlistPrint(SubExp *beg){
    // se crea un puntero temporal para recorrer la
    // lista
    SubExp *tmp;
    tmp = beg;
    while(tmp != NULL){
        dlistPrintNode(tmp);
        tmp = tmp->right;
    }
    printf("\n");
    
    return 0;
}

SubExp *search(SubExp *beg, char* data){
    bool finded = false;
    SubExp *tmp = beg;
    SubExp *ans = NULL;

    while(tmp != NULL && finded == false){
        if(strcmp(data, tmp->symbol) == 0){
            finded = true;
            ans = tmp;
        }
        tmp = tmp->right;
    }
    return ans;
}

int deleteSubExp(SubExp *victim){
    return 0;
}

/* int main(void){ */
/*     SubExp *beg, *end; */
/*     dlistInit(&beg, &end); */

/*     for(int i = 0; i < 20; i++){ */
/*         SubExp *tmp = dlistFill(dlistNewNode(), "a"); */
/*             if(beg == NULL){ */
/*                 dlistFirst(&beg, &end, tmp); */
/*             } else{ */
/*                 dlistAppendEnd(&end, tmp); */
/*             } */
/*     } */
/*     dlistPrint(beg, end); */

/*     SubExp *ans = search(beg, "b"); */
/*     if(ans != NULL){ */
/*         printf("\n"); */
/*         dlistPrintNode(ans); */
/*     } */

/*     return 0; */
/* } */
