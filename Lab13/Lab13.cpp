#define _CRT_SECURE_NO_WARNINGS // ������������� ��� ���������� �������������� ��� ������ �� scanf � printf

#include <iostream>
#include <cstdio>

using namespace std;

struct Stack { // ��������� �������� �����
    Stack* parent = NULL; // ��������� �� ������������ �������
    int value; // �������� ��������
};

Stack* AddStack(Stack*, int); // ���������� �������� � ����
void FindThirdStack(Stack*, int); // ����� ������� �������� �������� � ��������� � ������ ����
void PrintStack(Stack*); // ������� ��� �������� ����� �� �����
void DeleteStack(Stack*); // �������� �����

Stack* answer = new Stack; // ���� � ������ ������� ��������� ��������� �����

int main()
{
    setlocale(LC_ALL, "Russian"); // ��������� ���������
    Stack* base = new Stack; // �������� ����
    
    int n;
    printf("������� ���������� ��������� � �������� ������� �����: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) { // ������ ��������� ��������� �����
        int temp;
        scanf("%d", &temp);
        base = AddStack(base, temp);
    }

    printf("���������� ������� �����: \n");
    PrintStack(base); // ����� ���������� ��������� ����� �� �����

    FindThirdStack(base, n); // ����� ������� �������� ��������

    printf("���������� ������� �����: \n"); 
    PrintStack(answer); // ����� ���������� ������� ����� �� �����
    DeleteStack(base); // �������� �����
    return 0;
}

Stack* AddStack(Stack* item, int val) { // ���������� �������� � ����
    Stack* child = new Stack; // �������� ��������� �������� �����
    child->parent = item; // ������ ������������ ������� �����
    child->value = val; // ������ �������� �������� �����
    return child; // ���������� ��������� �� ����� ��������� ������� �����
}
void FindThirdStack(Stack* item, int i) { // ����� ������� �������� �������� � ��������� � ������ ����
    if (item->parent != 0) {
        FindThirdStack(item->parent, i - 1); // ���������� ���� �� �����, ���� �� ������ �� ��� ������
        if (i % 3 == 0) { // ���� ����� �������� ������� �� 3, �� ��������� ��� �� ������ ����
            answer = AddStack(answer, item->value);
        }
    }

}
void PrintStack(Stack* item) { // ������� ��� �������� ����� �� �����
    if (item->parent != NULL) { 
        printf("%d ", item->value);
        PrintStack(item->parent); // ���������� ������� ��� �������� �����
    }
    else {
        printf("\n"); // ������� �� ����� ������� ����� ������ ���� ���������
    }
}
void DeleteStack(Stack* base) { // �������� �����
    Stack* item;
    while (base != 0) {
        item = base;
        base = base->parent;
        delete item;
    }
}