#include <stdio.h>

int add(int a, int b) {
    int carry;
    while (b != 0) {
        carry = a & b;//��������� ���� �������� � ��������� ������
        a = a ^ b;//��������� �������� ��� ����� ��������
        b = carry << 1;//�������� ���� �������� �����, ����� �������� �� � ��������� ����
    }
    return a;
}

int size_of_str(const char* str) {
    int k = 0;
    while (str[k] != '\0') {
        k = add(k, 1);
    }
    return k;
}

void reverse(char* array) {
    int i = 0;
    int b = add(size_of_str(array), -1);
    while (i < b) {
        char t = array[i];
        array[i] = array[b];
        array[b] = t;
        i = add(i, 1);
        b = add(b, -1);
    }
}

void right_shift(char* array) {// ����� ����� ��� - ����
    int size = size_of_str(array);
    for (int i = size; i > 0; i = add(i, -1)) {
        array[i] = array[add(i, -1)];
    }
    array[0] = ' ';
}

void translate_to_system(int dec, char* result, int r) {
    if (dec == 0) {
        result[0] = '0';
        result[1] = '\0';
        return;
    }
    int a = dec;
    int base = 1 << r; // ��������� �� ��� 2^r
    int mask = base - 1; // ����� ��� ���������� r ������� ����� �����
    int sign = 0;
    if (dec < 0) {
        a = add(~dec, 1);
        sign = 1;
    }
    char* alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
    int i = 0;
    while (a > 0) {
        result[i] = alphabet[a & mask]; // ����������� r ������� ����� ����� a
        a = a >> r; // ����� ������ �� r ���
        i = add(i, 1);
    }
    result[i] = '\0';
    reverse(result);
    if (sign) {
        right_shift(result);
        result[0] = '-';
    }
}

int main() {
    char result[34];
    translate_to_system(10, result, 3); 
    printf("%s\n", result);
    return 0;
}