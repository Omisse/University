#ifndef S2L1_OUTPUT_H
#define S2L1_OUTPUT_H

#include <clocale>
#include <cstdio>
#include <cstring>
#include <vector>

#include "functions.hpp"

namespace S2L1::Output {
//Функция для форматированного вывода вектора в поток stdout;
void print_vector(std::vector<int> val, int length);
//Функция для проверки работы функции F20_*, и форматированного вывода результатов;
void print_f20(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2);
//Функция для проверки работы функции F29_*, и форматированного вывода результатов;
void print_f29(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2);
//Функция для проверки работы функции F32_*, и форматированного вывода результатов;
void print_f32(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2);
//Функция для проверки работы функции F50_*, и форматированного вывода результатов;
void print_f50(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2);
//Функция для проверки работы функции F56_*, и форматированного вывода результатов;
void print_f56(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2);
}

#endif