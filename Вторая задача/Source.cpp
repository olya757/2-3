/*№2 
Запись о товаре на складе представляет собой структуру с полями: номер счета,*/
#pragma once
#include "Base.h"
#include "Product.h"
#include "Date.h"
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	string FileName;
	Base<Product> base;
	_int32 r;
	do {
		r = PrintMenu(base.Count()==0?2:10);
		switch (r) {
		case 1: {
			Product p;
			p.Input();
			if (base.Add(p))
			{
				ShowMessage("Продукт добавлен");
			}
			break;
		}
		case 2: {
			Product p;
			InputNum("Введите код товара", p.Code);
			if (base.Delete(p))
			{
				ShowMessage("Продукт удален");
			}
			else
			{
				ShowMessage("Продукт не найден");
			}
			break;
		}
		case 3: {
			Product p;
			p.Input();
			if (base.Change(p))
			{
				ShowMessage("Продукт изменен");
			}
			else
			{
				ShowMessage("Продукт не найден");
			}
			break;
		}
		case 4: {
			Product p;
			InputNum("Введите код товара", p.Code);
			Base<Product> result;
			if (ChooseType())
			{
				result.Assign(base.LinSearch(CompCode,p));
			}
			else
			{
				result.Assign(base.BinSearch(CompCode, p));
			}
			result.Print();
			break;
		}
		case 5: {
			Product p;
			InputNum("Введите номер склада", p.NumOfStock);
			Base<Product> result;
			if (ChooseType())
			{
				result.Assign(base.LinSearch(CompNumOfStock,p));
			}
			else
			{
				result.Assign(base.BinSearch(CompNumOfStock, p));
			}
			switch (FiltrType()) {
				case 1: {
					sort(result.base.begin(), result.base.end(), CompInputDate);
					break;
				}
				case 2: {
					sort(result.base.begin(), result.base.end(), CompOutPutDate);
					break;
				}
				case 3: {
					sort(result.base.begin(), result.base.end(), CompCount);
					break;
				}
				case 4: {
					sort(result.base.begin(), result.base.end(), CompPrice);
					break;
				}
			}
			result.Print();
			break;
		}
		case 6: {
			Product p;
			p.OutPutDate.Input("Введите текущую дату");
			Base<Product> result;
			if (InputQuery("Выполнить поиск в отсортированной базе?")) 
			{
				result.Assign(base.SortAndSearch_Life(p));
			}
			else
			{
				result.Assign(base.LinSearch_Life(p));
			}
			result.Print();
			if (InputQuery("Продолжить операции с новой базой?")) base = result;
			break;
		}
		case 7: {
			Product p;
			p.InputDate.Input("Введите необходимую дату");
			Base<Product> result;
			if (ChooseType())
			{
				result.Assign(base.LinSearch(CompInputDate, p));
			}
			else
			{
				result.Assign(base.BinSearch(CompInputDate, p));
			}
			result.Print();
			if (InputQuery("Продолжить операции с новой базой?")) base = result;
			break;
		}
		case 8: {
			base.Print();
			break;
		}
		case 9: {
			_int32 ans = 1;
			Base<Product> res=base;
			cout << "Выберите критерии для поиска" << endl;
			while (ans == 1) {
				ChooseProductWithCriteries(res);
				res.Print();
				ans = (_int32)InputQuery("Добавить еще критерии?");
			}
			if (InputQuery("Переместить выбранные продукты в новый склад?")) {
				_int32 stock;
				InputNum("Введите номер склада", stock);
				base.ChangeStockOfChoosenElems(res, stock);
			}
			break;
		}
		case 10: {
			ShowResultsForEachStock(base);
			break;
		}
		}
	} while (r != 0);
	return 0;
}


