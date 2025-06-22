#include <stdio.h>
#include <math.h>
#include <locale.h>

double getValue(double x, double n) {
    return (double)(pow(x-1.0f, n)/(n*pow(x, n))); //вычисляем значение n-го члена ряда
}

double sumSequence(double x, double epsilon) {
    double result = 0.0f; //изначально сумма равна нулю
    int idx = 1; //ряд начинается с первого элемента, n==1
    double elem = getValue(x, idx); //вычисляем первый элемент

    while (fabs(elem) > epsilon) { //пока n-й элемент по модулю меньше нашего "эпсилон"
        result += elem; //суммируем элементы
        elem = getValue(x, (double)++idx); //вычисляем следующий (++idx обеспечивает увеличение счётчика ДО копирования значения в функцию)
    }
    return result;//возвращаем результат
}

int main(void) {
    setlocale(LC_ALL, "RUSSIAN"); //установили локаль
    const double startX = 0.5f; //начало диапазона значений X
    const double increment = 0.1f; //приращение X

    const double target_epsilon[3] = {1e-2, 1e-4, 1e-5}; //целевые значения точности
    double referenceResult[3][10] = {}; //массив под результаты ln(x)
    double sumSequenceResult[3][10] = {}; //массив под результаты sumSequence(x, epsilon)
    for (int i = 0; i < 3; i++) { //вычисляем сразу три точности
        for (int j = 0; j < 10; j++) {// для каждой - по 10 экземпляров значения функции и суммы ряда
            referenceResult[i][j] = log(startX+increment*j); //несмотря на то, что i,j - int, их можно так использовать
            sumSequenceResult[i][j] = sumSequence(startX+increment*j, target_epsilon[i]);
        }
        
    }
    /*
    Форматированный вывод
    */
    printf("Точность сходимости: %.e\t\t\t", target_epsilon[0]);
    printf("Точность сходимости: %.e\t\t\t", target_epsilon[1]);
    printf("Точность сходимости: %.e\n", target_epsilon[2]);
    printf("%8s\t%10s\t%8s\t", "X", "Сумма ряда", "ln(x)");
    printf("%8s\t%10s\t%8s\t", "X", "Сумма ряда", "ln(x)");
    printf("%8s\t%10s\t%8s\n", "X", "Сумма ряда", "ln(x)");
    for (int row = 0; row < 10; row++) { //выводим значения по рядам.
        for (int i = 0; i < 3; i++) {
            printf("%8.1lf\t%10.5lf\t%8.5lf\t", startX+0.1f*(double)(row), sumSequenceResult[i][row], referenceResult[i][row]);
        }
        printf("\n");
    }
    return 0;
}