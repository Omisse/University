#include <stdlib.h>
#include <stdio.h>

#include "list.h"

//добавление элемента в конец списка
void list_push_back(int value, list** head)
{
    if (!head) return; //некорректные данные, выход
    list* ptr = *head; //служебные указатели
    list* prev = 0;
    while (ptr)
    { //движение в конец списка
        prev = ptr;
        ptr = ptr->next;
    }
    ptr = malloc(sizeof(list)); //выделение памяти
    *ptr = (list){value, 0}; //инициализация
    if (prev) prev->next = ptr; //если есть прошлый элемент
    else *head = ptr; //иначе - мы в начале списка
    return;
}

//добавление элемента в начало списка
void list_insert(int value, list** head)
{
    if (!head) return; //некорректные данные, выход
    list* temp = malloc(sizeof(list)); //выделение памяти
    *temp = (list) {value, *head};//инициализация
    *head = temp; //добавление в список
}

//освобождение памяти под список
void list_dealloc(list** head)
{
    if (!head) return; //некорректные данные, выход
    if (!*head) return; //конец списка(или его просто нет)
    list_dealloc(&((*head)->next)); //рекурсивный вызов для следующего элемента
    free(*head); //очистка памяти
    *head = 0; //зануление, на случай если *head будет переиспользован
    return;
}

//вывод списка в поток stdout
void list_print(const list* head)
{
    if (!head) return; //некорректные данные, выход
    printf("%d ", head->value); //вывод значения
    list_print(head->next); //рекурсивный вызов для следующего элемента
    return;
}

//чтение списка из бинарного файла
int list_get_from_file(const char* path, list** head)
{
    int buffer; //новый элемент списка
    FILE* file = fopen(path, "rb"); //открываем бинарный файл на чтение
    if (!file) return 0; //файл не открылся, ошибка
    while(fread(&buffer, sizeof(int), 1, file))
    { //fread вернёт число считанных элементов, если 0 - значит, файл закончился или встречен некорректный формат(некратный 4)
        //пока что-то прочитано, записываем значение в конец списка
        list_push_back(buffer, head);
    }
    fclose(file); //закрываем поток.
    return 1;//1 == ошибок нет
}

//заполнение бинарного файла набором значений из списка.
int list_fill_file(const char* path, const list* head)
{
    FILE* file = fopen(path, "wb"); //открываем бинарный файл на чтение(содержимое будет стёрто)
    if (!file) return 0; //файл не открылся, ошибка
    while (head)
    {
        //запись значения в файл
        fwrite(&(head->value),sizeof(int), 1,file);
        //перемещение по списку
        head = head->next;
    }
    fclose(file); //закрываем поток
    return 1; //1 == ошибок нет
}

//получить адрес элемента с данным значением в списке
stacked_list* slist_get(int value, stacked_list* head)
{
    if (!head) return 0; //некорректные данные, выход
    if (head->value == value) return head; //если значение равно искомому - возвращаем адрес
    return slist_get(value, head->next); //рекурсивный вызов функции для следующего элемента (возвращаем результат)
}

//добавление элемента в начало списка (или, если он уже есть - увеличить кол-во на 1)
int slist_insert(int value, stacked_list** head)
{
    if (!head) return 0;//некорректные данные, выход
    stacked_list* elem = slist_get(value, *head);//если существует, получит адрес
    if (elem) elem->amount++; //если есть адрес, количество++
    else
    { //если нет такого элемента
        elem = malloc(sizeof(stacked_list)); //выделяем память
        *elem = (stacked_list){value, 1, *head}; //инициализация
        *head = elem; //добавление в начало списка
    }
    return 1; //1 == ошибок нет
}

int slist_add_s(int value, stacked_list** head, int is_raising)
{
    if (!head) return 0; //некорректные данные, выход
    stacked_list* ptr = *head, *prev = 0; //объявляем и инициализируем служебные переменные
    //если список пустой или такой элемент есть, сразу добавляем
    if (!ptr || slist_get(value, ptr)) return slist_insert(value, head);
    //иначе, начинаем искать место для элемента
    while (ptr //пока не дошли до конца
        //и (по возрастанию) значение элемента меньше входного
        && (((ptr->value < value) && is_raising)
        //или (по убыванию) значение элемента больше входного
        || ((ptr->value > value) && !is_raising)))
    {
        prev = ptr; //запоминаем прошлый элемент
        ptr = ptr->next; //движемся по списку
    }
    //Либо нашли место, и ставим элемент на него, либо мы находимся в начале списка.
    slist_insert(value, &ptr);
    //Если не в начале - добавляем элемент в список "справа"
    if (prev) prev->next = ptr;
    //если в начале - добавляем "слева".
    else *head = ptr;
    return 1; //1 == ошибок нет
}

//конвертация списка в список с количеством вхождений
int list_to_slist_s(const list* src, stacked_list** dest, int is_raising) {
    int all_good = 1; //флаговая переменная, 1 == ошибок нет
    while(src && all_good) { //пока не в конце исходного списка и нет ошибок...
        all_good = slist_add_s(src->value, dest, is_raising); //добавляем в список с количеством элемент
        src = src->next; //движемся по исходному списку
    }
    return all_good;
}

//вывод списка с количеством вхождений в формате <значение>[<количество>]...
void slist_print(const stacked_list* head)
{
    if (!head) return; //списка нет или мы уже в конце, выход
    printf("%d[%d] ", head->value, head->amount); //вывод значения
    slist_print(head->next); //рекурсивный вызов для следующего элемента
    return;
}

//вывод элементов, где количество вхождений больше 1.
void slist_print_many(const stacked_list* head)
{
    if (!head) return; //списка нет или мы уже в конце, выход
    if (head->amount > 1) printf("%d ", head->value); //вывод значения
    slist_print_many(head->next); //рекурсивный вызов для следующего элемента
    return;
}

//освобождение памяти
void slist_dealloc(stacked_list** head) {
    if (!head) return; //некорректные данные, выход
    if (!*head) return; //конец списка, выход
    slist_dealloc(&((*head)->next)); //рекурсивный вызов для следующего элемента
    free(*head);//освобождение памяти
    *head = 0; //зануление для возможности переиспользования указателя
    return;
}
