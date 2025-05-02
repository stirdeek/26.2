#include <stdio.h>
#include <stdlib.h>
#include "desc.h"
// Инициализация списка
void init_list(CyclicList* list) {
    list->current = NULL;
    list->size = 0;
}

// Проверка на пустоту списка
int is_empty(const CyclicList* list) {
    return list->current == NULL;
}

// Переход к следующему элементу
void move_next(CyclicList* list) {
    if (!is_empty(list)) {
        list->current = list->current->next;
    }
}

// Переход к предыдущему элементу
void move_prev(CyclicList* list) {
    if (!is_empty(list)) {
        list->current = list->current->prev;
    }
}

// Вставка элемента после текущего
void insert_after(CyclicList* list, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;

    if (is_empty(list)) {
        new_node->next = new_node;
        new_node->prev = new_node;
        list->current = new_node;
    } else {
        new_node->next = list->current->next;
        new_node->prev = list->current;
        list->current->next->prev = new_node;
        list->current->next = new_node;
    }

    list->size++;
}

// Вставка элемента перед текущим
void insert_before(CyclicList* list, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;

    if (is_empty(list)) {
        new_node->next = new_node;
        new_node->prev = new_node;
        list->current = new_node;
    } else {
        new_node->prev = list->current->prev;
        new_node->next = list->current;
        list->current->prev->next = new_node;
        list->current->prev = new_node;
    }

    list->size++;
}

// Удаление текущего элемента
int remove_current(CyclicList* list) {
    if (is_empty(list)) {
        return -1;
    }

    int removed_value = list->current->value;

    if (list->size == 1) {
        free(list->current);
        list->current = NULL;
    } else {
        Node* prev_node = list->current->prev;
        Node* next_node = list->current->next;

        prev_node->next = next_node;
        next_node->prev = prev_node;

        free(list->current);
        list->current = next_node;
    }

    list->size--;
    return removed_value;
}

// Создание копии списка
void copy_list(const CyclicList* src, CyclicList* dest) {
    if (!is_empty(dest)) {
        free_list(dest);
    }
    init_list(dest);

    if (is_empty(src)) {
        return;
    }

    Node* original_current = src->current;

    for (int i = 0; i < src->size; i++) {
        if (is_empty(dest)) {
            dest->current = (Node*)malloc(sizeof(Node));
            dest->current->value = original_current->value;
            dest->current->next = dest->current;
            dest->current->prev = dest->current;
        } else {
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->value = original_current->value;

            new_node->prev = dest->current->prev;
            new_node->next = dest->current;
            dest->current->prev->next = new_node;
            dest->current->prev = new_node;
        }

        dest->size++;
        original_current = original_current->next;
    }

    if (!is_empty(dest)) {
        dest->current = dest->current->next;
    }
}
// Вывод всех элементов списка
void display_list(const CyclicList* list) {
    if (is_empty(list)) {
        printf("Список пуст\n");
        return;
    }

    printf("Элементы списка (в порядке следования): ");
    Node* temp = list->current;

    for (int i = 0; i < list->size; i++) {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

// Освобождение памяти
void free_list(CyclicList* list) {
    if (is_empty(list)) {
        return;
    }

    Node* current = list->current;
    Node* next_node;

    for (int i = 0; i < list->size; i++) {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    list->current = NULL;
    list->size = 0;
}
