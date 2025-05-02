#ifndef DESC_H_INCLUDED
#define DESC_H_INCLUDED

// Структура узла списка
typedef struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
} Node;

// Структура циклического двусвязного списка
typedef struct {
    Node* current;
    int size;
} CyclicList;

void init_list(CyclicList* list);
int is_empty(const CyclicList* list);
void move_next(CyclicList* list);
void move_prev(CyclicList* list);
void insert_after(CyclicList* list, int value);
void insert_before(CyclicList* list, int value);
int remove_current(CyclicList* list);
void copy_list(const CyclicList* src, CyclicList* dest);
void display_list(const CyclicList* list);
void free_list(CyclicList* list);

#endif // DESC_H_INCLUDED
