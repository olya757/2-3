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

//������ � �������
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
//���������� � �������
void Product::Input() {
	InputNum("������� ���������� ��� ������", Code);
	InputStr("������� �������� ������", Name);
	InputNum("������� ����� ������", NumOfStock);
	InputDate.Input("������� ���� �����������");
	InputNum("������� ���� �������� � ����", Life);
	OutPutDate = InputDate;
	OutPutDate.Increase(Life);
	InputNum("������� ���������� ������", Count);
	InputNum("������� ���� ������ � ����������", Price);
}

//���� ����� � �������
void InputNum(string str, _int32 &res) {
	cout << str << endl;
	while (!(cin >> res && res>0));
}

void InputNum(string str, double &res) {
	cout << str << endl;
	while (!(cin >> res && res>0));
}

//���� ������ � �������
void InputStr(string str, string &res) {
	cout << str << endl;
	do {
		cin >> res;
	} while (res == "");
}