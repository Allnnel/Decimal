
#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_Decimal_ToNull(dst);
  int res = 1;
  int max = 2147483647;
  if (dst && src <= max) {
    if (src < 0) {
      s21_SetSign(dst, 1);
      src = -src;
    }
    dst->bits[0] = src;
    res = 0;
  }
  return res;
}
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 1;
  s21_truncate(src, &src);
  if (dst && src.bits[1] == 0 && src.bits[2] == 0) {
    *dst = src.bits[0];
    if (s21_GetSign(src)) {
      *dst = -*dst;
    }
    int scale = s21_GetScale(src);
    while (scale--) *dst /= 10;
    res = 0;
  }
  return res;
}
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = 1;
  if (dst) {
    double result = 0;
    int scale = s21_GetScale(src);
    for (int i = 0; i < 96; i++) {
      if (s21_GetBit(src, i) != 0) result += pow(2, i);
    }
    while (scale--) result /= 10;
    *dst = (float)result;
    if (s21_GetSign(src)) {
      *dst = -*dst;
    }
    res = 0;
  }
  return res;
}
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_Decimal_ToNull(dst);
  int res = 0;
  if (dst == NULL || src != src)
    res = 1;
  else if ((fabs(src) < powl(10.0, -28.0)) || (fabs(src) >= powl(2.0, 96.0)))
    res = 1;
  else {
    int scale = 0;
    double number = fabs((double)src);
    while (number < 1.0 && scale < 28) {
      number *= 10;
      scale++;
    }
    while (number / pow(10.0, 7) < 1.0 && scale < 28) {
      number *= 10;
      scale++;
    }
    number = floor(number);
    if (fmod(number, 10.0) >= 5) {
      number += 10 - fmod(number, 10.0);
      number = round(number);
    }
    if (scale > 0) {
      number = number / 10;
      scale--;
    }
    while (scale > 0 && (fmod(number, 10.0) < pow(10.0, -8))) {
      number = number / 10;
      number = round(number);
      scale--;
    }
    for (int i = 0; i < 96; i++)
      s21_SetBit(dst, i, s21_GetBitToFloat(number, i));
    if (src < 0) s21_SetSign(dst, 1);
    s21_SetScale(dst, scale);
  }

  return res;
}
