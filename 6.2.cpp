#include <iostream>
#include <cmath>
#include <limits>
#include <stdexcept>

using namespace std;

// Прототипы функций
/**
* @brief Вычисляет факториал числа
* @param n Неотрицательное целое число
* @return Факториал числа n
* @throws invalid_argument если n отрицательное
*/
unsigned long long factorial(int n);

/**
* @brief Вычисляет член последовательности
* @param k Индекс члена последовательности
* @return Значение k-го члена последовательности
*/
double calculateSequenceTerm(int k);

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
double sumTermsAboveE(double e);

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
            "Введите количество членов последовательности (n >= 0): ");
        
        double e = getPositiveDouble(
            "Введите минимальное абсолютное значение (e > 0): ");

        // Вычисления
        double sum_n = sumFirstNTerms(n);
        double sum_e = sumTermsAboveE(e);

        // Вывод результатов
        cout << "Сумма первых " << n << " членов: " << sum_n << endl;
        cout << "Сумма членов с |a_k| >= " << e << ": " << sum_e << endl;

    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}

// Реализации функций
unsigned long long factorial(int n) {
    if (n < 0) {
        throw invalid_argument("Факториал отрицательного числа не определен");
    }

    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double calculateSequenceTerm(int k) {
    double numerator = pow(-1, k);
    unsigned long long denominator = factorial(k + 2) * factorial(k + 3);
    return numerator / denominator;
}

double sumFirstNTerms(int n) {
    if (n < 0) {
        throw invalid_argument("n должно быть >= 0");
    }

    double sum = 0.0;
    for (int k = 0; k <= n; ++k) {
        sum += calculateSequenceTerm(k);
    }
    return sum;
}

double sumTermsAboveE(double e) {
    if (e <= 0) {
        throw invalid_argument("e должно быть > 0");
    }

    double sum = 0.0;
    int k = 0;
    while (true) {
        double term = calculateSequenceTerm(k);
        if (abs(term) < e) break;
        sum += term;
        k++;
        
        // Защита от слишком большого количества итераций
        if (k > 1000) {
            cerr << "Предупреждение: достигнуто максимальное количество итераций" << endl;
            break;
        }
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

