#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>
#include <vector>

using namespace std;

// Перечисление для выбора способа заполнения
enum class FillMethod {
    RANDOM = 1,
    MANUAL = 2
};

// Прототипы функций
size_t getPositiveSize(const string& prompt);
int getIntegerInput(const string& prompt);
int getIntegerInRange(const string& prompt, int min, int max);
int** createMatrix(size_t rows, size_t cols);
bool freeMatrix(int** matrix, size_t rows);
bool fillRandom(int** matrix, size_t rows, size_t cols, int min, int max);
bool fillManual(int** matrix, size_t rows, size_t cols);
bool printMatrix(const int* const* matrix, size_t rows, size_t cols);
bool replaceMaxAbs(int** matrix, size_t rows, size_t cols);
int** insertFirstAfterEven(const int* const* matrix, size_t& rows, size_t cols);

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    try {
        // Получаем размеры матрицы с проверкой ввода
        size_t n = getPositiveSize("Введите количество строк (n > 0): ");
        size_t m = getPositiveSize("Введите количество столбцов (m > 0): ");

        // Создаем матрицу
        int** matrix = createMatrix(n, m);

        // Выбираем способ заполнения
        cout << "Выберите способ заполнения:\n"
             << "1 - Случайные числа\n"
             << "2 - Вручную\n";
        int choice = getIntegerInRange("Ваш выбор: ", 1, 2);

        switch (static_cast<FillMethod>(choice)) {
            case FillMethod::RANDOM: {
                int min = getIntegerInput("Введите минимальное значение: ");
                int max = getIntegerInput("Введите максимальное значение: ");
                if (!fillRandom(matrix, n, m, min, max)) {
                    throw runtime_error("Ошибка при заполнении матрицы случайными числами");
                }
                break;
            }
            case FillMethod::MANUAL:
                if (!fillManual(matrix, n, m)) {
                    throw runtime_error("Ошибка при ручном заполнении матрицы");
                }
                break;
        }

        cout << "Исходная матрица:" << endl;
        if (!printMatrix(matrix, n, m)) {
            throw runtime_error("Ошибка при выводе матрицы");
        }

        // Первое задание - замена максимальных по модулю элементов
        if (!replaceMaxAbs(matrix, n, m)) {
            throw runtime_error("Ошибка при замене максимальных по модулю элементов");
        }
        cout << "После замены максимальных по модулю элементов:" << endl;
        if (!printMatrix(matrix, n, m)) {
            throw runtime_error("Ошибка при выводе матрицы");
        }

        // Второе задание - вставка первой строки после четных
        size_t newRows = n;
        int** newMatrix = insertFirstAfterEven(matrix, newRows, m);
        cout << "После вставки первой строки после четных:" << endl;
        if (!printMatrix(newMatrix, newRows, m)) {
            throw runtime_error("Ошибка при выводе матрицы");
        }

        // Освобождаем память
        if (!freeMatrix(matrix, n) || !freeMatrix(newMatrix, newRows)) {
            throw runtime_error("Ошибка при освобождении памяти");
        }

    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}

// Реализация функций
size_t getPositiveSize(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value > 0) {
            return static_cast<size_t>(value);
        }
        cout << "Ошибка: введите положительное число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int getIntegerInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        }
        cout << "Ошибка: введите целое число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int getIntegerInRange(const string& prompt, int min, int max) {
    while (true) {
        int value = getIntegerInput(prompt);
        if (value >= min && value <= max) {
            return value;
        }
        cout << "Ошибка: введите число от " << min << " до " << max << ".\n";
    }
}

int** createMatrix(size_t rows, size_t cols) {
    int** matrix = new int*[rows];
    for (size_t i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

bool freeMatrix(int** matrix, size_t rows) {
    if (matrix == nullptr) return false;
    
    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return true;
}

bool fillRandom(int** matrix, size_t rows, size_t cols, int min, int max) {
    if (matrix == nullptr || min > max) return false;
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % (max - min + 1) + min;
        }
    }
    return true;
}

bool fillManual(int** matrix, size_t rows, size_t cols) {
    if (matrix == nullptr) return false;
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix[i][j] = getIntegerInput("Введите элемент [" + to_string(i) + "][" + to_string(j) + "]: ");
        }
    }
    return true;
}

bool printMatrix(const int* const* matrix, size_t rows, size_t cols) {
    if (matrix == nullptr) return false;
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    return true;
}

bool replaceMaxAbs(int** matrix, size_t rows, size_t cols) {
    if (matrix == nullptr) return false;
    
    for (size_t i = 0; i < rows; ++i) {
        size_t maxAbsIndex = 0;
        for (size_t j = 1; j < cols; ++j) {
            if (abs(matrix[i][j]) > abs(matrix[i][maxAbsIndex])) {
                maxAbsIndex = j;
            }
        }
        matrix[i][maxAbsIndex] = -matrix[i][maxAbsIndex];
    }
    return true;
}

int** insertFirstAfterEven(const int* const* matrix, size_t& rows, size_t cols) {
    if (matrix == nullptr) return nullptr;
    
    size_t newRows = rows + (rows + 1) / 2;
    int** newMatrix = createMatrix(newRows, cols);

    size_t newRow = 0;
    for (size_t i = 0; i < rows; ++i) {
        // Копируем текущую строку
        for (size_t j = 0; j < cols; ++j) {
            newMatrix[newRow][j] = matrix[i][j];
        }
        newRow++;

        // Если строка четная, вставляем копию первой строки
        if (i % 2 == 0) {
            for (size_t j = 0; j < cols; ++j) {
                newMatrix[newRow][j] = matrix[0][j];
            }
            newRow++;
        }
    }

    rows = newRows;
    return newMatrix;
}
