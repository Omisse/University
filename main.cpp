#include "student_data.h"
#include <iostream>


void print_title(const char* title) {
    std::cout << "\033[32m|\\/| " << title << " |\\/|\033[0m" << std::endl;
}

void print_closing(const char* title) {
    std::cout << "\033[32m|^^| " << title << " |^^|\033[0m" << std::endl;
}


void print_valid_example(s3l1::StudentData& data) {
    print_title("Setters example (valid)");
    std::cout << "\tSET: Last name: Zaharov" << std::endl;
    std::cout << "\tSET: Age: 33" << std::endl;
    std::cout << "\tSET: Average score: 68.8" << std::endl << std::endl;

    data.set_last_name("Zaharov");
    data.set_age(33);
    data.set_average_score(68.8);
    data.print_data();

    print_closing("Setters example (valid) end");
}

void print_invalid_example(s3l1::StudentData& data) {
    print_title("Setters example (invalid)");
    std::cout << "\tSET: Last name: \"\"" << std::endl;
    std::cout << "\tSET: Age: -6" << std::endl;
    std::cout << "\tSET: Average score: -88.5" << std::endl << std::endl;

    data.set_last_name("");
    data.set_age(-6);
    data.set_average_score(-88.5);
    data.print_data();
    print_closing("Setters example (invalid) end");
}

s3l1::StudentData setup_copy() {
    s3l1::StudentData source("Ryazantsev", 24, 96.3);
    return s3l1::StudentData(source);
}

void print_simple_part() {
    s3l1::StudentData student_simple{};
    print_title("Simple constructor");
    student_simple.print_data();
    print_closing("Simple constructor end");
    print_valid_example(student_simple);
    print_invalid_example(student_simple);
}

void print_various_constructors_part() {
    print_title("Full constructor");
    s3l1::StudentData student_all_fields("Ryazantsev", 24, 96.3);
    student_all_fields.print_data();
    print_closing("Full constructor end");

    print_title("Full constructor (invalid)");
    s3l1::StudentData student_incorrect("", -444, -3.2);
    student_incorrect.print_data();
    print_closing("Full constructor (invalid) end");

    print_title("Copy constructor (Ryazantsev to new)");
    std::cout << "Original initialized out of scope and is deleted by this point" << std::endl;
    /*
    Чтобы показать копирование значения, а не поинтера,
    вызываю отдельную функцию, по истечении которой исходник удалится.
    */
    s3l1::StudentData student_copied = setup_copy();
    student_copied.print_data();
    print_closing("Copy constructor end");

    print_title("Move constructor (From Ryazantsev)");
    s3l1::StudentData student_moved = std::move(student_all_fields);
    std::cout << "Destination: " << std::endl;
    student_moved.print_data();
    std::cout << "Source: (will be deleted after function's return)" << std::endl;
    student_all_fields.print_data();
    print_closing("Move constructor end");
}

void print_getters() {
    print_title("Getters example");
    s3l1::StudentData student("Ryazantsev", 24, 96.3);
    student.print_data();
    std::cout << std::endl;

    std::cout << "student.get_last_name(): " << student.get_last_name() << std::endl;
    std::cout << "student.get_age(): " << student.get_age() << std::endl;
    std::cout << "student.get_average_score(): " << student.get_average_score() << std::endl;
    print_closing("Getters example end");
}

void print_prints() {
    print_title("Print functions example");

    s3l1::StudentData student("Ryazantsev", 24, 96.3);

    std::cout << "student.print_data():" << std::endl;
    student.print_data();
    std::cout << "student.print_last_name():" << std::endl;
    student.print_last_name();
    std::cout << "student.print_age():" << std::endl;
    student.print_age();
    std::cout << "student.print_average_score():" << std::endl;
    student.print_average_score();
    
    print_closing("Print functions end");
}
int main(void) {
    print_simple_part();
    print_various_constructors_part();
    print_getters();
    print_prints();
    return 0;
}