#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <iostream>
#include "./MSTRING.h"
#include "./ARRAY.hh"
#include "cstring"
//#include "string"

	//Проверка присутствия символа sym в строке razd

int IsRazd(char sym, const char* razd)
{
	for (int i = 0; razd[i]; i++)
		if (razd[i] == sym)
			return 1;
	return 0;
}

//Аналог стандартной функции strtok, выделяет и возвращает фрагменты str,
// ограниченные символами из razd, но при этом не портит строку str.

char* StrTok(const char* str, const char* razd)
{
	static char* p = nullptr, * p1, * p2;
	char* p3;
	int state = 1;
	int len;

	if (str)
	{
		for (len = 0; str[len]; len++);
		p = new char[len + 1];
		for (int k = 0; (p[k] = str[k]); k++);
		p1 = p2 = p;
	}

	while (true)
	{
		if (p == nullptr) return nullptr;
		switch (state)
		{
		case 1:
			if (*p2 == '\0')
			{
				delete[] p; p = nullptr; return nullptr;
			}
			if (IsRazd(*p2, razd))
			{
				p1 = ++p2; break;
			}
			state = 2;
		case 2:
			if (*p2 == '\0' || IsRazd(*p2, razd))
			{
				p3 = p1;
				if (*p2 == '\0') return p3;
				*p2 = '\0'; p1 = ++p2; return p3;
			}
			p2++;
		}
	}
}


class Toys_shop {
	//поля
	MString ToyName, ToyPrice, MinAge, MaxAge; //Название игрушки, цена, минимальный и максимальный возраст
	Array<MString> Shop_List; // список магазинов
public:
	//конструкторы
	Toys_shop(const char* ToyName, const char* ToyPrice, const char* MinAge, const char* MaxAge, const char* Shop_List);
	//конструктор копирования
	// Employee_Vacation(const Employee_Vacation &);
	//корректировка данных
	MString* CorrectData(const char* name);
	//запись в лист отпусков
	void AddToy(const char* newRecord);
	//корректировка листа отпусков
	void CorrectToysList(int numberRecord, const char* newRecord);
	//перегрузка =
	Toys_shop& operator = (const Toys_shop&);
	//перегрузка <<
	friend std::ostream& operator << (std::ostream&, Toys_shop&);

};

Toys_shop::Toys_shop(const char* TN, const char* TP, const char* MiA, const char* MaA, const char* SL) : ToyName(TN), ToyPrice(TP), MinAge(MiA), MaxAge(MaA) {
	char* p;
	p = StrTok(SL, ";");
	if (p) {
		Shop_List.Add(p);
		while ((p = StrTok(nullptr, ";")))
			Shop_List.Add(p);
	}
}

MString* Toys_shop::CorrectData(const char* name) {
	if (!strcmp(name, "TN"))
		return &ToyName;
	if (!strcmp(name, "TP"))
		return &ToyPrice;
	if (!strcmp(name, "MiA"))
		return &MinAge;
	if (!strcmp(name, "MaA"))
		return &MaxAge;
	return nullptr;
}

void Toys_shop::AddToy(const char* newRecord) {
	char* p;
	p = StrTok(newRecord, ";");
	if (p) {
		Shop_List.Add(p);
		while ((p = StrTok(nullptr, ";")))
			Shop_List.Add(p);
	}
}

void Toys_shop::CorrectToysList(int numberRecord, const char* newRecord) {
	//if (newRecord == nullptr) {
	Shop_List[numberRecord] = newRecord;
	//}
	//else {
	//	Shop_List.Insert(newRecord, numberRecord);
	//}
}

Toys_shop& Toys_shop::operator = (const Toys_shop & OneToy) {
	ToyName = OneToy.ToyName;
	ToyPrice = OneToy.ToyPrice;
	MinAge = OneToy.MinAge;
	MaxAge = OneToy.MaxAge;
	Shop_List = OneToy.Shop_List;
	return *this;
}

std::ostream& operator<<(std::ostream & ostream, Toys_shop & OneToy) {
	int size, i = 0;
	ostream << "ToyName: " << OneToy.ToyName << std::endl;
	ostream << "MinAge: " << OneToy.MinAge << std::endl;
	ostream << "MaxAge: " << OneToy.MaxAge << std::endl;
	ostream << "Price: " << OneToy.ToyPrice << std::endl;
	size = OneToy.Shop_List.Size();
	if (size) {
		ostream << "Vacation list: " << std::endl;
		for (; i < size; i++) {
			ostream << i + 1 << ") " << OneToy.Shop_List[i];
			ostream << std::endl;
		}
	}
	return ostream;
}


void main() {
	using namespace std;
	setlocale(LC_ALL, "");

	Toys_shop Woody("Woody", "2500", "2 years", "10 years", "London - Ul.222;Russia - Moscow;Vinece - Muerto");
	cout << Woody << endl;
	Toys_shop Dolly("Dolly", "7000", "3 years", "7 years", "Spain - Ul.222;Russia - Murmansk;Vinece - Muerto");
	cout << Dolly << endl;
	Toys_shop Molly(Dolly);
	//cout << Molly << endl;

	*Molly.CorrectData("TN") = MString("Molly");
	Molly.CorrectToysList(0, "Correcting Toy");
	Molly.AddToy("Add new toy?");
	cout << Molly << endl;
	cout << Molly << endl;

	//return 0;
	system("pause");
}