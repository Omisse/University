#ifndef LIST_H
#define LIST_H //защита от переопределения

//список
typedef struct list
{
    int value; //значение
    struct list* next; //служебная часть
}
list;

//список с подсчётом количества вхождений
typedef struct stacked_list
{
    int value; //значение
    int amount; //количество вхождений
    struct stacked_list* next; //служебная часть
}
stacked_list;

/*
функции описаны в файле с определениями.
*/

void list_push_back(int value, list** head);

void list_insert(int value, list** head);

void list_add_sorted(int value, list** head);

void list_dealloc(list** head);

void list_print(const list* head);

const list* list_contains(int value, const list* head);

int list_contains_amount(int value, const list* head);

int list_get_from_file(const char* path, list** head);

int list_fill_file(const char* path, const list* head);

stacked_list* slist_get(int value, stacked_list* head);

int slist_insert(int value, stacked_list** head);

int slist_add_s(int value, stacked_list** head, int is_raising);

int list_to_slist_s(const list* src, stacked_list** dest, int is_raising);

void slist_print(const stacked_list* head);

void slist_print_many(const stacked_list* head);

void slist_dealloc(stacked_list** head);

#endif