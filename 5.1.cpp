#include <iostream>
#include <cmath>
using namespace std;

/**
 * @brief Считывает значения с клавиатуры с проверкой ввода
 * @return Возвращает значение, если оно правильное, иначе завершает программу
 */
double get_value();

/**
 * @brief Рекурсивно вычисляет факториал числа
 * @param n Число для вычисления факториала
 * @return Факториал числа n
 */
double factorial_recursive(int n);

/**
 * @brief Рекурсивно вычисляет сумму ряда
 * @param k Текущий индекс (начинается с 1)
 * @param n Максимальный индекс
 * @param sum Накопленная сумма
 */
double calculate_first_n_series_sum_recursive(int k, int n, double sum);

/**
 * @brief Рекурсивно вычисляет сумму всех членов ряда, по модулю не меньших заданного числа e
 * @param k Текущий индекс
 * @param eps Заданная точность
 * @param sum Накопленная сумма
 */
double calculate_series_sum_above_epsilon_recursive(int k, double eps, double sum);

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
  cout << "Сумма первых " << n << " членов ряда: " << calculate_first_n_series_sum_recursive(1, n, 0.0) << endl;

  cout << "Сумма членов ряда, не меньших по модулю ε" << endl;
  cout << "Введите значение e (e > 0): ";
  double eps = get_value();
  cout << "Сумма членов ряда, не меньших по модулю " << eps << ": " << calculate_series_sum_above_epsilon_recursive(1, eps, 0.0) << endl;

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

double factorial_recursive(int n)
{
  if (n == 0 || n == 1)
  {
    return 1.0;
  }
  return n * factorial_recursive(n - 1);
}

double calculate_first_n_series_sum_recursive(int k, int n, double sum)
{
  if (k > n)
  {
    return sum;
  }

  double numerator = pow(-1, k);
  double denominator = factorial_recursive(k + 2) * factorial_recursive(k + 3);
  double term = numerator / denominator;

  sum += term;

  return calculate_first_n_series_sum_recursive(k + 1, n, sum);
}

double calculate_series_sum_above_epsilon_recursive(int k, double eps, double sum)
{
  double numerator = pow(-1, k);
  double denominator = factorial_recursive(k + 2) * factorial_recursive(k + 3);
  double term = numerator / denominator;

  if (fabs(term) < eps)
  {
    return sum;
  }

  sum += term;

  return calculate_series_sum_above_epsilon_recursive(k + 1, eps, sum);
}
