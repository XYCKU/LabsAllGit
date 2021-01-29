#define _CRT_SECURE_NO_WARNINGS // Предпроцессор для отключения предупреждений при работе со scanf и printf

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

struct CallInfo { // Структура для одной записи на АТС
    int number, duration; // Длительность звонка в секундах
    double rate; // Тариф за минуту
};

FILE* F; // Указатель на файл
char fileName[20]; // Имя файла

int n; // Количество записей в массиве
CallInfo a[100]; // Массив записей разговоров

// Прототипы функций
int menu(); // Вызов меню
void readFileName(); // Чтение имени файла
void createFile(); // Создание нового файла
void readFile(); // Чтение данных из файла
void writeFile(); // Запись данных в файл
void printData(); // Вывод данных о звонках на экран
void calculateAnswer(); // Вычисление суммы для абонента
void insertSort(CallInfo*, int); // Сортировка вставками
void quickSort(CallInfo*, int, int); // Быстрая сортировка
int stupidSearch(CallInfo*, int, int); // Линейный поиск
int interSearch(CallInfo*, int, int); // Интерполяционный поиск

int main()
{
    setlocale(LC_ALL, "Russian"); // Поддержка кириллицы

    readFileName(); // Чтение имени файла

    printf("Cписок команд:\n1.Ввести имя файла\n2.Создать файл\n3.Прочитать данные из файла\n4.Записать данные в файл\n5.Вывести данные на экран\n6.Сумма для абонента\n7.Сортировка вставкой\n8.Быстрая сортировка\n9.Линейный поиск\n10.Интерполяционный поиск\n11.Закончить работу\n");
    while (true) { // Бесконечный цикл для выбора команды
        switch (menu()) { // 
        case 1: readFileName(); break;
        case 2: createFile(); break;
        case 3: readFile();  break;
        case 4: writeFile(); break;
        case 5: printData(); break;
        case 6: calculateAnswer(); break;
        case 7: insertSort(a, n); printf("Массив отсортирован с помощью сортировки вставками\n"); break;
        case 8: quickSort(a, 0, n - 1); printf("Массив отсортирован методом быстрой сортировки\n"); break;
        case 9: {
            printf("Линейный поиск\n");
            int t = stupidSearch(a, n, 21603);
            if (t > -1) {
                printf("Данные номера 21603: %d %.2lf\n", a[t].duration, a[t].rate);
            }
            else printf("Такого номера нет\n");
            break; 
        }
        case 10: {
            printf("Интерполяционный поиск\n");
            int t = interSearch(a, n, 21603);
            if (t > -1) {
                printf("Данные номера 21603: %d %.2lf\n", a[t].duration, a[t].rate);
            }
            else printf("Такого номера нет\n");
            break; 
        }
        case 11: printf("Завершение работы\n"); return 0; break; // Выход из программыы
        default: printf("Введите корректное значение\n"); // Если введено некорректное значение, то пользователь увидит ошибку
        }
    }
    return 0;
}

int menu() { // Тело функции по вызову меню
    printf("\nВыберите действие: ");
    int choose;
    scanf_s("%d", &choose); // Чтение номера команды
    printf("\n");
    return choose;
}
void readFileName() { // Чтение имени файла
    printf("Введите имя файла: ");
    cin >> fileName;
}
void createFile() { // Создание нового файла
    if ((F = fopen(fileName, "w")) == NULL) { // В случае ошибки программа прекратит работу
        printf("Ошибка при создании файла\n");
        exit(1);
    }
    cout << "Файл " << fileName << " создан успешно" << endl;
    fclose(F);
}
void readFile() { // Чтение данных из файла
    if ((F = fopen(fileName, "r")) == NULL) { // В случае ошибки программа прекратит работу
        printf("Ошибка при открытии файла\n");
        exit(1);
    }
    rewind(F); // Перемещение указателя в конец файла
    n = 0;
    while (!feof(F)) { // Чтение до момента достижения конца файла
        fscanf(F, "%d%d%lf\n", &a[n].number, &a[n].duration, &a[n].rate);
        n++;
    }
    printf("Всего прочитано записей: %d\n", n);
    fclose(F);
}
void writeFile() { // Запись данных в файл
    char fName[20];
    FILE* fl;
    printf("Введите имя файла вывода: ");
    cin >> fName; // Чтение имени файла для записи
    if ((fl = fopen(fName, "w")) == NULL) { // В случае ошибки программа прекратит работу
        printf("Ошибка при создании файла вывода\n");
        exit(1);
    }
    string s;
    while (getline(cin, s)) { // Чтение данных о звонках
        printf("Введите информацию о звонке: ");
        fputs(s.c_str(), fl); // Помещение данных в файл
    }
    fclose(fl);
}
void printData() { // Вывод данных о звонках на экран
    printf("Информация о звонках:\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d %.2lf\n", a[i].number, a[i].duration, a[i].rate);
    }
}
void calculateAnswer() { // Вычисление суммы для абонента
    int num;
    printf("Введите искомый номер: ");
    scanf("%d", &num); // Чтение номера абонента

    double answer = 0; // Переменная для подсчета стоимости абонентской платы за звонки

    for (int i = 0; i < n; i++) {
        if (num == a[i].number) { // Сравнение номера абонента и номера в записи АТС
            answer += (a[i].duration / 60) * a[i].rate + ((a[i].duration % 60 > 0) ? a[i].rate : 0); // Количество минут * тариф + (если есть хотя бы 1 секунда следующей минуты, то прибавляем тариф)
        }
    }

    printf("Оплата для абонента %d составляет %lf", num, answer);
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
