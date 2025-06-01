#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// Прототипы функций
/**
* @brief Выделяет память для двумерного массива
* @param rows Количество строк
* @param cols Количество столбцов
* @return Указатель на созданный массив
*/
int** createMatrix(int rows, int cols);

/**
* @brief Освобождает память двумерного массива
* @param matrix Указатель на массив
* @param rows Количество строк
*/
void freeMatrix(int** matrix, int rows);

/**
* @brief Заполняет массив случайными числами
* @param matrix Указатель на массив
* @param rows Количество строк
* @param cols Количество столбцов
* @param min Минимальное значение
* @param max Максимальное значение
*/
void fillRandom(int** matrix, int rows, int cols, int min, int max);

/**
* @brief Заполняет массив вручную
* @param matrix Указатель на массив
* @param rows Количество строк
* @param cols Количество столбцов
*/
void fillManual(int** matrix, int rows, int cols);

/**
* @brief Выводит массив на экран
* @param matrix Указатель на массив
* @param rows Количество строк
* @param cols Количество столбцов
*/
void printMatrix(int** matrix, int rows, int cols);

/**
* @brief Заменяет максимальный по модулю элемент каждой строки на противоположный
* @param matrix Указатель на массив
* @param rows Количество строк
* @param cols Количество столбцов
*/
void replaceMaxAbs(int** matrix, int rows, int cols);

/**
* @brief Вставляет копию первой строки после каждой четной строки
* @param matrix Указатель на массив (будет изменен)
* @param rows Указатель на количество строк (будет изменено)
* @param cols Количество столбцов
* @return Новая матрица с вставленными строками
*/
int** insertFirstAfterEven(int** matrix, int* rows, int cols);

int main() {
    srand(time(0));

    int n, m;
    cout << "Введите количество строк (n > 0): ";
    cin >> n;
    cout << "Введите количество столбцов (m > 0): ";
    cin >> m;

    if (n <= 0 || m <= 0) {
        cout << "Ошибка: размеры матрицы должны быть положительными." << endl;
        return 1;
    }

    // Создание матрицы
    int** matrix = createMatrix(n, m);

    int choice;
    cout << "Выберите способ заполнения (1 - случайные, 2 - вручную): ";
    cin >> choice;

    if (choice == 1) {
        int min, max;
        cout << "Введите минимальное значение: ";
        cin >> min;
        cout << "Введите максимальное значение: ";
        cin >> max;
        fillRandom(matrix, n, m, min, max);
    } 
    else if (choice == 2) {
        fillManual(matrix, n, m);
    } 
    else {
        cout << "Ошибка: неверный выбор." << endl;
        freeMatrix(matrix, n);
        return 1;
    }

    cout << "Исходная матрица:" << endl;
    printMatrix(matrix, n, m);

    // Первая задача
    replaceMaxAbs(matrix, n, m);
    cout << "После замены максимальных по модулю элементов:" << endl;
    printMatrix(matrix, n, m);

    // Вторая задача
    int newRows = n;
    int** newMatrix = insertFirstAfterEven(matrix, &newRows, m);
    cout << "После вставки первой строки после четных:" << endl;
    printMatrix(newMatrix, newRows, m);

    // Освобождение памяти
    freeMatrix(matrix, n);
    freeMatrix(newMatrix, newRows);

    return 0;
}

// Реализации функций
int** createMatrix(int rows, int cols) {
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void fillRandom(int** matrix, int rows, int cols, int min, int max) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % (max - min + 1) + min;
        }
    }
}

void fillManual(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "Введите элемент [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }
}

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void replaceMaxAbs(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        int maxAbsIndex = 0;
        for (int j = 1; j < cols; ++j) {
            if (abs(matrix[i][j]) > abs(matrix[i][maxAbsIndex])) {
                maxAbsIndex = j;
            }
        }
        matrix[i][maxAbsIndex] = -matrix[i][maxAbsIndex];
    }
}

int** insertFirstAfterEven(int** matrix, int* rows, int cols) {
    int newRows = *rows + (*rows + 1) / 2;
    int** newMatrix = createMatrix(newRows, cols);
    
    int newRow = 0;
    for (int i = 0; i < *rows; ++i) {
        // Копируем текущую строку
        for (int j = 0; j < cols; ++j) {
            newMatrix[newRow][j] = matrix[i][j];
        }
        newRow++;
        
        // Если строка четная, добавляем копию первой строки
        if (i % 2 == 0) {
            for (int j = 0; j < cols; ++j) {
                newMatrix[newRow][j] = matrix[0][j];
            }
            newRow++;
        }
    }
    
    *rows = newRows;
    return newMatrix;
}
