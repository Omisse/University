#include <stdio.h>
#include <locale.h>

//вспомогательная функция смены значений местами.
void swap_values(char* ptr1, char* ptr2)
{
    char buff = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = buff;
    return;
}

//вывод перестановок
//source - указатель на начало строки, всегда
//locked_ptr - указатель на "зафиксированный" элемент
int print_permutations(char* const source, char* const locked_ptr) 
{
    char* move_ptr = locked_ptr; //указатель на адрес, начиная от текущего зафиксированного
    //если на входе что-то не так - вернём ошибку
    if (!source || !locked_ptr) return 0;
    
    //если служебный указатель дошёл до конца строки - выведем итоговую строку
    if (!*locked_ptr) printf("%s\n",source);
    //начиная с позиции служебного указателя(при первом вызове - 0, далее - по элементам строки)
    //пока строка не кончилась
    while (*move_ptr)
    {   
        //поменяем местами значения по указателям (при первом вызове ничего не изменится)
        swap_values(locked_ptr, move_ptr);
        //рекурсивный вызов со сдвигом постоянной позиции на 1 (позиции "зафиксированного" элемента)
        print_permutations(source, locked_ptr+1);
        //поменяем местами обратно для следующего вызова.
        swap_values(locked_ptr, move_ptr);
        //движемся по строке далее
        move_ptr++;
    }
    return 1;
}

int main() {
    setlocale(LC_ALL, "Russian");
    // BUFSIZ - директива препроцессора из библиотеки stdio, определяющая размер буфера потока.
    char user_input[BUFSIZ] = {0};
    printf("Введите символы, не более %d:\n", BUFSIZ);
    scanf("%s", user_input);
    //или fgets(user_input, BUFSIZ-1, stdin);
    print_permutations(user_input, user_input);
    return 0;
}