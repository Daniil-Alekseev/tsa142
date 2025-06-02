#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

/**
* @brief Получает числовое значение от пользователя
* @param prompt Приглашение для ввода, отображаемое пользователю
* @return Введенное пользователем число типа double
*/
double getInput(const string& prompt);

/**
* @brief Получает положительное числовое значение от пользователя
* @param prompt Приглашение для ввода, отображаемое пользователю
* @return Введенное пользователем положительное число типа double
*/
double getPositiveInput(const string& prompt);

/**
* @brief Вычисляет значение функции y = 3*sin(√x) + 0.39x - 3.8
* @param x Аргумент функции (x должен быть >= 0)
* @return Значение функции в точке x
*/
double calculateFunction(double x);

/**
* @brief Основная функция программы
* @details Программа вычисляет значения функции y = 3*sin(√x) + 0.39x - 3.8
* на заданном интервале [start, end] с указанным шагом step.
* Для значений x < 0 выводится сообщение, что они не принадлежат области определения.
* В случае ошибок ввода выводится соответствующее сообщение и программа завершается.
* @return 0 при успешном выполнении, 1 при ошибке ввода
*/
int main() {
    // Ввод параметров
    double start = getInput("Введите начало интервала (start): ");
    double end = getInput("Введите конец интервала (end): ");
    double step = getPositiveInput("Введите шаг (step): ");

    // Проверка корректности интервала
    if (start > end) {
        cerr << "Ошибка: начало интервала должно быть меньше или равно концу." << endl;
        return 1;
    }

    // Настройка формата вывода (2 знака после запятой)
    cout << fixed << setprecision(2);

    // Вычисление и вывод значений функции
    const double epsilon = numeric_limits<double>::epsilon();
    for (double x = start; x <= end + epsilon; x += step) {
        if (x < 0) {
            cout << "x = " << setw(6) << x << " : не принадлежит ООФ" << endl;
            continue;
        }

        double y = calculateFunction(x);
        cout << "x = " << setw(6) << x << ", y = " << setw(8) << y << endl;
    }

    return 0;
}

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
    return 3 * sin(sqrt(x)) + 0.39 * x - 3.8;
}
