#define _CRT_SECURE_NO_WARNINGS // ������������� ��� ���������� �������������� ��� ������ �� scanf � printf

#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

struct Tree // ��������� �������� �������
{ 
    int value; // �������� ��������
    Tree* left = NULL; // ��������� �� ����� �������
    Tree* right = NULL; // ��������� �� ������ �������
};

Tree* BuildTree(int*, int, int, Tree*); // ���������� ������ �� ������� ������
Tree* NewNode(int); // �������� ������ ����
Tree* AddNode(Tree*, int); // ���������� ���� � ������
Tree* DeleteNode(Tree*, int); // �������� ���� �� ������
Tree* FindNode(Tree*, int); // ����� ���� � ������
Tree* DeleteTree(Tree*); // �������� ����� ������
Tree* MinValueNode(Tree*); // ����� ������������ �������� � ������
void StraightPrint(Tree*); // ������ ����� ������
void ReversePrint(Tree*); // �������� ����� ������
void IncPrint(Tree*); // ����� � ������� ����������� ���������
void quickSort(int*, int, int);
int CountNodes(Tree*); // ��������� ���������� �����

int main()
{
    setlocale(LC_ALL, "Russian"); // ��������� ���������
    srand(time(0)); // ������������� ��������������� �����

    int n;
    Tree* root = 0; // ������ ������

    printf("������� ���������� ���������: "); // ������ ���������� ���������
    scanf("%d", &n);
    int* a = new int[n];
    for (int i = 0; i < n; i++) // ���������� ������ ����������
    {
        int temp = rand() % 101 - 50; // ��������� ����� � ��������� [-50;50]
        a[i] = temp;
    }
    quickSort(a, 0, n - 1); // ���������� ������� ���������
    printf("�������� ����������� �����: ");
    root = BuildTree(a, 0, n - 1, root); // ���������� ����������������� ������
    printf("\n");

    printf("\n��� ���� ������ (������ �����):\n");
    StraightPrint(root); // ������ ����� ������
    printf("\n");

    printf("\n��� ���� ������ (� ������� �����������):\n");
    IncPrint(root); // ����� � ������� ����������� ���������
    printf("\n");
    
    printf("\n��� ���� ������ (�������� �����):\n");
    ReversePrint(root); // �������� ����� ������
    printf("\n");

    int toDelete, toFind; // �������� ��������� ��� ������ � ��������

    printf("\n������� �������� ��������� ��� ������ � ��������: ");
    scanf("%d%d", &toFind, &toDelete);

    if (FindNode(root, toFind) != 0) // ����� ���� �� ��������
    {
        printf("\n���� %d ����������\n", toFind);
    }
    else
    {
        printf("\n���� %d �� ����������\n", toFind);
    }

    printf("\n�������� �������� %d �� ������\n", toDelete);
    root = DeleteNode(root, toDelete); // �������� �������� �� ��������

    printf("��� ���� ������ ����� �������� %d:\n", toDelete);
    StraightPrint(root); // ������ ����� ������ 
    printf("\n");

    printf("\n���������� ����� � ����� ����� ������: %d\n", CountNodes(root->left)); // ������� ����� � ����� �����

    root = DeleteTree(root);
    printf("\n������ �������");

    return 0;
}
Tree* BuildTree(int* arr, int start, int end, Tree* root) // ���������� ����������� ������
{
    if (start > end) return 0;

    int mid = (start + end) / 2; // ������ �������� � �������� �������
    printf("%d ", arr[mid]);
    root = AddNode(root, arr[mid]); // ��������� �������� ����
    root->left = BuildTree(arr, start, mid - 1, root->left); // ��������� ���� � ����� �����
    root->right = BuildTree(arr, mid + 1, end, root->right); // ��������� ���� � ������ �����
    return root;
}
Tree* NewNode(int value) // �������� ������ ����
{
    Tree* node = new Tree; // �������� ������ ����
    node->value = value; // ������ �������� ����
    node->left = node->right = 0; // �������� ��������� �� �������� ��������
    return node; // ���������� ����
} 
Tree* AddNode(Tree* node, int value) // ���������� ���� � ������
{
    if (node == 0) return NewNode(value); // ���� ���� ���, �� ������� ���
    if (value < node->value) // ���� �������� ������, ��� � ����, �� ���� ���������� �����
        node->left = AddNode(node->left, value);
    else // ����� ������
        node->right = AddNode(node->right, value);
    return node; // ���������� ������ ������
}
Tree* DeleteNode(Tree* root, int value) // �������� ���� �� ������
{
    if (root == 0) return root; // ���� ���� ���, �� ������ �� ������
    if (value < root->value) // ���� ������� �������� ������, �� ���� �����
        root->left = DeleteNode(root->left, value);
    else 
    {
        if (value > root->value) // ����� ���� ������
        {
            root->right = DeleteNode(root->right, value);
        }
        else // ���� ����� ���� �� ��������
        {
            if (root->left == 0) // ���� ��� ��������� �����, �� ������ ��������� ���������� �� ����� ����
            {
                Tree* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == 0) // ���� ��� ��������� ������, �� ����� ��������� ���������� �� ����� ����
            {
                Tree* temp = root->left;
                delete root;
                return temp;
            }
            // ���� ���� ��� ���������, �� ���� ����������� �������� � ������ ���������, ����� �� �������� ��������� ������
            Tree* temp = MinValueNode(root->right); // �������� ��������� �� ������� ����
            root->value = temp->value; // ���������� ��� �� ����� ����������
            root->right = DeleteNode(root->right, temp->value); // ������� ������������ ����
        }
    }
    return root; // ���������� ������ ������
}
Tree* FindNode(Tree* node, int value) // ����� ���� � ������
{ 
    if (node == NULL) return 0; // ���� ���� ���, �� ���������� 0
    if (node->value == value) return node; // ���� �����, �� ���������� ����
    
    if (value < node->value) // ���� ������� �������� ������ �������� ����, �� ���� �����
    {
        FindNode(node->left, value);
    }
    else // ����� ���� ������
    {
        FindNode(node->right, value);
    }
}
Tree* DeleteTree(Tree* root) // �������� ����� ������
{
    if (root == 0) return 0; // ���� ��� ����, �� ������ �� ������
    DeleteTree(root->left); // ���������� ������� ����������, � ����� ��� ����
    DeleteTree(root->right);
    delete root;
    return 0;
}
Tree* MinValueNode(Tree* root) // ����� ������������ �������� � ������
{
    Tree* node = root; // �������� ��� ����������� �� ������
    while (node && node->left) // ���� �� ����� �������, ���� �� ������ �� �����
        node = node->left;
    return node;
}
void StraightPrint(Tree* node) // ������ ����� ������
{
    if (node != 0) // ���� ���� ����������, �� ������� ������� ���, ����� ����� ��������� � ������� ������ ���������
    {
        printf("%d ", node->value);
        StraightPrint(node->left);
        StraightPrint(node->right);
    }
}
void ReversePrint(Tree* node) // �������� ����� ������
{
    if (node != 0) // ���� ���� ����������, �� ������� ������� ����� ���������, ����� ������ ��������� � ������� ���
    {
        ReversePrint(node->left);
        ReversePrint(node->right);
        printf("%d ", node->value);
    }
}
void IncPrint(Tree* node) // ����� � ������� ����������� ���������
{
    if (node != 0) // ���� ���� ����������, �� ������� ������� ����� ���������, ����� ��� � ������� ������ ���������
    {
        IncPrint(node->left);
        printf("%d ", node->value);
        IncPrint(node->right);
    }
}
void quickSort(int* arr, int first, int last) // ������� ����������
{
    if (first < last)
    {
        int left = first, right = last, middle = arr[(left + right) / 2];
        do
        {
            while (arr[left] < middle) left++;
            while (arr[right] > middle) right--;
            if (left <= right)
            {
                swap(arr[left], arr[right]);
                left++;
                right--;
            }
        } while (left <= right);
        quickSort(arr, first, right);
        quickSort(arr, left, last);
    }
}
int CountNodes(Tree* node) // ��������� ���������� �����
{
    if (!node) return 0; // ���� ���� ���, �� ���������� 0
    return CountNodes(node->left) + CountNodes(node->right) + 1; // ���������� ������� ���� � ����������� + ��� ����
}