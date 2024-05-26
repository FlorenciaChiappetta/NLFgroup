#include <stdlib.h>
#include <stdio.h>
#include "Lista.h"


node *new_empty_node();

//getter para linkedlist
node *list_get(list *linkedList, int index);


//Crea una nueva lista
list *new_empty_list() {
    list *linkedList = malloc(sizeof(linkedList));
    if (linkedList != NULL) {
        linkedList->head = new_empty_node();
        linkedList->length = 0;
    }

    return linkedList;  
}

// Crea un nuevo nodo
node *new_empty_node() {
    node *nodo = malloc(sizeof(node));
    if (nodo != NULL) {
        nodo->data = NULL;
        nodo->next = NULL;
    }

    return nodo;
}

//Inicializa una lista nueva
list *new_list(void *data) {
    list *linkedList = new_empty_list();
    list_add(linkedList, data);
    return linkedList;
}

//metodo para agregar un nodo a la lista
void list_add(list *linkedList, void *data) {

    if (linkedList == NULL || data == NULL)
        return;

    node *aux = linkedList->head;
    while (aux->next != NULL) {
        aux = aux->next;
    }

    aux->next = new_empty_node();
    aux->data = data;
    linkedList->length += 1;
}

//metodo para devolver la longitud de la lista
int list_length(list *linkedList) {
    return linkedList->length;
}

//metodo para devolver valor de un nodo por la posiciòn 
void *list_get_value(list *linkedList, int index) {
    node *pNode = list_get(linkedList, index);
    if (pNode == NULL)
        return NULL;

    return pNode->data;
}

//devuelve un puntero al dato del nodo sino devuelve null
 void *list_get_data(list *linkedList, void *data, size_t data_size) {
    if (linkedList == NULL || linkedList->head == NULL || linkedList->length == 0 || data == NULL || data_size <= 0) {
        return NULL;
    }

    node *pNode = NULL;
    node *actual = linkedList->head;
    while (actual != NULL && actual->data != NULL) {
            //Compara los bytes de los buffers.
        if (memcmp(actual->data, data, data_size) == 0) {
            pNode = actual;
            break;
        }

        actual = actual->next;
    }

    if (pNode != NULL) {
        return pNode->data;
    }

    return NULL;
}

//


//Me permite buscar informaciòn dentro de la lista. recibe puntero a la lista, 
//puntero a la funciòn de busqueda y el valor que necesitamos buscar
void *list_search_data(list *linkedList, int (*search_function)(void *data, void *other_data), void *other_data) {
    if (linkedList == NULL || linkedList->head == NULL || search_function == NULL || other_data == NULL)
        return NULL;

    node *itr_node = linkedList->head;
    while (itr_node != NULL && itr_node->data != NULL && !search_function(itr_node->data, other_data)) {
        itr_node = itr_node->next;
    }

    if (itr_node != NULL && itr_node->data != NULL && search_function(itr_node->data, other_data))
        return itr_node->data;

    return NULL;
}

//devuelve el nodo de la posicion indicada
node *list_get(list *linkedList, int index) {
    if (linkedList == NULL || linkedList->head == NULL || linkedList->length == 0 || index < 0 || index >= linkedList->length) {
        return NULL;
    }

    node *aux = linkedList->head;
    for (int i = 0; i < index && aux->next != NULL; ++i) {
        aux = aux->next;
    }
    return aux;
}
// valida si el dato existe en la lista, si no existe retorna 0
int list_contains(list *linkedList, int (*search_function)(void *data, void *other_data), void *other_data) {
    if (linkedList == NULL || linkedList->head == NULL || linkedList->length == 0 || search_function == NULL || other_data == NULL) {
        return 0;
    }

    return list_search_data(linkedList, search_function, other_data) != NULL;
}

//elimina nodo
int list_remove(list *linkedList, int index) {
    if (linkedList == NULL || linkedList->head == NULL || linkedList->length == 0 || index < 0 || index >= linkedList->length) {
        return -1;
    }

    node *node_remove;
    if (index == 0) {
        node_remove = linkedList->head;
        linkedList->head = linkedList->head->next;
    } else {
        node *change_prev_node = list_get(linkedList, index - 1);
        node_remove = change_prev_node->next;
        change_prev_node->next = node_remove->next;
    }

    free(node_remove);
    linkedList->length -= 1;
    return 0;
}

// permite borrar un nodo a partir de la informaciòn que busca

int list_remove_data(list *linkedList, void *data, size_t data_size) {
    if (linkedList == NULL || linkedList->head == NULL || linkedList->length == 0 || data == NULL || data_size <= 0) {
        return -1;
    }

    node **pNode = &linkedList->head;
    while ((*pNode)->next != NULL && memcmp((*pNode)->data, data, data_size) != 0) {
        pNode = &(*pNode)->next;
    }

    node *node_remove = *pNode;
    *pNode = (*pNode)->next;
    free(node_remove);
    linkedList->length -= 1;
    return 0;
}

