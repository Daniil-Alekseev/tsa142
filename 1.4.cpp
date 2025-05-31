#include <iostream>
#include <cmath> // Для математических функций (cos, sin, pow)

using namespace std;

// Прототипы функций с документацией
/**
* @brief Вычисляет значение a по формуле: 2 * cos(x - π/6)
* @param x Входное значение типа double
* @return Результат вычисления
*/
double calculate_a(const double x);

/**
* @brief Вычисляет значение b по формуле: 0.5 + sin²(y)
* @param y Входное значение типа double
* @return Результат вычисления
*/
double calculate_b(const double y);

/**
* @brief Вычисляет значение c по формуле: 1 + z²/(3 + z²/5)
* @param z Входное значение типа double
* @return Результат вычисления
*/
double calculate_c(const double z);

/**
* @brief Главная функция программы
* @details Вычисляет и выводит значения a, b, c для заданных констант x, y, z
* @return 0 при успешном выполнении
*/
int main() {
    // Заданные константы
    const double x = 1.426; // Исходное значение x
    const double y = -1.22; // Исходное значение y
    const double z = 3.5;   // Исходное значение z

    // Вывод исходных данных
    cout << "Исходные данные:" << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl;

    // Вывод результатов вычислений
    cout << "\nРезультаты вычислений:" << endl;
    cout << "a = 2 * cos(x - π/6) = " << calculate_a(x) << endl;
    cout << "b = 1/2 + sin²(y) = " << calculate_b(y) << endl;
    cout << "c = 1 + z²/(3 + z²/5) = " << calculate_c(z) << endl;

    return 0;
}

// Реализации функций
double calculate_a(const double x) {
    return 2 * cos(x - M_PI / 6);
}

double calculate_b(const double y) {
    return 0.5 + pow(sin(y), 2);
}

double calculate_c(const double z) {
    return 1 + (pow(z, 2) / (3 + (pow(z, 2) / 5)));
}
