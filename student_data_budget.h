#ifndef S3L4_STUDENT_DATA_BUDGET_H
#define S3L4_STUDENT_DATA_BUDGET_H

#include "student_data.h"

#include <fstream>


namespace prog_s3 {
    class StudentDataBudget: public StudentData {
        public:
            StudentDataBudget();
            StudentDataBudget(const char* last_name, int age = 0, float average = 0.0, float grant = 0.0);
            virtual ~StudentDataBudget() = default;

            bool set_grant(float new_grant);
            void print_grant() const;
            virtual void print_data() const override;

            virtual const char* get_json_string() const override;

        protected:
            float _grant;
            bool _is_valid_grant(float value);

            virtual void _save_binary(std::ofstream& out) const override;
            virtual void _load_binary(std::ifstream& in) override;
    };//class StudentDataBudget
} //namespace prog_s3

#endif //S3L4_STUDENT_BUDGET_H