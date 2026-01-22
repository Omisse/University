#ifndef S3L7_LIST_HPP
#define S3L7_LIST_HPP

#include "list_node.hpp"

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>

//это старый лист из школы21, под задачу он подходит, пусть и чуть сложнее требуемого
namespace prog_s3 {
template<typename T>
class list {
    protected:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using size_type = std::size_t;
        using pointer_type = T*;

        template <bool is_const>
        class BaseIterator {
            public:
                using value_ref = typename std::conditional<is_const, const_reference, reference>::type;
                using node_ptr = typename std::conditional<is_const, const Node<value_type>*, Node<value_type>*>::type;

                BaseIterator(): node_() {};
                BaseIterator(node_ptr node): node_(node) {}
                BaseIterator(const BaseIterator &other) = default;
                BaseIterator(BaseIterator &&other) = default;
                value_ref operator*()  { return node_->value; }
                BaseIterator &operator++() {node_ = node_->next; return *this;}
                BaseIterator operator++(int) {node_ = node_->next; return BaseIterator(node_->previous);};
                BaseIterator &operator--() {node_ = node_->previous; return *this;}
                BaseIterator operator--(int) {node_ = node_->previous; return *BaseIterator(node_->next);};
                bool operator==(const BaseIterator &other) const {return this->node_ == other.node_;}
                bool operator!=(const BaseIterator &other) const {return !(this->node_ == other.node_);}

            protected:
                friend class list;
                node_ptr node_;
        };

        using ListIterator = BaseIterator<false>;
        using ListConstIterator = BaseIterator<true>;

        prog_s3::Node<value_type> header_;
        size_type size_;

        void insert_borrow(ListIterator pos, ListIterator other, size_type& dest_size, size_type& src_size) {
            prog_s3::Node<value_type>* dest = pos.node_;
            prog_s3::Node<value_type>* src = other.node_;
            src->previous = dest->previous;
            src->next = dest;
            dest->previous = src;
            dest_size++;
            src_size--;
        }

        ListIterator get_offset_iterator(size_type offset) {
            ListIterator pos = begin();
            for (size_type i = 0; i < offset; i++) {
                pos++;
            }
            return pos;
        }

        reference get_offset_value(size_type offset) {
            return *get_offset_iterator(offset);
        }

        void set_offset_value(size_type offset, reference value) {
            *get_offset_iterator(offset) = value;
        }

        void swap_offset_values(size_type offset1, size_type offset2) {
            value_type value_holder = get_offset_value(offset1);
            set_offset_value(offset1, get_offset_value(offset2));
            set_offset_value(offset2, value_holder);
        }

        void remove_all_but_first(const_reference value) {
            bool first = true;
            while (auto i = begin() != end()) {
                if (*i == value) {
                    if (first) first = !first;
                    else erase(i++);
                }
            }
        }

        ListIterator qsort_divide(ListIterator part_low, ListIterator part_high) {
            ListIterator swap_point = part_low;
            value_type value_holder = value_type();
            while (part_low != part_high) {
                if (*part_low <= *part_high) {
                    value_holder = *swap_point;
                    *swap_point = *part_low;
                    *part_low = value_holder;
                    swap_point++;
                }
                part_low++;
            }
            
            value_holder = *swap_point;
            *swap_point = *part_high;
            *part_high = value_holder;

            return swap_point;
        }

        bool iterator_less(ListIterator source, ListIterator compare) {
            bool is_less = false;
            if (source != compare)
                while (source != end() && !is_less) {
                    is_less = source == compare;
                    source++;
                }
            return is_less;
        }

        void qsort(ListIterator part_low, ListIterator part_high) {
            if (size_ < 2) return;
            if (iterator_less(part_low, part_high)) {
                ListIterator swap_point = qsort_divide(part_low, part_high);
                qsort(part_low, (--swap_point)++);
                qsort(++swap_point, part_high);
            }
        }

    public:
        using iterator = ListIterator;
        using const_iterator = ListConstIterator;

        list(): header_{}, size_(0) {};

        list(size_type n): list() {
            size_ = n;
            while (n) {
                push_back(value_type());
                n--;
            }
        }

        list(std::initializer_list<value_type> const &items): list() {
            for (auto item = items.begin(); item != items.end(); item++) {
                push_back(*item);
            }
        }

        list(const list &l) { //copy
            for (auto item = l.begin(); item != l.end(); item++) {
                push_back(*item);
            }
        }

        list(list &&l) { //move
            clear();
            while (!l.empty()) {
                push_back(*(l.begin()));
                l.erase(l.begin());
            }
        }

        virtual ~list() { this->clear(); } //destructor

        list& operator=(list &&l) { //assignment move
            if (this != &l) {
                clear();
                while (!l.empty()) {
                    push_back(*(l.begin()));
                    l.erase(l.begin());
                }
            }
            return *this;
        }

            //access methods
        const_reference front() { 
            if (!empty()) {
                return begin().node_->value;
            } else {
                throw std::out_of_range("the list is empty");
            }
            
        }
        const_reference back() {
            if (!empty()) {
                return end().node_->previous->value;
            } else {
                throw std::out_of_range("the list is empty");
            }
        }

        const_reference at(size_type pos) {
            if (empty()) throw std::out_of_range("the list is empty");
            return get_offset_value(pos%size_);
        }

            //iterators
        iterator begin() { return iterator(header_.next); }
        iterator end() { return iterator(&header_); }

        const_iterator cbegin() const { return const_iterator(header_.next); }
        const_iterator cend() const { return const_iterator(&header_); }

            //capacity
        bool empty() {return size_ == 0; }
        size_type size() { return size_; }
        size_type max_size() { return std::numeric_limits<size_type>::max(); }

            //mutators
        void clear() {
            while (begin() != end())
                erase(begin());
        }

        iterator insert(iterator pos, const_reference value) {             
            prog_s3::Node<value_type>* past = pos.node_->previous;
            prog_s3::Node<value_type>* next = pos.node_;
            prog_s3::Node<value_type>* alloc = new Node<value_type>(value, next, past);
            past->next = alloc;
            next->previous = alloc;
            size_++;
            return iterator(alloc);
        }

        iterator insert_at(size_type pos, const_reference value) {
            size_type real_pos = size_ > 0 ? pos%(size_) : 0;
            //сдвинем в конец, чтобы было интуитивно понятно, что это новый элемент
            if (pos >= size_ && real_pos == 0) real_pos += size_;
            return insert(get_offset_iterator(real_pos), value);
        }

        void erase(iterator pos) { //may throw exception
            if (pos.node_ != nullptr && pos != end()) {
                pos.node_->next->previous = pos.node_->previous;
                pos.node_->previous->next = pos.node_->next;
                delete pos.node_;
                size_--;
            } else {
                throw std::out_of_range("erasing header_ || null");
            }
        }

        void push_back(const_reference value) {
            insert(end(), value);
        }

        void pop_back() { //remove last! (exceptional)
            erase(iterator(end().node_->previous));
        }

        void push_front(const_reference value) {
            insert(begin(), value);
        }

        void pop_front() { //remove first (exceptional)
            erase(begin());
        }

        void swap(list& other) {
            Node<value_type> temporary_header = header_;
            size_type temporary_size = size_;
            header_ = other.header_;
            size_ = other.size_;
            other.header_ = temporary_header;
            other.size_ = temporary_size;
        }

        void merge(list& other) { //we assume that both our lists are already sorted (std behaviour)
            if (end() != other.end()) {
                while(other.begin() != other.end()) {
                    auto dest_iter = begin();
                    while (dest_iter != end() && std::less<value_type>(*(dest_iter++), *(other.begin())));
                    insert_borrow(dest_iter, other.begin(), size_, other.size_);
                }
            }
        }

        void splice(const_iterator pos, list& other) { //transfer from other list to this one, starting from pos.
            //if (end() != other.end()) //std assumes that those are different lists anyway, behaviour is undefined
            while (other.begin() != other.end()) {
                insert_borrow(pos, other.begin(), size_, other.size_);
            }
        }

        void reverse() {
            iterator item = begin();
            while (item != end()) {
                prog_s3::Node<value_type>* tmp_node = item.node_->next;
                item.node_->next = item.node_->previous;
                item.node_->previous = item.node_->next;
                item--;
            }

            prog_s3::Node<value_type>* old_next = header_.next;
            header_.next = header_.previous;
            header_.previous = old_next;
        }

        void unique() {  //deduplicate
            auto iter = begin();
            while (iter != end()) {
                remove_all_but_first(*iter);
            }
        }

        void sort() { qsort(begin(), --end()); }
}; //class list

} //namespace prog_s3

#endif //S3L7_LIST_HPP
