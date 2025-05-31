#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits> // Для numeric_limits<double>::epsilon()

using namespace std;

int main() {
    double start, end, step;

    // Запрашиваем у пользователя ввод интервала и шага с проверкой
    cout << "Введите начало интервала (start): ";
    while (!(cin >> start)) {
        cout << "Ошибка ввода. Пожалуйста, введите число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Введите конец интервала (end): ";
    while (!(cin >> end)) {
        cout << "Ошибка ввода. Пожалуйста, введите число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Введите шаг (step): ";
    while (!(cin >> step) || step <= 0) {
        cout << "Ошибка ввода. Пожалуйста, введите положительное число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Проверка корректности входных данных
    if (start > end) {
        cout << "Ошибка: начало интервала должно быть меньше или равно концу." << endl;
        return 1;
    }

    // Настройка формата вывода (2 знака после запятой)
    cout << fixed << setprecision(2);

    // Итерация по значениям x с учетом погрешности округления
    const double epsilon = numeric_limits<double>::epsilon();
    for (double x = start; x <= end + epsilon; x += step) {
        // Проверка на отрицательное значение x (корень не определен)
        if (x < 0) {
            cout << "x = " << x << " : Ошибка — x отрицательный." << endl;
            continue;
        }

        // Вычисление компонентов функции
        double sqrt_x = sqrt(x); // Квадратный корень x
        double sin_sqrt_x = sin(sqrt_x); // Синус корня
        double y = 3 * sin_sqrt_x + 0.39 * x - 3.8; // Итоговое значение y

        // Проверка на недопустимое значение (NaN)
        if (isnan(y)) {
            cout << "x = " << x << " : Результат не определен." << endl;
        } else {
            // Вывод корректного результата
            cout << "x = " << x << ", y = " << y << endl;
        }
    }

    return 0;
}
