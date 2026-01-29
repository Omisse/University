#ifndef ARRAY_CORE_HPP
#define ARRAY_CORE_HPP

/*
Динамический массив структур с уплотнением при удалении и с
расширением при переполнении.
*/

namespace prog_s3 {
    template <typename T>
    class DynamicArrayCore {
        protected:
            typedef unsigned long size_t;
            size_t size_;
            T** fields_;            

        public:
            DynamicArrayCore(): fields_(nullptr), size_(0) {};
            virtual ~DynamicArrayCore() {clear();}
            DynamicArrayCore(const DynamicArrayCore&) = delete;
            DynamicArrayCore(DynamicArrayCore&&) = delete;

            void add(const T& item) {
                T** new_fields = new T*[size_+1];
                T* element = new T(item);
                for (size_t i = 0; i < size_; i++) {
                    new_fields[i] = fields_[i];
                }
                new_fields[size_] = element;
                if (fields_) delete [] fields_;
                fields_ = new_fields;
                size_+=1;
            }

            bool insert(const T& item, const size_t& pos) {
                if (pos > size_) return false;

                T** new_fields = new T*[size_+1];
                T* element = new T(item);
                size_t current = 0;
                while (current < pos) {
                    new_fields[current] = fields_[current];
                    current++;
                }
                new_fields[current++] = element;
                for (;current < size_+1; current++) {
                    new_fields[current] = fields_[current-1];
                }

                if (fields_) delete [] fields_;
                fields_ = new_fields;
                size_+=1;
                
                return true;
            }

            void remove(const size_t& pos) {
                if (pos >= size_) return;

                if (fields_[pos]) delete fields_[pos];
                fields_[pos] = nullptr;
                if (size_ <= 1) {
                    delete fields_;
                    size_ = 0;
                } else {
                    T** new_fields = new T*[size_-1];
                    size_t nf_pos = 0;
                    for (size_t i = 0; i < size_; i++) {
                        if (i != pos) new_fields[nf_pos++] = fields_[i];
                    }
                    if (fields_) delete [] fields_;
                    fields_ = new_fields;
                    size_--;                        
                }
            }
            
            T* get(const size_t& pos) {
                if (pos >= size_) return nullptr;
                return fields_[pos];
            }

            void clear() {
                if (fields_ == nullptr) {
                    size_ = 0;
                    return;
                } 

                for(size_t i = 0; i < size_; i++) {
                    if (fields_[i] != nullptr) delete fields_[i];
                }
                delete [] fields_;
                fields_ = nullptr;
                size_ = 0;
            }
    };
} //namespace prog_s3


#endif //ARRAY_CORE_HPP

