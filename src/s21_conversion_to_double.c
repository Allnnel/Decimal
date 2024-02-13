#include "s21_decimal.h"

//  ДЛЯ ПЕРЕВОДА В double !!!!!!!!!

int s21_Equate_Double_ToDecimal(s21_decimal value,
                                s21_double_decimal* double_value) {
  int error = 0;
  if (double_value) {
    double_value->bits[0] = value.bits[0];
    double_value->bits[1] = value.bits[1];
    double_value->bits[2] = value.bits[2];
    double_value->bits[5] = value.bits[3];  // степень и знак
  } else
    error = 1;
  return error;
}

int s21_Double_CommonDenominator(s21_double_decimal* value_1,
                                 s21_double_decimal* value_2) {
  int error = 0;
  int sign_1 = s21_Double_GetSign(*value_1);
  int sign_2 = s21_Double_GetSign(*value_2);
  if (sign_1 != sign_2)
    sign_1 == 1 ? s21_Double_SetSign(value_1, 0)
                : s21_Double_SetSign(value_2, 0);
  if (value_1->bits[5] != value_2->bits[5]) {
    if (value_1->bits[5] > value_2->bits[5])
      s21_Double_CommonDenominator(value_2, value_1);
    else {
      value_1->bits[5] = value_1->bits[5] >> 16;
      value_2->bits[5] = value_2->bits[5] >> 16;
      while (value_1->bits[5] != value_2->bits[5]) {
        s21_Double_SubScale(value_1);
        s21_double_decimal one = s21_Double_ShiftLeft(*value_1, 3);
        s21_double_decimal two = s21_Double_ShiftLeft(*value_1, 1);
        *value_1 = s21_Double_Summ(one, two);
      }
      value_1->bits[5] = value_1->bits[5] << 16;
      value_2->bits[5] = value_2->bits[5] << 16;
    }
  }
  if (sign_1 != sign_2)
    sign_1 == 1 ? s21_Double_SetSign(value_1, 1)
                : s21_Double_SetSign(value_2, 1);
  return error;
}

int s21_Double_DecimalZero(s21_double_decimal value_1,
                           s21_double_decimal value_2) {
  int error = 0;
  if ((value_1.bits[0] | value_1.bits[1] | value_1.bits[2]) == 0) error = 1;
  if ((value_2.bits[0] | value_2.bits[1] | value_2.bits[2]) == 0) error += 2;
  return error;
}

s21_double_decimal s21_Double_Summ(s21_double_decimal double_value_1,
                                   s21_double_decimal double_value_2) {
  s21_double_decimal value = {};
  value.bits[5] = double_value_1.bits[5];
  int flag_plus_1 = 0;
  for (int i = 0; i != 160; i++) {
    int number = s21_Double_GetBit(double_value_1, i) +
                 s21_Double_GetBit(double_value_2, i) + flag_plus_1;
    s21_Double_SetBit(&value, i, number % 2);
    flag_plus_1 = number / 2;
  }

  return value;
}

void s21_Double_SubScale(s21_double_decimal* value) { value->bits[5] += 1; }

int s21_Double_GetSign(s21_double_decimal value) {
  return (value.bits[5] >> 31);
}

void s21_Double_SetSign(s21_double_decimal* value, int bit) {
  unsigned number = 1;
  if (bit == 0)
    value->bits[5] = ~(~value->bits[5] | number << 31);
  else
    value->bits[5] = value->bits[5] | number << 31;
}

int s21_Converting_Double_Decimal(s21_decimal* result,
                                  s21_double_decimal double_result) {
  int error = 0;
  if (double_result.bits[3] != 0 || double_result.bits[4] != 0) error = 1;
  if (error == 1 && s21_Double_GetSign(double_result) == 1) error = 2;
  if (error == 0) {
    result->bits[0] = double_result.bits[0];
    result->bits[1] = double_result.bits[1];
    result->bits[2] = double_result.bits[2];
    result->bits[3] = double_result.bits[5];
  }
  return error;
}
