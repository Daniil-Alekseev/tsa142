#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

// Прототипы функций
/**
* @brief Получает числовое значение от пользователя
* @param prompt Сообщение для пользователя
* @return Введенное значение
*/
double getInput(const string& prompt);

/**
* @brief Получает положительное числовое значение от пользователя
* @param prompt Сообщение для пользователя
* @return Введенное положительное значение
*/
double getPositiveInput(const string& prompt);

/**
* @brief Вычисляет значение функции y = 3*sin(√x) + 0.39x - 3.8
* @param x Аргумент функции
* @return Значение функции
*/
double calculateFunction(double x);

// Главная функция
/**
* @brief Основная функция программы
* @details Вычисляет значения функции на заданном интервале с указанным шагом
* @return 0 при успешном выполнении, 1 при ошибке ввода
*/
int main() {
    // Ввод параметров
    double start, end, step;
    
    cout << "Введите начало интервала (start): ";
    if (!(cin >> start)) {
        cerr << "Ошибка ввода: требуется числовое значение." << endl;
        return 1;
    }
    
    cout << "Введите конец интервала (end): ";
    if (!(cin >> end)) {
        cerr << "Ошибка ввода: требуется числовое значение." << endl;
        return 1;
    }
    
    cout << "Введите шаг (step): ";
    if (!(cin >> step) || step <= 0) {
        cerr << "Ошибка: значение должно быть положительным." << endl;
        return 1;
    }

    // Проверка интервала
    if (start > end) {
        cerr << "Ошибка: начало интервала должно быть меньше или равно концу." << endl;
        return 1;
    }

    // Настройка вывода
    cout << fixed << setprecision(2);

    // Вычисление и вывод значений функции
    const double epsilon = numeric_limits<double>::epsilon();
    for (double x = start; x <= end + epsilon; x += step) {
        if (x < 0) {
            cout << "x = " << setw(6) << x << " : не принадлежит ООФ" << endl;
            continue;
        }
        
        double y = 3 * sin(sqrt(x)) + 0.39 * x - 3.8;
        cout << "x = " << setw(6) << x << ", y = " << setw(8) << y << endl;
    }

    return 0;
}

// Реализации функций
double getInput(const string& prompt) {
    double value;
    cout << prompt;
    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Ошибка ввода: требуется числовое значение." << endl;
        exit(1);
    }
    return value;
}

double getPositiveInput(const string& prompt) {
    double value = getInput(prompt);
    if (value <= 0) {
        cerr << "Ошибка: значение должно быть положительным." << endl;
        exit(1);
    }
    return value;
}

double calculateFunction(double x) {
    if (x < 0) {
        cerr << "не принадлежит ООФ" << endl;
        exit(1);
    }
    double sqrt_x = sqrt(x);
    return 3 * sin(sqrt_x) + 0.39 * x - 3.8;
}
