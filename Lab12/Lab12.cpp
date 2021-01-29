#define _CRT_SECURE_NO_WARNINGS // ������������� ��� ���������� �������������� ��� ������ �� scanf � printf

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

struct CallInfo { // ��������� ��� ����� ������ �� ���
    int number, duration; // ������������ ������ � ��������
    double rate; // ����� �� ������
};

FILE* F; // ��������� �� ����
char fileName[20]; // ��� �����

int n; // ���������� ������� � �������
CallInfo a[100]; // ������ ������� ����������

// ��������� �������
int menu(); // ����� ����
void readFileName(); // ������ ����� �����
void createFile(); // �������� ������ �����
void readFile(); // ������ ������ �� �����
void writeFile(); // ������ ������ � ����
void printData(); // ����� ������ � ������� �� �����
void calculateAnswer(); // ���������� ����� ��� ��������
void insertSort(CallInfo*, int); // ���������� ���������
void quickSort(CallInfo*, int, int); // ������� ����������
int stupidSearch(CallInfo*, int, int); // �������� �����
int interSearch(CallInfo*, int, int); // ���������������� �����

int main()
{
    setlocale(LC_ALL, "Russian"); // ��������� ���������

    readFileName(); // ������ ����� �����

    printf("C����� ������:\n1.������ ��� �����\n2.������� ����\n3.��������� ������ �� �����\n4.�������� ������ � ����\n5.������� ������ �� �����\n6.����� ��� ��������\n7.���������� ��������\n8.������� ����������\n9.�������� �����\n10.���������������� �����\n11.��������� ������\n");
    while (true) { // ����������� ���� ��� ������ �������
        switch (menu()) { // 
        case 1: readFileName(); break;
        case 2: createFile(); break;
        case 3: readFile();  break;
        case 4: writeFile(); break;
        case 5: printData(); break;
        case 6: calculateAnswer(); break;
        case 7: insertSort(a, n); printf("������ ������������ � ������� ���������� ���������\n"); break;
        case 8: quickSort(a, 0, n - 1); printf("������ ������������ ������� ������� ����������\n"); break;
        case 9: {
            printf("�������� �����\n");
            int t = stupidSearch(a, n, 21603);
            if (t > -1) {
                printf("������ ������ 21603: %d %.2lf\n", a[t].duration, a[t].rate);
            }
            else printf("������ ������ ���\n");
            break; 
        }
        case 10: {
            printf("���������������� �����\n");
            int t = interSearch(a, n, 21603);
            if (t > -1) {
                printf("������ ������ 21603: %d %.2lf\n", a[t].duration, a[t].rate);
            }
            else printf("������ ������ ���\n");
            break; 
        }
        case 11: printf("���������� ������\n"); return 0; break; // ����� �� ����������
        default: printf("������� ���������� ��������\n"); // ���� ������� ������������ ��������, �� ������������ ������ ������
        }
    }
    return 0;
}

int menu() { // ���� ������� �� ������ ����
    printf("\n�������� ��������: ");
    int choose;
    scanf_s("%d", &choose); // ������ ������ �������
    printf("\n");
    return choose;
}
void readFileName() { // ������ ����� �����
    printf("������� ��� �����: ");
    cin >> fileName;
}
void createFile() { // �������� ������ �����
    if ((F = fopen(fileName, "w")) == NULL) { // � ������ ������ ��������� ��������� ������
        printf("������ ��� �������� �����\n");
        exit(1);
    }
    cout << "���� " << fileName << " ������ �������" << endl;
    fclose(F);
}
void readFile() { // ������ ������ �� �����
    if ((F = fopen(fileName, "r")) == NULL) { // � ������ ������ ��������� ��������� ������
        printf("������ ��� �������� �����\n");
        exit(1);
    }
    rewind(F); // ����������� ��������� � ����� �����
    n = 0;
    while (!feof(F)) { // ������ �� ������� ���������� ����� �����
        fscanf(F, "%d%d%lf\n", &a[n].number, &a[n].duration, &a[n].rate);
        n++;
    }
    printf("����� ��������� �������: %d\n", n);
    fclose(F);
}
void writeFile() { // ������ ������ � ����
    char fName[20];
    FILE* fl;
    printf("������� ��� ����� ������: ");
    cin >> fName; // ������ ����� ����� ��� ������
    if ((fl = fopen(fName, "w")) == NULL) { // � ������ ������ ��������� ��������� ������
        printf("������ ��� �������� ����� ������\n");
        exit(1);
    }
    string s;
    while (getline(cin, s)) { // ������ ������ � �������
        printf("������� ���������� � ������: ");
        fputs(s.c_str(), fl); // ��������� ������ � ����
    }
    fclose(fl);
}
void printData() { // ����� ������ � ������� �� �����
    printf("���������� � �������:\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d %.2lf\n", a[i].number, a[i].duration, a[i].rate);
    }
}
void calculateAnswer() { // ���������� ����� ��� ��������
    int num;
    printf("������� ������� �����: ");
    scanf("%d", &num); // ������ ������ ��������

    double answer = 0; // ���������� ��� �������� ��������� ����������� ����� �� ������

    for (int i = 0; i < n; i++) {
        if (num == a[i].number) { // ��������� ������ �������� � ������ � ������ ���
            answer += (a[i].duration / 60) * a[i].rate + ((a[i].duration % 60 > 0) ? a[i].rate : 0); // ���������� ����� * ����� + (���� ���� ���� �� 1 ������� ��������� ������, �� ���������� �����)
        }
    }

    printf("������ ��� �������� %d ���������� %lf", num, answer);
}
void insertSort(CallInfo* arr, int N) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && arr[j].number < arr[j - 1].number; j--) {
            swap(arr[j - 1], arr[j]);
        }
    }
}
void quickSort(CallInfo* arr, int first, int last) {
    if (first < last) {
        int left = first, right = last, middle = arr[(left + right) / 2].number;
        do {
            while (arr[left].number < middle) left++;
            while (arr[right].number > middle) right--;
            if (left <= right) {
                swap(arr[left], arr[right]);
                left++;
                right--;
            }
        } while (left <= right);
        quickSort(arr, first, right);
        quickSort(arr, left, last);
    }
}

int stupidSearch(CallInfo* arr, int n, int number) {
    for (int i = 0; i < n; i++) {
        if (arr[i].number == number) {
            return i;
        }
    }
    return -1;
}

int interSearch(CallInfo* arr, int n, int number) {
    int i = 0, j = n - 1, m;
    while (i < j) {
        if (a[i].number == a[j].number) {
            if (a[i].number == number) {
                return i;
            }
            else return -1;
        }
        m = i + (j - i) * (number - a[i].number) / (a[j].number - a[i].number);
        if (a[m].number == number) 
            return m;
        else {
            if (number > a[m].number)
                i = m + 1;
            else
                j = m - 1;
        }
    }
    return -1;
}
