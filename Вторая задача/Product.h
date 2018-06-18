#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <fstream>
#include "Date.h"
using namespace std;
class Product {
public:
	_int32 NumOfStock;//����� ������
	_int32 Code;
	string Name;
	Date InputDate;//���� �����������
	Date OutPutDate;//���� ��������� ����� ��������
	_int32 Life;//���� �������� � ����
	_int32 Count;
	double Price;
	Product();
	void Print();//������ � �������
	void Input();//���� � �������
};


//���� ����� � �������
void InputNum(string str, _int32 &res);

void InputNum(string str, double &res);
//���� ������ � �������
void InputStr(string str, string &res);

