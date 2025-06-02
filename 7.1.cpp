#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>

using namespace std;

/**
* @brief Перечисление методов заполнения матрицы
*/
enum class FillMethod { RANDOM = 1, MANUAL = 2 };

// Прототипы функций
/**
* @brief Создает двумерный массив (матрицу) заданного размера
* @param rows - количество строк в матрице (должно быть > 0)
* @param cols - количество столбцов в матрице (должно быть > 0)
* @return Указатель на созданную матрицу
*/
int** createMatrix(const size_t rows, const size_t cols);

/**
* @brief Освобождает память, занятую матрицей
* @param matrix - указатель на освобождаемую матрицу
* @param rows - количество строк в матрице
* @return nullptr (нулевой указатель)
*/
int** freeMatrix(int** matrix, const size_t rows);

/**
* @brief Заполняет матрицу случайными числами в заданном диапазоне
* @param matrix - указатель на заполняемую матрицу
* @param rows - количество строк в матрице
* @param cols - количество столбцов в матрице
* @param min - минимальное значение для генерации случайных чисел
* @param max - максимальное значение для генерации случайных чисел
* @return Указатель на заполненную матрицу
*/
int** fillRandom(int** matrix, const size_t rows, const size_t cols, const int min, const int max);

/**
* @brief Заполняет матрицу значениями, вводимыми пользователем вручную
* @param matrix - указатель на заполняемую матрицу
* @param rows - количество строк в матрице
* @param cols - количество столбцов в матрице
* @return Указатель на заполненную матрицу
*/
int** fillManual(int** matrix, const size_t rows, const size_t cols);

/**
* @brief Выводит матрицу в стандартный поток вывода
* @param matrix - указатель на выводимую матрицу
* @param rows - количество строк в матрице
* @param cols - количество столбцов в матрице
* @return 0 в случае успешного вывода
*/
int printMatrix(const int* const* matrix, const size_t rows, const size_t cols);

/**
* @brief Заменяет максимальный по модулю элемент каждой строки на противоположный
* @param matrix - указатель на преобразуемую матрицу
* @param rows - количество строк в матрице
* @param cols - количество столбцов в матрице
* @return Указатель на преобразованную матрицу
*/
int** replaceMaxAbs(int** matrix, const size_t rows, const size_t cols);

/**
* @brief Вставляет копию первой строки после каждой четной строки
* @param matrix - указатель на исходную матрицу
* @param rows - количество строк в исходной матрице
* @param cols - количество столбцов в матрице
* @param newRows - ссылка на переменную для хранения нового количества строк
* @return Указатель на новую матрицу с вставленными строками
*/
int** insertFirstAfterEven(const int* const* matrix, const size_t rows, const size_t cols, size_t& newRows);

/**
* @brief Запрашивает у пользователя положительное целое число
* @param prompt - приглашение для ввода, выводимое пользователю
* @return Введенное пользователем положительное целое число
*/
size_t getPositiveInteger(const string& prompt);

/**
* @brief Основная функция программы
* @details Создает матрицу, заполняет ее выбранным способом,
* выполняет преобразования (замена максимальных по модулю элементов
* и вставка строк) и выводит результаты
* @return 0 при успешном выполнении программы
*/
int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    const size_t n = getPositiveInteger("Введите количество строк (n > 0): ");
    const size_t m = getPositiveInteger("Введите количество столбцов (m > 0): ");

    int** matrix = createMatrix(n, m);

    cout << "Выберите способ заполнения:\n"
         << static_cast<int>(FillMethod::RANDOM) << " - случайные\n"
         << static_cast<int>(FillMethod::MANUAL) << " - вручную\n"
         << "Ваш выбор: ";
    
    int choice;
    cin >> choice;
    while (choice != static_cast<int>(FillMethod::RANDOM) && 
           choice != static_cast<int>(FillMethod::MANUAL)) {
        cout << "Неверный выбор. Введите 1 или 2: ";
        cin >> choice;
    }

    if (static_cast<FillMethod>(choice) == FillMethod::RANDOM) {
        int min, max;
        cout << "Введите минимальное значение: ";
        cin >> min;
        cout << "Введите максимальное значение: ";
        cin >> max;
        matrix = fillRandom(matrix, n, m, min, max);
    } else {
        matrix = fillManual(matrix, n, m);
    }

    cout << "Исходная матрица:" << endl;
    printMatrix(matrix, n, m);

    matrix = replaceMaxAbs(matrix, n, m);
    cout << "После замены максимальных по модулю элементов:" << endl;
    printMatrix(matrix, n, m);

    size_t newRows = 0;
    int** newMatrix = insertFirstAfterEven(matrix, n, m, newRows);
    cout << "После вставки первой строки после четных:" << endl;
    printMatrix(newMatrix, newRows, m);

    matrix = freeMatrix(matrix, n);
    newMatrix = freeMatrix(newMatrix, newRows);

    return 0;
}

// Реализации функций

int** createMatrix(const size_t rows, const size_t cols) {
    int** matrix = new int*[rows];
    for (size_t i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

int** freeMatrix(int** matrix, const size_t rows) {
    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return nullptr;
}

int** fillRandom(int** matrix, const size_t rows, const size_t cols, const int min, const int max) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % (max - min + 1) + min;
        }
    }
    return matrix;
}

int** fillManual(int** matrix, const size_t rows, const size_t cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            cout << "Введите элемент [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

int printMatrix(const int* const* matrix, const size_t rows, const size_t cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    return 0;
}

int** replaceMaxAbs(int** matrix, const size_t rows, const size_t cols) {
    for (size_t i = 0; i < rows; ++i) {
        size_t maxAbsIndex = 0;
        for (size_t j = 1; j < cols; ++j) {
            if (abs(matrix[i][j]) > abs(matrix[i][maxAbsIndex])) {
                maxAbsIndex = j;
            }
        }
        matrix[i][maxAbsIndex] = -matrix[i][maxAbsIndex];
    }
    return matrix;
}

int** insertFirstAfterEven(const int* const* matrix, const size_t rows, const size_t cols, size_t& newRows) {
    newRows = rows + (rows + 1) / 2;
    int** newMatrix = createMatrix(newRows, cols);

    size_t newRow = 0;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            newMatrix[newRow][j] = matrix[i][j];
        }
        newRow++;

        if (i % 2 == 0) {
            for (size_t j = 0; j < cols; ++j) {
                newMatrix[newRow][j] = matrix[0][j];
            }
            newRow++;
        }
    }

    return newMatrix;
}

size_t getPositiveInteger(const string& prompt) {
    int value;
    cout << prompt;
    cin >> value;
    while (cin.fail() || value <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода. Пожалуйста, введите положительное целое число: ";
        cin >> value;
    }
    return static_cast<size_t>(value);
}
