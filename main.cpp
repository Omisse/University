#include "student_data.h"
#include "student_data_budget.h"
#include "student_data_debt.h"
#include "data_list.h"

#include <fstream>
#include <iostream>
#include <new>
#include <stdexcept>


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
    /*
    тут не будет try/catch,
    поскольку дефолтный конструктор память не выделяет,
    а больше причин ругаться у него нет
    */
    prog_s3::StudentData student_simple{};
    print_title("Simple constructor");
    student_simple.print_data();
    print_closing("Simple constructor end");
    print_valid_example(student_simple);
    print_invalid_example(student_simple);
}

void print_various_constructors_part() {
    print_title("Full constructor");
    try {
        prog_s3::StudentData student_all_fields("Ryazantsev", 24, 96.3);
        student_all_fields.print_data();
    } catch (std::bad_alloc ex) {
        std::cout << "Full constructor: bad allocation" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
    print_closing("Full constructor end");
    
    
    print_title("Full constructor (invalid)");
    try {
        prog_s3::StudentData student_incorrect("", -444, -3.2);
        student_incorrect.print_data();
    } catch (std::bad_alloc ex) {
        std::cout << "Invalid constructor: bad allocation" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
    print_closing("Full constructor (invalid) end");
    

    print_title("Copy constructor (Ryazantsev to new)");
    /*
    Чтобы показать копирование значения, а не поинтера,
    вызываю отдельную функцию, по истечении которой исходник удалится.
    */
    try {
        prog_s3::StudentData student_copied = setup_copy();
        std::cout << "Original initialized out of scope and is deleted by this point" << std::endl;
        student_copied.print_data();
    } catch (std::bad_alloc ex) {
        std::cout << "Copy constructor: bad allocation" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
    print_closing("Copy constructor end");

    print_title("Move constructor (From Ryazantsev)");
    try {
        prog_s3::StudentData student_source("Ryazantsev", 24, 96.3);
        prog_s3::StudentData student_moved(std::move(student_source));
        std::cout << "Destination: " << std::endl;
        student_moved.print_data();
        std::cout << "Source: (will be deleted after function's return)" << std::endl;
        student_source.print_data();
    } catch (std::bad_alloc ex) {
        std::cout << "Move constructor: bad allocation" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
    print_closing("Move constructor end");
}

void print_getters() {
    print_title("Getters example");
    try {
        prog_s3::StudentData student("Ryazantsev", 24, 96.3);
        student.print_data();
        std::cout << std::endl;
        std::cout << "student.get_last_name(): " << student.get_last_name() << std::endl;
        std::cout << "student.get_age(): " << student.get_age() << std::endl;
        std::cout << "student.get_average_score(): " << student.get_average_score() << std::endl;
    } catch (std::bad_alloc ex) {
        std::cout << "print_getters() - bad allocation" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
    print_closing("Getters example end");
}

void print_prints() {
    print_title("Print functions example");
    try {
        prog_s3::StudentData student("Ryazantsev", 24, 96.3);
        std::cout << "student.print_data():" << std::endl;
        student.print_data();
        std::cout << "student.print_last_name():" << std::endl;
        student.print_last_name();
        std::cout << "student.print_age():" << std::endl;
        student.print_age();
        std::cout << "student.print_average_score():" << std::endl;
        student.print_average_score();
    } catch (std::bad_alloc ex) {
        std::cout << "print_prints() - bad allocation" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
    print_closing("Print functions end");
}

void print_move_assignment() {
    print_title("Move assignment example");
    //неохота совать всё в большой try/catch, сделаю поинтеры вовне скопа
    prog_s3::StudentData* s1ptr = NULL;
    prog_s3::StudentData* s2ptr = NULL;
    try {
        s1ptr = new prog_s3::StudentData("Ryazantsev", 24, 96.3);
        s2ptr = new prog_s3::StudentData("Zaharov", 33, 68.8);
    } catch (std::bad_alloc ex) {
        std::cout << "print_move_assignment() - bad alloc"
            << " during initialization" << std::endl;
        std::cerr << ex.what() << std::endl;
        if (s1ptr) delete s1ptr;
        if (s2ptr) delete s2ptr;
        print_closing("Move assignment example end");
        return;
    }
    char buff[16];

    std::cout << "Start values" << std::endl;
    std::cout << "s1:" << std::endl;
    s1ptr->print_data();
    std::cout << "s2:" << std::endl;
    s2ptr->print_data();

    sprintf(buff, "%p", s1ptr->get_last_name());
    std::cout << std::endl << "s1 name pointer: " << buff << std::endl;
    sprintf(buff, "%p", s2ptr->get_last_name());
    std::cout << "s2 name pointer: " << buff << std::endl;

    std::cout << "s1 = std::move(s2)" << std::endl;
    try {
        *s1ptr = std::move(*s2ptr);
    } catch (std::bad_alloc ex) {
        std::cout << "print_move_assignment() - bad alloc"
            << " during assignment" << std::endl;
        std::cerr << ex.what() << std::endl;
        if (s1ptr) delete s1ptr;
        if (s2ptr) delete s2ptr;
        print_closing("Move assignment example end");
        return;
    }
    
    std::cout << "s1:" << std::endl;
    s1ptr->print_data();
    std::cout << "s2:" << std::endl;
    s2ptr->print_data();

    sprintf(buff, "%p", s1ptr->get_last_name());
    std::cout << std::endl << "s1 name pointer: " << buff << std::endl;
    sprintf(buff, "%p", s2ptr->get_last_name());
    std::cout << "s2 name pointer: " << buff << std::endl;

    if (s1ptr) delete s1ptr;
    if (s2ptr) delete s2ptr;
    
    print_closing("Move assignment example end");
}

void print_copy_assignment() {
    print_title("Copy assignment example");
    prog_s3::StudentData* s1ptr = NULL;
    prog_s3::StudentData* s2ptr = NULL;
    try {
        s1ptr = new prog_s3::StudentData("Ryazantsev", 24, 96.3);
        s2ptr = new prog_s3::StudentData("Zaharov", 33, 68.8);
    } catch (std::bad_alloc ex) {
        std::cout << "print_copy_assignment() - bad alloc"
            << " during initialization" << std::endl;
        std::cerr << ex.what() << std::endl;
        if (s1ptr) delete s1ptr;
        if (s2ptr) delete s2ptr;
        print_closing("Copy assignment example end");
        return;
    }

    std::cout << "Start values" << std::endl;
    std::cout << "s1:" << std::endl;
    s1ptr->print_data();
    std::cout << "s2:" << std::endl;
    s2ptr->print_data();

    std::cout << "s1 = s2" << std::endl;
    try {
        *s1ptr = *s2ptr;
    } catch (std::bad_alloc ex) {
        std::cout << "print_copy_assignment() - bad alloc"
            << " during assignment" << std::endl;
        std::cerr << ex.what() << std::endl;
        if (s1ptr) delete s1ptr;
        if (s2ptr) delete s2ptr;
        print_closing("Copy assignment example end");
        return;
    }
    
    std::cout << "s1:" << std::endl;
    s1ptr->print_data();
    std::cout << "s2:" << std::endl;
    s2ptr->print_data();

    char buff[16];
    sprintf(buff, "%p", s1ptr->get_last_name());
    std::cout << std::endl << "s1 name pointer: " << buff << std::endl;
    sprintf(buff, "%p", s2ptr->get_last_name());
    std::cout << "s2 name pointer: " << buff << std::endl;

    if (s1ptr) delete s1ptr;
    if (s2ptr) delete s2ptr;

    print_closing("Copy assignment example end");
}

void print_assignment() {
    print_move_assignment();
    print_copy_assignment();

}

void print_increment() {
    print_title("Increments overloading example");
    try {
        prog_s3::StudentData student("Ryazantsev", 24, 96.3);
        std::cout << "Start values: " << std::endl;
        student.print_data();
        std::cout << "\n(++student).print_data()" << std::endl;
        (++student).print_data();
        std::cout << "\n(student++).print_data()" << std::endl;
        (student++).print_data();
        std::cout << "\nEnd values:" << std::endl;
        student.print_data();
    } catch (std::bad_alloc ex) {
        std::cout << "print_increment() - bad alloc" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
    print_closing("Increments overloading end");
}

void print_addition() {
    print_title("Addition overloading example");
    try {
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
    } catch (std::bad_alloc ex) {
        std::cout << "print_addition() - bad alloc" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
    print_closing("Addition example end");
}

void print_subtraction() {
    print_title("Subtraction overloading example");
    try {
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
    } catch (std::bad_alloc ex) {
        std::cout << "print_subtraction() - bad alloc" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
    
    print_closing("Subtraction overloading end");
}

void print_conversion() {
    print_title("Implicit conversion overloading example");
    try {
        prog_s3::StudentData student("Ryazantsev", 24, 96.3);
        std::cout << "Start values" << std::endl;
        student.print_data();

        std::cout << "std::cout << student << std::endl;" << std::endl;
        std::cout << "Expected: Implicit conversion of student object into JSON string" << std::endl;
        std::cout << student << std::endl;
    } catch (std::bad_alloc ex) {
        std::cout << "print_conversion() - bad alloc" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
    print_closing("Implicit conversion end");
}

void print_files() {
    print_title("Outputting to files: data.txt, data.bin");
    prog_s3::StudentData* sptr = NULL;
    try {
        sptr = new prog_s3::StudentData("Ryazantsev", 24, 96.3);
    } catch (std::bad_alloc ex) {
        std::cout << "print_files() - bad alloc on init" << std::endl;
        std::cerr << ex.what() << std::endl;
        if (sptr) delete sptr;
        return;
    }

    //iostream и производные по умолчанию не бросают исключения
    std::ofstream text("data.txt", std::ios::out);
    if (text.good()) {
        text << *sptr;
        text.close();
    } else {
        std::cerr << "Cannot open file \"data.txt\" in write mode" << std::endl;
    }
    
    std::ofstream bin("data.bin", std::ofstream::out | std::ofstream::binary);
    if (bin.good()) {
        bin << sptr->binary_mode(true);
        bin.close();    
    } else {
        std::cerr << "Cannot open file \"data.bin\" in write mode" << std::endl;
    }

    if (sptr) delete sptr;
    print_closing("Outputting to files end");
}

void load_from_binary() {
    print_title("Loading from binary: data.bin");
    prog_s3::StudentData new_student{};
    std::cout << "Before load: " << std::endl;
    new_student.print_data();

    //iostream и производные по умолчанию не бросают исключения
    std::ifstream bin("data.bin", std::ifstream::in | std::ifstream::binary);
    if (bin.good()) {
        try {
            bin >> new_student;
        } catch (std::bad_alloc ex) {
            std::cout << "load_from_binary() - bad alloc on loading" << std::endl;
            std::cerr << ex.what() << std::endl;
        }
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
    /*
        Это ужасная практика и мне стыдно,
        но дальнейшие конструкторы зависят от текущих,
        а переписывать - долго, и времени нет.
    */
    try {
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
    } catch (std::bad_alloc ex) {
        std::cout << "print_constructors_budget() - bad alloc" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
    
    print_closing("Derived:Budget, constructors end");
}

void print_constructors_debt(){
    print_title("Derived:Debt, constructors");
    /*
        Это ужасная практика и мне стыдно,
        но дальнейшие конструкторы зависят от текущих,
        а переписывать - долго, и времени нет.
    */
    try {
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
    } catch (std::bad_alloc ex) {
        std::cout << "print_constructors_debt() - bad alloc" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
    
    print_closing("Derived:Debt, constructors end");
}

void print_derived_constructors() {
    print_constructors_debt();
    print_constructors_budget();
}

void print_virtuals_debt() {
    print_title("Derived:Debt, virtual example");
    try {
        prog_s3::StudentData parent("Ryazantsev", 24, 96.3);
        prog_s3::StudentDataDebt derived("Ryazantsev", 24, 96.3, 3);
        std::cout << "parent.get_json_string(): " << std::endl << parent.get_json_string() << std::endl;
        std::cout << "derived.get_json_string(): "  << std::endl << derived.get_json_string() << std::endl;
        std::cout << "((ParentClass*) &derived)->get_json_string() [[OVERRIDDEN]]:" << std::endl << ((prog_s3::StudentData*) &derived)->get_json_string() << std::endl;
    } catch (std::bad_alloc ex) {
        std::cout << "print_virtuals_debt() - bad alloc on init" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
    
    print_closing("Derived:Debt, virtual example end");
}

void print_virtuals_budget() {
    print_title("Derived:Budget, virtual example");
    try {
        prog_s3::StudentData parent("Ryazantsev", 24, 96.3);
        prog_s3::StudentDataBudget derived("Ryazantsev", 24, 96.3, 330.53);
        std::cout << "parent.get_json_string(): " << std::endl << parent.get_json_string() << std::endl;
        std::cout << "derived.get_json_string(): " << std::endl << derived.get_json_string() << std::endl;
        std::cout << "((ParentClass*) &derived)->get_json_string() [[OVERRIDDEN]]:" << std::endl << ((prog_s3::StudentData*) &derived)->get_json_string() << std::endl;
    } catch (std::bad_alloc ex) {
        std::cout << "print_virtuals_budget() - bad alloc on init" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
    print_closing("Derived:Budget, virtual example end");
}

void print_derived_virtuals() {
    print_virtuals_debt();
    print_virtuals_budget();
}

void print_polymorphic() {
    print_title("Simple StudentData container");
    prog_s3::DataList my_list{};
    std::cout << "List contents: " << std::endl;
    prog_s3::StudentData* simple_ptr{0};
    prog_s3::StudentDataDebt* debt_ptr{0};
    prog_s3::StudentDataBudget* budget_ptr{0};
    try {
        simple_ptr = new prog_s3::StudentData("SData", 33, 3.3);
        debt_ptr = new prog_s3::StudentDataDebt("SDataDebt", 66, 66.67, 66);
        budget_ptr = new prog_s3::StudentDataBudget("SDataBudget", 100, 99.99, 9999.99);
    } catch (std::bad_alloc ex) {
        std::cout << "print_polymorphic() - bad alloc on init" << std::endl;
        std::cerr << ex.what() << std::endl;
        if (simple_ptr) delete simple_ptr;
        if (debt_ptr) delete debt_ptr;
        if (budget_ptr) delete budget_ptr;
        print_closing("Simple StudentData container end");
        return;
    }
     
    std::cout << "Expected pos: 0 ";
    simple_ptr->print_data();
    std::cout << "Expected pos: 1 ";
    debt_ptr->print_data();
    std::cout << "Expected pos: 2 ";
    budget_ptr->print_data();
    /*
    push_front просто будет для процессора дешевле,
    так что сделаю им, но в обратном порядке
    */
    try {
        my_list.push_front(*budget_ptr);
        my_list.push_front(*debt_ptr);
        my_list.push_front(*simple_ptr);
    } catch (std::bad_alloc ex) {
        std::cout << "print_polymorphic() - bad alloc on list.push_front()" << std::endl;
        std::cerr << ex.what() << std::endl;
        if (simple_ptr) delete simple_ptr;
        if (debt_ptr) delete debt_ptr;
        if (budget_ptr) delete budget_ptr;
        print_closing("Simple StudentData container end");
        return;
    }

    //они нам просто больше не нужны
    if (simple_ptr) delete simple_ptr;
    if (debt_ptr) delete debt_ptr;
    if (budget_ptr) delete budget_ptr;

    std::cout << "List structure: " << std::endl;
    my_list.print_structure();
    
    print_title("Polymorphic behaviour example");
    try {
        std::cout << "my_list.get(0)->print_data(): " << std::endl;
        my_list.get(0)->print_data();
        std::cout << "my_list.get(1)->print_data(): " << std::endl;
        my_list.get(1)->print_data();
        std::cout << "my_list.get(2)->print_data(): " << std::endl;
        my_list.get(2)->print_data();
    } catch (std::out_of_range ex) {
        std::cout << "print_polymorphic() - out of range on list.get()" << std::endl;
        std::cerr << ex.what() << std::endl;
    }
    
    print_closing("Polymorphism example end");
    print_closing("Simple StudentData container end");
}

void print_exception() {
    print_title("Exceptions example");
    prog_s3::DataList list;
    std::cout << "Trying: DataList{}.get(64):  ";
    try {
        list.get(64);
        std::cout << "Success, somehow" << std::endl;
    } catch (std::out_of_range ex) {
        std::cout << "std::out_of_range caught!" << std::endl;
        std::cerr << "\t" << ex.what() << std::endl;
    }

    std::cout << "Trying: DataList{}.remove_at(0):  ";
    try { 
        list.remove_at(0);
        std::cout << "Removed nothing, what a miracle" << std::endl;
    } catch (std::out_of_range ex) {
        std::cout << "std::out_of_range caught!" << std::endl;
        std::cerr << "\t" << ex.what() << std::endl;
    }
    print_closing("Exceptions example");
}


int main(void) {
    try {
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
        print_polymorphic();
        print_exception();
    } catch (std::bad_alloc ex) {
        /*
        в целом, каждый момент аллокации и так обёрнут в свой,
        но если мы забыли или не знали - тут хоть поймает.
        */
        std::cerr << ex.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "unhandled exception" << std::endl;
        return 2;
    }
    
    return 0;
}