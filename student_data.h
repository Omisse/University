#ifndef S3L1_STUDENT_DATA_H
#define S3L1_STUDENT_DATA_H

#include <cstddef>
#include <ostream>

namespace prog_s3 {
    class StudentData {
        public:
            StudentData();
            StudentData(const char* last_name, int age = 0, float average_score = 0.0);
            virtual ~StudentData();
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
            virtual void print_data() const;

            virtual const char* get_json_string() const;

            StudentData& binary_mode(bool is_binary);
        
        protected:
            char* _last_name;
            int _age;
            float _average_score;

            float _score_sum;
            std::size_t _score_count;

            bool _ofstream_binary;

            const char _k_default_name[5] = "NULL";
            static void _copy_string(char** dest, const char* src);
            static std::size_t _get_true_size(const char* str);
            static bool _is_valid_name(const char* name);
            static bool _is_valid_age(const int age);
            static bool _is_valid_average(const float average);

            virtual void _save_to_file(std::ofstream& out) const;
            virtual void _load_from_file(std::ifstream& in);
            virtual void _save_binary(std::ofstream& out) const;
            virtual void _load_binary(std::ifstream& in);
    };
}


#endif //S3L1_STUDENT_DATA_H