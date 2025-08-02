#include <stdio.h>
#include <stdlib.h>

#include "s21_matrix.h"

// Yordamchi funksiya: matritsani ekranga chiqarish
void print_matrix(matrix_t* A, const char* title) {
  printf("--- %s ---\n", title);
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        printf("%10.2f ", A->matrix[i][j]);
      }
      printf("\n");
    }
  } else {
    printf("Matritsa mavjud emas.\n");
  }
  printf("----------------\n");
}

int main() {
  int result_code;
  matrix_t A, B, C;
  double det_result;

  printf("Matritsa operatsiyalarini sinovdan o'tkazish\n\n");

  // 1. Matritsa yaratish va o'chirish misoli
  printf("1. create_matrix va remove_matrix misoli\n");
  result_code = s21_create_matrix(3, 3, &A);
  if (result_code == OK) {
    print_matrix(&A, "Yangi yaratilgan A matritsasi");
    s21_remove_matrix(&A);
    print_matrix(&A, "O'chirilgan A matritsasi");
  } else {
    printf("Matritsa yaratishda xato: %d\n", result_code);
  }

  // 2. Ikkita matritsani taqqoslash misoli
  printf("\n2. eq_matrix misoli\n");
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1; A.matrix[0][1] = 2;
  A.matrix[1][0] = 3; A.matrix[1][1] = 4;
  B.matrix[0][0] = 1; B.matrix[0][1] = 2;
  B.matrix[1][0] = 3; B.matrix[1][1] = 4;
  if (s21_eq_matrix(&A, &B) == SUCCESS) {
    printf("A va B matritsalari teng.\n");
  } else {
    printf("A va B matritsalari teng emas.\n");
  }
  B.matrix[1][1] = 5; // Matritsani o'zgartirish
  if (s21_eq_matrix(&A, &B) == SUCCESS) {
    printf("A va B matritsalari teng.\n");
  } else {
    printf("A va B matritsalari teng emas.\n");
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  // 3. Matritsalarni qo'shish misoli
  printf("\n3. sum_matrix misoli\n");
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1; A.matrix[0][1] = 2;
  A.matrix[1][0] = 3; A.matrix[1][1] = 4;
  B.matrix[0][0] = 5; B.matrix[0][1] = 6;
  B.matrix[1][0] = 7; B.matrix[1][1] = 8;
  result_code = s21_sum_matrix(&A, &B, &C);
  if (result_code == OK) {
    print_matrix(&A, "Matritsa A");
    print_matrix(&B, "Matritsa B");
    print_matrix(&C, "A + B natijasi");
    s21_remove_matrix(&C);
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  // 4. Matritsalarni ayirish misoli
  printf("\n4. sub_matrix misoli\n");
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1; A.matrix[0][1] = 2;
  A.matrix[1][0] = 3; A.matrix[1][1] = 4;
  B.matrix[0][0] = 5; B.matrix[0][1] = 6;
  B.matrix[1][0] = 7; B.matrix[1][1] = 8;
  result_code = s21_sub_matrix(&A, &B, &C);
  if (result_code == OK) {
    print_matrix(&A, "Matritsa A");
    print_matrix(&B, "Matritsa B");
    print_matrix(&C, "A - B natijasi");
    s21_remove_matrix(&C);
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  // 5. Matritsani songa ko'paytirish misoli
  printf("\n5. mult_number misoli\n");
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1; A.matrix[0][1] = 2;
  A.matrix[1][0] = 3; A.matrix[1][1] = 4;
  double number = 2.5;
  result_code = s21_mult_number(&A, number, &C);
  if (result_code == OK) {
    print_matrix(&A, "Matritsa A");
    printf("Ko'paytiruvchi son: %.2f\n", number);
    print_matrix(&C, "A * 2.5 natijasi");
    s21_remove_matrix(&C);
  }
  s21_remove_matrix(&A);

  // 6. Matritsalarni ko'paytirish misoli
  printf("\n6. mult_matrix misoli\n");
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3;
  A.matrix[1][0] = 4; A.matrix[1][1] = 5; A.matrix[1][2] = 6;
  B.matrix[0][0] = 7; B.matrix[0][1] = 8;
  B.matrix[1][0] = 9; B.matrix[1][1] = 1;
  B.matrix[2][0] = 2; B.matrix[2][1] = 3;
  result_code = s21_mult_matrix(&A, &B, &C);
  if (result_code == OK) {
    print_matrix(&A, "Matritsa A (2x3)");
    print_matrix(&B, "Matritsa B (3x2)");
    print_matrix(&C, "A * B natijasi (2x2)");
    s21_remove_matrix(&C);
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  // 7. Matritsani transponirlash misoli
  printf("\n7. transpose misoli\n");
  s21_create_matrix(2, 3, &A);
  A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3;
  A.matrix[1][0] = 4; A.matrix[1][1] = 5; A.matrix[1][2] = 6;
  result_code = s21_transpose(&A, &C);
  if (result_code == OK) {
    print_matrix(&A, "Asl A matritsasi");
    print_matrix(&C, "A^T transponirlangan matritsasi");
    s21_remove_matrix(&C);
  }
  s21_remove_matrix(&A);

  // 8. Determinantni hisoblash misoli
  printf("\n8. determinant misoli\n");
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3;
  A.matrix[1][0] = 4; A.matrix[1][1] = 5; A.matrix[1][2] = 6;
  A.matrix[2][0] = 7; A.matrix[2][1] = 8; A.matrix[2][2] = 9;
  result_code = s21_determinant(&A, &det_result);
  if (result_code == OK) {
    print_matrix(&A, "Matritsa A");
    printf("Determinant |A| = %.2f\n", det_result);
  }
  s21_remove_matrix(&A);

  // 9. Algebraik to'ldiruvchilar matritsasini hisoblash misoli
  printf("\n9. calc_complements misoli\n");
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3;
  A.matrix[1][0] = 0; A.matrix[1][1] = 4; A.matrix[1][2] = 2;
  A.matrix[2][0] = 5; A.matrix[2][1] = 2; A.matrix[2][2] = 1;
  result_code = s21_calc_complements(&A, &C);
  if (result_code == OK) {
    print_matrix(&A, "Asl A matritsasi");
    print_matrix(&C, "Algebraik to'ldiruvchilar matritsasi");
    s21_remove_matrix(&C);
  }
  s21_remove_matrix(&A);

  // 10. Teskari matritsani hisoblash misoli
  printf("\n10. inverse_matrix misoli\n");
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2; A.matrix[0][1] = 5; A.matrix[0][2] = 7;
  A.matrix[1][0] = 6; A.matrix[1][1] = 3; A.matrix[1][2] = 4;
  A.matrix[2][0] = 5; A.matrix[2][1] = -2; A.matrix[2][2] = -3;
  result_code = s21_inverse_matrix(&A, &C);
  if (result_code == OK) {
    print_matrix(&A, "Asl A matritsasi");
    print_matrix(&C, "Teskari A matritsasi (A^-1)");
    // A * A^-1 = I (yakka matritsa) ekanligini tekshirish
    matrix_t Identity_Check;
    s21_mult_matrix(&A, &C, &Identity_Check);
    print_matrix(&Identity_Check, "A * A^-1 (Tekshirish natijasi)");
    s21_remove_matrix(&Identity_Check);
    s21_remove_matrix(&C);
  } else {
    printf("Teskari matritsani topishda xato: %d\n", result_code);
  }
  s21_remove_matrix(&A);

  return 0;
}
