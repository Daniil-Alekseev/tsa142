#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

// Функция для вычисления суммы первых n членов последовательности с использованием рекуррентного соотношения
double sum_first_n_terms(int n) {
    if (n < 0) return 0.0;
    
    double sum = 0.0;
    double current_term = 1.0 / 12.0; // Первый член последовательности (k=0)
    sum += current_term;
    
    for (int k = 1; k <= n; ++k) {
        // Рекуррентное соотношение: a_k = -a_{k-1} * (k+1)/((k+3)(k+4))
        current_term *= -1.0 * (k + 1) / ((k + 3) * (k + 4));
        sum += current_term;
    }
    
    return sum;
}

// Функция для вычисления суммы членов последовательности, по модулю не меньших e
double sum_terms_above_epsilon(double e) {
    if (e <= 0) return 0.0;
    
    double sum = 0.0;
    double current_term = 1.0 / 12.0; // Первый член последовательности (k=0)
    int k = 0;
    
    while (abs(current_term) >= e) {
        sum += current_term;
        k++;
        // Рекуррентное соотношение для следующего члена
        current_term *= -1.0 * (k + 1) / ((k + 3) * (k + 4));
        
        // Защита от бесконечного цикла при очень маленьких e
        if (k > 1000) break;
    }
    
    return sum;
}

int main() {
    int n;
    double e;

    // Запрос ввода n с проверкой
    cout << "Введите количество членов последовательности n (целое число >= 0): ";
    while (!(cin >> n) || n < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода. Пожалуйста, введите целое число >= 0: ";
    }

    // Запрос ввода e с проверкой
    cout << "Введите минимальное абсолютное значение e (число > 0): ";
    while (!(cin >> e) || e <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода. Пожалуйста, введите число > 0: ";
    }

    // Вычисление и вывод суммы первых n членов
    double sum_n = sum_first_n_terms(n);
    cout << "Сумма первых " << n << " членов последовательности: " << sum_n << endl;

    // Вычисление и вывод суммы членов, по модулю не меньших e
    double sum_epsilon = sum_terms_above_epsilon(e);
    cout << "Сумма членов последовательности с |член| >= " << e << ": " << sum_epsilon << endl;

    return 0;
}
