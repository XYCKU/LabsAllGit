#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int M = 10; // ������ ������� ���-������� � ���������������� �������

struct Book { // ��������� �����
	char name[40];
	int pages, releaseDate;
};

void HashWrite(Book* item, Book* hash[], int* misc); // ������� ���������� �������� � ���-�������
int HashFind(int key, Book* hash[], int* misc); // ������� ������ �������� � ���-������� �� ���� �������

int main() {
	setlocale(LC_ALL, "ru"); // ��������� ���������

	int n, rands[M];

	printf("������� ���������� ����: "); // ������ ���������� ����
	scanf("%d", &n);

	Book* a = new Book[n];
	Book* H[M];

	printf("��������������� ������:\n");
	for (int i = 0; i < M; i++) { // ������� ���-�������, ������ ��������������� �������� ��� ���������������� �������
		H[i] = nullptr;
		rands[i] = 1 + (rand() % (M - 1));
		printf("%d ", rands[i]); // ������� ��������������� ������
	}

	printf("\n\n");
	for (int i = 0; i < n; i++) { // ������ ���������� � ������ �����
		printf("������� �������� �����: ");
		scanf(" %[^\n]s", a[i].name);
		printf("������� ���������� ������� � ��� �������: ");
		scanf("%d%d", &a[i].pages, &a[i].releaseDate);

		HashWrite(&a[i], H, rands); // ���������� ����� � ���-�������
	}

	for (int i = 0; i < M; i++) { // ����� ����������� ���-�������
		int o;
		if (H[i] != nullptr)
			o = H[i]->releaseDate;
		else
			o = -1;
		printf("H[%d] = %d\n", i, o);
	}

	int key = 0, i;
	while (key != -1) { // ����� ������ �����, ���� ������������ �� ������ -1
		printf("������� ��� ������� ������� �����: ");
		scanf("%d", &key);
		i = HashFind(key, H, rands); // ����� ����� � ���-�������
		if (i != -1) { // ���� �����, �� ������� ���������� � �����
			printf("������ ������� ����� � ���-�������: %d\n", i);
			printf("��������: %s\n���������� �������: %d\n��� �������: %d\n\n", H[i]->name, H[i]->pages, H[i]->releaseDate);
		} 
		else {
			printf("�� ������� ����� �����!\n");
		}
		printf("\n");
	}

 	delete[] a; // ������� ������
	return 0;
}

void HashWrite(Book* key, Book* hash[], int* misc) { // ������� ���������� �������� � ���-�������
	int i = abs(key->releaseDate % M);
	int attempt = 0;
	while (hash[i] != nullptr) { // ���� ��������� ����� � ���-�������
		i = i + misc[attempt];
		if (i >= M) 
			i = 0;
		attempt++;
	}
	hash[i] = key;
}
int HashFind(int key, Book* hash[], int* misc) { // ������� ������ �������� � ���-������� �� ���� �������
	int i = abs(key % M);
	int attempt = 0;
	while (hash[i] != nullptr) { // ��������� ��� ��, ��� � ��� ���������� ��������
		if (hash[i]->releaseDate == key)  // ���������� ��� ����� � ������� ���������
			return i;

		i = i + misc[attempt];
		if (i >= M)
			i = 0;
		attempt++;
	}
	return -1; // ���� �� ����� ����� �����
}