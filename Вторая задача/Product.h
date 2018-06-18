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
	_int32 NumOfStock;//номер склада
	_int32 Code;
	string Name;
	Date InputDate;//дата поступления
	Date OutPutDate;//дата окончания срока годности
	_int32 Life;//срок годности в днях
	_int32 Count;
	double Price;
	Product();
	void Print();//печать в консоль
	void Input();//ввод с консоли
};


//ввод числа с консоли
void InputNum(string str, _int32 &res);

void InputNum(string str, double &res);
//ввод строки с консоли
void InputStr(string str, string &res);

