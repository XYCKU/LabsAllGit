#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const double EPS = 1e-4;

int main()
{
	setlocale(LC_ALL, "Russian");
	double a = -0.8, b = 0.9, h = 0.1, delta = 1, sum;
	int k;

	for (double x = a; x < b + h / 2; x += h) {
		//cout << "step " << x << endl;
		k = 2;
		delta = x*x;
		sum = 0;
		while (fabs(delta) > EPS) {
			delta *= -1;

			for (int p = min(2, 4 * (k - 1)); p <= 4 * k; p += 2) {
				//cout << -p << endl;
				delta /= p;
			}

			for (int p = min(3, abs(4 * (k - 1) - 5)); p <= 4 * k - 5; p += 2) {
				delta *= p;
				//cout << p << endl;
			}

			sum += delta;
			k++;
		}

		double y = sqrt(sqrt(x + 1)) - (4 - x) / 4;

		printf("Число итераций = %d\nЗначение рекуррента = %lf\nСумма = %lf\nЗначение Y = %lf\n\n", k - 2, delta, sum, y);
	}

	return 0;
}
