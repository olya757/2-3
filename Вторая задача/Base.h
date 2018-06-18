#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <fstream>
#include "Product.h"
using namespace std;
//Base база данных продуктов
template <class T>
class Base {
public:
	vector<T> base;
	string FileName;//имя файла
	void Assign(vector<T> b);
	Base();
	~Base();
	_int32 Count();
	bool Add(T p);
	bool Delete(T p);
	bool Change(T p);
	vector<T> LinSearch(bool(*f)(T&, T&), T need);//линейный поиск
	vector<T> BinSearch(bool(*f)(T&, T&), T need);//бинарный поиск
	vector<T> LinSearch_Life(T need);//линейный поиск просроченных, немного отличается от простого поиска
	vector<T> SortAndSearch_Life(T need);//бинарный поиск просроченных
	vector<T> GetStock(_int32 num);//получить все продукты с определенного склада
	void  LoadFromFile();//загрузить из файла
	void  SaveToFile();//сохранить в файл
	void Print();//печать в консоль
	void ChangeStockOfChoosenElems(Base<Product> res, _int32 newStock);//переместить продукты на другой склад
};
//сравнение дат
bool CompDate(const Date &T1, const Date &T2);
//сравнение складов
bool CompNumOfStock(Product &T1, Product &T2);
//сравнение кода
bool CompCode(Product &T1, Product &T2);
//сравнение даты поступления
bool CompInputDate(Product &T1, Product &T2);
//сравнение даты окончания срока годности
bool CompOutPutDate(Product &T1, Product &T2);
//сравнить количество
bool CompCount(Product &T1, Product &T2);
//сравнить цену
bool CompPrice(Product &T1, Product &T2);

//выбор критерия сортировки
_int32 FiltrType();

//отфильтровать продукты по критериям
void ChooseProductWithCriteries(Base<Product> &res);

//ввод имени файла
void InputFileName(string &FileName);
//показывает сообщение
void ShowMessage(string str);

//показывает итоги по каждому файлу
void ShowResultsForEachStock(Base<Product> b);
//считывает ответ да или нет
bool InputQuery(string str);

//печать меню
_int32 PrintMenu(_int32 p);

//выбор типа поиска
bool ChooseType();
//реализация


void PrintHeader() {
	cout << "Код                 " <<
		"Название            " <<
		"Склад               " <<
		"Дата поступления    " <<
		"Срок годности       " <<
		"Количество          " <<
		"Цена                " << endl;
}

template <class T>
void Base<T>::Print() {
	PrintHeader();
	for (Product p : base) {
		p.Print();
	}
}

template <class T>
Base<T>::Base() {
	FileName = "binfile.bin";
	LoadFromFile();
}

template <class T>
Base<T>::~Base() {
	SaveToFile();
}

char* FromStr(string str) {
	char *mas = new char[str.size()];
	for (int i = 0; i < str.size(); i++) {
		mas[i] = str[i];
	}
	return mas;
}

string FromChar(char *mas, int len) {
	string str = "";
	for (int i = 0; i < len; i++) {
		str += mas[i];
	}
	return str;
}

template <class T>
void Base<T>::LoadFromFile() {
	base.clear();
	ifstream fin(FileName, ios::binary);
	Product p;
	if (fin) {
		size_t len;
		while (
			fin.read((char *)(&p.Code), sizeof(_int32)) &&
			fin.read((char *)(&p.Count), sizeof(_int32)) &&
			fin.read((char *)(&p.InputDate), sizeof(Date)) &&
			fin.read((char *)(&p.Life), sizeof(_int32)) &&
			fin.read((char *)(&p.NumOfStock), sizeof(_int32)) &&
			fin.read((char *)(&p.OutPutDate), sizeof(Date)) &&
			fin.read((char *)(&len), sizeof(len))) {
			char * buf = new char[len];
			if (fin.read((char *)(buf), len) &&
				fin.read((char *)(&p.Price), sizeof(double)))
			{
				p.Name = buf;
				base.push_back(p);
			}
			delete[] buf;
		}
	}
	fin.close();
}

template <class T>
void Base<T>::SaveToFile() {
	ofstream fout(FileName, ios::binary);
	for (Product p : base) {
		size_t len = p.Name.length() + 1;
		fout.write((char *)(&p.Code), sizeof(_int32));
		fout.write((char *)(&p.Count), sizeof(_int32));
		fout.write((char *)(&p.InputDate), sizeof(Date));
		fout.write((char *)(&p.Life), sizeof(_int32));
		fout.write((char *)(&p.NumOfStock), sizeof(_int32));
		fout.write((char *)(&p.OutPutDate), sizeof(Date));
		fout.write((char *)(&len), sizeof(len));
		const char *buf = p.Name.c_str();
		fout.write((char *)(buf), len);
		fout.write((char *)(&p.Price), sizeof(double));
	}
	fout.close();
}

template <class T>
void  Base<T>::Assign(vector<T> b) {
	base = b;
}

template <class T>
vector<T> Base<T>::LinSearch(bool(*f)(T&, T&), T need) {
	vector<T> Result;
	for (auto it = base.begin(); it != base.end(); it++) {
		if (!f(*it, need) && !f(need, *it)) {
			Result.push_back(*it);
		}
	}
	return Result;
}

template <class T>
vector<T> Base<T>::BinSearch(bool(*f)(T&, T&), T need) {
	vector<T> Result;
	sort(base.begin(), base.end(), f);
	_int32 begin = 0, end = base.size() - 1;
	while (begin != end) {
		_int32 m = (begin + end) / 2;
		if (f(base[m], need)) { 
			begin = m + 1; 
		}
		else
		{
			end = m;
		}
	}
	_int32 i = begin - 1;
	while (i > 0 && !f(base[i], need) && !f(need, base[i])) {
		Result.push_back(base[i]);
		i--;
	}
	while (begin < base.size() && !f(base[begin], need) && !f(need, base[begin])) {
		Result.push_back(base[begin]);
		begin++;
	}
	return Result;
}

template <class T>
vector<T> Base<T>::LinSearch_Life(T need)
{
	vector<T> Result;
	for (auto it = base.begin(); it != base.end(); it++) {
		if (!CompOutPutDate(need, *it)) {
			Result.push_back(*it);
		}
	}
	return Result;
}

template <class T>
vector<T> Base<T>::SortAndSearch_Life(T need) {
	vector<T> Result;
	sort(base.begin(), base.end(), CompOutPutDate);
	for (auto it = base.begin(); it != base.end() && !CompOutPutDate(need, *it); it++) {
		Result.push_back(*it);
	}
	return Result;
}

template <class T>
vector<T> Base<T>::GetStock(_int32 num) {
	vector<T> result;
	for (Product p : base) {
		if (p.NumOfStock == num) {
			result.push_back(p);
		}
	}
	return result;
}

template <class T>
bool Base<T>::Add(T p) {
	if (LinSearch(CompCode, p).size() > 0) {
		if (InputQuery("Такой элемент есть. Заменить?")) {
			Change(p);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		base.push_back(p);
		return true;
	}
}

template <class T>
bool Base<T>::Delete(T p) {
	for (auto tmp = base.begin(); tmp != base.end(); tmp++)
	{
		if (!CompCode(*tmp, p) && !CompCode(p, *tmp))
		{
			base.erase(tmp);
			return true;
		}
	}
	return false;
}

template <class T>
bool Base<T>::Change(T p) {
	for (auto tmp = base.begin(); tmp != base.end(); tmp++) {
		if (!CompCode(*tmp, p) && !CompCode(p, *tmp)) {
			*tmp = p;
			return true;
		}
	}
	return false;
}

template <class T>
_int32 Base<T>::Count() {
	return base.size();
}
template <class T>
void Base<T>::ChangeStockOfChoosenElems(Base<Product> res, _int32 newStock) {
	for (Product p : res.base) {
		for (Product &p1 : base) {
			if (p.Code == p1.Code && p.NumOfStock == p1.NumOfStock) {
				p1.NumOfStock = newStock;
				break;
			}
		}
	}
}

//сравнение дат
bool CompDate(const Date &T1, const Date &T2) {
	if (T1.yy != T2.yy) { 
		return T1.yy < T2.yy; 
	}
	if (T1.mm != T2.mm) {
		return T1.mm < T2.mm; 
	}
	return T1.dd < T2.dd;
}
//сравнение складов
bool CompNumOfStock(Product &T1, Product &T2) {
	return (T1.NumOfStock < T2.NumOfStock);
}
//сравнение кода
bool CompCode(Product &T1, Product &T2) {
	return (T1.Code < T2.Code);
}
//сравнение даты поступления
bool CompInputDate(Product &T1, Product &T2) {
	return CompDate(T1.InputDate, T2.InputDate);
}
//сравнение даты окончания срока годности
bool CompOutPutDate(Product &T1, Product &T2) {
	return CompDate(T1.OutPutDate, T2.OutPutDate);
}
//сравнить количество
bool CompCount(Product &T1, Product &T2) {
	return (T1.Count < T2.Count);
}
//сравнить цену
bool CompPrice(Product &T1, Product &T2) {
	return (T1.Price < T2.Price);
}

//выбор критерия сортировки
_int32 FiltrType() {
	cout << "По какому критерию сортировать?" << endl;
	_int32 res = 0;
	do {
		cout << "1 - По дате поступления на склад" << endl;
		cout << "2 - По сроку годности" << endl;
		cout << "3 - По количеству товара" << endl;
		cout << "4 - По цене" << endl;
		cin >> res;
	} while (res <= 0 || res > 4);
	return res;
}

//отфильтровать продукты по критериям
void ChooseProductWithCriteries(Base<Product> &res) {
	cout << "1 - Номер склада" << endl;
	cout << "2 - Дата появления" << endl;
	cout << "3 - Срок годности" << endl;
	cout << "4 - Количество товара" << endl;
	cout << "5 - Стоимость товара" << endl;
	_int32 ans = 0;
	while (!(cin >> ans) && (ans <= 0 || ans > 5));
	switch (ans) {
	case 1: {
		Product p;
		InputNum("Введите номер склада", p.NumOfStock);
		res.base = res.BinSearch(CompNumOfStock, p);
		break; 
	}
	case 2: {
		Product p;
		p.InputDate.Input("Введите дату появления");
		res.base = res.BinSearch(CompInputDate, p);
		break;
	}
	case 3: {
		Product p;
		p.OutPutDate.Input("Введите дату окончания срока годности");
		res.base = res.BinSearch(CompOutPutDate, p);
		break;
	}
	case 4: {
		Product p;
		InputNum("Введите количество товара", p.Count);
		res.base = res.BinSearch(CompCount, p);
		break; 
	}
	case 5: {
		Product p;
		InputNum("Введите стоимость", p.Price);
		res.base = res.BinSearch(CompPrice, p);
		break; 
	}
	}
}

//ввод имени файла
void InputFileName(string &FileName) {
	cout << "Введите имя файла" << endl;
	do {
		cin >> FileName;
	} while (FileName == "");
}
//показывает сообщение
void ShowMessage(string str) {
	cout << str << endl << endl;
}

//показывает итоги по каждому файлу
void ShowResultsForEachStock(Base<Product> b) {
	if (b.Count() == 0) return;
	sort(b.base.begin(), b.base.end(), CompNumOfStock);
	_int32 cntTypes = 0;
	_int32 cntAll = 0;
	double Summ = 0;
	_int32 NumOfStock = b.base[0].NumOfStock;
	cout << "Склад №" << NumOfStock << endl;
	for (Product p : b.base) {
		if (p.NumOfStock != NumOfStock) {
			cout << "Количество наименований:" << cntTypes << endl;
			cout << "Количество товаров:" << cntAll << endl;
			cout << "Суммарная стоимость:" << Summ << endl;
			cntTypes = 0;
			cntAll = 0;
			Summ = 0;
			NumOfStock = p.NumOfStock;
			cout << "Склад №" << NumOfStock << endl;
		}
		cntTypes++;
		cntAll += p.Count;
		Summ += p.Price;
	}
	cout << "Количество наименований:" << cntTypes << endl;
	cout << "Количество товаров:" << cntAll << endl;
	cout << "Суммарная стоимость:" << Summ << endl;
}
//считывает ответ да или нет
bool InputQuery(string str) {
	cout << str << endl;
	cout << "0 - нет" << endl;
	cout << "1 - да" << endl;
	_int32 ans;
	while (!(cin >> ans && (ans == 0 || ans == 1)));
	return ans == 1;
}


//печать меню
_int32 PrintMenu(_int32 p) {
	cout << "1 - Добавить продукт" << endl;
	if (p > 2) {
		cout << "2 - Удалить продукт" << endl;
		cout << "3 - Изменить продукт" << endl;
		cout << "4 - Найти продукт по коду" << endl;
		cout << "5 - Показать продукты по номеру склада" << endl;
		cout << "6 - Найти просроченные продукты" << endl;
		cout << "7 - Найти товары по дате поступления" << endl;
		cout << "8 - Напечатать в консоли" << endl;
		cout << "9 - Найти товар по критериям" << endl;
		cout << "10 - Показать сводный отчет по складам" << endl;
	}
	cout << "0 - Выход" << endl;
	_int32 res;
	while (!(cin >> res && res <= p && res >= 0));
	return res;
}


//выбор типа поиска
bool ChooseType() {
	cout << "Выберите тип поиска:" << endl;
	cout << "0 - Бинарный" << endl;
	cout << "1 - Линейный" << endl;
	_int32 ans;
	while (!(cin >> ans && (ans == 1 || ans == 0)));
	return ans == 1;
}