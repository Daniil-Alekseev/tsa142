#include <iostream>
#include <cmath>
using namespace std;

/**
 * @brief Считывает значения с клавиатуры с проверкой ввода
 * @return Возвращает значение, если оно правильное, иначе завершает программу
 */
double get_value();

/**
 * @brief Вычисляет следующий член ряда на основе предыдущего
 * @param k Текущий индекс
 * @param prev_term Предыдущий член ряда
 * @return Следующий член ряда a_k
 */
double get_next_term(int k, double prev_term);

/**
 * @brief Рекурсивно вычисляет сумму ряда
 * @param k Текущий индекс (начинается с 1)
 * @param n Максимальный индекс
 * @param sum Накопленная сумма
 * @param term Член ряда
 */
double calculate_first_n_series_sum_recursive(int k, int n, double sum, double term);

/**
 * @brief Рекурсивно вычисляет сумму всех членов ряда, по модулю не меньших заданного числа e
 * @param k Текущий индекс
 * @param eps Заданная точность
 * @param sum Накопленная сумма
 * @param term Член ряда
 */
double calculate_series_sum_above_epsilon_recursive(int k, double eps, double sum, double term);

/**
 * @brief Точка входа в программу
 * @return Возвращает 0, если программа выполнена корректно
 */
int main()
{
  setlocale(LC_ALL, "Russian");

  cout << "Сумма первых n членов ряда" << endl;
  cout << "Введите количество элементов ряда (n > 0): ";
  int n = get_value();
  cout << "Сумма первых " << n << " членов ряда: " << calculate_first_n_series_sum_recursive(1, n, 0, -1.0 / 144.0) << endl;

  cout << "Сумма членов ряда, не меньших по модулю ε" << endl;
  cout << "Введите значение e (e > 0): ";
  double eps = get_value();
  cout << "Сумма членов ряда, не меньших по модулю " << eps << ": " << calculate_series_sum_above_epsilon_recursive(1, eps, 0, -1.0 / 144.0) << endl;

  return 0;
}

double get_value()
{
  double value = 0;
  cin >> value;
  if (cin.fail())
  {
    cout << "Некорректное значение" << endl;
    abort();
  }
  if (value <= 0)
  {
    cout << "Значение должно быть положительным" << endl;
    abort();
  }
  return value;
}

double get_next_term(int k, double prev_term)
{
  return -prev_term / ((k + 2) * (k + 3));
}

double calculate_first_n_series_sum_recursive(int k, int n, double sum, double term)
{
  if (k > n)
  {
    return sum;
  }

  double next_term = get_next_term(k, term);

  if (k == 1)
  {
    next_term = term;
  }

  sum += next_term;

  return calculate_first_n_series_sum_recursive(k + 1, n, sum, next_term);
}

double calculate_series_sum_above_epsilon_recursive(int k, double eps, double sum, double term)
{
  double next_term = get_next_term(k, term);

  if (k == 1)
  {
    next_term = term;
  }

  if (fabs(next_term) < eps)
  {
    return sum;
  }

  sum += next_term;

  return calculate_series_sum_above_epsilon_recursive(k + 1, eps, sum, term);
}
