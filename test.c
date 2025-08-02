#include <check.h>
#include <stdlib.h>

#include "s21_matrix.h"

// create_matrix funksiyasi uchun test to'plami
START_TEST(create_matrix_test) {
  matrix_t matrix;
  int rows = 3;
  int cols = 3;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &matrix), OK);
  s21_remove_matrix(&matrix);

  // Noto'g'ri o'lchamlar
  ck_assert_int_eq(s21_create_matrix(-1, 3, &matrix), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_create_matrix(3, -1, &matrix), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_create_matrix(0, 0, &matrix), INCORRECT_MATRIX);
}
END_TEST

// remove_matrix funksiyasi uchun test to'plami
START_TEST(remove_matrix_test) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

// eq_matrix funksiyasi uchun test to'plami
START_TEST(eq_matrix_test) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  // Bir xil matritsalar
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = B.matrix[i][j] = i + j;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

  // Har xil matritsalar
  B.matrix[1][1] = 10;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  // Noto'g'ri o'lchamlar
  matrix_t C;
  s21_create_matrix(2, 2, &C);
  ck_assert_int_eq(s21_eq_matrix(&A, &C), FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

// sum_matrix funksiyasi uchun test to'plami
START_TEST(sum_matrix_test) {
  matrix_t A, B, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &expected);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i;
      B.matrix[i][j] = j;
      expected.matrix[i][j] = i + j;
    }
  }

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  // Hisoblash xatosi
  matrix_t C;
  s21_create_matrix(2, 2, &C);
  ck_assert_int_eq(s21_sum_matrix(&A, &C, &result), CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&C);
}
END_TEST

// sub_matrix funksiyasi uchun test to'plami
START_TEST(sub_matrix_test) {
  matrix_t A, B, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &expected);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i;
      B.matrix[i][j] = j;
      expected.matrix[i][j] = i - j;
    }
  }

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  // Hisoblash xatosi
  matrix_t C;
  s21_create_matrix(2, 2, &C);
  ck_assert_int_eq(s21_sub_matrix(&A, &C, &result), CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&C);
}
END_TEST

// mult_number funksiyasi uchun test to'plami
START_TEST(mult_number_test) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);
  double num = 2.0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i;
      expected.matrix[i][j] = i * num;
    }
  }

  ck_assert_int_eq(s21_mult_number(&A, num, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// mult_matrix funksiyasi uchun test to'plami
START_TEST(mult_matrix_test) {
  matrix_t A, B, result, expected;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 4;

  expected.matrix[0][0] = 9;
  expected.matrix[0][1] = 11;
  expected.matrix[0][2] = 17;
  expected.matrix[1][0] = 12;
  expected.matrix[1][1] = 13;
  expected.matrix[1][2] = 22;
  expected.matrix[2][0] = 15;
  expected.matrix[2][1] = 15;
  expected.matrix[2][2] = 27;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  // Hisoblash xatosi
  matrix_t C;
  s21_create_matrix(3, 3, &C);
  ck_assert_int_eq(s21_mult_matrix(&A, &C, &result), CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&C);
}
END_TEST

// transpose funksiyasi uchun test to'plami
START_TEST(transpose_test) {
  matrix_t A, result, expected;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  expected.matrix[0][0] = 1;
  expected.matrix[1][0] = 2;
  expected.matrix[2][0] = 3;
  expected.matrix[0][1] = 4;
  expected.matrix[1][1] = 5;
  expected.matrix[2][1] = 6;

  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// determinant funksiyasi uchun test to'plami
START_TEST(determinant_test) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  double det = 0;
  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq_tol(det, 0, 1e-7);

  s21_remove_matrix(&A);

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;
  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq_tol(det, 5, 1e-7);
  s21_remove_matrix(&A);

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq_tol(det, -2, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

// calc_complements funksiyasi uchun test to'plami
START_TEST(calc_complements_test) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;

  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

// inverse_matrix funksiyasi uchun test to'plami
START_TEST(inverse_matrix_test) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = -1;
  expected.matrix[0][2] = 1;
  expected.matrix[1][0] = -38;
  expected.matrix[1][1] = 41;
  expected.matrix[1][2] = -34;
  expected.matrix[2][0] = 27;
  expected.matrix[2][1] = -29;
  expected.matrix[2][2] = 24;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);

  // Determinant 0 bo'lganda test
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

Suite *matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Matrix Operations");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, create_matrix_test);
  tcase_add_test(tc_core, remove_matrix_test);
  tcase_add_test(tc_core, eq_matrix_test);
  tcase_add_test(tc_core, sum_matrix_test);
  tcase_add_test(tc_core, sub_matrix_test);
  tcase_add_test(tc_core, mult_number_test);
  tcase_add_test(tc_core, mult_matrix_test);
  tcase_add_test(tc_core, transpose_test);
  tcase_add_test(tc_core, determinant_test);
  tcase_add_test(tc_core, calc_complements_test);
  tcase_add_test(tc_core, inverse_matrix_test);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = matrix_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
