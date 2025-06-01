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
* @throws runtime_error при некорректном вводе
*/
double getInput(const string& prompt);

/**
* @brief Получает положительное числовое значение от пользователя
* @param prompt Сообщение для пользователя
* @return Введенное положительное значение
* @throws runtime_error при некорректном вводе
*/
double getPositiveInput(const string& prompt);

/**
* @brief Вычисляет значение функции y = 3*sin(√x) + 0.39x - 3.8
* @param x Аргумент функции
* @return Значение функции
* @throws domain_error при отрицательном x
*/
double calculateFunction(double x);

// Главная функция
/**
* @brief Основная функция программы
* @details Вычисляет значения функции на заданном интервале с указанным шагом
* @return 0 при успешном выполнении, 1 при ошибке ввода
*/
int main() {
    try {
        // Ввод параметров
        double start = getInput("Введите начало интервала (start): ");
        double end = getInput("Введите конец интервала (end): ");
        double step = getPositiveInput("Введите шаг (step): ");

        // Проверка интервала
        if (start > end) {
            throw runtime_error("Ошибка: начало интервала должно быть меньше или равно концу.");
        }

        // Настройка вывода
        cout << fixed << setprecision(2);

        // Вычисление и вывод значений функции
        const double epsilon = numeric_limits<double>::epsilon();
        for (double x = start; x <= end + epsilon; x += step) {
            try {
                double y = calculateFunction(x);
                cout << "x = " << x << ", y = " << y << endl;
            } catch (const domain_error& e) {
                cout << "x = " << x << " : " << e.what() << endl;
            }
        }
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
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
        throw runtime_error("Ошибка ввода: требуется числовое значение.");
    }
    return value;
}

double getPositiveInput(const string& prompt) {
    double value = getInput(prompt);
    if (value <= 0) {
        throw runtime_error("Ошибка: значение должно быть положительным.");
    }
    return value;
}

double calculateFunction(double x) {
    if (x < 0) {
        throw domain_error("Ошибка — x отрицательный.");
    }
    double sqrt_x = sqrt(x);
    return 3 * sin(sqrt_x) + 0.39 * x - 3.8;
}
