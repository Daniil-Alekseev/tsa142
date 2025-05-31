#include <iostream>
#include <limits> // Для numeric_limits при проверке ввода

using namespace std;

// Прототипы функций
/**
* @brief Безопасно получает числовое значение от пользователя
* @param prompt Приглашение для ввода
* @param errorMsg Сообщение об ошибке
* @return Введенное пользователем положительное число
* @note При некорректном вводе завершает программу
*/
double getValue(const string& prompt, const string& errorMsg);

/**
* @brief Вычисляет длину второй стороны прямоугольника
* @param a Длина первой стороны
* @param n Коэффициент в процентах
* @return Длина второй стороны (n% от a)
*/
double calculateSideB(const double a, const double n);

/**
* @brief Вычисляет площадь прямоугольника
* @param a Длина первой стороны
* @param b Длина второй стороны
* @return Площадь прямоугольника
*/
double calculateArea(const double a, const double b);

/**
* @brief Вычисляет периметр прямоугольника
* @param a Длина первой стороны
* @param b Длина второй стороны
* @return Периметр прямоугольника
*/
double calculatePerimeter(const double a, const double b);

/**
* @brief Главная функция программы
* @details Запрашивает параметры прямоугольника, вычисляет и выводит результаты
* @return 0 при успешном выполнении
*/
int main() {
    // Ввод длины стороны a
    double a = getValue(
        "Введите длину стороны a (должно быть положительное число): ",
        "Ошибка! Введено некорректное значение для a."
    );

    // Ввод коэффициента n
    double n = getValue(
        "Введите коэффициент n (в %, например, 50 для 50%): ",
        "Ошибка! Введено некорректное значение для n."
    );

    // Вычисления
    double b = calculateSideB(a, n);
    double area = calculateArea(a, b);
    double perimeter = calculatePerimeter(a, b);

    // Вывод результатов
    cout << "\nРезультаты вычислений:" << endl;
    cout << "Длина стороны a: " << a << endl;
    cout << "Длина стороны b (n% от a): " << b << endl;
    cout << "Площадь прямоугольника: " << area << endl;
    cout << "Периметр прямоугольника: " << perimeter << endl;

    return 0;
}

// Реализации функций
double getValue(const string& prompt, const string& errorMsg) {
    double value = 0.0;
    cout << prompt;
    
    if (!(cin >> value) || value <= 0) {
        cerr << errorMsg << endl;
        exit(1); // Завершение программы при ошибке
    }
    
    return value;
}

double calculateSideB(const double a, const double n) {
    return (n / 100) * a;
}

double calculateArea(const double a, const double b) {
    return a * b;
}

double calculatePerimeter(const double a, const double b) {
    return 2 * (a + b);
}
