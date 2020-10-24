#include <cstdio>

char a[99999]; //Массив символов

int main()
{
	int k, size = 0;

	printf("Vvedite kolichestvo simvolov: ");
	scanf_s("%d", &k); // Ввод количества символов

	char temp;

	for (int i = 0; i < k; i++) { // Чтение массива

		printf("Vvedite simvol: ");
		scanf_s(" %c", &temp); // Чтение символа 

		for (int j = 0; j <= size; j++) { // Если символ встречается впервые, то он вносится в массив
			if (temp == a[j]) break; // Если такой символ присутствует в массиве, то выходим из цикла
			if (j == size) { // Если символ не встретился в массиве, то добавляем его туда
				a[j] = temp;
				size++;
				break;
			}
		}
	}

	printf("Kolichestvo razlichnyh simvolov = %d", size); // Вывод ответ

	return 0;
}