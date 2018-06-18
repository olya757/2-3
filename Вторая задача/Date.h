#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <fstream>
using namespace std;
class Date {
public:
	_int32 dd;
	_int32 mm;
	_int32 yy;
	Date();
	string ToString();
	bool Check();
	void Increase(_int32 count);//в днях
	void Input(string str);
	void Print();
};


//вспомогательная функция, получает число из строки
bool GetNum(string str, _int32 p1, _int32 p2, _int32 &res);
//пытается конвертировать строку в дату
bool TryStrToDate(string str, Date &d);