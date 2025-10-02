#include <iostream>
#include <ctime>
#include <algorithm>
#include <climits>
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
 * @brief Проверяет диапазон
 * @param min Минимальное значение диапазона значений элементов массива
 * @param max Максимальное значение диапазона значений элементов массива
 */
void check_range(const int min, const int max);

/**
 * @brief Заполнение массива автоматически случайными числами в заданном диапазоне
 * @param arr Массив
 * @param n Размер массива
 * @param min Минимальное значение диапазона значений элементов массива
 * @param max Максимальное значение диапазона значений элементов массива
 */
void fill_arr_random(int *arr, const int n, const int min, const int max);

/**
 * @brief Заполнение массива вручную
 * @param arr Массив
 * @param n -Размер массива
 * @param min Минимальное значение диапазона значений элементов массива
 * @param max Максимальное значение диапазона значений элементов массива
 */
void fill_arr(int *arr, const int n, const int min, const int max);

/**
 * @brief Выводит массив на экран
 * @param arr Массив
 * @param n Размер массива
 */
void print_arr(const int *arr, const int n);

/**
 * @brief Выводит сумму элементов, имеющих нечётное значение
 * @param arr Указатель на массив целых чисел
 * @param n Размер массива
 */
void print_sum_of_odd_elements(const int *arr, const int n);

/**
 * @brief Выводит индексы элементов, значения которых больше заданного числа А
 * @param arr Указатель на исходный массив
 * @param n Размер массива
 * @param a Заданное число для сравнения
 */
void print_indices_of_elements_greater_than_A(const int *arr, const int n, const int a);

/**
 * @brief Заменяет второй элемент массива на максимальный среди отрицательных
 * @param arr Указатель на исходный массив
 * @param n Размер массива
 */
void print_array_with_second_element_replaced(const int *arr, const int n);

/**
 * @brief Точка входа в программу
 * @return Возвращает 0, если программа выполнена корректно
 */
int main()
{
  setlocale(LC_ALL, "Russian");
  int n = get_size_arr();
  int *arr = new int[n];

  cout << "Введите минимальное и максимальное значение интервала: ";
  int minValue = get_value();
  int maxValue = get_value();
  check_range(minValue, maxValue);

  cout << "Введите выбор для заполнения массива: " << endl
       << RANDOM << " Для случайного заполнения" << endl
       << MANUALLY << " Для ручного заполнения" << endl;

  int choice = get_value();

  switch ((enum SELECT)choice)
  {
  case RANDOM:
    fill_arr_random(arr, n, minValue, maxValue);
    break;
  case MANUALLY:
    fill_arr(arr, n, minValue, maxValue);
    break;
  default:
    cout << "Ваш выбор неверен" << endl;
    delete[] arr;
    return 0;
  }

  cout << "Элементы массива:" << endl;
  print_arr(arr, n);

  print_sum_of_odd_elements(arr, n);
  cout << "Введите число A: ";
  int a = get_value();
  cout << "Индексы элементов, значения которых больше " << a << ":" << endl;
  print_indices_of_elements_greater_than_A(arr, n, a);
  print_array_with_second_element_replaced(arr, n);

  delete[] arr;

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
  cout << "Введите размер массива: ";
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

void check_range(const int min, const int max)
{
  if (min > max)
  {
    cout << "Введен неправильный интервал" << endl;
    abort();
  }
}

void fill_arr_random(int *arr, const int n, const int min, const int max)
{
  srand(time(0));
  for (size_t i = 0; i < n; i++)
  {
    arr[i] = rand() % (max - min) + min;
  }
}

void fill_arr(int *arr, const int n, const int min, const int max)
{
  for (size_t i = 0; i < n;)
  {
    cout << "Введите значение для arr[" << i << "] (диапазон [" << min << ".." << max << "]): ";
    int value = get_value();

    if (value >= min && value <= max)
    {
      arr[i] = value;
      i++;
    }
    else
    {
      abort();
    }
  }
}

void print_arr(const int *arr, const int n)
{
  for (size_t i = 0; i < n; i++)
  {
    cout << "arr[" << i << "] = " << arr[i] << endl;
  }
}

void print_sum_of_odd_elements(const int *arr, const int n)
{
  double sum = 0;
  bool found = false;

  for (size_t i = 0; i < n; i++)
  {
    if (arr[i] % 2 != 0)
    {
      sum += arr[i];
      found = true;
    }
  }

  if (!found)
  {
    cout << "В массиве нет элементов с нечётными значениями." << endl;
  }
  else
  {
    cout << "Сумма элементов с нечётными значениями: " << sum << endl;
  }
}

void print_indices_of_elements_greater_than_A(const int *arr, const int n, const int a)
{
  bool found = false;

  for (size_t i = 0; i < n; i++)
  {
    if (arr[i] > a)
    {
      cout << "arr[" << i << "] = " << arr[i] << endl;
      found = true;
    }
  }

  if (!found)
  {
    cout << "В массиве нет элементов, больших " << a << "." << endl;
  }
}

void print_array_with_second_element_replaced(const int *arr, const int n)
{
  int *new_arr = new int[n];
  copy(arr, arr + n, new_arr);

  int max_negative = INT_MIN;
  bool found_negative = false;

  for (size_t i = 0; i < n; i++)
  {
    if (arr[i] < 0 && arr[i] > max_negative)
    {
      max_negative = arr[i];
      found_negative = true;
    }
  }

  if (found_negative)
  {
    new_arr[1] = max_negative;
    cout << "Второй элемент заменен на максимальный отрицательный: " << max_negative << endl;
    cout << "Копия массива после замены:" << endl;
    print_arr(new_arr, n);
  }
  else
  {
    cout << "В массиве нет отрицательных элементов для замены." << endl;
  }

  delete[] new_arr;
}
    
