#ifndef S2L1_OUTPUT_H
#define S2L1_OUTPUT_H

#include <cstdio>
#include <vector>

#include "functions.hpp"

namespace S2L1::Output {
void print_vector(std::vector<int> val, int length);
void print_f20(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2);
void print_f29(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2);
void print_f32(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2);
void print_f50(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2);
void print_f56(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2);
}  // namespace S2L1::Output

#endif