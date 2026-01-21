#ifndef S3L4_STUDENT_DATA_DEBT_H
#define S3L4_STUDENT_DATA_DEBT_H

#include "student_data.h"

#include <fstream>


namespace prog_s3 {
    class StudentDataDebt: public StudentData {
        public:
            StudentDataDebt();
            StudentDataDebt(const char* last_name, int age = 0, float average = 0.0, int debts = 0);

            bool set_debts(int count);
            void close_debt(int amount = 1);
            void add_debt(int amount = 1);

            void print_debt() const;
            virtual void print_data() const override;
            virtual const char* get_json_string() const override;

        protected:
            int _debts;
            bool _is_valid_debt(int value);

            virtual void _save_binary(std::ofstream& out) const override;
            virtual void _load_binary(std::ifstream& in) override;

    };//class StudentDataDebt
} //namespace prog_s3


#endif //S3L4_STUDENT_COURSES_H