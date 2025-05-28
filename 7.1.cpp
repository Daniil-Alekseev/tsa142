#include <iostream>  // Для ввода/вывода
#include <cstdlib>    // Для функций rand() и srand()
#include <ctime>      // Для функции time()
#include <vector>     // Для использования динамического массива
#include <cmath>      // Для функции abs()

using namespace std;  // Использование стандартного пространства имен

/**
 * Функция для заполнения массива случайными числами.
 * @param matrix Ссылка на двумерный вектор (матрицу).
 * @param n Количество строк.
 * @param m Количество столбцов.
 * @param min Минимальное значение случайного числа.
 * @param max Максимальное значение случайного числа.
 */
void fillRandom(vector<vector<int>>& matrix, int n, int m, int min, int max) {
    for (int i = 0; i < n; ++i) {          // Цикл по строкам
        vector<int> row;                    // Создаем новую строку
        for (int j = 0; j < m; ++j) {       // Цикл по столбцам
            // Генерация случайного числа в диапазоне [min, max] и добавление в строку
            row.push_back(rand() % (max - min + 1) + min);
        }
        matrix.push_back(row);              // Добавляем строку в матрицу
    }
}

/**
 * Функция для заполнения массива вручную с клавиатуры.
 * @param matrix Ссылка на двумерный вектор (матрицу).
 * @param n Количество строк.
 * @param m Количество столбцов.
 */
void fillManual(vector<vector<int>>& matrix, int n, int m) {
    for (int i = 0; i < n; ++i) {           // Цикл по строкам
        vector<int> row;                    // Создаем новую строку
        for (int j = 0; j < m; ++j) {       // Цикл по столбцам
            int num;                        // Переменная для хранения вводимого числа
            cout << "Введите элемент [" << i << "][" << j << "]: ";
            cin >> num;                     // Ввод числа с клавиатуры
            row.push_back(num);              // Добавление числа в строку
        }
        matrix.push_back(row);              // Добавление строки в матрицу
    }
}

/**
 * Функция для вывода массива на экран.
 * @param matrix Константная ссылка на двумерный вектор (матрицу).
 */
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {       // Цикл по строкам матрицы
        for (int num : row) {              // Цикл по элементам строки
            cout << num << "\t";            // Вывод элемента с табуляцией
        }
        cout << endl;                       // Переход на новую строку
    }
}

/**
 * Функция для замены максимального по модулю элемента каждой строки на противоположный.
 * @param matrix Ссылка на двумерный вектор (матрицу).
 */
void replaceMaxAbs(vector<vector<int>>& matrix) {
    for (auto& row : matrix) {             // Цикл по строкам матрицы
        if (row.empty()) continue;          // Пропуск пустых строк
        
        int maxAbsIndex = 0;               // Индекс максимального по модулю элемента
        for (int j = 1; j < row.size(); ++j) {  // Поиск максимального по модулю элемента
            if (abs(row[j]) > abs(row[maxAbsIndex])) {
                maxAbsIndex = j;
            }
        }
        row[maxAbsIndex] = -row[maxAbsIndex];  // Меняем знак на противоположный
    }
}

/**
 * Функция для вставки первой строки после каждой четной строки.
 * @param matrix Ссылка на двумерный вектор (матрицу).
 */
void insertFirstRowAfterEven(vector<vector<int>>& matrix) {
    if (matrix.empty()) return;            // Если матрица пуста, ничего не делаем
    
    vector<vector<int>> newMatrix;         // Новая матрица для результата
    for (int i = 0; i < matrix.size(); ++i) {  // Цикл по строкам исходной матрицы
        newMatrix.push_back(matrix[i]);    // Добавляем текущую строку
        
        if (i % 2 == 0) {                 // Если строка четная (индексация с 0)
            newMatrix.push_back(matrix[0]); // Вставляем первую строку
        }
    }
    matrix = newMatrix;                   // Обновляем исходную матрицу
}

int main() {
    srand(time(0));                       // Инициализация генератора случайных чисел

    int n, m;
    cout << "Введите количество строк (n): ";
    cin >> n;
    cout << "Введите количество столбцов (m): ";
    cin >> m;

    if (n <= 0 || m <= 0) {               // Проверка корректности размеров
        cout << "Ошибка: размеры матрицы должны быть положительными." << endl;
        return 1;
    }

    vector<vector<int>> matrix;            // Создание матрицы

    int choice;
    cout << "Выберите способ заполнения матрицы (1 - случайные числа, 2 - вручную): ";
    cin >> choice;

    if (choice == 1) {                    // Заполнение случайными числами
        int min, max;
        cout << "Введите минимальное значение случайного числа: ";
        cin >> min;
        cout << "Введите максимальное значение случайного числа: ";
        cin >> max;
        fillRandom(matrix, n, m, min, max);
    } 
    else if (choice == 2) {               // Ручное заполнение
        fillManual(matrix, n, m);
    } 
    else {
        cout << "Ошибка: неверный выбор." << endl;
        return 1;
    }

    cout << "Исходная матрица:" << endl;
    printMatrix(matrix);

    // Выполнение первой задачи - замена максимальных по модулю элементов
    replaceMaxAbs(matrix);
    cout << "Матрица после замены максимальных по модулю элементов:" << endl;
    printMatrix(matrix);

    // Выполнение второй задачи - вставка первой строки после четных
    insertFirstRowAfterEven(matrix);
    cout << "Матрица после вставки первой строки после каждой четной:" << endl;
    printMatrix(matrix);

    return 0;                             // Успешное завершение программы
}
