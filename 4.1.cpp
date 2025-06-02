#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

// Прототипы функций
double getInput(const string& prompt);
double getPositiveInput(const string& prompt);
double calculateFunction(double x);

int main() {
    // Инициализация переменных
    double start = 0.0;
    double end = 0.0;
    double step = 0.0;

    // Ввод параметров
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

        double y = calculateFunction(x);
        cout << "x = " << setw(6) << x << ", y = " << setw(8) << y << endl;
    }

    return 0;
}

double getInput(const string& prompt) {
    double value = 0.0;
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
