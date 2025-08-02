#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Matritsa tuzilmasi
typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
} matrix_t;

// Xato kodlari
#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2

// Funksiya prototiplari
int s21_create_matrix(int rows, int columns, matrix_t* result);
void s21_remove_matrix(matrix_t* A);
int s21_eq_matrix(matrix_t* A, matrix_t* B);
int s21_sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
int s21_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
int s21_mult_number(matrix_t* A, double number, matrix_t* result);
int s21_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
int s21_transpose(matrix_t* A, matrix_t* result);
int s21_calc_complements(matrix_t* A, matrix_t* result);
int s21_determinant(matrix_t* A, double* result);
int s21_inverse_matrix(matrix_t* A, matrix_t* result);

// Yordamchi funksiyalar
int s21_is_valid_matrix(matrix_t* A);
void s21_copy_matrix(matrix_t* from, matrix_t* to);
void s21_get_minor(matrix_t* A, matrix_t* minor_matrix, int row, int column);
double s21_get_determinant(matrix_t* A);

#endif  // S21_MATRIX_H