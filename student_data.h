#ifndef S3L1_STUDENT_DATA_H
#define S3L1_STUDENT_DATA_H

/*
Для класса из лабораторной работы №2 перегрузить операции
ввода/вывода, позволяющие осуществлять ввод и вывод в удобной форме
объектов классов:
 - вывод объекта класса в текстовый файл;
 - вывод объекта класса в двоичный файл;
 - ввод объекта класса из двоичного файла.
Дополнить демонстрационную программу, продемонстрировав все
перегруженные операции.
*/


#include <cstddef>
#include <initializer_list>
#include <ostream>

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

            friend std::ofstream& operator<<(std::ofstream& out, StudentData& data);
            friend std::ifstream& operator>>(std::ifstream& in, StudentData& data);
            
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

            StudentData& binary_mode(bool is_binary);


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
                и если кто вздумает хранить приведённый тип, то он расстроится

                к третьей лабе появилась мысль хранить его внутри функции статикой,
                не знаю, хорошая она или нет
            */
            char* _as_json;

            bool _ofstream_binary;

            bool _is_valid_name(const char* name) const;
            bool _is_valid_age(const int age) const;
            bool _is_valid_average(const float average) const;

            void _memcpy(char* dest, const char* src, std::size_t size);
            void _copy_string(char** dest,const char* src);
            void _update_json();
            static std::size_t _get_true_size(const char* str);
        
    };
}


#endif //S3L1_STUDENT_DATA_H