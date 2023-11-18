#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Variable{
    int type;
    char* name;
    char* value;
    struct Variable *next;
} Variable;

// Inicializar los punteros
int listInit(Variable **beg, Variable **end){
    // El puntero principal para localizar y recorrer la lista
    *beg = NULL;
    *end = NULL;
    return 0;
    }

Variable* listAppend(){
    // apuntador temporal para crear el nodo
    Variable *tmp;
    Variable *p = malloc(sizeof(Variable));
    tmp = malloc(sizeof(Variable));
    return tmp;
}

Variable* listFill(Variable *tmp, int type, char* name){

    // rellena el nodo
    tmp->type = type;
    tmp->name = name;
    tmp->next = NULL;

    return tmp;
}

int listFirst(Variable **beg, Variable **end, Variable *tmp){
    // el caso es del primer nodo
    // se crean los enlaces, el nodo es el primero y el
    // último
    *beg = tmp;
    *end = tmp;
    return 0;
}

int listLink(Variable **end, Variable *tmp) {
    // se derenferencia a la dirección de memoria para poder
    // acceder a la información del nodo
    Variable *last = *end;
    // se enlaza el nuevo nodo con el que estaba al
    // último
    last->next = tmp;
    
    // la dirección del nodo final (la dirección de un
    // puntero) es la que se utiliza para actualizar el
    // final de la lista
    *end = tmp;
    return 0;
}

void listPrintVariable(Variable *tmp){
    printf("\t%i, \t%s \t%s\n",
           tmp->type, tmp->name, tmp->value);
    /* printf("%p, \t%i, \t%s \t%p\n", */
           /* tmp, tmp->type, tmp->name, tmp->next); */
}

int listPrint(Variable *beg, Variable *end){
    // se crea un puntero temporal para recorrer la
    // lista
    Variable *tmp;
    tmp = beg;
    while(tmp != NULL){
        listPrintVariable(tmp);
        tmp = tmp->next;
    }
    
    return 0;
}

Variable* listSearch(Variable *beg, char* name){
    bool finded = false;
    Variable *tmp = beg;
    Variable *ans = NULL;

    while(tmp != NULL && finded == false){
        if(strcmp(tmp->name, name) == 0){
            /* printf("\t%s vs  %s\n", tmp->name, name); */
            finded = true;
            ans = tmp;
        }
        tmp = tmp->next;
    }
    return ans;
}

int variableAssign(Variable* beg, char* name, char* value){
    Variable* var = listSearch(beg, name);
    if (var != NULL){
        var->value = value;
    }
}


int listDeleteVariable(Variable *victim){
    return 0;
}

/* int main(void){ */
/*     Variable *beg, *end; */
/*     listInit(&beg, &end); */

/*     for(int i = 0; i < 20; i++){ */
/*         Variable *tmp = listFill(listAppend(), i, "int"); */
/*             if(beg == NULL){ */
/*                     listFirst(&beg, &end, tmp); */
/*             } else{ */
/*                 listLink(&end, tmp); */
/*             } */
/*     } */
/*     listPrint(beg, end); */

/*     Variable *ans = listSearch(beg, "a"); */
/*     if(ans != NULL){ */
/*         printf("\n"); */
/*         listPrintVariable(ans); */
/*     } */

/*     return 0; */
/* } */
