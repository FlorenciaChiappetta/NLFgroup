#include <stdio.h>


//genero el tipo de dato para el nodo de la linkedList
typedef struct node {
    void *data;
    struct node *next;
} node;

//genero el tipo de dato para la linkedList con puntero a un NoDO
typedef struct linkedList {
    node *head;
    int length;
} list;

//metodos

linkedList *new_empty_list();

linkedList *new_list(void *data);

void list_add(linkedList *lista, void *data);

int list_length(linkedList *lista);

void *list_get_value(linkedList *lista, int index);

void *list_get_data(linkedList *lista, void *data, size_t data_size);

void *list_search_data(linkedList *lista, int (*search_function)(void *data, void *other_data), void *other_data);

int list_contains(linkedList *lista, int (*search_function)(void *data, void *other_data), void *other_data);

int list_remove(linkedList *lista, int index);

int list_remove_data(linkedList *lista, void *data, size_t data_size);

void list_print(linkedList *lista, void (*print_function)(void *), int number_records);

void list_destroy(linkedList *lista);