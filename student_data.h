#ifndef S3L1_STUDENT_DATA_H
#define S3L1_STUDENT_DATA_H

/*
Для разработанного класса из лабораторной работы №1 реализовать
набор операций для работы с объектами класса:
сложение (как метод класса),
вычитание (как дружественную функцию),
присваивание (как метод класса),
инкремент постфиксный
и инкремент префиксный (как методы класса)
(разобраться и вникнуть, в чем между ними разница!),
приведение к некоторому типу (как метод класса).
Дополнить демонстрационную программу, продемонстрировав все
перегруженные операции.
*/


#include <cstddef>
#include <initializer_list>

#define S3L1_STUDENT_DATA_DEFAULT_PRINT_NAME "NULL"

namespace s3l1 {
    class StudentData {
        public:
            StudentData();
            StudentData(const char* last_name, int age = 0, float average_score = 0.0);
            ~StudentData();
            StudentData(const StudentData &sd);
            StudentData(StudentData &&sd);
            StudentData& operator=(const StudentData& sd);
            StudentData& operator=(StudentData &&sd);

            StudentData& operator++();
            StudentData operator++(int);
            StudentData operator+(float score);
            operator const char*();
            friend StudentData operator-(StudentData& data, float score);
            
            const char* get_last_name() const;
            int get_age() const;
            float get_average_score() const;
            bool set_last_name(const char* name);
            bool set_age(int age);
            bool set_average_score(float score);

            void print_last_name() const;
            void print_age() const;
            void print_average_score() const;
            void print_data() const;


        private:
            char* _last_name;
            int _age;
            float _average_score;

            float _score_sum;
            std::size_t _score_count;
            /*
                по сути, это временное хранилище нашего json из приведения типов.
                сделано оно для того, чтобы я мог принтить его достаточно спокойно
                но придётся держать в уме, что поинтеры на неё удалятся после деструктора,
                и если кто-вздумает хранить приведённый тип, то он расстроится
            */
            char* _as_json;

            bool _is_valid_name(const char* name) const;
            bool _is_valid_age(const int age) const;
            bool _is_valid_average(const float average) const;

            void _copy_string(char** dest,const char* src);
            std::size_t _get_true_size(const char* src);
            void _update_json();
    };
}


#endif //S3L1_STUDENT_DATA_H