#include <iostream>
#include <cmath>
#include <limits>
#include <stdexcept>

using namespace std;

// Прототипы функций
/**
* @brief Вычисляет текущий член последовательности
* @param k Номер члена последовательности (k >= 0)
* @return Значение k-го члена
*/
double calculateTerm(int k);

/**
* @brief Вычисляет сумму первых n членов последовательности
* @param n Количество членов (должно быть >= 0)
* @return Сумма членов
*/
double sumFirstNTerms(int n);

/**
* @brief Вычисляет сумму членов последовательности с |член| >= e
* @param e Минимальное абсолютное значение (должно быть > 0)
* @return Сумма подходящих членов
*/
double sumTermsAboveEpsilon(double e);

/**
* @brief Получает неотрицательное целое число от пользователя
* @param prompt Сообщение для пользователя
* @return Введенное число
*/
int getNonNegativeInteger(const string& prompt);

/**
* @brief Получает положительное число от пользователя
* @param prompt Сообщение для пользователя
* @return Введенное число
*/
double getPositiveDouble(const string& prompt);

int main() {
    try {
        // Ввод параметров
        int n = getNonNegativeInteger("Введите количество членов последовательности (n >= 0): ");
        double e = getPositiveDouble("Введите минимальное абсолютное значение (e > 0): ");

        // Вычисление сумм
        double sum_n = sumFirstNTerms(n);
        double sum_e = sumTermsAboveEpsilon(e);

        // Вывод результатов
        cout << "Сумма первых " << n << " членов последовательности: " 
             << sum_n << endl;
        cout << "Сумма членов последовательности с |член| >= " << e 
             << ": " << sum_e << endl;

    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}

// Реализации функций
double calculateTerm(int k) {
    static double prev_term = 1.0/12.0; // a₀

    if (k == 0) {
        return prev_term;
    }

    // Рекуррентное соотношение: aₖ = -aₖ₋₁ * k/((k+2)(k+3))
    prev_term *= -1.0 * k / ((k + 2) * (k + 3));
    return prev_term;
}

double sumFirstNTerms(int n) {
    double sum = 0.0;
    for (int k = 0; k < n; ++k) {
        sum += calculateTerm(k);
    }
    return sum;
}

double sumTermsAboveEpsilon(double e) {
    if (e <= 0) {
        throw invalid_argument("e должно быть > 0");
    }

    double sum = 0.0;
    double term;
    int k = 0;

    do {
        term = calculateTerm(k);
        if (abs(term) >= e) {
            sum += term;
        }
        k++;
    } while (abs(term) >= e || k < 1000); // Добавлено ограничение на максимальное количество итераций

    return sum;
}

int getNonNegativeInteger(const string& prompt) {
    int value = 0;
    cout << prompt;

    if (!(cin >> value) || value < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Неверный ввод. Требуется целое число >= 0.");
    }

    return value;
}

double getPositiveDouble(const string& prompt) {
    double value = 0.0;
    cout << prompt;

    if (!(cin >> value) || value <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Неверный ввод. Требуется число > 0.");
    }

    return value;
}
