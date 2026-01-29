#ifndef ADVERT_H
#define ADVERT_H

#include <chrono>
#include <cstring>

namespace prog_s3 {
    class Advert {
        protected:
            enum AdType: unsigned char {
                kNone=0,
                kBuy=1,
                kSell=2,
            };

            struct save_struct {
                //in seconds
                std::size_t time_since_epoch;
                std::size_t text_size;
                unsigned short category_size;
                unsigned char phone_size;
                unsigned char type;
            };

            //in seconds
            std::size_t time_since_epoch_;
            char* text_;
            char* category_;
            char* phone_;
            AdType type_;
            
            std::size_t get_string_size(const char* src) const {
                if (src == nullptr) return 0;
                const char* ptr = src;
                while(*(ptr++));
                return ptr-src;
            }

            void free_string(char** dest) {
                if (*dest) delete[] dest;
                *dest = nullptr;
            }

            void set_string(char** dest, const char* src) {
                if (dest == nullptr) return;
                free_string(dest);
                if (src != nullptr) {
                    std::size_t size = get_string_size(src);
                    *dest = new char[size];
                    memcpy(*dest, src, size);
                }
            }

            std::size_t get_timestamp() const {
                return std::chrono::duration_cast<std::chrono::seconds>
                        (std::chrono::system_clock::now().time_since_epoch())
                            .count();
            }

        public:
            Advert():
                type_(AdType::kNone),
                text_(nullptr),
                category_(nullptr),
                phone_(nullptr),
                time_since_epoch_(get_timestamp()) {}

            ~Advert() {
                free_string(&text_);
                free_string(&category_);
                free_string(&phone_);
            }

            Advert(AdType type, const char* text, const char* category, const char* phone): Advert() {
                set_type(type);
                set_text(text);
                set_category(category);
                set_phone(phone);
                time_since_epoch_ = get_timestamp();
            }

            Advert(const Advert& ad): Advert(ad.type_, ad.category_, ad.text_, ad.phone_) {};
            Advert(Advert&& ad): Advert(ad.type_, nullptr, nullptr, nullptr) {
                text_ = ad.text_;
                category_ = ad.category_;
                phone_ = ad.phone_;
                ad.text_ = nullptr;
                ad.category_ = nullptr;
                ad.phone_ = nullptr;
            }

            //время тут не трогаем, потому что это не момент создания
            Advert& operator=(const Advert& ad) {
                set_type(ad.type_);
                set_text(ad.text_);
                set_category(ad.category_);
                set_phone(ad.phone_);
                return *this;
            }

            //время тут не трогаем, потому что это не момент создания
            Advert& operator=(Advert&& ad) {
                set_type(ad.type_);
                free_string(&text_);
                free_string(&category_);
                free_string(&phone_);
                text_ = ad.text_;
                category_ = ad.category_;
                phone_ = ad.phone_;
                ad.text_ = nullptr;
                ad.category_ = nullptr;
                ad.phone_ = nullptr;
                return *this;
            }

            bool operator<(const Advert& other) {
                return time_since_epoch_ < other.time_since_epoch_;
            }

            AdType get_type() const { return type_; }
            const char* get_category() const { return category_; }
            const char* get_text() const { return text_; }
            const char* get_phone_number() const { return phone_; }

            void set_type(AdType type) { type_ = type; }

            void set_text(const char* text) { set_string(&text_, text); }

            void set_category(const char* name) { set_string(&category_, name); }

            bool set_phone(const char* src) {
                free_string(&phone_);
                if (validate_phone(src)) {
                    set_string(&phone_, src);
                    return true;
                } else {
                    return false;
                }
            }

            //вынесем сюда чтобы человек мог проверить не залезая в данные
            bool validate_phone(const char* src) const {
                if (src == nullptr) return false;
                bool is_valid = true;
                while (*src && is_valid) {
                    is_valid = *src >= '0' && *src <= '9';
                    src++;
                }
                return is_valid;
            }

            //DEALLOCATE BY URSELF, WAS new char[]
            char* as_bytes() const {
                //инициализируем полностью
                save_struct static_data{};
                static_data = {
                    time_since_epoch_,
                    get_string_size(text_),
                    (unsigned short) get_string_size(category_),
                    (unsigned char) get_string_size(phone_),
                    type_
                };
                std::size_t save_size = sizeof(save_struct)
                    +static_data.text_size
                    +static_data.category_size
                    +static_data.phone_size;
                char* out = new char[save_size+1];
                char* optr = out;
                memcpy(optr, &static_data, sizeof(static_data));
                optr += sizeof(static_data)+1;
                memcpy(optr, text_, static_data.text_size);
                optr += static_data.text_size+1;
                memcpy(optr, category_, static_data.category_size);
                optr += static_data.category_size+1;
                memcpy(optr, text_, static_data.phone_size);
                //Я ОТДАЮ ДИНАМИЧЕСКУЮ ПАМЯТЬ, КОТОРУЮ НИГДЕ НЕ УБИРАЮ САМ
                return out;
            }

            static Advert from_bytes(const char* byte_string) {
                save_struct static_data{};
                std::size_t offset{0};
                const char* text_ptr{nullptr};
                const char* category_ptr{nullptr};
                const char* phone_ptr{nullptr};
                memcpy(&static_data, byte_string, sizeof(static_data));
                //+1 потому что мы иначе в последнюю ячейку прошлого фрагмента придём
                offset += sizeof(static_data)+1;
                if (static_data.text_size > 0) {
                    text_ptr = byte_string+offset;
                    offset += static_data.text_size+1;
                }
                if (static_data.category_size > 0) {
                    category_ptr = byte_string+offset;
                    offset += static_data.category_size+1;
                }
                if (static_data.phone_size > 0) {
                    phone_ptr = byte_string+offset;
                }
                Advert ad = Advert((AdType)static_data.type, text_ptr, category_ptr, phone_ptr);
                ad.time_since_epoch_ = static_data.time_since_epoch;
                return ad;
            }
            
            std::size_t get_byte_size() const {
                return sizeof(save_struct)+
                    +get_string_size(text_)
                    +get_string_size(category_)
                    +get_string_size(phone_);
            }
    };
} //prog_s3


#endif //ADVERT_H