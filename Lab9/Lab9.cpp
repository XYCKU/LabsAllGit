#include <cstdio>

double rec(int i) {
    if (i > 0) 
        return 1. / i + rec(i - 1);
    return 0;
}

int main()
{
    int k;
    printf("Vvedite K: ");
    scanf_s("%d", &k);

    printf("%.4lf\n", rec(k));

    return 0;
}
