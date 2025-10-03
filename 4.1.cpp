#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <fstream>
using namespace std;
/**
 * @brief Считывает значения с клавиатуры с проверкой ввода
 * @return Возвращает значение, если оно правильное, иначе завершает программу
 */
double get_value();

/**
 * @brief Вычисляет значение функции
 * @param x Значение x
 * @return Вычисленное значение или 0
 */
double calculate_expression(const double x);

/**
 * @brief Проверяет, что значение x является ООФ
 * @param x Значение x
 * @return true, если x является ООФ, иначе false
 */
bool isOOF(double x);

/**
 * @brief Точка входа в программу
 * @return Возвращает 0, если программа выполнена корректно
 */
int main()
{
  setlocale(LC_ALL, "Russian");

  cout << "Введите интервал: ";
  double start = get_value();
  double end = get_value();

  cout << "Введите шаг: ";
  double step = get_value();

  if (start >= end || step <= 0)
  {
    cout << "Некорректные параметры интервала или шага" << endl;
    abort();
  }

  cout << "\nТаблица значений функции на интервале [" << start << ", " << end << "] с шагом " << step << ":" << endl;
  cout << "======================================================" << endl;
  cout << "    x    |    y" << endl;
  cout << "---------|---------" << endl;

  for (double x = start; x < end + step; x += step)
  {
    cout.precision(4);
    cout << fixed;

    if (isOOF(x))
    {
      double y = calculate_expression(x);
      cout << x << " | " << y << endl;
    }
    else
    {
      cout << x << " | Отсутствует решение" << endl;
    }
  }

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
  return value;
}

double calculate_expression(const double x)
{
  if (x < 0)
  {
    return 0;
  }

  return 3 * sin(sqrt(x)) + 0.39 * x - 3.8;
}

bool isOOF(double x)
{
  return (fabs(x) > std::numeric_limits<double>::epsilon());
}
