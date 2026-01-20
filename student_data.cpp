#include "student_data.h"

#include <cstddef>
#include <cmath>
#include <iostream>

namespace s3l1 {
    const char* StudentData::get_last_name() {
        return _last_name;
    }

    int StudentData::get_age() {
        return _age;
    }

    float StudentData::get_average_score() {
        return _average_score;
    }

    bool StudentData::set_last_name(const char* name) {
        const char* size_ptr = name;
        std::size_t size = 0;

        if (!_is_valid_name(name)) {
            return false;
        }

        //получим размер+1
        while (*(size_ptr++));
        size = size_ptr-name;

        if (_last_name) delete _last_name;
        _last_name = new char[size];
        //скопируем имя
        _memcpy(_last_name, name, size);
        /*
        явно скажем, что это конец строки
        это необязательно(в источнике там уже 0),
        но понять становится чуть попроще
        */
        _last_name[size-1] = 0;
        return true;
    }

    bool StudentData::set_age(int age) {
        if (!_is_valid_age(age)) return false;
        _age = age;
        return true;
    }

    bool StudentData::set_average_score(float score) {
        if (!_is_valid_average(score)) return false;

        _average_score = score;
        return true;
    }

    StudentData::StudentData(): _last_name(NULL), _age(0), _average_score(0.0) {}

    StudentData::StudentData(const char* last_name, int age, float average_score): _last_name(NULL) {
        if (!set_last_name(last_name)) _last_name = NULL;
        if (!set_age(age)) _age = 0;
        if (!set_average_score(average_score)) _average_score = 0.0;
    }

    StudentData::~StudentData() {
        if (_last_name) {
            delete _last_name;
        }
    }

    StudentData::StudentData(const StudentData &sd) {
        _age = sd._age;
        _average_score = sd._average_score;
        _last_name = NULL;
        if (sd._last_name) {
            set_last_name(sd._last_name);
        }
    }

    StudentData::StudentData(StudentData &&sd) {
        _age = sd._age;
        _average_score = sd._average_score;
        _last_name = sd._last_name;
        sd._last_name = NULL;
    }

    StudentData& StudentData::operator=(const StudentData& sd) {
        if (_last_name) delete _last_name;
        _last_name = NULL;
        _age = sd._age;
        _average_score = sd._average_score;
        if (sd._last_name) {
            set_last_name(sd._last_name);
        }

        return *this;
    }

    StudentData& StudentData::operator=(StudentData &&sd) {
        if (_last_name) delete _last_name;
        _last_name = NULL;
        _age = sd._age;
        _average_score = sd._average_score;
        _last_name = sd._last_name;
        sd._last_name = NULL;

        return *this;
    }

    void StudentData::print_last_name() {
        const char* to_print = _last_name ? _last_name : S3L1_STUDENT_DATA_DEFAULT_PRINT_NAME;
        std::cout << to_print << std::endl;
    }

    void StudentData::print_age() {
        std::cout << _age << std::endl;
    }

    void StudentData::print_average_score() {
        std::cout << _average_score << std::endl;
    }

    void StudentData::print_data() {
        std::cout << "Student: ";
        print_last_name();
        std::cout << "\tAge: ";
        print_age();
        std::cout << "\tAverage Score: ";
        print_average_score();
    }



    bool StudentData::_is_valid_name(const char* name) {
        if (!name) {
            return false;
        }
        return (*name != 0);
    }

    bool StudentData::_is_valid_age(const int age) {
        /*
        понятно, что студент вряд ли будет младенцем или старичком 100+,
        но кто-то, например, может быть зачислен с рождения
        или числиться в базах до смерти,
        и мы не хотим вывалиться в ошибку по недосмотру
        */
        return age >= 0 && age <= 150;
    }


    /*
    система оценки не указана, так что просто проверим что это вообще число,
    что оно больше нуля,
    и далее отдадим всё в руки того, кто будет дёргать за ручки нашего интерфейса.
    */
    bool StudentData::_is_valid_average(const float average) {
        if (std::isnan(average) || std::isinf(average)) {
            return false;
        }
        return average >= 0.0;
    }

    void StudentData::_memcpy(char* dest, const char* src, std::size_t size) {
        for (std::size_t i{0}; i < size; i++) {
            dest[i] = src[i];
        }
    }
}

