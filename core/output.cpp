#include "output.hpp"
namespace S2L1::Output {
#define NF_BREAK "-----------------------------------------"

void print_vector(std::vector<int> val, int length) {
  printf("{");
  for (int i = 0; i < length; i++) {
    if (i != 0) {
      printf(", ");
    }
    //В рамках данных тестов, все входные значения по модулю меньше 1000.
    printf("%4d", val[i]);
  }
  printf("}\n");
}

void print_function_preexec(const char* name, const int iteration,
                            std::vector<int> array, int length) {
  //Устанавливаем локаль, если вдруг была другая.
  if (!strcmp(setlocale(LC_ALL, NULL), "Russian")) {
    setlocale(LC_ALL, "Russian");
  }
  char out_str[255] = "";
  //Выводим строку сначала в буфер, чтобы иметь возможность указать длину при выводе в stdout.
  snprintf(out_str, 254, "%s-%d-%s", name, iteration, "входной массив");
  printf("%-43s: ", out_str);
  print_vector(array, length);
}

void print_function_postexec(const char* name, const int iteration,
                             std::vector<int> array, int length, int result) {
  if (!strcmp(setlocale(LC_ALL, NULL), "Russian")) {
    setlocale(LC_ALL, "Russian");
  }
  char out_str[255] = "";
  //Выводим строку сначала в буфер, чтобы иметь возможность указать длину при выводе в stdout.
  sprintf(out_str, "%s-%d-%s", name, iteration, "итоговый массив");
  printf("%-44s: ", out_str);
  print_vector(array, length);
  //Выводим строку сначала в буфер, чтобы иметь возможность указать длину при выводе в stdout.
  sprintf(out_str, "%s-%d-%s", name, iteration, "результат");
  printf("%-39s: %d\n", out_str, result);
}

void print_f20(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2) {
  /*
  Здесь и далее:
  test_vector, n - копии эталонных значений для отслеживания изменений
  res - переменная под вывод функций
  */
  std::vector<int> test_vector = {};
  int n = 0;
  int res = 0;

  //Выводим --------------------- для красоты
  printf("%s\n", NF_BREAK);

  /*
  Здесь и далее: логика вывода:
  выводим название функции, номер набора входных значений, входные значения.
  получаем результат работы функции в res.
  выводим название функции, номер набора входных значений, выходные значения.
  выводим название функции, номер набора входных значений, результат работы.
  */
  test_vector = rval_1;
  n = rlen_1;
  print_function_preexec("F20_val", 1, test_vector, n);
  res = S2L1::Functions::F20_val(test_vector, n);
  print_function_postexec("F20_val", 1, test_vector, n, res);

  test_vector = rval_1;
  n = rlen_1;
  print_function_preexec("F20_ref", 1, test_vector, n);
  res = S2L1::Functions::F20_ref(test_vector, n);
  print_function_postexec("F20_ref", 1, test_vector, n, res);

  test_vector = rval_1;
  n = rlen_1;
  print_function_preexec("F20_pointer", 1, test_vector, n);
  res = S2L1::Functions::F20_pointer(&test_vector, &n);
  print_function_postexec("F20_pointer", 1, test_vector, n, res);

  printf("\n");

  test_vector = rval_2;
  n = rlen_2;
  print_function_preexec("F20_val", 2, test_vector, n);
  res = S2L1::Functions::F20_val(test_vector, n);
  print_function_postexec("F20_val", 2, test_vector, n, res);

  test_vector = rval_2;
  n = rlen_2;
  print_function_preexec("F20_ref", 2, test_vector, n);
  res = S2L1::Functions::F20_ref(test_vector, n);
  print_function_postexec("F20_ref", 2, test_vector, n, res);

  test_vector = rval_2;
  n = rlen_2;
  print_function_preexec("F20_pointer", 2, test_vector, n);
  res = S2L1::Functions::F20_pointer(&test_vector, &n);
  print_function_postexec("F20_pointer", 2, test_vector, n, res);

  printf("%s\n", NF_BREAK);
}

void print_f29(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2) {
  std::vector<int> test_vector = {};
  int n = 0;
  int res = 0;

  printf("%s\n", NF_BREAK);

  test_vector = rval_1;
  n = rlen_1;
  print_function_preexec("F29_val", 1, test_vector, n);
  res = S2L1::Functions::F29_val(test_vector, n);
  print_function_postexec("F29_val", 1, test_vector, n, res);

  test_vector = rval_1;
  n = rlen_1;
  print_function_preexec("F29_ref", 1, test_vector, n);
  res = S2L1::Functions::F29_ref(test_vector, n);
  print_function_postexec("F29_ref", 1, test_vector, n, res);

  test_vector = rval_1;
  n = rlen_1;
  print_function_preexec("F29_pointer", 1, test_vector, n);
  res = S2L1::Functions::F29_pointer(&test_vector, &n);
  print_function_postexec("F29_pointer", 1, test_vector, n, res);

  printf("\n");

  test_vector = rval_2;
  n = rlen_2;
  print_function_preexec("F29_val", 2, test_vector, n);
  res = S2L1::Functions::F29_val(test_vector, n);
  print_function_postexec("F29_val", 2, test_vector, n, res);

  test_vector = rval_2;
  n = rlen_2;
  print_function_preexec("F29_ref", 2, test_vector, n);
  res = S2L1::Functions::F29_ref(test_vector, n);
  print_function_postexec("F29_ref", 2, test_vector, n, res);

  test_vector = rval_2;
  n = rlen_2;
  print_function_preexec("F29_pointer", 2, test_vector, n);
  res = S2L1::Functions::F29_pointer(&test_vector, &n);
  print_function_postexec("F29_pointer", 2, test_vector, n, res);

  printf("%s\n", NF_BREAK);
}

void print_f32(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2) {
  std::vector<int> test_vector = {};
  int n = 0, res = 0;

  printf("%s\n", NF_BREAK);

  test_vector = rval_1;
  n = rlen_1;
  print_function_preexec("F32_val", 1, test_vector, n);
  res = S2L1::Functions::F32_val(test_vector, n);
  print_function_postexec("F32_val", 1, test_vector, n, res);

  test_vector = rval_1;
  n = rlen_1;
  print_function_preexec("F32_ref", 1, test_vector, n);
  res = S2L1::Functions::F32_ref(test_vector, n);
  print_function_postexec("F32_ref", 1, test_vector, n, res);

  test_vector = rval_1;
  n = rlen_1;
  print_function_preexec("F32_pointer", 1, test_vector, n);
  res = S2L1::Functions::F32_pointer(&test_vector, &n);
  print_function_postexec("F32_pointer", 1, test_vector, n, res);

  printf("\n");

  test_vector = rval_2;
  n = rlen_2;
  print_function_preexec("F32_val", 2, test_vector, n);
  res = S2L1::Functions::F32_val(test_vector, n);
  print_function_postexec("F32_val", 2, test_vector, n, res);

  test_vector = rval_2;
  n = rlen_2;
  print_function_preexec("F32_ref", 2, test_vector, n);
  res = S2L1::Functions::F32_ref(test_vector, n);
  print_function_postexec("F32_ref", 2, test_vector, n, res);

  test_vector = rval_2;
  n = rlen_2;
  print_function_preexec("F32_pointer", 2, test_vector, n);
  res = S2L1::Functions::F32_pointer(&test_vector, &n);
  print_function_postexec("F32_pointer", 2, test_vector, n, res);

  printf("%s\n", NF_BREAK);
}

void print_f50(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2) {
  std::vector<int> test_vector = {};
  int n = 0;
  int res = 0;

  printf("%s\n", NF_BREAK);

  test_vector = rval_1;
  n = rlen_1;
  print_function_preexec("F50_val", 1, test_vector, n);
  res = S2L1::Functions::F50_val(test_vector);
  print_function_postexec("F50_val", 1, test_vector, n, res);

  test_vector = rval_1;
  n = rlen_1;
  print_function_preexec("F50_ref", 1, test_vector, n);
  res = S2L1::Functions::F50_ref(test_vector);
  print_function_postexec("F50_ref", 1, test_vector, n, res);

  test_vector = rval_1;
  n = rlen_1;
  print_function_preexec("F50_pointer", 1, test_vector, n);
  res = S2L1::Functions::F50_pointer(&test_vector);
  print_function_postexec("F50_pointer", 1, test_vector, n, res);

  printf("\n");

  test_vector = rval_2;
  n = rlen_2;
  print_function_preexec("F50_val", 2, test_vector, n);
  res = S2L1::Functions::F50_val(test_vector);
  print_function_postexec("F50_val", 2, test_vector, n, res);

  test_vector = rval_2;
  n = rlen_2;
  print_function_preexec("F50_ref", 2, test_vector, n);
  res = S2L1::Functions::F50_ref(test_vector);
  print_function_postexec("F50_ref", 2, test_vector, n, res);

  test_vector = rval_2;
  n = rlen_2;
  print_function_preexec("F50_pointer", 2, test_vector, n);
  res = S2L1::Functions::F50_pointer(&test_vector);
  print_function_postexec("F50_pointer", 2, test_vector, n, res);

  printf("%s\n", NF_BREAK);
}

void print_f56(std::vector<int> rval_1, std::vector<int> rval_2, int rlen_1,
               int rlen_2) {
  std::vector<int> test_vector = {};
  int n = 0, res = 0;

  printf("%s\n", NF_BREAK);

  test_vector = rval_1;
  n = rlen_1;
  print_function_preexec("F56_val", 1, test_vector, n);
  res = S2L1::Functions::F56_val(test_vector);
  print_function_postexec("F56_val", 1, test_vector, n, res);

  test_vector = rval_1;
  n = rlen_1;
  print_function_preexec("F56_ref", 1, test_vector, n);
  res = S2L1::Functions::F56_ref(test_vector);
  print_function_postexec("F56_ref", 1, test_vector, n, res);

  test_vector = rval_1;
  n = rlen_1;
  print_function_preexec("F56_pointer", 1, test_vector, n);
  res = S2L1::Functions::F56_pointer(&test_vector);
  print_function_postexec("F56_pointer", 1, test_vector, n, res);

  printf("\n");

  test_vector = rval_2;
  n = rlen_2;
  print_function_preexec("F56_val", 2, test_vector, n);
  res = S2L1::Functions::F56_val(test_vector);
  print_function_postexec("F56_val", 2, test_vector, n, res);

  test_vector = rval_2;
  n = rlen_2;
  print_function_preexec("F56_ref", 2, test_vector, n);
  res = S2L1::Functions::F56_ref(test_vector);
  print_function_postexec("F56_ref", 2, test_vector, n, res);

  test_vector = rval_2;
  n = rlen_2;
  print_function_preexec("F56_pointer", 2, test_vector, n);
  res = S2L1::Functions::F56_pointer(&test_vector);
  print_function_postexec("F56_pointer", 2, test_vector, n, res);

  printf("%s\n", NF_BREAK);
}
}  // namespace S2L1::Output