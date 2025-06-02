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
double calculateTerm(const int k);

/**
* @brief Вычисляет сумму первых n членов последовательности
* @param n Количество членов (должно быть >= 0)
* @return Сумма членов
*/
double sumFirstNTerms(const int n);

/**
* @brief Вычисляет сумму членов последовательности с |член| >= e
* @param e Минимальное абсолютное значение (должно быть > 0)
* @return Сумма подходящих членов
*/
double sumTermsAboveEpsilon(const double e);

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

/**
* @brief Основная функция программы
* @details Запрашивает у пользователя параметры n и e, вычисляет суммы последовательности
* и выводит результаты на экран
* @return 0 при успешном выполнении
*/
int main() {
    // Ввод параметров
    const int n = getNonNegativeInteger("Введите количество членов последовательности (n >= 0): ");
    const double e = getPositiveDouble("Введите минимальное абсолютное значение (e > 0): ");

    // Вычисление сумм
    const double sum_n = sumFirstNTerms(n);
    const double sum_e = sumTermsAboveEpsilon(e);

    // Вывод результатов
    cout << "Сумма первых " << n << " членов последовательности: " 
         << sum_n << endl;
    cout << "Сумма членов последовательности с |член| >= " << e 
         << ": " << sum_e << endl;

    return 0;
}

// Реализации функций
double calculateTerm(const int k) {
    static double prev_term = 1.0/12.0; // a₀

    if (k == 0) {
        return prev_term;
    }

    // Рекуррентное соотношение: aₖ = -aₖ₋₁ * k/((k+2)(k+3))
    prev_term *= -1.0 * k / ((k + 2) * (k + 3));
    return prev_term;
}

double sumFirstNTerms(const int n) {
    double sum = 0.0;
    for (int k = 0; k < n; ++k) {
        sum += calculateTerm(k);
    }
    return sum;
}

double sumTermsAboveEpsilon(const double e) {
    if (e <= 0) {
        throw invalid_argument("e должно быть > 0");
    }

    double sum = 0.0;
    double term;
    int k = 0;

    while (true) {
        term = calculateTerm(k);
        if (abs(term) < e) {
            break;
        }
        sum += term;
        k++;
    }
    
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
