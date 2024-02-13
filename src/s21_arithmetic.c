#include "s21_decimal.h"
// +
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int error = s21_Decimal_ToNull(result);
  if (error == 0) {
    int sign_1 = s21_GetSign(value_1);
    int sign_2 = s21_GetSign(value_2);
    s21_double_decimal double_value_1 = {{0}};
    s21_double_decimal double_value_2 = {{0}};
    s21_double_decimal double_result = {{0}};
    s21_Equate_Double_ToDecimal(value_1, &double_value_1);
    s21_Equate_Double_ToDecimal(value_2, &double_value_2);
    if (sign_1 == sign_2) {
      int decimal_zero = s21_Double_DecimalZero(double_value_1, double_value_2);
      if (decimal_zero == 0) {
        s21_Double_CommonDenominator(&double_value_1, &double_value_2);
        s21_double_add(double_value_1, double_value_2, &double_result);
        error = s21_Converting_Double_Decimal(result, double_result);
      } else if (decimal_zero != 3)
        error = s21_Converting_Double_Decimal(
            result, decimal_zero == 1 ? double_value_2 : double_value_1);
    } else {
      sign_1 == 1 ? s21_SetSign(&value_1, 0) : s21_SetSign(&value_2, 0);
      if (s21_is_less(value_1, value_2) != 0) {
        s21_double_sub(double_value_2, double_value_1, &double_result);
        if ((double_result.bits[0] | double_result.bits[1] |
             double_result.bits[2]) != 0)
          s21_Double_SetSign(&double_result, sign_2);
      } else {
        s21_double_sub(double_value_1, double_value_2, &double_result);
        if ((double_result.bits[0] | double_result.bits[1] |
             double_result.bits[2]) != 0)
          s21_Double_SetSign(&double_result, sign_1);
      }
      error = s21_Converting_Double_Decimal(result, double_result);
    }
  }
  return error;
}

void s21_double_add(s21_double_decimal double_value_1,
                    s21_double_decimal double_value_2,
                    s21_double_decimal* double_result) {
  s21_Double_DecimalToNull(double_result);
  int flag_plus_1 = 0;
  for (int i = 0; i != 160; i++) {
    int number = s21_Double_GetBit(double_value_1, i) +
                 s21_Double_GetBit(double_value_2, i) + flag_plus_1;
    s21_Double_SetBit(double_result, i, number % 2);
    flag_plus_1 = number / 2;
  }
  double_result->bits[5] = double_value_1.bits[5];
}

// -
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int error = s21_Decimal_ToNull(result);
  if (error == 0) {
    if (!(s21_is_equal(value_1, value_2))) {
      int flag = 1;
      int sign_1 = s21_GetBit(value_2, 127);
      int sign_2 = s21_GetBit(value_1, 127);
      s21_double_decimal double_value_1 = {{0}};
      s21_double_decimal double_value_2 = {{0}};
      s21_double_decimal double_result = {{0}};

      if ((s21_DecimalOne(value_1) ^ s21_DecimalOne(value_2)) == 1) {
        flag = 0;
        s21_DecimalOne(value_1) ? s21_bankround(value_1, &value_1)
                                : s21_bankround(value_2, &value_2);
      }
      s21_Equate_Double_ToDecimal(value_1, &double_value_1);
      s21_Equate_Double_ToDecimal(value_2, &double_value_2);
      if (flag == 1)
        s21_Double_CommonDenominator(&double_value_1, &double_value_2);

      if (sign_1 == sign_2) {
        if (sign_1 == 1) {
          s21_SetSign(&value_1, 0);
          s21_SetSign(&value_2, 0);
        }
        if (s21_is_less(value_1, value_2)) {
          s21_double_sub(double_value_2, double_value_1, &double_result);
          sign_1 == 1 ? s21_Double_SetSign(&double_result, 0)
                      : s21_Double_SetSign(&double_result, 1);
        } else {
          s21_double_sub(double_value_1, double_value_2, &double_result);
          sign_1 != 1 ? s21_Double_SetSign(&double_result, 0)
                      : s21_Double_SetSign(&double_result, 1);
        }
      } else
        s21_double_add(double_value_1, double_value_2, &double_result);
      error = s21_Converting_Double_Decimal(result, double_result);
    }
  }
  return error;
}

void s21_double_sub(s21_double_decimal double_value_1,
                    s21_double_decimal double_value_2,
                    s21_double_decimal* double_result) {
  int flag_sub = 0;
  for (int i = 0; i < 160; i++) {
    if (!(s21_Double_GetBit(double_value_1, i)) &&
        s21_Double_GetBit(double_value_2, i)) {
      int j = i;
      for (; (j < 160) && (s21_Double_GetBit(double_value_1, j) == 0); j++)
        s21_Double_SetBit(&double_value_1, j, 1);
      s21_Double_SetBit(&double_value_1, j, 0);
      flag_sub = 1;
    }
    int number = s21_Double_GetBit(double_value_1, i) -
                 s21_Double_GetBit(double_value_2, i) - flag_sub;
    s21_Double_SetBit(double_result, i, s21_fabs(number));
    flag_sub = 0;
  }
  if ((double_result->bits[0] | double_result->bits[1] |
       double_result->bits[2]) != 0)
    double_result->bits[5] = double_value_1.bits[5];
}

// *
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int error = s21_Decimal_ToNull(result);
  if (error == 0) {
    s21_double_decimal double_value_1 = {{0}};
    s21_double_decimal double_value_2 = {{0}};
    s21_double_decimal double_result = {{0}};
    s21_Equate_Double_ToDecimal(value_1, &double_value_1);
    s21_Equate_Double_ToDecimal(value_2, &double_value_2);
    if (s21_Double_DecimalZero(double_value_1, double_value_2) == 0) {
      int sign_1 = s21_GetBit(value_2, 127);
      int sign_2 = s21_GetBit(value_1, 127);
      s21_Double_CommonDenominator(&double_value_1, &double_value_2);
      sign_1 == sign_2 ? s21_Double_SetSign(&double_result, 0)
                       : s21_Double_SetSign(&double_result, 1);
      s21_double_mul(double_value_1, double_value_2, &double_result);
      error = s21_Converting_Double_Decimal(result, double_result);
    }
  }
  return error;
}

void s21_double_mul(s21_double_decimal double_value_1,
                    s21_double_decimal double_value_2,
                    s21_double_decimal* double_result) {
  for (int i = 0; i != 160; i++) {
    s21_double_decimal value = double_value_1;
    if (s21_Double_GetBit(double_value_2, i) == 1) {
      if (i != 0) {
        int step = i;
        while (step > 31) {
          value.bits[4] = value.bits[3];
          value.bits[3] = value.bits[2];
          value.bits[2] = value.bits[1];
          value.bits[1] = value.bits[0];
          value.bits[0] = 0;
          step -= 32;
        }
        value = s21_Double_ShiftLeft(value, step);
      }
      s21_double_add(*double_result, value, double_result);
    }
  }
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int error = s21_Decimal_ToNull(result);
  if (error == 0) {
    s21_double_decimal double_value_1 = {{0}};
    s21_double_decimal double_value_2 = {{0}};
    s21_double_decimal double_result = {{0}};  // 192 бита
    s21_Equate_Double_ToDecimal(value_1, &double_value_1);
    s21_Equate_Double_ToDecimal(value_2, &double_value_2);
    int sign = s21_GetBit(value_2, 127) ^ s21_GetBit(value_1, 127);
    s21_Double_SetSign(&double_value_1, 0);
    s21_Double_SetSign(&double_value_2, 0);

    if (!(s21_Double_DecimalZeroOne(double_value_2)))
      error = 3;
    else {
      s21_Double_CommonDenominator(&double_value_1, &double_value_2);
      error = s21_double_div(double_value_1, double_value_2, &double_result);
      s21_Double_SetSign(&double_result, sign);

      if (!error) error = s21_Converting_Double_Decimal(result, double_result);
    }
  }

  return error;
}
int s21_double_div(s21_double_decimal double_value_1,
                   s21_double_decimal double_value_2,
                   s21_double_decimal* double_result) {
  int scale = double_value_1.bits[5] >> 16;
  double_value_1.bits[5] = 0;
  double_value_2.bits[5] = 0;
  int error = 0;

  s21_double_decimal tmp = {{0}};
  s21_double_decimal tmp_res = {{0}};
  s21_Division(double_value_1, double_value_2, double_result, &tmp);

  if (s21_Double_DecimalZeroOne(tmp)) {
    int scale_tmp = 28;
    double_value_1 = tmp;
    double_value_1 = s21_ShiftLeftTen(double_value_1, 28);
    s21_Double_DecimalToNull(&tmp);
    s21_Division(double_value_1, double_value_2, &tmp_res, &tmp);
    *double_result = s21_ShiftLeftTen(*double_result, 28);
    s21_double_add(*double_result, tmp_res, double_result);
    while (scale_tmp > 0 && s21_CheckFraction(*double_result)) {
      *double_result = s21_Double_ShiftRightTen(*double_result, 1);
      scale_tmp--;
    }
    if ((scale_tmp + scale) <= 28)
      double_result->bits[5] = (scale_tmp + scale) << 16;
    else
      error = 1;
  }
  return error;
}

void s21_Division(s21_double_decimal double_value_1,
                  s21_double_decimal double_value_2,
                  s21_double_decimal* double_result, s21_double_decimal* tmp) {
  for (int i = 159; i >= 0; i--) {
    *tmp = s21_Double_ShiftLeft(*tmp, 1);
    if (s21_Double_GetBit(double_value_1, i)) s21_Double_SetBit(tmp, 0, 1);
    if (s21_Double_Greater(*tmp, double_value_2)) {
      s21_double_sub(*tmp, double_value_2, tmp);
      s21_Double_SetBit(double_result, i, 1);
    }
  }
}
