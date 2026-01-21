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
    s3l1::StudentData dest(source);
    return dest;
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

void print_move_assignment() {
    print_title("Move assignment example");

    s3l1::StudentData s1("Ryazantsev", 24, 96.3);
    s3l1::StudentData s2("Zaharov", 33, 68.8);
    char buff[16];

    std::cout << "Start values" << std::endl;
    std::cout << "s1:" << std::endl;
    s1.print_data();
    std::cout << "s2:" << std::endl;
    s2.print_data();

    sprintf(buff, "%p", s1.get_last_name());
    std::cout << std::endl << "s1 name pointer: " << buff << std::endl;
    sprintf(buff, "%p", s2.get_last_name());
    std::cout << "s2 name pointer: " << buff << std::endl;
    
    std::cout << "s1 = std::move(s2)" << std::endl;
    s1 = std::move(s2);
    std::cout << "s1:" << std::endl;
    s1.print_data();
    std::cout << "s2:" << std::endl;
    s2.print_data();

    sprintf(buff, "%p", s1.get_last_name());
    std::cout << std::endl << "s1 name pointer: " << buff << std::endl;
    sprintf(buff, "%p", s2.get_last_name());
    std::cout << "s2 name pointer: " << buff << std::endl;
    
    print_closing("Move assignment example end");
}

void print_copy_assignment() {
    print_title("Copy assignment example");
    s3l1::StudentData s1("Ryazantsev", 24, 96.3);
    s3l1::StudentData s2("Zaharov", 33, 68.8);

    std::cout << "Start values" << std::endl;
    std::cout << "s1:" << std::endl;
    s1.print_data();
    std::cout << "s2:" << std::endl;
    s2.print_data();

    std::cout << "s1 = s2" << std::endl;
    s1 = s2;

    std::cout << "s1:" << std::endl;
    s1.print_data();
    std::cout << "s2:" << std::endl;
    s2.print_data();

    char buff[16];
    sprintf(buff, "%p", s1.get_last_name());
    std::cout << std::endl << "s1 name pointer: " << buff << std::endl;
    sprintf(buff, "%p", s2.get_last_name());
    std::cout << "s2 name pointer: " << buff << std::endl;
    print_closing("Copy assignment example end");
}

void print_assignment() {
    print_move_assignment();
    print_copy_assignment();

}

void print_increment() {
    print_title("Increments overloading example");
    s3l1::StudentData student("Ryazantsev", 24, 96.3);
    std::cout << "Start values: " << std::endl;
    student.print_data();
    std::cout << "\n(++student).print_data()" << std::endl;
    (++student).print_data();
    std::cout << "\n(student++).print_data()" << std::endl;
    (student++).print_data();
    std::cout << "\nEnd values:" << std::endl;
    student.print_data();
    print_closing("Increments overloading end");
}

void print_addition() {
    print_title("Addition overloading example");
    s3l1::StudentData student("Ryazantsev", 24, 96.3);
    std::cout << "Start values:" << std::endl;
    student.print_data();
    std::cout << "\nstudent = student+0.0" << std::endl;
    std::cout << "Expected: average score = (96.3+0.0)/2 = 48.15" << std::endl;
    student = student+0.0;
    student.print_data();
    std::cout << "\nstudent = student+55.4" << std::endl;
    std::cout << "Expected: average score = (96.3+55.4)/3 ~= 50.57" << std::endl;
    student = student+55.4;
    student.print_data();
    print_closing("Addition example end");
}

void print_subtraction() {
    print_title("Subtraction overloading example");
    s3l1::StudentData student("Ryazantsev", 24, 96.3);
    student = (student + 0.0) + 55.4;
    std::cout << "Start values:" << std::endl;
    student.print_data();

    std::cout << "\nstudent = student-0.0" << std::endl;
    std::cout << "Expected: average score = 50.57" << std::endl;
    student = student - 0.0;
    student.print_data();

    std::cout << "\nstudent = student - 15.52" << std::endl;
    std::cout << "Expected: average score = 35.05" << std::endl;
    student = student - 15.52;
    student.print_data();

    std::cout << "\nstudent = student - 88.3" << std::endl;
    std::cout << "Expected: average score = 0.0" << std::endl;
    student = student - 88.3;
    student.print_data();

    print_closing("Subtraction overloading end");
}

void print_conversion() {
    print_title("Implicit conversion overloading example");
    s3l1::StudentData student("Ryazantsev", 24, 96.3);
    std::cout << "Start values" << std::endl;
    student.print_data();

    std::cout << "std::cout << student << std::endl;" << std::endl;
    std::cout << "Expected: Implicit conversion of student object into JSON string" << std::endl;
    std::cout << student << std::endl;

    print_closing("Implicit conversion end");
}

int main(void) {
    print_simple_part();
    print_various_constructors_part();
    print_getters();
    print_prints();
    print_assignment();
    print_increment();
    print_addition();
    print_subtraction();
    print_conversion();
    return 0;
}