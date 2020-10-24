#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const double EPS = 1e-4; // ��������� ��� �������� ��������

void DeltaCalculating(double &delta, int k) { // ���������� ����������
	for (int p = min(2, 4 * (k - 1)); p <= 4 * k; p += 2) {
		delta /= p;
	}

	for (int p = min(3, abs(4 * (k - 1) - 5)); p <= 4 * k - 5; p += 2) {
		delta *= p;
	}
}

double Y(double x) { // ���������� Y
	return sqrt(sqrt(x + 1)) - (4 - x) / 4;
}

void Solve(double a, double b, double h) { // �������� ������� ��� ������� ������
	double delta = 1, sum;
	int k;

	for (double x = a; x < b + h / 2; x += h) {	// ���� � ����� h
		k = 2; // ������������� ����������
		delta = x * x;
		sum = 0;

		while (fabs(delta) > EPS) { // ���� while ��� ���������� �������� EPS
			delta *= -1;

			DeltaCalculating(delta, k); // ����� ������� ��� �������� ����������

			sum += delta; // ���������� �����
			k++;
		}

		printf("�������� X = %.2lf\n���������� �������� = %d\n�������� ���������� = %lf\n����� = %lf\n�������� Y = %lf\n\n", x, k - 2, delta, sum, Y(x)); // ����� ������ ��� ������� ����
	}
}

int main()
{
	setlocale(LC_ALL, "Russian"); // ���������� ��������� ��������� � �������
	Solve(-0.8, 0.9, 0.1); // ����� �������� ������� ��� ������� ������
	return 0;
}
