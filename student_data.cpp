#include "student_data.h"

#include <cstddef>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>

namespace prog_s3 {
    const char* StudentData::get_last_name() const {
        return _last_name;
    }

    int StudentData::get_age() const {
        return _age;
    }

    float StudentData::get_average_score() const {
        return _average_score;
    }

    bool StudentData::set_last_name(const char* name) {
        if (!_is_valid_name(name)) {
            return false;
        }

        _copy_string(&_last_name,name);

        return true;
    }

    bool StudentData::set_age(int age) {
        if (!_is_valid_age(age)) return false;
        _age = age;
        return true;
    }

    bool StudentData::set_average_score(float score) {
        if (!_is_valid_average(score)) return false;
        _score_count = 1;
        _score_sum = score;
        _average_score = score;
        return true;
    }

    StudentData::StudentData():
            _last_name(NULL),
            _age(0),
            _average_score(0.0),
            _score_count(0),
            _score_sum(0.0),
            _ofstream_binary(false)
        {}

    StudentData::StudentData(const char* last_name, int age, float average_score): StudentData() {
        set_last_name(last_name);
        set_age(age);
        set_average_score(average_score);
    }

    StudentData::~StudentData() {
        if (_last_name) {
            delete[] _last_name;
            _last_name = NULL;
        }
    }

    StudentData::StudentData(const StudentData &sd): StudentData() {
        _age = sd._age;
        _average_score = sd._average_score;
        _copy_string(&_last_name, sd._last_name);

        _score_count = sd._score_count;
        _score_sum = sd._score_sum;
    }

    StudentData::StudentData(StudentData &&sd): StudentData() {
        _age = sd._age;
        _average_score = sd._average_score;
        _last_name = sd._last_name;
        sd._last_name = NULL;
        
        _score_count = sd._score_count;
        _score_sum = sd._score_sum;
    }

    StudentData& StudentData::operator=(const StudentData& sd) {
        if (&sd == this) return *this;

        _age = sd._age;
        _average_score = sd._average_score;
        _copy_string(&_last_name, sd._last_name);
        _score_count = sd._score_count;
        _score_sum = sd._score_sum;

        return *this;
    }

    StudentData& StudentData::operator=(StudentData &&sd) {
        if (&sd == this) return *this;

        _age = sd._age;
        _average_score = sd._average_score;
        if (_last_name) {
            delete [] _last_name;
        }
        _last_name = sd._last_name;
        sd._last_name = NULL;

        _score_count = sd._score_count;
        _score_sum = sd._score_sum;

        return *this;
    }

    void StudentData::print_last_name() const {
        const char* to_print = _last_name ? _last_name : _k_default_name;
        std::cout << to_print << std::endl;
    }

    void StudentData::print_age() const {
        std::cout << _age << std::endl;
    }

    void StudentData::print_average_score() const {
        char buff[16]; sprintf(buff, "%.2f", _average_score);
        std::cout << buff << std::endl;
    }

    void StudentData::print_data() const {
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
        return (bool)(*name != 0);
    }

    bool StudentData::_is_valid_age(const int age) {
        /*
        понятно, что студент вряд ли будет младенцем или старичком 100+,
        но кто-то, например, может быть зачислен с рождения (как в гарри поттере, да)
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
        if (!std::isfinite(average)) return false;
        return average >= 0.0;
    }

    void StudentData::_copy_string(char** dest, const char* src) {
        if (!dest) return;
        if (*dest == src) return;

        if (*dest) {
            delete[] *dest;
            *dest = NULL;
        }

        if (src) {
            std::size_t size = _get_true_size(src);
            *dest = new char[size];
            memcpy(*dest, src, size);
            (*dest)[size-1] = 0;
        }
    }

    StudentData& StudentData::operator++() {
        _age++;
        return *this;
    }

    StudentData StudentData::operator++(int) {
        StudentData temp = *this;
        _age++;
        return temp;   
    }

    StudentData StudentData::operator+(float score) {
        StudentData new_sd(*this);

        new_sd._score_count+=1;
        new_sd._score_sum+=score;
        new_sd._average_score = new_sd._score_sum/(float)new_sd._score_count;

        return new_sd;
    }

    StudentData operator-(StudentData& lv, float score) {
        /*
        благодаря этой штучке мы не улетим в отрицательные значения
        если на фронте кто-то будет усердно вычитать
        */
        StudentData new_sd(lv);
        float subtract = score <= new_sd._average_score ? score : new_sd._average_score;
        new_sd._average_score -= subtract;
        new_sd._score_sum = new_sd._average_score*new_sd._score_count;
        return new_sd;
    }

    StudentData::operator const char *() {
        return get_json_string();
    }

    const char * StudentData::get_json_string() const {
        static char buffer[BUFSIZ] = {};
        memset(buffer, 0, BUFSIZ);
        snprintf(buffer, BUFSIZ-1,
            "{\"_last_name\": \"%s\", \"_age\":\"%d\", \"_average_score\":\"%.2f\", \"_score_sum\":\"%.2f\", \"_score_count\":\"%ld\"}",
            _last_name ? _last_name : _k_default_name,
            _age,
            _average_score,
            _score_sum,
            _score_count
        );
        return buffer;
    }

    std::size_t StudentData::_get_true_size(const char* str) {
        if (!str) return 0;

        const char* start = str;
        while (*(str++));
        return str-start;
    }

    StudentData& StudentData::binary_mode(bool is_binary) {
        _ofstream_binary = is_binary;
        return *this;
    }

    std::ofstream& operator<<(std::ofstream& out, StudentData& data) {
        data._save_to_file(out);
        return out;
    }

    std::ifstream& operator>>(std::ifstream& in, StudentData& data) {
        data._load_from_file(in);
        return in;
    }

    void StudentData::_save_to_file(std::ofstream& out) const {
        if (_ofstream_binary) {
            _save_binary(out);
        } else {
            out << get_json_string();
        }
    }

    void StudentData::_load_from_file(std::ifstream& in) {
        _load_binary(in);
    }
    

    void StudentData::_save_binary(std::ofstream& out) const {
        std::size_t name_size = StudentData::_get_true_size(_last_name);
        struct save_template {
            int age;
            float average;
            std::size_t score_count;
            float score_sum;
            std::size_t name_size;
        } static_data = {};
        /*
        тут разделили, потому что полезной нагрузки у нас на 28 байт,
        а вот структура получится 32 (выравнивание 8 байт)
        Если игнорировать, получим 4 байта всего что угодно
        между score_sum и name_size, чего не хочется.
        Инициализируем сначала дефолтным конструктором, он забьёт всё нулями
        Потом уже можно.
        */
        static_data = {
            _age,
            _average_score,
            _score_count,
            _score_sum, 
            name_size,
        };
        out.write((char*)(&static_data), sizeof(static_data));
        if (name_size > 1) {
            out.write(_last_name, name_size);
        }
    }

    void StudentData::_load_binary(std::ifstream& in) {
        struct save_template {
            int age;
            float average;
            std::size_t score_count;
            float score_sum;
            std::size_t name_size;
        } static_data = {};
        char* buffer = NULL;

        in.read((char*)&static_data, sizeof(static_data));
        if (in.good() && static_data.name_size > 1) {
            buffer = new char[static_data.name_size];
            in.read(buffer, static_data.name_size);
            buffer[static_data.name_size-1] = 0;
        }
        if (in.good()) {
            if (_last_name) delete [] _last_name;
            _last_name = NULL;
            _age = static_data.age;
            _average_score = static_data.average;
            _score_sum = static_data.score_sum;
            _score_count = static_data.score_count;
        }

        if (buffer) {
            if (in.good()) _copy_string(&_last_name, buffer);
            delete [] buffer;
        }
    }
}

