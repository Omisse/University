#include "functions.hpp"

namespace S2L1::Functions {
int find_max(std::vector<int> A, int n) {
  int out = 0x80000000;  // min int
  for (int i = 0; i < n; i++) {
    if (A[i] > out) {
      out = A[i];
    }
  }
  return out;
}

int F20_val(std::vector<int> A, int n) {
  int i = 0, k = 0, j = 0;
  for (i = 1, k = 0; i < n; i++)
    if (A[i] > A[k]) k = i;
  int out = A[k];
  for (j = k; j < n - 1; j++) A[j] = A[j + 1];
  n--;
  return out;
}

int F20_ref(std::vector<int>& A, int& n) {
  int i = 0, k = 0, j = 0;
  for (i = 1, k = 0; i < n; i++)
    if (A[i] > A[k]) k = i;
  int out = A[k];
  for (j = k; j < n - 1; j++) A[j] = A[j + 1];
  n--;
  return out;
}

int F20_pointer(std::vector<int>* A, int* n) {
  int i = 0, k = 0, j = 0;
  for (i = 1, k = 0; i < *n; i++)
    if ((*A)[i] > (*A)[k]) k = i;
  int out = (*A)[k];
  for (j = k; j < (*n) - 1; j++) (*A)[j] = (*A)[j + 1];
  (*n)--;
  return out;
}

int F29_val(std::vector<int> A, int n) {
  int v = find_max(A, n);
  int i = 0;
  for (i = 0; i < n; i++)
    if (A[i] % v != 0) {
      v--;
      i = -1;
    }
  return v;
}

int F29_ref(std::vector<int>& A, int& n) {
  int v = find_max(A, n);
  int i = 0;
  for (i = 0; i < n; i++)
    if (A[i] % v != 0) {
      v--;
      i = -1;
    }
  return v;
}

int F29_pointer(std::vector<int>* A, int* n) {
  int v = find_max(*A, *n);
  int i = 0;
  for (i = 0; i < *n; i++)
    if ((*A)[i] % v != 0) {
      v--;
      i = -1;
    }
  return v;
}

int F32_val(std::vector<int> c, int n) {
  int s, i, k, j, b;
  for (s = 0, i = 0; i < n; i++) {
    for (k = 0, j = 0; j < n; j++)
      if (c[i] == c[j]) k++;
    if (k > s) s = k, b = i;
  }
  return b;
}

int F32_ref(std::vector<int>& c, int& n) {
  int s, i, k, j, b;
  for (s = 0, i = 0; i < n; i++) {
    for (k = 0, j = 0; j < n; j++)
      if (c[i] == c[j]) k++;
    if (k > s) s = k, b = i;
  }
  return b;
}

int F32_pointer(std::vector<int>* c, int* n) {
  int s, i, k, j, b;
  for (s = 0, i = 0; i < (*n); i++) {
    for (k = 0, j = 0; j < (*n); j++)
      if ((*c)[i] == (*c)[j]) k++;
    if (k > s) s = k, b = i;
  }
  return b;
}

int F50_val(std::vector<int> A) {
  int i, s, k;
  for (i = 0, s = 0, k = 0; i < 10; i++) {
    if (A[i] < 0)
      k = 1;
    else {
      if (k == 1) s++;
      k = 0;
    }
  }
  return s;
}

int F50_ref(std::vector<int>& A) {
  int i, s, k;
  for (i = 0, s = 0, k = 0; i < 10; i++) {
    if (A[i] < 0)
      k = 1;
    else {
      if (k == 1) s++;
      k = 0;
    }
  }
  return s;
}

int F50_pointer(std::vector<int>* A) {
  int i, s, k;
  for (i = 0, s = 0, k = 0; i < 10; i++) {
    if ((*A)[i] < 0)
      k = 1;
    else {
      if (k == 1) s++;
      k = 0;
    }
  }
  return s;
}

int F56_val(std::vector<int> A) {
  int i, s = 0;
  for (i = 1, s = 0; i < 10; i++)
    if (A[i] > 0 && A[i - 1] < 0) s++;
  return s;
}

int F56_ref(std::vector<int>& A) {
  int i, s = 0;
  for (i = 1, s = 0; i < 10; i++)
    if (A[i] > 0 && A[i - 1] < 0) s++;
  return s;
}

int F56_pointer(std::vector<int>* A) {
  int i, s = 0;
  for (i = 1, s = 0; i < 10; i++)
    if ((*A)[i] > 0 && (*A)[i - 1] < 0) s++;
  return s;
}
}  // namespace S2L1::Functions
