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
 * @brief Создаёт файл с данными для построения графика через GNUplot утилиту
 * @param x_values Вектор значений x
 * @param y_values Вектор значений y
 */
void create_gnuplot_script(const vector<double> &x_values, const vector<double> &y_values);

/**
 * @brief Находит корни функции на заданном интервале
 * @param x_values Вектор значений x
 * @param y_values Вектор значений y
 * @param step Шаг вычисления
 */
void find_roots(const vector<double> &x_values, const vector<double> &y_values, double step);

/**
 * @brief Находит минимальное и максимальное значение функции
 * @param x_values Вектор значений x
 * @param y_values Вектор значений y
 */
void find_extremums(const vector<double> &x_values, const vector<double> &y_values);

/**
 * @brief Вычисляет определенный интеграл методом трапеций
 * @param x_values Вектор значений x
 * @param y_values Вектор значений y
 * @param step Шаг вычисления
 * @return Значение интеграла
 */
double calculate_integral(const vector<double> &x_values, const vector<double> &y_values, double step);

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

  vector<double> x_values, y_values;

  for (double x = start; x < end + step; x += step)
  {
    double y = calculate_expression(x);

    if (y == 0)
    {
      cout << "x: " << x << endl;
      cout << "y: Отсутствует решение" << endl;
      cout << endl;
    }
    else
    {
      x_values.push_back(x);
      y_values.push_back(y);
    }
  }

  create_gnuplot_script(x_values, y_values);

  cout << "Данные для графика сохранены в файлы:" << endl;
  cout << "- function_data.txt - данные функции" << endl;
  cout << "- plot_script.plt - скрипт для GNUplot" << endl;

  int result = system("gnuplot plot_script.plt");

  if (result == 0)
  {
    cout << "✓ График успешно создан: function_plot.png" << endl;
  }
  else
  {
    cout << "✗ Ошибка при построении графика" << endl;
  }

  // Дополнительный анализ функции
  cout << "\n=== АНАЛИЗ ФУНКЦИИ ===" << endl;
  
  find_roots(x_values, y_values, step);
  find_extremums(x_values, y_values);
  
  double integral = calculate_integral(x_values, y_values, step);
  cout << "Определенный интеграл на интервале: " << integral << endl;

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

void create_gnuplot_script(const vector<double> &x_values, const vector<double> &y_values)
{
  ofstream data_file("function_data.txt");
  ofstream script_file("plot_script.plt");

  for (size_t i = 0; i < x_values.size(); i++)
  {
    data_file << x_values[i] << " " << y_values[i] << endl;
  }
  data_file.close();

  script_file << "set terminal png size 800,600" << endl;
  script_file << "set output 'function_plot.png'" << endl;
  script_file << "set title 'График функции y = 3sin(sqrt(x)) + 0.39x - 3.8'" << endl;
  script_file << "set xlabel 'x'" << endl;
  script_file << "set ylabel 'y'" << endl;
  script_file << "set grid" << endl;
  script_file << "plot 'function_data.txt' with linespoints title 'Функция'" << endl;
  script_file << "pause -1" << endl;
  script_file.close();
}

void find_roots(const vector<double> &x_values, const vector<double> &y_values, double step)
{
  cout << "\nПоиск корней функции:" << endl;
  bool found_roots = false;
  
  for (size_t i = 1; i < y_values.size(); i++)
  {
    if (y_values[i-1] * y_values[i] <= 0)
    {
      double root = x_values[i-1] + (x_values[i] - x_values[i-1]) * abs(y_values[i-1]) / (abs(y_values[i-1]) + abs(y_values[i]));
      cout << "Корень функции: x ≈ " << root << endl;
      found_roots = true;
    }
  }
  
  if (!found_roots)
  {
    cout << "Корни не найдены на заданном интервале" << endl;
  }
}

void find_extremums(const vector<double> &x_values, const vector<double> &y_values)
{
  if (y_values.size() < 3)
  {
    cout << "Недостаточно точек для поиска экстремумов" << endl;
    return;
  }

  double min_y = y_values[0];
  double max_y = y_values[0];
  double min_x = x_values[0];
  double max_x = x_values[0];

  for (size_t i = 1; i < y_values.size(); i++)
  {
    if (y_values[i] < min_y)
    {
      min_y = y_values[i];
      min_x = x_values[i];
    }
    if (y_values[i] > max_y)
    {
      max_y = y_values[i];
      max_x = x_values[i];
    }
  }

  cout << "\nЭкстремумы функции:" << endl;
  cout << "Минимум: x = " << min_x << ", y = " << min_y << endl;
  cout << "Максимум: x = " << max_x << ", y = " << max_y << endl;
}

double calculate_integral(const vector<double> &x_values, const vector<double> &y_values, double step)
{
  if (y_values.size() < 2)
  {
    return 0.0;
  }

  double integral = 0.0;
  for (size_t i = 1; i < y_values.size(); i++)
  {
    integral += (y_values[i-1] + y_values[i]) * step / 2.0;
  }

  return integral;
}
