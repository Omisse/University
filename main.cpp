/*
Структура данных: двусвязный циклический список, содержащий
элементы данных.
Операция: включение по заданному номеру.
Операция: поиск и возвращение элемента данных по заданному
номеру
*/

#include "my_list.hpp"

#include <iostream>

/*
используется весьма комплексный контейнер времён моей учёбы в школе21
он не тестировался в достаточной степени, чтобы считаться безопасным, 
но вроде работает.
*/

/*
В контейнер для данной ЛР добавлены методы insert_at() и at()
Что, в сущности, можно было бы сделать и унаследовав его...
*/


template <typename T>
void print_list(const prog_s3::list<T>& list) {
    for (auto i = list.cbegin(); i != list.cend(); i++) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
}


void print_title(const char* title) {
    std::cout << "\033[32m|\\/| " << title << " |\\/|\033[0m" << std::endl;
}

void print_closing(const char* title) {
    std::cout << "\033[32m|^^| " << title << " |^^|\033[0m" << std::endl;
}


void print_int() {
    print_title("Template container for int");
    prog_s3::list<int> list{1,2,3,4,5,6,7,8,9};
    std::cout << "Before insertion: " << std::endl;
    print_list(list);
    std::cout << "list.insert_at(552,777)" << std::endl;
    std::cout << "Expected: insertion at [3]" << std::endl;
    try {
        list.insert_at(552, 777);
    } catch(std::bad_alloc ex) {
        std::cerr << ex.what() << std::endl;
    }
    std::cout << "After insertion: " << std::endl;
    print_list(list);

    std::cout << std::endl << "list.at(3): " << list.at(3) << std::endl;
    print_closing("Template container for int");
}

void print_char() {
    print_title("Template container for char");
    prog_s3::list<char> list{'s','i','z','e'};
    std::cout << "Before insertion: " << std::endl;
    print_list(list);
    std::cout << "list.insert_at(8, 'd')" << std::endl;
    std::cout << "Expected: insertion at [4]" << std::endl;
    try {
        list.insert_at(8, 'd');
    } catch(std::bad_alloc ex) {
        std::cerr << ex.what() << std::endl;
    }
    std::cout << "After insertion: " << std::endl;
    print_list(list);
    std::cout << "list.insert_at(0, 'r')" << std::endl;
    std::cout << "list.insert_at(1, 'e')" << std::endl;
    std::cout << "Expected: insertion of {r,e} at [0] and [1]" << std::endl;
    try {
        list.insert_at(0, 'r');
        list.insert_at(1, 'e');
    } catch(std::bad_alloc ex) {
        std::cerr << ex.what() << std::endl;
    }
    std::cout << "After insertion: " << std::endl;
    print_list(list);

    std::cout << std::endl << "list.at(34): " << list.at(34) << std::endl;

    print_closing("Template container for char");
}

int main() {
    print_int();
    print_char();
    return 0;
}