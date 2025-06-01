#include <iostream>
#include <cmath>
#include <limits>
#include <stdexcept>

using namespace std;

// Прототипы функций
/**
* @brief Вычисляет текущий член последовательности
* @param k Номер члена последовательности
* @return Значение k-го члена
*/
double calculateTerm(int k);

/**
* @brief Вычисляет сумму первых n членов последовательности
* @param n Количество членов (должно быть >= 0)
* @return Сумма членов
* @throws invalid_argument если n отрицательное
*/
double sumFirstNTerms(int n);

/**
* @brief Вычисляет сумму членов последовательности с |член| >= e
* @param e Минимальное абсолютное значение (должно быть > 0)
* @return Сумма подходящих членов
* @throws invalid_argument если e не положительное
*/
double sumTermsAboveEpsilon(double e);

/**
* @brief Безопасно получает целое число >= 0 от пользователя
* @param prompt Приглашение для ввода
* @return Введенное число
* @throws runtime_error при ошибке ввода
*/
int getNonNegativeInteger(const string& prompt);

/**
* @brief Безопасно получает положительное число от пользователя
* @param prompt Приглашение для ввода
* @return Введенное число
* @throws runtime_error при ошибке ввода
*/
double getPositiveDouble(const string& prompt);

/**
* @brief Главная функция программы
* @return 0 при успешном выполнении
*/
int main() {
    try {
        // Ввод данных
        int n = getNonNegativeInteger(
            "Введите количество членов последовательности n (целое число >= 0): ");
        
        double e = getPositiveDouble(
            "Введите минимальное абсолютное значение e (число > 0): ");

        // Вычисления
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
    
    // Рекуррентное соотношение: aₖ = -aₖ₋₁ * (k+1)/((k+3)(k+4))
    prev_term *= -1.0 * (k) / ((k + 2) * (k + 3));
    return prev_term;
}

double sumFirstNTerms(int n) {
    if (n < 0) {
        throw invalid_argument("n должно быть >= 0");
    }

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
    
    while (true) {
        term = calculateTerm(k);
        if (abs(term) < e) break;
        sum += term;
        k++;
    }
    
    return sum;
}

int getNonNegativeInteger(const string& prompt) {
    int value;
    cout << prompt;
    
    if (!(cin >> value) || value < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Неверный ввод. Требуется целое число >= 0.");
    }
    
    return value;
}

double getPositiveDouble(const string& prompt) {
    double value;
    cout << prompt;
    
    if (!(cin >> value) || value <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Неверный ввод. Требуется число > 0.");
    }
    
    return value;
}
