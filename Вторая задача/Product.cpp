#pragma once
#include "Product.h"
#include <stdio.h>
#include <stdlib.h>
Product::Product() {
	NumOfStock = 0;
	Code = 0;
	Name = "";
	Life = 9;
	Count = 0;
	Price = 0;
}


void PrintNum(int num, int N) {
	string str = to_string(num);
	for (int i = str.size(); i < N; i++) {
		str += ' ';
	}
	str.substr(N);
	cout << str;
}

void PrintStr(string str, int N) {
	for (int i = str.size(); i < N; i++) {
		str += ' ';
	}
	str.substr(N);
	cout << str;
}

void PrintDouble(double d, int N) {
	string str = to_string(d);
	for (int i = str.size(); i < N; i++) {
		str += ' ';
	}
	str.substr(N);
	cout << str;
}

//печать в консоль
void Product::Print() {
	int N = 20;
	PrintNum(Code, N);
	PrintStr(Name, N);
	PrintNum(NumOfStock, N);
	PrintStr(InputDate.ToString(), N);
	PrintNum(Life, N);
	PrintNum(Count, N);
	PrintDouble(Price, N);
	cout << endl;
}
//считывание с консоли
void Product::Input() {
	InputNum("¬ведите уникальный код товара", Code);
	InputStr("¬ведите название товара", Name);
	InputNum("¬ведите номер склада", NumOfStock);
	InputDate.Input("¬ведите дату поступлени€");
	InputNum("¬ведите срок годности в дн€х", Life);
	OutPutDate = InputDate;
	OutPutDate.Increase(Life);
	InputNum("¬ведите количество товара", Count);
	InputNum("¬ведите цену товара в симолеонах", Price);
}

//ввод числа с консоли
void InputNum(string str, _int32 &res) {
	cout << str << endl;
	while (!(cin >> res && res>0));
}

void InputNum(string str, double &res) {
	cout << str << endl;
	while (!(cin >> res && res>0));
}

//ввод строки с консоли
void InputStr(string str, string &res) {
	cout << str << endl;
	do {
		cin >> res;
	} while (res == "");
}