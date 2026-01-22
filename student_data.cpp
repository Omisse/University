#include "student_data.h"

#include <cstddef>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>

namespace s3l1 {
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
            _as_json(NULL),
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
        if (_as_json) {
            delete[] _as_json;
            _as_json = NULL;
        }
    }

    StudentData::StudentData(const StudentData &sd): StudentData() {
        _age = sd._age;
        _average_score = sd._average_score;
        _copy_string(&_last_name, sd._last_name);

        _score_count = sd._score_count;
        _score_sum = sd._score_sum;
        _as_json = NULL;
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

        if (_as_json) {
            delete [] _as_json;
            _as_json = NULL;
        }

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
        const char* to_print = _last_name ? _last_name : S3L1_STUDENT_DATA_DEFAULT_PRINT_NAME;
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



    bool StudentData::_is_valid_name(const char* name) const {
        if (!name) {
            return false;
        }
        return (bool)(*name != 0);
    }

    bool StudentData::_is_valid_age(const int age) const {
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
    bool StudentData::_is_valid_average(const float average) const {
        if (std::isnan(average) || std::isinf(average)) {
            return false;
        }
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
        _update_json();
        return _as_json;
    }

    void StudentData::_update_json() {
        char new_json[BUFSIZ] = {0};
        /*
        Делаем все прошлые поинтеры инвалидными, чтобы жизнь мёдом не казалась тем кто копировал бездумно.
        */
        if (_as_json) {
            delete[] _as_json;
            _as_json = NULL;
        }

        memset(new_json, 0, BUFSIZ);

        std::size_t new_size = snprintf(new_json, BUFSIZ-1,
            "{\"_last_name\": \"%s\", \"_age\":\"%d\", \"_average_score\":\"%.2f\", \"_score_sum\":\"%.2f\", \"_score_count\":\"%ld\"}",
            _last_name ? _last_name : S3L1_STUDENT_DATA_DEFAULT_PRINT_NAME,
            _age,
            _average_score,
            _score_sum,
            _score_count
        );
        
        _as_json = new char[new_size+1];
        memcpy(_as_json, new_json, new_size+1);
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
        std::cout << data._ofstream_binary;
        if (data._ofstream_binary) {
            std::size_t name_size = StudentData::_get_true_size(data._last_name);
            struct save_template {
                int age;
                float average;
                std::size_t score_count;
                float score_sum;
                std::size_t name_size;
            } static_data = {};
            /*
            делаем именно так чтобы посередине не было неинициализированных значений
            */
            static_data = {
                data._age,
                data._average_score,
                data._score_count,
                data._score_sum, 
                name_size,
            };
            out.write((char*)&static_data, sizeof(static_data));
            if (name_size > 1) {
                out.write(data._last_name, name_size);
            }
        } else {
            //Если тут не привести тип, мы в бесконечную рекурсию упадём.
            out << (const char*) data;
        }
        
        return out;
    }

    std::ifstream& operator>>(std::ifstream& in, StudentData& data) {
        struct save_template {
            int age;
            float average;
            std::size_t score_count;
            float score_sum;
            std::size_t name_size;
        } static_data = {};
        char* buffer = NULL;

        in.read((char*)&static_data, sizeof(static_data));
        if (static_data.name_size > 1) {
            buffer = new char[static_data.name_size];
            in.read(buffer, static_data.name_size);
            buffer[static_data.name_size-1] = 0;
        }

        data = StudentData(buffer, static_data.age, static_data.average);
        data._score_count = static_data.score_count;
        data._score_sum = static_data.score_sum;
        if (buffer) {
            delete [] buffer;
        }
        return in;
    }
}

