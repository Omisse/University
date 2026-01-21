#include "student_data_budget.h"

#include <cmath>
#include <cstring>
#include <iostream>


namespace prog_s3 {    
    StudentDataBudget::StudentDataBudget()
        : _grant(0.0) {};

    StudentDataBudget::StudentDataBudget(const char* last_name, int age, float average, float grant)
            :StudentData(last_name, age, average) {
        _grant = 0.0;
        set_grant(grant);
    }

    bool StudentDataBudget::set_grant(float new_grant) {
        if (!_is_valid_grant(new_grant)) return false;

        _grant = new_grant;
        return true;
    }

    void StudentDataBudget::print_grant() const {
        char buff[32] = {};
        snprintf(buff, 31, "%.2f", _grant);
        std::cout << buff << std::endl;
    }

    void StudentDataBudget::print_data() const {
        StudentData::print_data();
        std::cout << "\tGrant: ";
        print_grant();
    }

    bool StudentDataBudget::_is_valid_grant(float value) {
        if (!std::isfinite(value)) return false;
        return value >= 0.0;
    }

    const char* StudentDataBudget::get_json_string() const {
        static char buffer[BUFSIZ] = {};
        memset(buffer, 0, BUFSIZ);
        snprintf(buffer, BUFSIZ-1,
            "{\"_last_name\": \"%s\", \"_age\":\"%d\", \"_average_score\":\"%.2f\", \"_score_sum\":\"%.2f\", \"_score_count\":\"%ld\", \"_grant\":\"%.2f\"}",
            _last_name ? _last_name : _k_default_name,
            _age,
            _average_score,
            _score_sum,
            _score_count,
            _grant
        );
        return buffer;
    }

    void StudentDataBudget::_save_binary(std::ofstream& out) const {
        std::size_t name_size = StudentData::_get_true_size(_last_name);
        struct save_template {
            int age;
            float average;
            std::size_t score_count;
            float score_sum;
            float grant;
            std::size_t name_size;
        } static_data = {};
        static_data = {
            _age,
            _average_score,
            _score_count,
            _score_sum,
            _grant,
            name_size,
        };
        out.write((char*)&static_data, sizeof(static_data));
        if (name_size > 1) {
            out.write(_last_name, name_size);
        }
    }

    void StudentDataBudget::_load_binary(std::ifstream& in) {
        struct save_template {
            int age;
            float average;
            std::size_t score_count;
            float score_sum;
            float grant;
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
            _grant = static_data.grant;
        }
        
        if (buffer) {
            if (in.good()) _copy_string(&_last_name, buffer);
            delete [] buffer;
        }
    }
} //namespace prog_s3