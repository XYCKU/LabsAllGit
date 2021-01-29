#define _CRT_SECURE_NO_WARNINGS // ������������� ��� ���������� �������������� ��� ������ �� scanf � printf

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

struct CallInfo { // ��������� ��� ����� ������ �� ���
    char number[15]; // ����� ��������
    int duration; // ������������ ������ � ��������
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

int main()
{
    setlocale(LC_ALL, "Russian"); // ��������� ���������

    readFileName(); // ������ ����� �����

    printf("C����� ������:\n1.������ ��� �����\n2.������� ����\n3.��������� ������ �� �����\n4.�������� ������ � ����\n5.������� ������ �� �����\n6.����� ��� ��������\n7.��������� ������\n");
    while (true) { // ����������� ���� ��� ������ �������
        switch (menu()) { // 
        case 1: readFileName(); break;
        case 2: createFile(); break;
        case 3: readFile();  break;
        case 4: writeFile(); break;
        case 5: printData(); break;
        case 6: calculateAnswer(); break;
        case 7: printf("���������� ������\n"); return 0; break; // ����� �� ����������
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
        fscanf(F, "%s %d%lf\n", &a[n].number, &a[n].duration, &a[n].rate);
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
        printf("������ ��� �������� ����� ������");
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
        printf("%s %d %.2lf\n", a[i].number, a[i].duration, a[i].rate);
    }
}

void calculateAnswer() { // ���������� ����� ��� ��������
    char number[15];
    printf("������� ������� �����: ");
    scanf("%s", number); // ������ ������ ��������

    double answer = 0; // ���������� ��� �������� ��������� ����������� ����� �� ������

    for (int i = 0; i < n; i++) {
        if (strcmp(number, a[i].number) == 0) { // ��������� ������ �������� � ������ � ������ ���
            answer += (a[i].duration / 60) * a[i].rate + ((a[i].duration % 60 > 0) ? a[i].rate : 0); // ���������� ����� * ����� + (���� ���� ���� �� 1 ������� ��������� ������, �� ���������� �����)
        }
    }
    
    printf("������ ��� �������� %s ���������� %lf", number, answer);
}
