#include <cstdio>
#include <iostream>

double rec(int i, int n, double recur) // Рекурсивная функция
{ 
    recur /= i; // Рекурент
    if (i <= n)
        return recur + rec(i + 1, n, recur);
    return 0;
}

double notRec(int n) // Не рекурсивная функция
{ 
    double ans = 1;
    double recur = 1; // Рекурент
    for (int i = 2; i <= n; i++)
    {
        recur /= i; // Вычисление рекурента
        ans += recur; // Прибавление к ответу
    }
    return ans;
}

int main()
{
    setlocale(LC_ALL, "Russian"); // Поддержка кирилицы
    int k; // Переменная
    printf("Введите K: "); // Ввод данных
    scanf_s("%d", &k);

    printf("Результат при рекурентном подсчете: %10.5lf\n", rec(1, k, 1)); // Подсчет рекурентно
    printf("Результат при не рекурентном подсчете: %7.5lf\n", notRec(k)); // Подсчет не рекурентно

    return 0;
}
