#include "output.hpp"

namespace S2L1::Output {
#define NF_BREAK "--------------------"

void print_vector(std::vector<int> val, int length) {
  printf("{");
  for (int i = 0; i < length; i++) {
    if (i != 0) {
      printf(", ");
    }
    printf("%4d", val[i]);
  }
  printf("}\n");
}

void print_f20(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2) {
  std::vector<int> test_vector = {};
  int n = 0;

  printf("%s\n", NF_BREAK);

  printf("F20, набор значений 1:\n");
  test_vector = rval_1;
  n = rlen_1;
  printf("F20_val - входной массив:      ");
  print_vector(test_vector, n);
  printf("F20_val - %d\n", S2L1::Functions::F20_val(test_vector, n));
  printf("F20_val - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_1;
  n = rlen_1;
  printf("F20_ref - входной массив:      ");
  print_vector(test_vector, n);
  printf("F20_ref - %d\n", S2L1::Functions::F20_ref(test_vector, n));
  printf("F20_ref - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_1;
  n = rlen_1;
  printf("F20_pointer - входной массив:  ");
  print_vector(test_vector, n);
  printf("F20_pointer - %d\n", S2L1::Functions::F20_pointer(&test_vector, &n));
  printf("F20_pointer - итоговый массив: ");
  print_vector(test_vector, n);

  printf("F20, набор значений 2:\n");
  test_vector = rval_2;
  n = rlen_2;
  printf("F20_val - входной массив:      ");
  print_vector(test_vector, n);
  printf("F20_val - %d\n", S2L1::Functions::F20_val(test_vector, n));
  printf("F20_val - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_2;
  n = rlen_2;
  printf("F20_ref - входной массив:      ");
  print_vector(test_vector, n);
  printf("F20_ref - %d\n", S2L1::Functions::F20_ref(test_vector, n));
  printf("F20_ref - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_2;
  n = rlen_2;
  printf("F20_pointer - входной массив:  ");
  print_vector(test_vector, n);
  printf("F20_pointer - %d\n", S2L1::Functions::F20_pointer(&test_vector, &n));
  printf("F20_pointer - итоговый массив: ");
  print_vector(test_vector, n);

  printf("%s\n", NF_BREAK);
}

void print_f29(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2) {
  std::vector<int> test_vector = {};
  int n = 0;

  printf("%s\n", NF_BREAK);

  printf("F29, набор значений 1:\n");
  test_vector = rval_1;
  n = rlen_1;
  printf("F29_val - входной массив:      ");
  print_vector(test_vector, n);
  printf("F29_val - %d\n", S2L1::Functions::F29_val(test_vector, n));
  printf("F29_val - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_1;
  n = rlen_1;
  printf("F29_ref - входной массив:      ");
  print_vector(test_vector, n);
  printf("F29_ref - %d\n", S2L1::Functions::F29_ref(test_vector, n));
  printf("F29_ref - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_1;
  n = rlen_1;
  printf("F29_pointer - входной массив:  ");
  print_vector(test_vector, n);
  printf("F29_pointer - %d\n", S2L1::Functions::F29_pointer(&test_vector, &n));
  printf("F29_pointer - итоговый массив: ");
  print_vector(test_vector, n);

  printf("F29, набор значений 2:\n");
  test_vector = rval_2;
  n = rlen_2;
  printf("F29_val - входной массив:      ");
  print_vector(test_vector, n);
  printf("F29_val - %d\n", S2L1::Functions::F29_val(test_vector, n));
  printf("F29_val - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_2;
  n = rlen_2;
  printf("F29_ref - входной массив:      ");
  print_vector(test_vector, n);
  printf("F29_ref - %d\n", S2L1::Functions::F29_ref(test_vector, n));
  printf("F29_ref - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_2;
  n = rlen_2;
  printf("F29_pointer - входной массив:  ");
  print_vector(test_vector, n);
  printf("F29_pointer - %d\n", S2L1::Functions::F29_pointer(&test_vector, &n));
  printf("F29_pointer - итоговый массив: ");
  print_vector(test_vector, n);

  printf("%s\n", NF_BREAK);
}

void print_f32(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2) {
  std::vector<int> test_vector = {};
  int n = 0;

  printf("%s\n", NF_BREAK);

  printf("F32, набор значений 1:\n");
  test_vector = rval_1;
  n = rlen_1;
  printf("F32_val - входной массив:      ");
  print_vector(test_vector, n);
  printf("F32_val - %d\n", S2L1::Functions::F32_val(test_vector, n));
  printf("F32_val - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_1;
  n = rlen_1;
  printf("F32_ref - входной массив:      ");
  print_vector(test_vector, n);
  printf("F32_ref - %d\n", S2L1::Functions::F32_ref(test_vector, n));
  printf("F32_ref - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_1;
  n = rlen_1;
  printf("F32_pointer - входной массив:  ");
  print_vector(test_vector, n);
  printf("F32_pointer - %d\n", S2L1::Functions::F32_pointer(&test_vector, &n));
  printf("F32_pointer - итоговый массив: ");
  print_vector(test_vector, n);

  printf("F32, набор значений 2:\n");
  test_vector = rval_2;
  n = rlen_2;
  printf("F32_val - входной массив:      ");
  print_vector(test_vector, n);
  printf("F32_val - %d\n", S2L1::Functions::F32_val(test_vector, n));
  printf("F32_val - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_2;
  n = rlen_2;
  printf("F32_ref - входной массив:      ");
  print_vector(test_vector, n);
  printf("F32_ref - %d\n", S2L1::Functions::F32_ref(test_vector, n));
  printf("F32_ref - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_2;
  n = rlen_2;
  printf("F32_pointer - входной массив:  ");
  print_vector(test_vector, n);
  printf("F32_pointer - %d\n", S2L1::Functions::F32_pointer(&test_vector, &n));
  printf("F32_pointer - итоговый массив: ");
  print_vector(test_vector, n);

  printf("%s\n", NF_BREAK);
}

void print_f50(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2) {
  std::vector<int> test_vector = {};
  int n = 0;

  printf("%s\n", NF_BREAK);

  printf("F50, набор значений 1:\n");
  test_vector = rval_1;
  n = rlen_1;
  printf("F50_val - входной массив:      ");
  print_vector(test_vector, n);
  printf("F50_val - %d\n", S2L1::Functions::F50_val(test_vector));
  printf("F50_val - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_1;
  n = rlen_1;
  printf("F50_ref - входной массив:      ");
  print_vector(test_vector, n);
  printf("F50_ref - %d\n", S2L1::Functions::F50_ref(test_vector));
  printf("F50_ref - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_1;
  n = rlen_1;
  printf("F50_pointer - входной массив:  ");
  print_vector(test_vector, n);
  printf("F50_pointer - %d\n", S2L1::Functions::F50_pointer(&test_vector));
  printf("F50_pointer - итоговый массив: ");
  print_vector(test_vector, n);

  printf("F50, набор значений 2:\n");
  test_vector = rval_2;
  n = rlen_2;
  printf("F50_val - входной массив:      ");
  print_vector(test_vector, n);
  printf("F50_val - %d\n", S2L1::Functions::F50_val(test_vector));
  printf("F50_val - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_2;
  n = rlen_2;
  printf("F50_ref - входной массив:      ");
  print_vector(test_vector, n);
  printf("F50_ref - %d\n", S2L1::Functions::F50_ref(test_vector));
  printf("F50_ref - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_2;
  n = rlen_2;
  printf("F50_pointer - входной массив:  ");
  print_vector(test_vector, n);
  printf("F50_pointer - %d\n", S2L1::Functions::F50_pointer(&test_vector));
  printf("F50_pointer - итоговый массив: ");
  print_vector(test_vector, n);

  printf("%s\n", NF_BREAK);
}

void print_f56(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2) {
  std::vector<int> test_vector = {};
  int n = 0;

  printf("%s\n", NF_BREAK);

  printf("F56, набор значений 1:\n");
  test_vector = rval_1;
  n = rlen_1;
  printf("F56_val - входной массив:      ");
  print_vector(test_vector, n);
  printf("F56_val - %d\n", S2L1::Functions::F56_val(test_vector));
  printf("F56_val - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_1;
  n = rlen_1;
  printf("F56_ref - входной массив:      ");
  print_vector(test_vector, n);
  printf("F56_ref - %d\n", S2L1::Functions::F56_ref(test_vector));
  printf("F56_ref - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_1;
  n = rlen_1;
  printf("F56_pointer - входной массив:  ");
  print_vector(test_vector, n);
  printf("F56_pointer - %d\n", S2L1::Functions::F56_pointer(&test_vector));
  printf("F56_pointer - итоговый массив: ");
  print_vector(test_vector, n);

  printf("F56, набор значений 2:\n");
  test_vector = rval_2;
  n = rlen_2;
  printf("F56_val - входной массив:      ");
  print_vector(test_vector, n);
  printf("F56_val - %d\n", S2L1::Functions::F56_val(test_vector));
  printf("F56_val - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_2;
  n = rlen_2;
  printf("F56_ref - входной массив:      ");
  print_vector(test_vector, n);
  printf("F56_ref - %d\n", S2L1::Functions::F56_ref(test_vector));
  printf("F56_ref - итоговый массив:     ");
  print_vector(test_vector, n);

  test_vector = rval_2;
  n = rlen_2;
  printf("F56_pointer - входной массив:  ");
  print_vector(test_vector, n);
  printf("F56_pointer - %d\n", S2L1::Functions::F56_pointer(&test_vector));
  printf("F56_pointer - итоговый массив: ");
  print_vector(test_vector, n);

  printf("%s\n", NF_BREAK);
}
}  // namespace S2L1::Output