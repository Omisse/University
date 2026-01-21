#include "data_list.h"
#include "student_data.h"
#include "student_data_budget.h"
#include "student_data_debt.h"

#include <cstddef>
#include <cstring>

namespace prog_s3 {
    DataList::DataList(): _root(NULL), _size(0) {};
    DataList::DataList(DataList&& other) {
        clear();
        this->_root = other._root;
        this->_size = other._size;
        other._root = NULL;
        other._size = 0;
    }

    DataList::~DataList() {
        clear();
    }

    void DataList::clear() {
        while (_root) {
            DataNode* next = _root->next;
            delete _root;
            _root = next;
        }
        _root = NULL;
    }

    void DataList::push_front(StudentData& item) {
        _push_front_ptr(new StudentData(item));
    }

    void DataList::push_back(StudentData& item) {
        _push_back_ptr(new StudentData(item));
    }

    bool DataList::insert_at(StudentData& item, std::size_t pos) {
        StudentData* new_ptr = new StudentData(item);
        bool is_ok = _insert_ptr(new_ptr, pos);
        if (!is_ok) {
            delete new_ptr;
        }
        return is_ok;
    }

    void DataList::push_front(StudentDataDebt& item) {
        _push_front_ptr((StudentData*) new StudentDataDebt(item));
    }
    void DataList::push_back(StudentDataDebt& item) {
        _push_back_ptr((StudentData*) new StudentDataDebt(item));
    }

    bool DataList::insert_at(StudentDataDebt& item, std::size_t pos) {
        StudentData* new_ptr = (StudentData*) new StudentDataDebt(item);
        bool is_ok = _insert_ptr(new_ptr, pos);
        if (!is_ok) {
            delete new_ptr;
        }
        return is_ok;
    }

    void DataList::push_front(StudentDataBudget& item) {
        _push_front_ptr((StudentData*) new StudentDataBudget(item));
    }

    void DataList::push_back(StudentDataBudget& item) {
        _push_back_ptr((StudentData*) new StudentDataBudget(item));
    }

    bool DataList::insert_at(StudentDataBudget& item, std::size_t pos) {
        StudentData* new_ptr = (StudentData*) new StudentDataBudget(item);
        bool is_ok = _insert_ptr(new_ptr, pos);
        if (!is_ok) {
            delete new_ptr;
        }
        return is_ok;
    }

    bool DataList::pop_front() {
        if (!_root || is_empty()) return false;
        _delete_node(&_root, NULL);
        
        return true;
    }

    bool DataList::pop_back() {
        if (!_root || is_empty()) return false;
        
        DataNode* ptr = _root;
        DataNode* prev = NULL;
        while (ptr->next) {
            prev = ptr;
            ptr=ptr->next;
        }
        _delete_node(&ptr, prev);
        return true;
    }

    bool DataList::erase(StudentData* element) {
        if (!_root || is_empty()) return false;

        DataNode* ptr = _root;
        DataNode* prev = NULL;
        while (ptr && ptr->value != element) {
            prev = ptr;
            ptr = ptr->next;
        }

        if (ptr) {
            _delete_node(&ptr, prev);
            return true;
        }
        return false;
    }

    bool DataList::remove_at(std::size_t pos) {
        if (is_empty() || pos >= _size) return false;
        DataNode* delptr = _root;
        DataNode* prev = NULL;
        for(std::size_t i = 0; i < pos; i++) {
            prev = delptr;
            delptr = delptr->next;
        }
        _delete_node(&delptr, prev);
        return true;
    }

    StudentData* DataList::get(std::size_t pos) {
        if (is_empty() || pos >= _size) return NULL;
        DataNode* ptr = _root;
        for (std::size_t i = 0; i < pos; i++) {
            ptr = ptr->next;
        }
        StudentData* retval = ptr ? ptr->value : NULL;
        return retval;
    }

    StudentData* DataList::find(const char* name, std::size_t from) {
        if (is_empty() || from >= _size) return NULL;
        StudentData* retval = NULL;
        DataNode* ptr = _root;
        for (std::size_t i = from; i < _size && !retval; i++) {
            if (strcmp(ptr->value->get_last_name(), name) == 0) {
                retval = ptr->value;
            }
            ptr = ptr->next;
        }
        return retval;
    }

    std::size_t DataList::count(const char* name, std::size_t from) {
        if (is_empty() || from >= _size) return 0;
        std::size_t amount = 0;
        DataNode* ptr = _root;
        for (std::size_t i = from; i < _size; i++) {
            amount += (strcmp(ptr->value->get_last_name(), name) == 0);
            ptr = ptr->next;
        }
        return amount;
    }

    std::size_t DataList::size() {
        return _size;
    }

    bool DataList::is_empty() {
        return _size == 0;
    }

    bool DataList::_insert_ptr(StudentData* value, std::size_t pos) {
        if (pos>_size || !value) return false;
        DataNode* ptr = _root;
        DataNode* prev = NULL;
        for (std::size_t i = 0; i < pos; i++) {
            prev = ptr;
            ptr = ptr->next;
        }
        if (!prev) {
            _root = new DataNode(value, ptr);
        } else {
            prev->next = new DataNode(value, ptr);
        }
        _size++;
        return true;
    }

    void DataList::_push_back_ptr(StudentData* value) {
        _insert_ptr(value, _size);
    }

    void DataList::_push_front_ptr(StudentData* value) {
        _insert_ptr(value, 0);
    }

    void DataList::_delete_node(DataNode** node, DataNode* prev) {
        if (is_empty() || !node) return;
        if (!*node) return;

        DataNode* next = (*node)->next;
        delete *node;
        if (prev == NULL || prev == *node) {
            *node = next;
        } else {
            prev->next = next;
        }
        _size -= 1;
    }

    DataList::DataNode::DataNode():DataNode(NULL, NULL) {};
    DataList::DataNode::DataNode(StudentData *value, DataNode *next)
        : value(value), next(next) {};
    DataList::DataNode::~DataNode() {
        if (value) delete value;
    }
}

