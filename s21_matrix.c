#include "s21_matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Matritsa yaratadi va unga xotira ajratadi.
 *
 * @param rows Matritsa qatorlari soni.
 * @param columns Matritsa ustunlari soni.
 * @param result Yaratilgan matritsaga ishora qiluvchi ko'rsatkich.
 * @return int OK (0) yoki INCORRECT_MATRIX (1) xato kodi.
 */
int s21_create_matrix(int rows, int columns, matrix_t* result) {
  int res = OK;
  if (rows <= 0 || columns <= 0) {
    res = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double**)calloc(rows, sizeof(double*));
    if (result->matrix == NULL) {
      res = INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double*)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          s21_remove_matrix(result);
          res = INCORRECT_MATRIX;
          break;
        }
      }
    }
  }
  return res;
}

/**
 * @brief Matritsaning xotirasini bo'shatadi.
 *
 * @param A O'chiriladigan matritsaga ishora qiluvchi ko'rsatkich.
 */
void s21_remove_matrix(matrix_t* A) {
  if (A && A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) {
        free(A->matrix[i]);
      }
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

/**
 * @brief Ikkita matritsani taqqoslaydi.
 *
 * @param A Birinchi matritsaga ishora qiluvchi ko'rsatkich.
 * @param B Ikkinchi matritsaga ishora qiluvchi ko'rsatkich.
 * @return int SUCCESS (1) yoki FAILURE (0) xato kodi.
 */
int s21_eq_matrix(matrix_t* A, matrix_t* B) {
  int res = SUCCESS;
  if (!s21_is_valid_matrix(A) || !s21_is_valid_matrix(B) || A->rows != B->rows ||
      A->columns != B->columns) {
    res = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
          res = FAILURE;
          break;
        }
      }
      if (res == FAILURE) {
        break;
      }
    }
  }
  return res;
}

/**
 * @brief Ikkita matritsani qo'shadi.
 *
 * @param A Birinchi matritsaga ishora qiluvchi ko'rsatkich.
 * @param B Ikkinchi matritsaga ishora qiluvchi ko'rsatkich.
 * @param result Natijaviy matritsaga ishora qiluvchi ko'rsatkich.
 * @return int OK (0), INCORRECT_MATRIX (1) yoki CALCULATION_ERROR (2) xato kodi.
 */
int s21_sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  int res = OK;
  if (!s21_is_valid_matrix(A) || !s21_is_valid_matrix(B)) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    res = CALCULATION_ERROR;
  } else {
    if (s21_create_matrix(A->rows, A->columns, result) == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      res = INCORRECT_MATRIX;
    }
  }
  return res;
}

/**
 * @brief Ikkita matritsani ayiradi.
 *
 * @param A Birinchi matritsaga ishora qiluvchi ko'rsatkich.
 * @param B Ikkinchi matritsaga ishora qiluvchi ko'rsatkich.
 * @param result Natijaviy matritsaga ishora qiluvchi ko'rsatkich.
 * @return int OK (0), INCORRECT_MATRIX (1) yoki CALCULATION_ERROR (2) xato kodi.
 */
int s21_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  int res = OK;
  if (!s21_is_valid_matrix(A) || !s21_is_valid_matrix(B)) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    res = CALCULATION_ERROR;
  } else {
    if (s21_create_matrix(A->rows, A->columns, result) == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      res = INCORRECT_MATRIX;
    }
  }
  return res;
}

/**
 * @brief Matritsani songa ko'paytiradi.
 *
 * @param A Ko'paytiriladigan matritsaga ishora qiluvchi ko'rsatkich.
 * @param number Ko'paytiriladigan skalyar son.
 * @param result Natijaviy matritsaga ishora qiluvchi ko'rsatkich.
 * @return int OK (0) yoki INCORRECT_MATRIX (1) xato kodi.
 */
int s21_mult_number(matrix_t* A, double number, matrix_t* result) {
  int res = OK;
  if (!s21_is_valid_matrix(A)) {
    res = INCORRECT_MATRIX;
  } else {
    if (s21_create_matrix(A->rows, A->columns, result) == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    } else {
      res = INCORRECT_MATRIX;
    }
  }
  return res;
}

/**
 * @brief Ikkita matritsani ko'paytiradi.
 *
 * @param A Birinchi matritsaga ishora qiluvchi ko'rsatkich.
 * @param B Ikkinchi matritsaga ishora qiluvchi ko'rsatkich.
 * @param result Natijaviy matritsaga ishora qiluvchi ko'rsatkich.
 * @return int OK (0), INCORRECT_MATRIX (1) yoki CALCULATION_ERROR (2) xato kodi.
 */
int s21_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  int res = OK;
  if (!s21_is_valid_matrix(A) || !s21_is_valid_matrix(B)) {
    res = INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    res = CALCULATION_ERROR;
  } else {
    if (s21_create_matrix(A->rows, B->columns, result) == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = 0;
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      res = INCORRECT_MATRIX;
    }
  }
  return res;
}

/**
 * @brief Matritsani transponirlaydi.
 *
 * @param A Transponirlanadigan matritsaga ishora qiluvchi ko'rsatkich.
 * @param result Natijaviy matritsaga ishora qiluvchi ko'rsatkich.
 * @return int OK (0) yoki INCORRECT_MATRIX (1) xato kodi.
 */
int s21_transpose(matrix_t* A, matrix_t* result) {
  int res = OK;
  if (!s21_is_valid_matrix(A)) {
    res = INCORRECT_MATRIX;
  } else {
    if (s21_create_matrix(A->columns, A->rows, result) == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    } else {
      res = INCORRECT_MATRIX;
    }
  }
  return res;
}

/**
 * @brief Matritsaning algebraik to'ldiruvchilarini hisoblaydi.
 *
 * @param A Matritsaga ishora qiluvchi ko'rsatkich.
 * @param result Algebraik to'ldiruvchilar matritsasiga ishora qiluvchi ko'rsatkich.
 * @return int OK (0), INCORRECT_MATRIX (1) yoki CALCULATION_ERROR (2) xato kodi.
 */
int s21_calc_complements(matrix_t* A, matrix_t* result) {
  int res = OK;
  if (!s21_is_valid_matrix(A)) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res = CALCULATION_ERROR;
  } else {
    if (s21_create_matrix(A->rows, A->columns, result) == OK) {
      if (A->rows == 1) {
        result->matrix[0][0] = 1;
      } else {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            matrix_t minor;
            s21_get_minor(A, &minor, i, j);
            double det_minor = s21_get_determinant(&minor);
            result->matrix[i][j] = det_minor * pow(-1, i + j);
            s21_remove_matrix(&minor);
          }
        }
      }
    } else {
      res = INCORRECT_MATRIX;
    }
  }
  return res;
}

/**
 * @brief Kvadrat matritsaning determinantini hisoblaydi.
 *
 * @param A Matritsaga ishora qiluvchi ko'rsatkich.
 * @param result Determinant qiymatiga ishora qiluvchi ko'rsatkich.
 * @return int OK (0), INCORRECT_MATRIX (1) yoki CALCULATION_ERROR (2) xato kodi.
 */
int s21_determinant(matrix_t* A, double* result) {
  int res = OK;
  if (!s21_is_valid_matrix(A)) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res = CALCULATION_ERROR;
  } else {
    *result = s21_get_determinant(A);
  }
  return res;
}

/**
 * @brief Kvadrat matritsaning teskari matritsasini hisoblaydi.
 *
 * @param A Matritsaga ishora qiluvchi ko'rsatkich.
 * @param result Teskari matritsaga ishora qiluvchi ko'rsatkich.
 * @return int OK (0), INCORRECT_MATRIX (1) yoki CALCULATION_ERROR (2) xato kodi.
 */
int s21_inverse_matrix(matrix_t* A, matrix_t* result) {
  int res = OK;
  if (!s21_is_valid_matrix(A)) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res = CALCULATION_ERROR;
  } else {
    double det = 0;
    s21_determinant(A, &det);
    if (fabs(det) < 1e-7) {
      res = CALCULATION_ERROR;
    } else {
      if (A->rows == 1) {
        if (s21_create_matrix(1, 1, result) == OK) {
          result->matrix[0][0] = 1.0 / A->matrix[0][0];
        } else {
          res = INCORRECT_MATRIX;
        }
      } else {
        matrix_t complements;
        s21_calc_complements(A, &complements);
        matrix_t transposed_complements;
        s21_transpose(&complements, &transposed_complements);
        s21_mult_number(&transposed_complements, 1.0 / det, result);
        s21_remove_matrix(&complements);
        s21_remove_matrix(&transposed_complements);
      }
    }
  }
  return res;
}

/**
 * @brief Matritsaning to'g'ri ekanligini tekshiradi.
 *
 * @param A Tekshiriladigan matritsaga ishora qiluvchi ko'rsatkich.
 * @return int SUCCESS (1) yoki FAILURE (0) xato kodi.
 */
int s21_is_valid_matrix(matrix_t* A) {
  int res = FAILURE;
  if (A && A->matrix && A->rows > 0 && A->columns > 0) {
    res = SUCCESS;
  }
  return res;
}

/**
 * @brief Matritsani boshqa matritsaga nusxalaydi.
 *
 * @param from Nusxalanadigan matritsa.
 * @param to Nusxalanuvchi matritsa.
 */
void s21_copy_matrix(matrix_t* from, matrix_t* to) {
  s21_create_matrix(from->rows, from->columns, to);
  for (int i = 0; i < from->rows; i++) {
    for (int j = 0; j < from->columns; j++) {
      to->matrix[i][j] = from->matrix[i][j];
    }
  }
}

/**
 * @brief Berilgan matritsadan minor matritsani yaratadi.
 *
 * @param A Asosiy matritsa.
 * @param minor_matrix Yaratiladigan minor matritsa.
 * @param row O'chiriladigan qator indeksi.
 * @param column O'chiriladigan ustun indeksi.
 */
void s21_get_minor(matrix_t* A, matrix_t* minor_matrix, int row, int column) {
  s21_create_matrix(A->rows - 1, A->columns - 1, minor_matrix);
  int minor_i = 0;
  int minor_j = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == row) continue;
    minor_j = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == column) continue;
      minor_matrix->matrix[minor_i][minor_j] = A->matrix[i][j];
      minor_j++;
    }
    minor_i++;
  }
}

/**
 * @brief Rekursiv usulda determinantni hisoblaydi.
 *
 * @param A Matritsaga ishora qiluvchi ko'rsatkich.
 * @return double Hisoblangan determinant qiymati.
 */
double s21_get_determinant(matrix_t* A) {
  double det = 0;
  if (A->rows == 1) {
    det = A->matrix[0][0];
  } else if (A->rows == 2) {
    det = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    for (int j = 0; j < A->columns; j++) {
      matrix_t minor;
      s21_get_minor(A, &minor, 0, j);
      det += A->matrix[0][j] * pow(-1, j) * s21_get_determinant(&minor);
      s21_remove_matrix(&minor);
    }
  }
  return det;
}