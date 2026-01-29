#ifndef ADVERT_ARRAY_HPP
#define ADVERT_ARRAY_HPP

#include "dynamic_array.hpp"
#include "advert.h"

namespace prog_s3 {
    class AdvertArray: public DynamicArray<Advert> {
        std::size_t find();
        //comparator is bool that takes two Adverts 
    };
} //namespace prog_s3

#endif //ADVERT_ARRAY_HPP