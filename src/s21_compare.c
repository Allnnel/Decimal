#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int less = 0;
  if ((value_1.bits[0] | value_1.bits[1] | value_1.bits[2] | value_2.bits[0] |
       value_2.bits[1] | value_2.bits[2]) != 0) {
    s21_double_decimal double_value_1 = {};
    s21_double_decimal double_value_2 = {};
    s21_Equate_Double_ToDecimal(value_1, &double_value_1);
    s21_Equate_Double_ToDecimal(value_2, &double_value_2);
    int sign_1 = s21_Double_GetSign(double_value_1);
    int sign_2 = s21_Double_GetSign(double_value_2);
    if (sign_1 == sign_2) {
      s21_Double_CommonDenominator(&double_value_1, &double_value_2);
      for (int i = 5; i >= 0 && less == 0; i--) {
        if (double_value_1.bits[i] > double_value_2.bits[i])
          less = sign_1 != 1 ? 2 : 1;
        else if (double_value_1.bits[i] < double_value_2.bits[i])
          less = sign_1 != 1 ? 1 : 2;
      }
      less = less == 2 ? 0 : less;
    } else if (sign_1 == 1)
      less = 1;
  }
  return less;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int sign = s21_GetSign(value_1) ^ s21_GetSign(value_2);
  int equal = 1;
  if ((value_1.bits[0] | value_1.bits[1] | value_1.bits[2] | value_2.bits[0] |
       value_2.bits[1] | value_2.bits[2]) != 0) {
    equal = sign == 0 ? 1 : 0;
    if (equal) {
      s21_double_decimal double_value_1 = {};
      s21_double_decimal double_value_2 = {};
      s21_Equate_Double_ToDecimal(value_1, &double_value_1);
      s21_Equate_Double_ToDecimal(value_2, &double_value_2);
      s21_Double_CommonDenominator(&double_value_1, &double_value_2);
      for (int i = 0; i < 3 && equal == 1; i++) {
        if ((double_value_1.bits[i] ^ double_value_2.bits[i]) != 0) equal = 0;
      }
    }
  }
  return equal;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) | s21_is_equal(value_1, value_2);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return (!(s21_is_less(value_1, value_2))) | s21_is_equal(value_1, value_2);
}
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less(value_1, value_2) && !s21_is_equal(value_1, value_2);
}
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}
