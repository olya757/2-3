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
	void Increase(_int32 count);//� ����
	void Input(string str);
	void Print();
};


//��������������� �������, �������� ����� �� ������
bool GetNum(string str, _int32 p1, _int32 p2, _int32 &res);
//�������� �������������� ������ � ����
bool TryStrToDate(string str, Date &d);