﻿#include <iostream>
using namespace std;

// Домашняя работа.

int main()
{
    setlocale(LC_ALL, "Russian");

    //======================================================================================================================================
    // 1. Написать программу, проверяющую что сумма двух (введенных с клавиатуры) чисел лежит в пределах от 10 до 20 (включительно), 
    // если да – вывести строку "true", в противном случае – "false";

    int a, b, sum;
    cout << "Введите число a: ";
    cin >> a;
    cout << "Введите число b: ";
    cin >> b;
    sum = a + b;
    if (sum >= 10 && sum <= 20) {
        cout << "true";
    }
    else {
        cout << "false";
    }
    cout << "\n" << endl;

    //======================================================================================================================================
    // 2. Написать программу, выводящую на экран строку “true”, если две целочисленные константы, объявленные в её начале либо обе равны 
    // десяти сами по себе, либо их сумма равна десяти. Иначе "false".

    const int X = 10;
    const int Y = 10;

    if (X == 10 && Y == 10) {
        cout << "true";
    }
    else if (X + Y == 10) {
        cout << "true";
    }
    else {
        cout << "false";
    }
    cout << "\n" << endl;

    //======================================================================================================================================
    // 3. Написать программу которая выводит на экран список всех нечетных чисел от 1 до 50. Например: "Your numbers: 1 3 5 7 9 11 13 ...". 
    // Для решения используйте любой С++ цикл.

    cout << "Спсок нечетных чисел от 0 до 50: ";
    for (int i = 0; i <= 50; i++) {
        if (i % 2 != 0) {
            cout << i << " ";
        }
    }
    cout << "\n" << endl;

    //======================================================================================================================================
    // *4. Написать программу, проверяющую, является ли некоторое число - простым. Простое число — это целое положительное число, 
    // которое делится без остатка только на единицу и себя само.

    cout << "Положительные числа от 0 до 100: ";
    for (int i = 2; i < 100; i++) {
        bool isPrime = true;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            cout << i << " ";
        }
    }
    cout << "\n" << endl;

    //======================================================================================================================================
    // *5.  Пользователь вводит с клавиатуры число (год): от 1 до 3000. Написать программу, которая определяет является ли этот год високосным. 
    // Каждый 4-й год является високосным, кроме каждого 100-го, при этом каждый 400-й – високосный. 
    // Вывести результаты работы программы в консоль.

    int year;
    cout << "Введите год: ";
    cin >> year;
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
        cout << year << " - високосный год.";
    }
    else {
        cout << year << " - невисокосный год.";
    }
    return 0;
}
