#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	double x, y, f, temp, ans; // Переменные
	int choice;

	// Чтение данных
	cout << "Vvedite x, y: "; cin >> x >> y;

	cout << "Vibirite f: 1 - sh(x), 2 - x^2, 3 - exp(x): "; cin >> choice;

	switch (choice) { // Выбор функции
	case 1:
		f = sinh(x); cout << "Vybrana sh(x)" << endl;  break;
	case 2:
		f = pow(x, 2); cout << "Vybrana x^2" << endl; break;
	case 3:
		f = exp(x); cout << "Vybrana e^x" << endl; break;
	default:
		cout << "Ne vibrana funkciya!"; return 1;
	}

	temp = pow(x, 3); // x^3 для условия if

	if (temp > 0) {
		ans = pow(log(f), 3); // Вычисление ответа, если x^3 > 0
		cout << "Vybrana vetv' ln(f(x))^3" << endl;
	}
	else if (temp < 0) {
		ans = tan(temp) + f; // Вычисление ответа, если x^3 < 0
		cout << "Vybrana vetv' tg(x^3) + f(x)" << endl;
	}
	else {
		ans = pow( fabs( pow(y,3) - pow(x,2) ), 1/3. ); // Вычисление ответа, если x^3 = 0
		cout << "Vybrana vetv' (|y^3-x^2|)^(1/3)" << endl;
	}
	
	cout << ans << endl; // Вывод ответа

	return 0;
}