#include "s21_decimal.h"

void s21_Double_SetBit(s21_double_decimal *dec, int index, int bit) {
  int num_int = index / 32;
  int num_bit = index % 32;
  if (bit == 1)
    dec->bits[num_int] |= (1u << num_bit);
  else
    dec->bits[num_int] &= (~((1u) << num_bit));
}

int s21_Double_GetBit(s21_double_decimal dec, int index) {
  int error = -1;
  if (index >= 0 && index <= 191) {
    int num_int = index / 32;
    int num_bit = index % 32;
    error = !!(dec.bits[num_int] & (1u << num_bit));
  }
  return error;
}

int s21_Decimal_ToNull(s21_decimal *src) {
  int error = 0;
  if (src)
    for (int i = 0; i != 4; i++) src->bits[i] = 0;
  else
    error = 1;
  return error;
}

int s21_GetSign(s21_decimal dec) { return (!!(dec.bits[3] >> 31)); }

int s21_GetBit(s21_decimal dec, int index) {
  int error = -1;
  if (index >= 0 && index <= 127) {
    int num_int = index / 32;
    int num_bit = index % 32;
    error = !!(dec.bits[num_int] & (1u << num_bit));
  }
  return error;
}

int s21_GetScale(s21_decimal dec) {
  int result = (char)(dec.bits[3] >> 16);
  return result;
}

void s21_SetBit(s21_decimal *dec, int index, int bit) {
  int num_int = index / 32;
  int num_bit = index % 32;
  if (bit == 1)
    dec->bits[num_int] |= (1u << num_bit);
  else
    dec->bits[num_int] &= (~((1u) << num_bit));
}

void s21_SetScale(s21_decimal *dec, int scale) {
  for (int i = 112; i < 119; i++) {
    s21_SetBit(dec, i, scale & 1);
    scale >>= 1;
  }
}

void s21_SetSign(s21_decimal *dec, int sign) { s21_SetBit(dec, 127, sign); }

int s21_GetBitToFloat(double number, int bit_number) {
  int result = -1;
  for (int i = 0; i < bit_number; i++) number = floor(number / 2);
  result = (int)s21_fmod(number, 2.0);
  return result;
}

s21_double_decimal s21_Double_ShiftLeft(s21_double_decimal value, int inex) {
  for (int i = 4; i != -1; i--) {
    int remain = 0;
    if (i != 0 && ((value.bits[i - 1] >> (32 - inex)) != 0))
      remain = value.bits[i - 1] >> (32 - inex);
    value.bits[i] = (value.bits[i] << inex) | remain;
  }
  return value;
}
long double s21_fabs(double x) {
  if (x < 0) {
    x = x * (-1);
  }
  return x;
}

long double s21_fmod(double x, double y) {
  long double n = 0;
  int v = x / y;
  n = x - y * v;
  if (y == 0) n = S21_NAN;
  if (x == S21_INF) n = S21_NAN;
  if (y == S21_INF) n = 0;
  if (x != 0 && y == S21_INF) n = S21_NAN;
  return n;
}

void div_other(s21_decimal value_1, s21_decimal *result, s21_decimal *rem,
               int number) {
  s21_Decimal_ToNull(result);
  s21_Decimal_ToNull(rem);
  s21_decimal value_2 = {{0}};  // 10
  value_2.bits[0] = number;
  for (int i = 95; i >= 0; i--) {
    *rem = s21_ShiftLeft(*rem, 1);
    if (s21_GetBit(value_1, i)) s21_SetBit(rem, 0, 1);
    if (s21_Greater(*rem, value_2)) {
      s21_other_sub(*rem, value_2, rem);
      s21_SetBit(result, i, 1);
    }
  }
}

s21_decimal s21_ShiftLeft(s21_decimal value, int inex) {
  for (int i = 2; i != -1; i--) {
    int remain = 0;
    if (i != 0 && ((value.bits[i - 1] >> (32 - inex)) != 0))
      remain = value.bits[i - 1] >> (32 - inex);
    value.bits[i] = (value.bits[i] << inex) | remain;
  }
  return value;
}

int s21_Greater(s21_decimal value_1, s21_decimal value_2) {
  int comp = 1;
  for (int i = 2; i >= 0; i--) {
    if (value_1.bits[i] < value_2.bits[i]) comp = 0;
  }
  return comp;
}
void s21_other_sub(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  int flag_sub = 0;
  for (int i = 0; i < 96; i++) {
    if (!(s21_GetBit(value_1, i)) && s21_GetBit(value_2, i)) {
      int j = i;
      for (; (j < 96) && (s21_GetBit(value_1, j) == 0); j++)
        s21_SetBit(&value_1, j, 1);
      s21_SetBit(&value_1, j, 0);
      flag_sub = 1;
    }
    int number = s21_GetBit(value_1, i) - s21_GetBit(value_2, i) - flag_sub;
    s21_SetBit(result, i, s21_fabs(number));
    flag_sub = 0;
  }
}

void s21_Double_DecimalToNull(s21_double_decimal *value) {
  for (int i = 0; i < 6; i++) {
    value->bits[i] = 0;
  }
}

int s21_Double_DecimalZeroOne(s21_double_decimal tmp) {
  int error = 1;
  if ((tmp.bits[0] + tmp.bits[1] + tmp.bits[2] + tmp.bits[3] + tmp.bits[4]) ==
      0) {
    error = 0;
  }
  return error;
}

int s21_DecimalOne(s21_decimal tmp) {
  int error = 0;
  for (int i = 95; i >= 0 && error != 1; i--) {
    if (!s21_GetBit(tmp, i)) error = 1;
  }
  return error;
}
int s21_Double_Greater(s21_double_decimal double_value_1,
                       s21_double_decimal double_value_2) {
  int comp = 1;
  for (int i = 4; i >= 0; i--) {
    if (double_value_1.bits[i] < double_value_2.bits[i]) comp = 0;
  }
  return comp;
}

s21_double_decimal s21_Double_ShiftRightTen(s21_double_decimal double_value,
                                            int shift) {
  for (int i = 0; i < shift; i++)
    double_value = s21_double_div_ten(double_value);
  return double_value;
}

s21_double_decimal s21_double_div_ten(s21_double_decimal double_value) {
  unsigned int number = 10;
  s21_double_decimal double_value1 = {{0}};
  s21_double_decimal double_result = {{0}};
  s21_double_decimal tmp = {{0}};
  double_value1.bits[0] = number;
  s21_Division(double_value, double_value1, &double_result, &tmp);
  return double_result;
}

int s21_CheckFraction(s21_double_decimal double_value) {
  int result = 0;
  s21_double_decimal tmp;
  tmp = s21_Double_ShiftRightTen(double_value, 1);
  tmp = s21_ShiftLeftTen(tmp, 1);
  if (s21_Double_Equal(double_value, tmp)) result = 1;
  return result;
}

int s21_Double_Equal(s21_double_decimal double_value_1,
                     s21_double_decimal double_value_2) {
  int equal = 1;
  for (int i = 0; i < 5 && equal == 1; i++) {
    if ((double_value_1.bits[i] ^ double_value_2.bits[i]) != 0) equal = 0;
  }
  return equal;
}

s21_double_decimal s21_ShiftLeftTen(s21_double_decimal src, int shift) {
  for (int i = 0; i < shift; i++) {
    src = s21_Double_Summ(s21_Double_ShiftLeft(src, 3),
                          s21_Double_ShiftLeft(src, 1));
    ;
  }
  return src;
}
