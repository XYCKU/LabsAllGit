#define _CRT_SECURE_NO_WARNINGS // ������������� ��� ���������� �������������� ��� ������ �� scanf � printf

#include <iostream>
#include <cstdio>

using namespace std;

struct Queue { // ��������� �������� �������
    Queue* child = NULL; // ��������� �� ������������ �������
    int value; // �������� ��������
};

void AddItemQueue(Queue**, Queue**, int); // ���������� �������� � �������
void FindUnderAverageQueue(Queue**, double); // ����� � �������� ��������� �������, ������� ������ �������� ��������
void DeleteNextQueue(Queue*); // �������� ���������� �� ���� �������� �������
void PrintQueue(Queue*); // ������� ��� �������� ������� �� �����
void DeleteQueue(Queue**, Queue**); // �������� �������

int main()
{
    setlocale(LC_ALL, "Russian"); // ��������� ���������
    Queue* begin;
    Queue* end; // ��������� �� ������ � ����� �������
    begin = end = new Queue; 

    int n;
    double average = 0;
    printf("������� ���������� ��������� � �������� �������: "); // ������ ���������� ���������
    scanf("%d", &n);

    for (int i = 0; i < n; i++) { // ������ ��������� �������
        int temp;
        scanf("%d", &temp);
        average += temp; // ��������� ��� �������� �������
        AddItemQueue(&begin, &end, temp); // ���������� �������� � �������
    }
    average /= n; // ������� ������� �������� ���� ���������

    printf("���������� ������� �� ��������: \n");
    PrintQueue(begin->child); // ����� ���������� �������� ������� �� �����
    printf("������� �������� ���������: %lf\n", average);

    FindUnderAverageQueue(&begin, average); // �������� ���� ���������, ������� ������ �������� ��������

    printf("���������� ������� ����� ��������: \n");
    PrintQueue(begin->child); // ����� ���������� ������� ����� �������� �� �����
    DeleteQueue(&begin, &end); // �������� �������
    return 0;
}

void AddItemQueue(Queue** begin, Queue** end, int val) { // ���������� �������� � �������
    Queue* item = new Queue; // ������� ����� �������
    item->value = val; // ������������ ��������
    (*end)->child = item; // ����������� � ����� �������
    *end = item;
}
void PrintQueue(Queue* item) { // ������� ��� �������� ������� �� �����
    if (item != 0) {
        printf("%d ", item->value);
        PrintQueue(item->child); // ���������� ������� ��� �������� �������
    }
    else {
        printf("\n"); // ������� �� ����� ������ ����� ������ ���� ���������
    }
}
void DeleteNextQueue(Queue* item) { // �������� ���������� �� ���� ��������
    if (item->child == 0) return; // ���� ��� �����, �� ������ �� ������
    Queue* temp = item->child; // ���������� ����� ���������� ��������
    item->child = item->child->child;
    delete temp; // ������� ������
}
void FindUnderAverageQueue(Queue** item, double aver) { // ����� � �������� ���������, ������� ������ �������� ��������
    if ((*item)->child == 0) return; // ���� ��� ��������� �������, �� ������ �� ������
    if ((*item)->child->value < aver) { // ���� �������� ������� ������ ��������, �� ������� ��� � ������� ����� �������� �������
        DeleteNextQueue(*item);
        FindUnderAverageQueue(item, aver);
    }
    else { // ����� ��������� � ���������� ��������
        FindUnderAverageQueue(&((*item)->child), aver);
    }    
}
void DeleteQueue(Queue** begin, Queue** end) { // �������� �������
    Queue* item;
    while (*begin != 0) {
        item = *begin;
        *begin = (*begin)->child;
        delete item;
    }
    *end = 0;
    printf("������� �������\n");
}
