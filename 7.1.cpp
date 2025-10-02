#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

/**
 * @brief оператор выбора способа заполнения массива
 * @param RANDOM = 0 автоматическое заполнение
 * @param MANUALLY = 1 ручное заполнение
 */
enum SELECT
{
  RANDOM = 0,
  MANUALLY = 1
};

/**
 * @brief Считывает значения с клавиатуры с проверкой ввода
 * @return Возвращает значение, если оно правильное, иначе завершает программу
 */
double get_value();

/**
 * @brief Возвращает размер массива
 * @return Размер массива
 */
size_t get_size_arr();

/**
 * @brief Проверяет размер массива
 * @param n Размер массива
 */
void check_arr_n(const int n);

/**
 * @brief Возвращает новый двумерный массив.
 * @param rows Кол-во строк массива
 * @param cols Кол-во столбцов массива
 * @return Новый двумерный массив
 */
int **get_new_arr(int const rows, int const cols);

/**
 * @brief Проверяет диапазон
 * @param min Минимальное значение диапазона значений элементов массива
 * @param max Максимальное значение диапазона значений элементов массива
 */
void check_range(const int min, const int max);

/**
 * @brief Заполнение массива автоматически случайными числами в заданном диапазоне
 * @param arr Массив
 * @param rows Кол-во строк массива
 * @param cols Кол-во столбцов массива
 * @param min Минимальное значение диапазона значений элементов массива
 * @param max Максимальное значение диапазона значений элементов массива
 */
void fill_arr_random(int **arr, int const rows, int const cols, int const min, int const max);

/**
 * @brief Заполнение массива вручную
 * @param arr Массив
 * @param rows Кол-во строк массива
 * @param cols Кол-во столбцов массива
 * @param min Минимальное значение диапазона значений элементов массива
 * @param max Максимальное значение диапазона значений элементов массива
 */
void fill_arr(int **arr, const int rows, const int cols, const int min, const int max);

/**
 * @brief Выводит массив на экран
 * @param arr Массив
 * @param rows Кол-во строк массива
 */
void print_arr(int **arr, const int rows, const int cols);

/**
 * @brief Заменяет максимальный по модулю элемент каждой строки на противоположный по знаку
 * @param arr Массив
 * @param rows Кол-во строк массива
 * @param cols Кол-во столбцов массива
 */
void replace_max_absolute_with_opposite(int **arr, int const rows, int const cols);

/**
 * @brief Вставляет после каждой чётной строки первую строку
 * @param arr Массив
 * @param rows Кол-во строк массива
 * @param cols Кол-во столбцов массива
 */
void insert_first_row_after_even_rows(int **arr, int const rows, int const cols);

/**
 * @brief Очищает массив из памяти
 * @param arr Массив
 * @param rows Кол-во строк массива
 */
void del_arr(int **arr, const int rows);

/**
 * @brief Точка входа в программу
 * @return Возвращает 0, если программа выполнена корректно
 */
int main()
{
  setlocale(LC_ALL, "Russian");
  cout << "Введите количество строк в массиве: ";
  int rows = get_size_arr();
  cout << "Введите количество столбцов в массиве: ";
  int cols = get_size_arr();

  int **arr = get_new_arr(rows, cols);

  cout << "Введите минимальное и максимальное значение интервала: ";
  int min_value = get_value();
  int max_value = get_value();
  check_range(min_value, max_value);

  cout << "Введите выбор для заполнения массива: " << endl
       << RANDOM << " Для случайного заполнения" << endl
       << MANUALLY << " Для ручного заполнения" << endl;

  int choice = get_value();

  switch ((enum SELECT)choice)
  {
  case RANDOM:
    fill_arr_random(arr, rows, cols, min_value, max_value);
    break;
  case MANUALLY:
    fill_arr(arr, rows, cols, min_value, max_value);
    break;
  default:
    cout << "Ваш выбор неверен" << endl;
    del_arr(arr, rows);
    return 0;
  }

  cout << "Элементы двумерного массива:" << endl;
  print_arr(arr, rows, cols);

  cout << "Копия массива с заменённым максимальным по модулю элементом каждой строки на противоположный по знаку:" << endl;
  replace_max_absolute_with_opposite(arr, rows, cols);

  cout << "Копия массива, где вставляется после каждой чётной строки первая строка" << endl;
  insert_first_row_after_even_rows(arr, rows, cols);

  del_arr(arr, rows);

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

size_t get_size_arr()
{
  int n = get_value();
  check_arr_n(n);
  return (size_t)n;
}

void check_arr_n(const int n)
{
  if (n <= 0)
  {
    cout << "Неправильный размер массива" << endl;
    abort();
  }
}

int **get_new_arr(int const rows, int const cols)
{
  int **arr = new int *[rows];
  for (int i = 0; i < rows; ++i)
  {
    arr[i] = new int[cols];
  }
  return arr;
}

void check_range(const int min, const int max)
{
  if (min > max)
  {
    cout << "Введен неправильный интервал" << endl;
    abort();
  }
}

void fill_arr_random(int **arr, int const rows, int const cols, int const min, int const max)
{
  srand((time(0)));
  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < cols; j++)
    {
      arr[i][j] = rand() % (max - min + 1) + min;
    }
  }
}

void fill_arr(int **arr, const int rows, const int cols, const int min, const int max)
{
  cout << "Введите элементы массива (диапазон [" << min << ".." << max << "]):" << endl;
  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < cols; j++)
    {
      cout << "arr[" << i << "][" << j << "]: ";
      int value = get_value();

      if (value >= min && value <= max)
      {
        arr[i][j] = value;
      }
      else
      {
        abort();
      }
    }
  }
}

void print_arr(int **arr, const int rows, const int cols)
{
  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < cols; j++)
    {
      cout << "arr[" << i << "][" << j << "] = " << arr[i][j] << endl;
    }
  }
}

void replace_max_absolute_with_opposite(int **arr, int const rows, int const cols)
{
  int **new_arr = new int *[rows];
  for (size_t i = 0; i < rows; ++i)
  {
    new_arr[i] = new int[cols];
    copy(arr[i], arr[i] + cols, new_arr[i]);
  }

  for (size_t i = 0; i < rows; i++)
  {
    if (cols > 0)
    {
      int max_abs_pos = 0;
      int max_abs_value = abs(new_arr[i][0]);

      for (size_t j = 1; j < cols; ++j)
      {
        if (abs(new_arr[i][j]) > max_abs_value)
        {
          max_abs_value = abs(new_arr[i][j]);
          max_abs_pos = j;
        }
      }
      new_arr[i][max_abs_pos] = -new_arr[i][max_abs_pos];
    }
  }

  print_arr(new_arr, rows, cols);
  del_arr(new_arr, rows);
}

void insert_first_row_after_even_rows(int **arr, int const rows, int const cols)
{
  int additional_rows = 0;
  for (int i = 0; i < rows; i++)
  {
    if (i % 2 == 0)
    {
      additional_rows++;
    }
  }

  int new_rows = rows + additional_rows;
  int **new_arr = new int *[new_rows];

  int new_index = 0;
  for (size_t i = 0; i < rows; i++)
  {
    new_arr[new_index] = new int[cols];
    copy(arr[i], arr[i] + cols, new_arr[new_index]);
    new_index++;

    if (i % 2 == 0)
    {
      new_arr[new_index] = new int[cols];
      copy(arr[0], arr[0] + cols, new_arr[new_index]);
      new_index++;
    }
  }

  print_arr(new_arr, new_rows, cols);
  del_arr(new_arr, new_rows);
}

void del_arr(int **arr, int const rows)
{
  for (size_t i = 0; i < rows; i++)
  {
    delete[] arr[i];
  }
  delete[] arr;
}
