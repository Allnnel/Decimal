#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_
#include <limits.h>  // UINT_MAX -  это макрос, который определяет наибольшее возможное значение для беззнакового целого типа данных (unsigned int).
#include <math.h>
#include <stdio.h>

// MATH
#define S21_PI 3.14159265358979323846
#define precision 0.00000000000000000000001
#define S21_NAN 0.0 / 0.0
#define S21_INF 1.0 / 0.0
typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[6];
} s21_double_decimal;

// s21_aritmetic.c
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_s21_Double_SubScale(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_double_add(s21_double_decimal double_value_1,
                    s21_double_decimal double_value_2,
                    s21_double_decimal *double_result);
void s21_double_sub(s21_double_decimal double_value_1,
                    s21_double_decimal double_value_2,
                    s21_double_decimal *double_result);
void s21_double_mul(s21_double_decimal double_value_1,
                    s21_double_decimal double_value_2,
                    s21_double_decimal *double_result);
int s21_double_div(s21_double_decimal double_value_1,
                   s21_double_decimal double_value_2,
                   s21_double_decimal *double_result);
void s21_Division(s21_double_decimal double_value_1,
                  s21_double_decimal double_value_2,
                  s21_double_decimal *double_result, s21_double_decimal *tmp);

// s21_conversion_to_double.c
int s21_Equate_Double_ToDecimal(s21_decimal value,
                                s21_double_decimal *double_value);
int s21_Double_DecimalZero(s21_double_decimal value_1,
                           s21_double_decimal value_2);
int s21_Double_DecimalZeroOne(s21_double_decimal tmp);  /// new
s21_double_decimal s21_Double_Summ(s21_double_decimal double_value_1,
                                   s21_double_decimal double_value_2);
void s21_Double_SubScale(s21_double_decimal *value);
int s21_Double_GetSign(s21_double_decimal value);
void s21_Double_SetSign(s21_double_decimal *value, int bit);
int s21_Converting_Double_Decimal(s21_decimal *result,
                                  s21_double_decimal double_result);
s21_double_decimal s21_Double_ShiftLeft(s21_double_decimal value, int inex);
int s21_Double_CommonDenominator(s21_double_decimal *value_1,
                                 s21_double_decimal *value_2);

// s21_compare.c
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_Double_Greater(s21_double_decimal double_value_1,
                       s21_double_decimal double_value_2);
int s21_Double_Equal(s21_double_decimal double_value_1,
                     s21_double_decimal double_value_2);

// s21_convertion.c
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);

// s21_other.c
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int copy_decimal(s21_decimal src, s21_decimal *dst);
int s21_round(s21_decimal value, s21_decimal *result);

// s21_math.c
long double s21_fabs(double x);
long double s21_fmod(double x, double y);
int s21_floor(s21_decimal value, s21_decimal *result);

// s21_functions.c
void s21_Double_SetBit(s21_double_decimal *dec, int index, int bit);
int s21_Double_GetBit(s21_double_decimal dec, int index);
void s21_Double_DecimalToNull(s21_double_decimal *value);
int s21_Decimal_ToNull(s21_decimal *src);
int s21_GetSign(s21_decimal dec);
int s21_GetBit(s21_decimal dec, int index);
int s21_GetScale(s21_decimal dec);
void s21_SetBit(s21_decimal *dec, int index, int bit);
void s21_SetScale(s21_decimal *dec, int scale);
void s21_SetSign(s21_decimal *dec, int sign);
int s21_GetBitToFloat(double number, int bit_number);
int s21_DecimalOne(s21_decimal tmp);
s21_double_decimal s21_Double_ShiftRightTen(s21_double_decimal double_value,
                                            int shift);
s21_double_decimal s21_ShiftLeftTen(s21_double_decimal src, int shift);
int s21_CheckFraction(s21_double_decimal double_value);
int s21_Double_DecimalZeroOne(s21_double_decimal tmp);
void div_other(s21_decimal value_1, s21_decimal *result, s21_decimal *rem,
               int number);
s21_decimal s21_ShiftLeft(s21_decimal value, int inex);
int s21_Greater(s21_decimal value_1, s21_decimal value_2);
void s21_other_sub(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);
int s21_bankround(s21_decimal value, s21_decimal *result);
s21_double_decimal s21_double_div_ten(s21_double_decimal double_value);

#endif
