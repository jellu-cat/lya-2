#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "regex.h"
#include "symbol.h"
#include "listsVariables.h"
#include "treeSubExp.h"
#include "listsSubExp.h"
#include "errors.h"

Variable *variableList, *variableListEnd;

// Guarda en una lista dinámica todas las variables declaradas
// en una misma línea
void saveVars(char* type, char *token){
    char* firstName;
    char *delimiter = " ,;";
    // hace la verificación incluida de que no se trate de un salto
    // de línea
    token = strtok(NULL, delimiter);
    while (token != NULL && strcmp(token, "\n")) {
        // se copia el nombre a otro espacio de memoria para
        // evitar que cambie en un futuro, pues la variable
        // token va ligada a una función que cambia su valor
        // (strtok)
        char* copy = malloc(strlen(token) + 1);
        // se usa malloc para asegurar que se reserve un espacio de
        // memoria diferente
        strcpy(copy, token);

        int id = mapTypeNumber(type);
        Variable *tmp = listFill(listAppend(), id, copy);
        if (variableList == NULL) {
            listFirst(&variableList, &variableListEnd, tmp);
        } else {
            listLink(&variableListEnd, tmp);
        }
        token = strtok(NULL, delimiter);
    }
}

bool declarationLine(char* token){
    char* type;
    bool declaration;

    for (int i = 0; i < n_datatypes; i++) {
        if (strcmp(token, data_types[i].token) == 0) {
            declaration = true;
            type = token;
            saveVars(type, token);
            break;
        }
    }
    return declaration;
}

// guarda una expresión en una lista doble para futuras
// manipulaciones
// para facilitar el trabajo, se asume que cada token está
// separado por uno o más espacios
SubExp* saveSubExp(char* copy){
    char* token = strdup(copy);
    char* delimeter = " ";
    SubExp *list, *end;
    token = strtok(copy, delimeter);

    dlistInit(&list, &end);
    while(token != NULL){
        SubExp *tmp = dlistFill(dlistNewNode(), token);
        if(list == NULL){
            dlistFirst(&list, &end, tmp);
        } else {
            dlistAppendEnd(&end, tmp);
        }
        token = strtok(NULL, delimeter);
    }
    return list;
}

TreeExp* createLeftChild(SubExp *tmp){
    char* name;
    name = tmp->left->symbol;
    Variable* var = listSearch(variableList, name);
    int type;

    if(opSearch(name) != 0){
        if (var == NULL) {
            printf("(!!) La variable \"%s\" no existe.\n", name);
            if(isNumber(name) != 0){
                return NULL;
            }
        } else type = var->type;
    }
    else {
    }
    TreeExp *left;
    if (tmp->left->link != NULL) {
        left = tmp->left->link;
    } else {
        left = treeFill(treeNew(), tmp->left->symbol, type);
    }
    /* treePrintNode(left); */
    return left;
}

TreeExp* createRightChild(SubExp *tmp){
    char* name;
    name = tmp->right->symbol;
    Variable* var = listSearch(variableList, name);
    int type;

    if(opSearch(name) != 0){
        if (var == NULL) {
            printf("(!!) La variable \"%s\" no existe.\n", name);
            if(isNumber(name) != 0){
                return NULL;
            }
        } else type = var->type;
    }

    TreeExp *right;
    if (tmp->right->link != NULL) {
        right = tmp->right->link;
    } else {
        right = treeFill(treeNew(), tmp->right->symbol, type);
    }
    /* treePrintNode(right); */
    return right;
}

TreeExp* createExpTree(SubExp** ref){
    SubExp* list = *ref;
    SubExp* tmp = NULL;
    TreeExp* root = NULL;
    treeInit(root);
    /* dlistFullPrint(list); */
    
    for(int i = 1; i < (MAX_OP + 1); i++){
        tmp = list;
        while (tmp != NULL) {
            if(getOpLevel(tmp->symbol) == i){
                TreeExp* subroot = NULL;
                treeInit(subroot);

                TreeExp* left = createLeftChild(tmp);
                TreeExp *right = createRightChild(tmp);
                subroot = treeRootFill(treeNew(), tmp->symbol,
                                       &right, &left);
                printf("------\n");

                dlistChangeLink(&tmp, subroot);
                dlistDeleteNode(ref, tmp->left);
                dlistDeleteNode(ref, tmp->right);

                subroot->type = handleOperations(subroot);
                root = subroot;
            }
            tmp = tmp->right;
        }
    }
    return root;
}

// cualquier otra línea que no sea de declaración de variables,
// es tratada como una línea en la cual se hace una operación
void operationLine(char* line){
    SubExp *list, *end;
    char* delimiter = ";";
    char* copy = strdup(line);
    printf("%s", line);
    copy = strtok(copy, delimiter);

    list = saveSubExp(strdup(copy));
    // dlistPrint(list);
    TreeExp* root = createExpTree(&list);
    treeInOrder(root, 0);
    printf("\n");
    if(strcmp(root->symbol, "=") == 0){
        if(handleAssign(root) == 0){
            char* name = root->left->symbol;
            printf("asignar 0 a %s\n", name);
            variableAssign(variableList, name, "0");
        }
    }

}

int main(int argc, char *argv[]) {
    FILE *f;
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    char *string = argv[1];
    int exit = 1;

    if(argc == 2){
        f = fopen(argv[1], "r");
        if(!f){
            exit = 1;
        }
        else {
            exit = 0;
            const char *delimiter = " ";
            char *token;
            listInit(&variableList, &variableListEnd);

            while ((read = getline(&line, &len, f)) != -1) {
                char* copy = strdup(line);
                token = strtok(copy, delimiter);
                if(declarationLine(token) == false){
                    operationLine(line);
                }
                printf("------------\n");
            }
            listPrint(variableList, variableListEnd);
        }
    }
    free(line);
    return exit;
}
