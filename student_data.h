#ifndef S3L1_STUDENT_DATA_H
#define S3L1_STUDENT_DATA_H

#include <cstddef>

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
            
            const char* get_last_name();
            int get_age();
            float get_average_score();
            bool set_last_name(const char* name);
            bool set_age(int age);
            bool set_average_score(float score);

            void print_last_name();
            void print_age();
            void print_average_score();
            void print_data();


        private:
            char* _last_name;
            int _age;
            float _average_score;

            bool _is_valid_name(const char* name);
            bool _is_valid_age(const int age);
            bool _is_valid_average(const float average);

            void _copy_string(char** dest, const char* src);
            std::size_t _get_true_size(const char* str);

    };
}


#endif //S3L1_STUDENT_DATA_H