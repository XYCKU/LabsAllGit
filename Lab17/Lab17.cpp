#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int M = 10; // Размер массива хеш-таблицы и вспомогательного массива

struct Book { // Структура книги
	char name[40];
	int pages, releaseDate;
};

void HashWrite(Book* item, Book* hash[], int* misc); // Функция добавления элемента в хеш-таблицу
int HashFind(int key, Book* hash[], int* misc); // Функция поиска элемента в хеш-таблице по году выпуска

int main() {
	setlocale(LC_ALL, "ru"); // Поддержка кириллицы

	int n, rands[M];

	printf("Введите количество книг: "); // Чтение количества книг
	scanf("%d", &n);

	Book* a = new Book[n];
	Book* H[M];

	printf("Вспомогательный массив:\n");
	for (int i = 0; i < M; i++) { // Очищаем хеш-таблицу, задаем псевдослучайные значения для вспомогательного массива
		H[i] = nullptr;
		rands[i] = 1 + (rand() % (M - 1));
		printf("%d ", rands[i]); // Выводим вспомогательный массив
	}

	printf("\n\n");
	for (int i = 0; i < n; i++) { // Чтение информации о каждой книге
		printf("Введите название книги: ");
		scanf(" %[^\n]s", a[i].name);
		printf("Введите количество страниц и год выпуска: ");
		scanf("%d%d", &a[i].pages, &a[i].releaseDate);

		HashWrite(&a[i], H, rands); // Добавление книги в хеш-таблицу
	}

	for (int i = 0; i < M; i++) { // Вывод содержимого хеш-таблицы
		int o;
		if (H[i] != nullptr)
			o = H[i]->releaseDate;
		else
			o = -1;
		printf("H[%d] = %d\n", i, o);
	}

	int key = 0, i;
	while (key != -1) { // Будем искать книгу, пока пользователь не введет -1
		printf("Введите год выпуска искомой книги: ");
		scanf("%d", &key);
		i = HashFind(key, H, rands); // Поиск книги в хеш-таблице
		if (i != -1) { // Если нашли, то выводим информацию о книге
			printf("Индекс искомой книги в хеш-таблице: %d\n", i);
			printf("Название: %s\nКоличество страниц: %d\nГод выпуска: %d\n\n", H[i]->name, H[i]->pages, H[i]->releaseDate);
		} 
		else {
			printf("Не найдено такой книги!\n");
		}
		printf("\n");
	}

 	delete[] a; // Очищаем память
	return 0;
}

void HashWrite(Book* key, Book* hash[], int* misc) { // Функция добавления элемента в хеш-таблицу
	int i = abs(key->releaseDate % M);
	int attempt = 0;
	while (hash[i] != nullptr) { // Ищем свободное место в хеш-таблице
		i = i + misc[attempt];
		if (i >= M) 
			i = 0;
		attempt++;
	}
	hash[i] = key;
}
int HashFind(int key, Book* hash[], int* misc) { // Функция поиска элемента в хеш-таблице по году выпуска
	int i = abs(key % M);
	int attempt = 0;
	while (hash[i] != nullptr) { // Действуем так же, как и при добавлении элемента
		if (hash[i]->releaseDate == key)  // Сравниваем год книги с искомым значением
			return i;

		i = i + misc[attempt];
		if (i >= M)
			i = 0;
		attempt++;
	}
	return -1; // Если не нашли такую книгу
}