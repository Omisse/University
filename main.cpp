#include "student_data.h"
#include <iostream>

void print_valid_example(s3l1::StudentData& data) {
    std::cout << std::endl << "-= SETTERS EXAMPLE [VALID] =-" << std::endl;
    std::cout << "\tSET: Last name: Zaharov" << std::endl;
    std::cout << "\tSET: Age: 33" << std::endl;
    std::cout << "\tSET: Average score: 68.8" << std::endl << std::endl;

    data.set_last_name("Zaharov");
    data.set_age(33);
    data.set_average_score(68.8);
    data.print_data();

    std::cout << "=-SETTERS EXAMPLE [VALID] END-=" << std::endl;
}

void print_invalid_example(s3l1::StudentData& data) {
    std::cout << std::endl << "-= SETTERS EXAMPLE [INVALID] =-" << std::endl;
    std::cout << "\tSET: Last name: \"\"" << std::endl;
    std::cout << "\tSET: Age: -6" << std::endl;
    std::cout << "\tSET: Average score: -88.5" << std::endl << std::endl;

    data.set_last_name("");
    data.set_age(-6);
    data.set_average_score(-88.5);
    data.print_data();
    std::cout << "=-SETTERS EXAMPLE [INVALID] END-=" << std::endl;
}

s3l1::StudentData setup_copy() {
    s3l1::StudentData source{"Ryazantsev", 24, 96.3};
    s3l1::StudentData dest = source;
    return dest;
}

void print_simple_part() {
    s3l1::StudentData student_simple{};
    std::cout << std::endl << "Simple constructor result: " << std::endl;
    student_simple.print_data();
    print_valid_example(student_simple);
    print_invalid_example(student_simple);
}

void print_various_constructors_part() {
    s3l1::StudentData student_all_fields{"Ryazantsev", 24, 96.3};
    std::cout << std::endl << "Fields-defined constructor result: " << std::endl;
    student_all_fields.print_data();

    std::cout << std::endl << "Incorrect values constructor result: " << std::endl;
    s3l1::StudentData student_incorrect{"", -444, -3.2};
    student_incorrect.print_data();

    std::cout << std::endl << "Copy constructor result: (copying Ryazantsev)" << std::endl;
    /*
    Чтобы показать копирование значения, а не поинтера,
    вызываю отдельную функцию, по истечении которой исходник удалится.
    */
    s3l1::StudentData student_copied = setup_copy();
    student_copied.print_data();

    std::cout << std::endl << "Move constructor result (moving Ryazantsev copy to incorrect)" << std::endl;
    s3l1::StudentData student_moved = std::move(student_all_fields);
    std::cout << "Destination: " << std::endl;
    student_moved.print_data();
    std::cout << "Source: (will be deleted after function's return)" << std::endl;
    student_all_fields.print_data();
}

void print_getters() {
    s3l1::StudentData student{"Ryazantsev", 24, 96.3};
    std::cout << std::endl << "-=GETTERS EXAMPLE=-" << std::endl;
    student.print_data();
    std::cout << std::endl;

    std::cout << "student.get_last_name(): " << student.get_last_name() << std::endl;
    std::cout << "student.get_age(): " << student.get_age() << std::endl;
    std::cout << "student.get_average_score(): " << student.get_average_score() << std::endl;
    std::cout << "=-GETTERS EXAMPLE [END]-=" << std::endl;
}

void print_prints() {
    s3l1::StudentData student{"Ryazantsev", 24, 96.3};
    std::cout << std::endl << "-=PRINTS EXAMPLE=-" << std::endl;

    std::cout << "student.print_data():" << std::endl;
    student.print_data();
    std::cout << "student.print_last_name():" << std::endl;
    student.print_last_name();
    std::cout << "student.print_age():" << std::endl;
    student.print_age();
    std::cout << "student.print_average_score():" << std::endl;
    student.print_average_score();
    
    std::cout << "=-PRINTS EXAMPLE [END]-=" << std::endl;
}

int main(void) {
    print_simple_part();
    print_various_constructors_part();
    print_getters();
    print_prints();

    s3l1::StudentData data("Ryazantsev", 24, 96.3);
    const char* smth = data;
    std::cout << data << std::endl;

    return 0;
}