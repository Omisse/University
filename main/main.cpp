#include <clocale>
#include <vector>

#include "../core/output.hpp"

int main(void) {
  // Создаём два эталонных вектора и их длину для использования в функциях.
  const std::vector<int> rval_1 = {447, 691, 126, -836, 748,
                                   767, 301, -37, 345,  -164};
  const std::vector<int> rval_2 = {-420, 2,   -160, 536, -573, -429, -233,
                                   905,  558, -772, 445, 862,  -312, 2};
  const int rlen_1 = 10;
  const int rlen_2 = 14;
  // Устанавливаем локаль для корректного вывода wchar_t кириллицы.
  setlocale(LC_ALL, "Russian");
  // Стилизованный вывод для каждой из наших функций
  S2L1::Output::print_f20(rval_1, rval_2, rlen_1, rlen_2);
  S2L1::Output::print_f29(rval_1, rval_2, rlen_1, rlen_2);
  S2L1::Output::print_f32(rval_1, rval_2, rlen_1, rlen_2);
  S2L1::Output::print_f50(rval_1, rval_2, rlen_1, rlen_2);
  S2L1::Output::print_f56(rval_1, rval_2, rlen_1, rlen_2);
  return 0;
}