#include "student_data.h"
#include "student_data_budget.h"
#include "student_data_debt.h"

#include <fstream>
#include <iostream>

void print_title(const char* title) {
    std::cout << "\033[32m|\\/| " << title << " |\\/|\033[0m" << std::endl;
}

void print_closing(const char* title) {
    std::cout << "\033[32m|^^| " << title << " |^^|\033[0m" << std::endl;
}


void print_valid_example(prog_s3::StudentData& data) {
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

void print_invalid_example(prog_s3::StudentData& data) {
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

prog_s3::StudentData setup_copy() {
    prog_s3::StudentData source("Ryazantsev", 24, 96.3);
    prog_s3::StudentData dest(source);
    return dest;
}

void print_simple_part() {
    prog_s3::StudentData student_simple{};
    print_title("Simple constructor");
    student_simple.print_data();
    print_closing("Simple constructor end");
    print_valid_example(student_simple);
    print_invalid_example(student_simple);
}

void print_various_constructors_part() {
    print_title("Full constructor");
    prog_s3::StudentData student_all_fields("Ryazantsev", 24, 96.3);
    student_all_fields.print_data();
    print_closing("Full constructor end");

    print_title("Full constructor (invalid)");
    prog_s3::StudentData student_incorrect("", -444, -3.2);
    student_incorrect.print_data();
    print_closing("Full constructor (invalid) end");

    print_title("Copy constructor (Ryazantsev to new)");
    std::cout << "Original initialized out of scope and is deleted by this point" << std::endl;
    /*
    Чтобы показать копирование значения, а не поинтера,
    вызываю отдельную функцию, по истечении которой исходник удалится.
    */
    prog_s3::StudentData student_copied = setup_copy();
    student_copied.print_data();
    print_closing("Copy constructor end");

    print_title("Move constructor (From Ryazantsev)");
    prog_s3::StudentData student_moved = std::move(student_all_fields);
    std::cout << "Destination: " << std::endl;
    student_moved.print_data();
    std::cout << "Source: (will be deleted after function's return)" << std::endl;
    student_all_fields.print_data();
    print_closing("Move constructor end");
}

void print_getters() {
    print_title("Getters example");
    prog_s3::StudentData student("Ryazantsev", 24, 96.3);
    student.print_data();
    std::cout << std::endl;

    std::cout << "student.get_last_name(): " << student.get_last_name() << std::endl;
    std::cout << "student.get_age(): " << student.get_age() << std::endl;
    std::cout << "student.get_average_score(): " << student.get_average_score() << std::endl;
    print_closing("Getters example end");
}

void print_prints() {
    print_title("Print functions example");

    prog_s3::StudentData student("Ryazantsev", 24, 96.3);

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

    prog_s3::StudentData s1("Ryazantsev", 24, 96.3);
    prog_s3::StudentData s2("Zaharov", 33, 68.8);
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
    prog_s3::StudentData s1("Ryazantsev", 24, 96.3);
    prog_s3::StudentData s2("Zaharov", 33, 68.8);

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
    prog_s3::StudentData student("Ryazantsev", 24, 96.3);
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
    prog_s3::StudentData student("Ryazantsev", 24, 96.3);
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
    prog_s3::StudentData student("Ryazantsev", 24, 96.3);
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
    prog_s3::StudentData student("Ryazantsev", 24, 96.3);
    std::cout << "Start values" << std::endl;
    student.print_data();

    std::cout << "std::cout << student << std::endl;" << std::endl;
    std::cout << "Expected: Implicit conversion of student object into JSON string" << std::endl;
    std::cout << student << std::endl;

    print_closing("Implicit conversion end");
}

void print_files() {
    print_title("Outputting to files: data.txt, data.bin");
    prog_s3::StudentData student("Ryazantsev", 24, 96.3);
    std::ofstream text("data.txt", std::ios::out);
    if (text) {
        text << student;
        text.close();
    } else {
        std::cerr << "Cannot open file \"data.txt\" in write mode" << std::endl;
    }
    
    std::ofstream bin("data.bin", std::ofstream::out | std::ofstream::binary);
    if (bin) {
        bin << student.binary_mode(true);
        bin.close();    
    } else {
        std::cerr << "Cannot open file \"data.bin\" in write mode" << std::endl;
    }
    print_closing("Outputting to files end");
}

void load_from_binary() {
    print_title("Loading from binary: data.bin");
    prog_s3::StudentData new_student{};
    std::cout << "Before load: " << std::endl;
    new_student.print_data();
    std::ifstream bin("data.bin", std::ifstream::in | std::ifstream::binary);
    if (bin) {
        /*
        он может выбросить тут эксепшн аж из ofstream.read(),
        но эта ситуация произойдёт только если в самом ofstream
        __forced_unwind == true, чего у нас нет, а если бы было -
        ну, судя по названию, правильно было бы чтоб всё сломалось.
        */
        bin >> new_student;
        bin.close();
        std::cout << "After load: " << std::endl;
        new_student.print_data();
    } else {
        std::cerr << "Cannot open file \"data.bin\" in read mode. Does it exist?" << std::endl;
    }
    
    print_closing("Loading from binary end");
}

void print_file_io() {
    print_files();
    load_from_binary();
}

void print_constructors_budget() {
    print_title("Derived:Budget, constructors");
    std::cout << "Simple constructor" << std::endl;
    prog_s3::StudentDataBudget simple{};
    simple.print_data();

    std::cout << std::endl << "Full constructor" << std::endl;
    prog_s3::StudentDataBudget defined("Ryazantsev", 24, 96.3, 3);
    defined.print_data();

    std::cout << std::endl << "Copy constructor (default)" << std::endl;
    std::cout << "Source object:" << std::endl;
    defined.print_data();
    std::cout << "New object:" << std::endl;
    simple = prog_s3::StudentDataBudget(defined);
    simple.print_data();
    char buff[16];
    sprintf(buff, "%p", defined.get_last_name());
    std::cout << "Source name pointer: " << buff << std::endl;
    sprintf(buff, "%p", simple.get_last_name());
    std::cout << "New name pointer: " << buff << std::endl;

    std::cout << std::endl << "Copy constructor (base(derived))" << std::endl;
    std::cout << "Source object:" << std::endl;
    defined.print_data();
    std::cout << "New object:" << std::endl;
    prog_s3::StudentData base(defined);
    base.print_data();
    sprintf(buff, "%p", defined.get_last_name());
    std::cout << "Source name pointer: " << buff << std::endl;
    sprintf(buff, "%p", base.get_last_name());
    std::cout << "New name pointer: " << buff << std::endl;
    print_closing("Derived:Budget, constructors end");
}

void print_constructors_debt(){
    print_title("Derived:Debt, constructors");
    std::cout << "Simple constructor" << std::endl;
    prog_s3::StudentDataDebt simple{};
    simple.print_data();

    std::cout << std::endl << "Full constructor" << std::endl;
    prog_s3::StudentDataDebt defined("Ryazantsev", 24, 96.3, 3);
    defined.print_data();

    std::cout << std::endl << "Copy constructor (default)" << std::endl;
    std::cout << "Source object:" << std::endl;
    defined.print_data();
    std::cout << "New object:" << std::endl;
    simple = prog_s3::StudentDataDebt(defined);
    simple.print_data();
    char buff[16];
    sprintf(buff, "%p", defined.get_last_name());
    std::cout << "Source name pointer: " << buff << std::endl;
    sprintf(buff, "%p", simple.get_last_name());
    std::cout << "New name pointer: " << buff << std::endl;

    std::cout << std::endl << "Copy constructor (base(derived))" << std::endl;
    std::cout << "Source object:" << std::endl;
    defined.print_data();
    std::cout << "New object:" << std::endl;
    prog_s3::StudentData base(defined);
    base.print_data();
    sprintf(buff, "%p", defined.get_last_name());
    std::cout << "Source name pointer: " << buff << std::endl;
    sprintf(buff, "%p", base.get_last_name());
    std::cout << "New name pointer: " << buff << std::endl;

    print_closing("Derived:Debt, constructors end");
}

void print_derived_constructors() {
    print_constructors_debt();
    print_constructors_budget();
}

void print_virtuals_debt() {
    print_title("Derived:Debt, virtual example");
    prog_s3::StudentData parent("Ryazantsev", 24, 96.3);
    prog_s3::StudentDataDebt derived("Ryazantsev", 24, 96.3, 3);
    std::cout << "parent.get_json_string(): " << std::endl << parent.get_json_string() << std::endl;
    std::cout << "derived.get_json_string(): "  << std::endl << derived.get_json_string() << std::endl;
    std::cout << "((ParentClass*) &derived)->get_json_string() [[OVERRIDDEN]]:" << std::endl << ((prog_s3::StudentData*) &derived)->get_json_string() << std::endl;
    print_closing("Derived:Debt, virtual example end");
}

void print_virtuals_budget() {
    print_title("Derived:Budget, virtual example");
    prog_s3::StudentData parent("Ryazantsev", 24, 96.3);
    prog_s3::StudentDataBudget derived("Ryazantsev", 24, 96.3, 330.53);
    std::cout << "parent.get_json_string(): " << std::endl << parent.get_json_string() << std::endl;
    std::cout << "derived.get_json_string(): " << std::endl << derived.get_json_string() << std::endl;
    std::cout << "((ParentClass*) &derived)->get_json_string() [[OVERRIDDEN]]:" << std::endl << ((prog_s3::StudentData*) &derived)->get_json_string() << std::endl;
    print_closing("Derived:Budget, virtual example end");
}

void print_derived_virtuals() {
    print_virtuals_debt();
    print_virtuals_budget();
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
    print_file_io();
    print_derived_constructors();
    print_derived_virtuals();
    return 0;
}