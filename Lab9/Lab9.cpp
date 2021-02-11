#include <cstdio>
#include <iostream>

double rec(int i, int n, double recur) // ����������� �������
{ 
    recur /= i; // ��������
    if (i <= n)
        return recur + rec(i + 1, n, recur);
    return 0;
}

double notRec(int n) // �� ����������� �������
{ 
    double ans = 1;
    double recur = 1; // ��������
    for (int i = 2; i <= n; i++)
    {
        recur /= i; // ���������� ���������
        ans += recur; // ����������� � ������
    }
    return ans;
}

int main()
{
    setlocale(LC_ALL, "Russian"); // ��������� ��������
    int k; // ����������
    printf("������� K: "); // ���� ������
    scanf_s("%d", &k);

    printf("��������� ��� ����������� ��������: %10.5lf\n", rec(1, k, 1)); // ������� ����������
    printf("��������� ��� �� ����������� ��������: %7.5lf\n", notRec(k)); // ������� �� ����������

    return 0;
}
