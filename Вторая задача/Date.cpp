#pragma once
#include "Date.h"

Date::Date() {
	dd = 1;
	mm = 1;
	yy = 1;
}


//дата в строку
string Date::ToString() {
	string s = to_string(dd) + '.' + to_string(mm) + '.' + to_string(yy);
	return s;
}
//проверить на правильность
bool Date::Check() {
	_int32 maxdd;
	switch (mm)
	{
	case 1:
	case 3:
	case 5: 
	case 7: 
	case 8: 
	case 10: 
	case 12: {maxdd = 31; break; }
	case 2: {
		maxdd = (yy % 4 == 0 && yy % 100 != 0)||(yy % 400 == 0) ? 29 : 28;//проверка
		break;
	}
	case 4: 
	case 6: 
	case 9: 
	case 11: {maxdd = 30; break; }
	default: return false;
	}
	return dd > 0 && dd <= maxdd && yy > 0;
}
//увеличить дату на указанное количество дней
void Date::Increase(_int32 count) {
	while (count > 0) {
		_int32 maxdd;
		switch (mm)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: {maxdd = 31; break; }
		case (2): {
			maxdd = (yy % 4 == 0 && yy % 100 != 0) || (yy % 400 == 0) ? 29 : 28;
			break;
		}
		default: maxdd = 30;
			break;
		}
		if (dd + count > maxdd) {
			_int32 p = dd;
			if (mm == 12) {
				mm = 1;
				yy++;
				dd = 1;
			}
			else
			{
				mm++;
			}
			count -= (maxdd - p) + 1;
		}
		else
		{
			dd += count;
			count = 0;
		}
	}
}

//ввод даты с консоли
void Date::Input(string str) {
	cout << str << endl;
	cout << "в формате dd.mm.yyyy" << endl;
	string res;
	do {
		cin >> res;
	} while (!TryStrToDate(res, *this));
}
//печать даты в консоль
void Date::Print() {
	cout << ToString() << endl;
}

bool GetNum(string str, _int32 p1, _int32 p2, _int32 &res) {
	res = 0;
	_int32 i = p1;
	while (i < p2) {
		if (str[i] > '9' || str[i] < '0') {
			return false;
		}
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return true;
}
//пытается конвертировать строку в дату
bool TryStrToDate(string str, Date &d) {
	unsigned _int32 i = 0;
	while (i < str.size() && str[i] != '.')
	{
		i++;
	}
	if (i >= str.size())
	{
		return false;
	}
	unsigned char p1 = i;
	i++;
	while (i < str.size() && str[i] != '.')
	{
		i++;
	}
	if (i >= str.size())
	{
		return false;
	}
	unsigned _int32 p2 = i;
	return GetNum(str, 0, p1, d.dd) &&
		GetNum(str, p1 + 1, p2, d.mm) &&
		GetNum(str, p2 + 1, str.size(), d.yy) &&
		d.Check();
}