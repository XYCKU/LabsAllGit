#define _CRT_SECURE_NO_WARNINGS // ������������� ��� ���������� �������������� ��� ������ �� scanf � printf

#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

struct List { // ��������� �������� �������
    List* left = 0; // ��������� �� ����� �������
    List* right = 0; // ��������� �� ������ �������
    int value; // �������� ��������
};

void NewList(List**, List**); // �������� ������ ������
void PushAfterList(List*, int); // ���������� �������� ������ �� ����������
void PushBeforeList(List*, int); // ���������� �������� ����� �� ����������
void PrintList(List*, List*); // ����� ����������� ������ �� �����
void FindItemList(List*, List*, int); // ����� �������� ������
void DivideIntoTwoLists(List*, List*, List**, List**, List**, List**); // ���������� �� ��� ������ 
void UniteLists(List**, List**, List*, List*, List*, List*); // ����������� ���� �������
void SortList(List**, List**); // ���������� ������
int DeleteItem(List*); // �������� �������� �� ������
void DeleteList(List**, List**); // �������� ������
void SwapElementsList(List*, List*); // �������� ������� ������ � ������������ �������� ������

int main()
{
    setlocale(LC_ALL, "Russian"); // ��������� ���������
    srand(time(0)); // ������������� ��������������� �����

    int n;
    int toFind = 14; // �����, ������� ���������� �����
    List* QLeft, *QRight; // ��������� �� ����� � ������ ������� ������
    NewList(&QLeft, &QRight); // �������� ������ ������

    printf("������� ���������� ���������: "); // ������ ���������� ���������
    scanf("%d", &n);

    for (int i = 0; i < n; i++) // ���������� ������ ����������
    { 
        int temp = rand() % 101 - 50; // ��������� ����� � ��������� [-50;50]
        PushBeforeList(QRight, temp); // ���������� � ������
    }
    printf("\n���������� ������: \n"); // ����� ����������� ������ �� ����������
    PrintList(QLeft, QRight);

    printf("\n");
    FindItemList(QLeft, QRight, toFind); // ����� ���������� ������ ����� � ������
    
    SwapElementsList(QLeft, QRight); // ������ ������� ������ � ������������ �������� ������
    printf("\n���������� ������ ����� ����� �������: \n");
    PrintList(QLeft, QRight); // ����� ����������� ������ ����� ��������� ����

    SortList(&QLeft, &QRight); // ���������� ������
    printf("\n���������� ������ ����� ����������: \n");
    PrintList(QLeft, QRight); // ����� ����������� ������ ����� ����������

    printf("\n");
    DeleteList(&QLeft, &QRight); // �������� ������
    return 0;
}
void NewList(List** left, List** right) // �������� ������ ������ 
{
    *left = new List; // �������� ����� ��������� ������
    *right = new List;
    (*left)->left = 0; // ��������� ��������� �� ������ � ����� ������
    (*left)->right = *right;
    (*right)->left = *left;
    (*right)->right = 0;
}
void PushAfterList(List* prev, int value) // ���������� �������� ������ �� ����������
{
    List* item = new List; // �������� ������ ��������
    item->value = value; // ���������� �������� ������ ��������
    item->left = prev; // ���������� �������� �� �������
    item->right = prev->right;
    prev->right = item;
    item->right->left = item;
}
void PushBeforeList(List* next, int value) // ���������� �������� ����� �� ����������
{
    List* item = new List; // �������� ������ �������� 
    item->value = value; // ���������� �������� ������ ��������
    item->right = next; // ���������� �������� �� �������
    item->left = next->left;
    next->left = item;
    item->left->right = item;
}
void PrintList(List* begin, List* end) // ����� ����������� ������ �� �����
{
    List* item = begin->right; // �������� ��� ������� �� ������
    while (item != end) // ���� �� ��������� ����� ������
    {
        printf("%d ", item->value);
        item = item->right; // ��������� �� ��������� ������� (������)
    }
    printf("\n");
    
}
void FindItemList(List* begin, List* end, int value) // ����� �������� ������
{
    List* item = begin->right; // �������� ��� ������� �� ������
    for (int i = 0; item != end; item = item->right, i++) // i - ����� ������� ��������, ���� �� ����; 
                                                          // � ������ ����� ����� ��������� ������� (������)
    {
        if (item->value == value)
        {
            printf("�������� %d ������� �� ������� ����� %d\n", value, i);
            return;
        }
    }
    printf("�������� %d �� ������� � ������\n", value);
}
void DivideIntoTwoLists(List* begin, List* end, List** leftL, List** rightL, List** leftR, List** rightR) // ���������� ������ �� ���
{
    NewList(leftL, rightL); // ������� ��� ����� ������
    NewList(leftR, rightR);
    List* item = begin->right; // �������� ��� ������� �� ��������� ������
    while (item != end) // ���� �� ��������� �����
    {
        PushBeforeList(*rightL, DeleteItem(item));
        item = begin->right;
        if (item != end)
        {
            PushBeforeList(*rightR, DeleteItem(item));
            item = begin->right;
        }
    }
    delete begin;
    delete end;
}
void UniteLists(List** begin, List** end, List* leftL, List* rightL, List* leftR, List* rightR) // ����������� ���� �������
{
    NewList(begin, end); // ����� ������, ���������� �� ���������� ����
    List* itemL = leftL->right; // ��������� ��� ���� �������
    List* itemR = leftR->right;
    while ((itemL != rightL) && (itemR != rightR)) // ���� �� ��������� ����� ����� �������
    {
        if (itemL->value < itemR->value) // �������� �� ������ ������ ����� ��������� �������
        {
            PushBeforeList(*end, DeleteItem(itemL));
            itemL = leftL->right;
        }
        else
        {
            PushBeforeList(*end, DeleteItem(itemR));
            itemR = leftR->right;
        }
    }
    while (itemL != rightL) // ���� ���� ������ ��� ������ �������, �� ��� ���������� �������� ��������� � �����
    {
        PushBeforeList(*end, DeleteItem(itemL));
        itemL = leftL->right;
    }
    delete leftL;
    delete rightL;
    while (itemR != rightR) // ���������� ����������� while
    {
        PushBeforeList(*end, DeleteItem(itemR));
        itemR = leftR->right;
    }
    delete leftR;
    delete rightR;
}
void SortList(List** begin, List** end) // ���������� ������
{
    List *leftL, *rightL, *leftR, *rightR; // ��������� ��� ���������� �� ��� ������
    if ((*begin)->right->right == *end) return; // ���� ������ ������� �� 1 ��������, �� ������ �� ������
    DivideIntoTwoLists(*begin, *end, &leftL, &rightL, &leftR, &rightR); // ���������� �� ��� ������ 
    SortList(&leftL, &rightL); // ���������� ���� �� ���� ����� �������
    SortList(&leftR, &rightR);
    UniteLists(begin, end, leftL, rightL, leftR, rightR); // ���������� 2 ������
}
int DeleteItem(List* item) // ������� ������� ������, ���������� ��� ��������
{
    int val = item->value; // ���������� ��������
    item->left->right = item->right; // ��������� ����� � ������ ��������
    item->right->left = item->left;
    delete item; // ������� ������
    return val; // ���������� ��������
}
void DeleteList(List** begin, List** end) // �������� ������
{
    List* item = (*begin)->right; // �������� ��� ������� �� ������
    while (item != *end) // ���� �� ��������� ����� ������ 
    {
        DeleteItem(item); // �������� �������� �� ������
        item = (*begin)->right; // ��������� � ���������� �������� (������)
    }
    delete* begin; // ������� ��������� �� ������� ������
    delete* end;
    *begin = *end = 0;
    printf("������ ������\n");
}
void SwapElementsList(List* begin, List* end) // ������ ������� ������ � ������������ �������� ������
{
    List* item = begin->right->right; // �������� ��� ������� �� ������
    List* max = begin->right; // ��������� �� ������� � ������������ ���������
    while (item != end) // ���� �� ��������� ����� ������ 
    {
        if (item->value > max->value) // ���� ����� �������� �������, ��� � max, �� ���������� ���
        {
            max = item;
        }
        item = item->right; // ��������� � ���������� �������� (������)
    }
    swap(max->value, begin->right->value); // ������ ������� ��������
}
