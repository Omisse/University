#ifndef S3L5_DATA_LIST_H
#define S3L5_DATA_LIST_H

#include "student_data.h"
#include "student_data_budget.h"
#include "student_data_debt.h"

namespace prog_s3 {
    class DataList {
        public:
            DataList();
            DataList(DataList&&);
            ~DataList();

            void clear();

            /*
            хочется темплейты, но темплейты пока нельзя.
            они будут по лабам дальше и в курсовой.
            */
            void push_front(StudentData& item);
            void push_back(StudentData& item);
            bool insert_at(StudentData& item, std::size_t pos = 0);

            void push_front(StudentDataDebt& item);
            void push_back(StudentDataDebt& item);
            bool insert_at(StudentDataDebt& item, std::size_t pos = 0);

            void push_front(StudentDataBudget& item);
            void push_back(StudentDataBudget& item);
            bool insert_at(StudentDataBudget& item, std::size_t pos = 0);

            bool pop_front();
            bool pop_back();

            bool erase(StudentData* element);
            bool remove_at(std::size_t pos);

            StudentData* get(std::size_t pos);
            StudentData* find(const char* name, std::size_t from = 0);

            std::size_t count(const char* name, std::size_t from = 0);

            std::size_t size();
            bool is_empty();

        protected:
            class DataNode {
                public:
                    DataNode();
                    DataNode(StudentData *value, DataNode *next = NULL);
                    ~DataNode();
                    StudentData* value;
                    DataNode* next;
                    
            };//class DataNode
        private:
            bool _insert_ptr(StudentData* value, std::size_t pos);
            void _push_back_ptr(StudentData* value);
            void _push_front_ptr(StudentData* value);
            void _delete_node(DataNode** node, DataNode* prev = NULL);
            DataNode* _root;
            std::size_t _size;
    };//class DataList
} //namespace prog_s3


#endif //S3_DATA_LIST_H