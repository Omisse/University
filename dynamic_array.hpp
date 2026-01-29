#ifndef S3_DYN_ARRAY_HPP
#define S3_DYN_ARRAY_HPP

#include "array_core.hpp"
#include <functional>
#include <iostream>
#include <stdexcept>

namespace prog_s3 {
template<typename T, typename Comp = std::less<T>>
class DynamicArray: private DynamicArrayCore<T> {
    public:
        typedef typename DynamicArrayCore<T>::size_t size_t;
        
        T& at(const size_t& pos) {
            T* val_ptr = DynamicArrayCore<T>::get(pos);
            if (val_ptr == nullptr) throw std::out_of_range("DynamicArray::at()");
            return *val_ptr;
        }

        void push_back(const T& item) {
            DynamicArrayCore<T>::add(item);
        }

        void erase(size_t pos) {
            DynamicArrayCore<T>::remove(pos);
        }

        void insert(const T& item,size_t pos) {
            if (!DynamicArrayCore<T>::insert(item, pos)) throw std::out_of_range("DynamicArray::insert()");
        }

        void insert_ordered(const T& item) {
            size_t pos = 0;
            bool found = false;
            if (!empty()) {
                try {
                    is_less(at(0), at(0));
                } catch(...) {
                    push_back(item);
                    return;
                }
                while (pos < size() && !found) {
                    found = is_less(item, at(pos++));
                }
                /*
                если не нашли == push_back()
                но если нашли, то в пределах [0;size-1].
                */
                pos -= int(found);
            }
            
            insert(item, pos);
            return;
        }
        
        void sort() {
            sort_custom(Comp{});
        }

        void sort_custom(std::function<bool(const T&, const T&)> is_less) {
            size_t size = this->size();
            if (size < 2) return;
            try {
                bool error_check = is_less(at(0), at(0));
            } catch(...) {
                std::cerr << "Is less runtime error\n";
                return;
            }
            qsort(is_less, 0, size-1);
        }

        size_t size() const {
            return DynamicArrayCore<T>::size_;
        }

        bool empty() const {
            return DynamicArrayCore<T>::size_ == 0;
        }

    protected:
        void swap(const size_t& p1, const size_t& p2) {
            if (p1 >= size() || p2 >= size() || p1 == p2) return;
            T* tmp = DynamicArrayCore<T>::get(p1);
            DynamicArrayCore<T>::fields_[p1] = DynamicArrayCore<T>::fields_[p2];
            DynamicArrayCore<T>::fields_[p2] = tmp;
        }


        size_t qsort_divide(std::function<bool(const T&, const T&)> is_less, size_t part_low, size_t part_high) {
            size_t swap_point = part_low;
            while (part_low != part_high) {
                if (is_less(at(part_low), at(part_high))) {
                    swap(swap_point, part_low);
                    swap_point++;
                }
                part_low++;
            }
            
            swap(swap_point, part_high);
            return swap_point;
        }

        void qsort(std::function<bool(const T&, const T&)> is_less, size_t part_low, size_t part_high) {
            if (part_low < part_high) {
                size_t swap_point = qsort_divide(is_less, part_low, part_high);
                qsort(part_low, (--swap_point)++);
                qsort(++swap_point, part_high);
            }
        }

};//class DynamicArray
} //namespace prog_s3


#endif //S3_DYN_ARRAY_HPP


