
Проект представляет собой разработку библиотеки s21_decimal.h на языке программирования C.

# Цель:

Цель - добавить поддержку типа "decimal" для финансовых расчетов, где требуется высокая точность и отсутствие ошибок округления. Библиотека включает функции для арифметических операций (сложение, вычитание, умножение, деление), сравнения, конвертации и другие операции с десятичными числами.

# Реализация:

Сложение: int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)

Вычитание: int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)

Умножение: int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)

Деление: int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)

Сравнение меньше: int s21_is_less(s21_decimal, s21_decimal)

Сравнение меньше или равно: int s21_is_less_or_equal(s21_decimal, s21_decimal)

Сравнение больше: int s21_is_greater(s21_decimal, s21_decimal)

Сравнение больше или равно: int s21_is_greater_or_equal(s21_decimal, s21_decimal)

Сравнение равно: int s21_is_equal(s21_decimal, s21_decimal)

Сравнение не равно: int s21_is_not_equal(s21_decimal, s21_decimal)

Конвертация из int: int s21_from_int_to_decimal(int src, s21_decimal *dst)

Конвертация из float: int s21_from_float_to_decimal(float src, s21_decimal *dst)

Конвертация в int: int s21_from_decimal_to_int(s21_decimal src, int *dst)

Конвертация в float: int s21_from_decimal_to_float(s21_decimal src, float *dst)

Округление в меньшую сторону: int s21_floor(s21_decimal value, s21_decimal *result)

Округление: int s21_round(s21_decimal value, s21_decimal *result)

Обрезка десятичной части: int s21_truncate(s21_decimal value, s21_decimal *result)

Умножение на -1: int s21_negate(s21_decimal value, s21_decimal *result)
