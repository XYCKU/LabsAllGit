#include <cstdio>

double rec(int i) { // Рекурсивная функция
    if (i > 0) 
        return 1. / i + rec(i - 1);
    return 0;
}

int main()
{
    int k; // Переменная
    printf("Vvedite K: "); // Ввод данных
    scanf_s("%d", &k);

    printf("%.4lf\n", rec(k)); // Вывод ответа

    return 0;
}
