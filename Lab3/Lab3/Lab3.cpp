#include <cstdio>
#include <cmath>

int main()
{
	double a, b, h, y; // Переменные
	int n = 120;

	printf("Vvedite a, b, n: ");
	scanf_s("%lf %lf %d", &a, &b, &n);

	h = (b - a) / 10; // Вычисление шага

	for (double x = a; x - h <= b; x += h) { // Цикл с шагом (b-a)/10
		double s = 0, delta = 1; // Переменные для подсчета суммы и разницы

		for (int i = 1; i <= n; i++) {
			delta *= x / i / 2 / (i * 2 + 1); // Подсчет разницы
			s += pow(i, 2) * delta; // Подсчет суммы
		}

		y = 0.25 * ((x + 1) / sqrt(x) * sinh(sqrt(x)) - cosh(sqrt(x))); // Вычисление Y

		printf("%10.3lf %10.6lf %10.6lf\n", x, y, s); // Вывод данных
	}

	return 0;
}