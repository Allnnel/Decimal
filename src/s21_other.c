#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_Decimal_ToNull(result);
  s21_decimal rem = {{0}};
  int res = 0;
  int scale = s21_GetScale(value);
  int sign = s21_GetSign(value);
  if (result) {
    for (int i = scale; i > 0; i--) {
      div_other(value, &value, &rem, 10);
    }
    *result = value;
    s21_SetScale(result, 0);
    s21_SetSign(result, sign);
  } else {
    res = 1;
  }
  return res;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int res = !s21_GetSign(value);
  if (result) {
    copy_decimal(value, result);
    s21_SetSign(result, res);
    res = 0;
  } else {
    res = 1;
  }
  return res;
}

int copy_decimal(s21_decimal src, s21_decimal *dst) {
  int res = 0;
  if (dst) {
    dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = src.bits[i];
    }
  } else {
    res = 1;
  }
  return res;
}
int s21_floor(s21_decimal value, s21_decimal *result) {
  int res = s21_Decimal_ToNull(result);
  if (res == 0) {
    int sign = s21_GetSign(value);
    s21_decimal one = {{0b00000000000000000000000000000001, 0, 0, 0}};  // 1
    int scale = s21_GetScale(value);
    if (result) {
      if (scale == 0) {
        *result = value;
      } else {
        s21_truncate(value, result);
        if (sign) {
          s21_sub(*result, one, result);
        }
      }
    } else {
      res = 1;
    }
  }
  return res;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_Decimal_ToNull(result);
  int res = 0;
  int sign = s21_GetSign(value);
  s21_SetSign(&value, 0);
  s21_decimal int_val = {{0, 0, 0, 0}};
  s21_decimal fract_val = {{0, 0, 0, 0}};
  s21_decimal one = {{0b00000000000000000000000000000001, 0, 0, 0}};
  s21_decimal five = {{0b00000000000000000000000000000101, 0, 0, 0}};
  s21_SetScale(&five, 1);
  if (result) {
    s21_truncate(value, &int_val);
    s21_sub(value, int_val, &fract_val);
    if (!s21_is_less(fract_val, five) || s21_is_equal(fract_val, five)) {
      s21_add(int_val, one, result);
      s21_SetScale(result, 0);
      s21_SetSign(result, sign);
    } else {
      *result = int_val;
      s21_SetScale(result, 0);
      s21_SetSign(result, sign);
    }
  } else {
    res = 1;
  }
  return res;
}

int s21_bankround(s21_decimal value, s21_decimal *result) {
  int res = s21_Decimal_ToNull(result);
  int sign = s21_GetSign(value); 
  s21_SetSign(&value, 0);
  s21_decimal rem = {{0}};
  s21_decimal res2 = {{0}};
  s21_decimal int_val = {{0, 0, 0, 0}};  
  s21_decimal fract_val = {{0, 0, 0, 0}}; 
  s21_decimal one = {{0b00000000000000000000000000000001, 0, 0, 0}};  
  s21_decimal null = {{0b00000000000000000000000000000000, 0, 0, 0}}; 
  if (result) { 
    s21_truncate(value, &int_val); 
    s21_sub(value, int_val,
            &fract_val); 
    div_other(int_val, &res2, &rem, 2);
    if (s21_is_equal(rem, null)) {
      *result = int_val;
      s21_SetScale(result, 0); 
      s21_SetSign(result, sign); 
    } else {
      s21_add(int_val, one, result); 
      s21_SetScale(result, 0); 
      s21_SetSign(result, sign); 
    }

  } else {
    res = 1; 
  }
  return res;
}
