#include "student_data_debt.h"

#include <cstring>
#include <iostream>

namespace prog_s3 {
    StudentDataDebt::StudentDataDebt(): _debts(0) {}

    StudentDataDebt::StudentDataDebt(
        const char* last_name, int age, float average, int debts)
            :StudentData(last_name, age, average) {
        _debts = 0;
        set_debts(debts);
    }
    
    bool StudentDataDebt::set_debts(int count) {
        if (!_is_valid_debt(count)) return false;
        _debts = count;
        return true;
    }

    void StudentDataDebt::close_debt(int amount) {
        if (amount > 0) {
            _debts -= amount > _debts ? _debts : amount;
        }
    }

    void StudentDataDebt::add_debt(int amount) {
        if (amount > 0) {
            _debts += amount;
        }
    }

    void StudentDataDebt::print_debt() const {
        std::cout << _debts << std::endl;
    }

    void StudentDataDebt::print_data() const {
        StudentData::print_data();
        std::cout << "\tDebts: ";
        print_debt();
    }

    bool StudentDataDebt::_is_valid_debt(int value) {
        return value >= 0;
    }

    const char* StudentDataDebt::get_json_string() const {
        static char buffer[BUFSIZ] = {};
        memset(buffer, 0, BUFSIZ);
        snprintf(buffer, BUFSIZ-1,
            "{\"_last_name\": \"%s\", \"_age\":\"%d\", \"_average_score\":\"%.2f\", \"_score_sum\":\"%.2f\", \"_score_count\":\"%ld\", \"_debts\":\"%d\"}",
            _last_name ? _last_name : _k_default_name,
            _age,
            _average_score,
            _score_sum,
            _score_count,
            _debts
        );
        return buffer;
    }


    void StudentDataDebt::_save_binary(std::ofstream& out) const {
        std::size_t name_size = StudentData::_get_true_size(_last_name);
        struct save_template {
            int age;
            float average;
            std::size_t score_count;
            float score_sum;
            int debts;
            std::size_t name_size;
        } static_data = {};
        static_data = {
            _age,
            _average_score,
            _score_count,
            _score_sum,
            _debts,
            name_size,
        };
        out.write((char*)&static_data, sizeof(static_data));
        if (name_size > 1) {
            out.write(_last_name, name_size);
        }
    }

    void StudentDataDebt::_load_binary(std::ifstream& in) {
        struct save_template {
            int age;
            float average;
            std::size_t score_count;
            float score_sum;
            int debts;
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
            _debts = static_data.debts;
        }        

        if (buffer) {
            if (in.good()) _copy_string(&_last_name, buffer);
            delete [] buffer;
        }
    }

} //namespace prog_s3

