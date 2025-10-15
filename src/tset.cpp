// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{   
    MaxPower = s.MaxPower;
    BitField = s.BitField;
}   

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
    MaxPower = bf.GetLength();
    BitField = bf;
}

TSet::operator TBitField()
{
    TBitField res(MaxPower);
    return res;
}

void TSet::EvenElem() const
{
	TSet add(MaxPower);
	for (int i = 0; i < MaxPower; i++)
	{
		if (i % 2 == 0) add.InsElem(i);
	}
    add = add * *this;
	cout << add;
}

void TSet::NotEvenElem() const
{
	TSet add(MaxPower);
	for (int i = 0; i < MaxPower; i++)
	{
		if (i % 2 == 1) add.InsElem(i);
	}
    add = add * *this;
	cout << add;
}

void TSet::MultipleNumber(int k) const
{
	TSet add(MaxPower);
	for (int i = 0; i < MaxPower; i++)
	{
		if (i % k == 0) add.InsElem(i);
	}
    add = add * *this;
	cout << add;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem); //не факт 
      
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField == s.BitField ? 1 : 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower) {
        return 1;
    }
    if (BitField != s.BitField) {
        return 1;
    }
    return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    int  len = MaxPower;
    if (s.MaxPower > len) {
        len = s.MaxPower;
    }
    TSet res(len);
    res.BitField = BitField | s.BitField;
    return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet res(MaxPower);
    res.BitField.SetBit(Elem);
    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet res(MaxPower);
    res.BitField.ClrBit(Elem);
    return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    int  len = MaxPower;
    if (s.MaxPower > len) {
        len = s.MaxPower;
    }
    TSet res(len);
    res.BitField = BitField & s.BitField;
    return res;
}

TSet TSet::operator~(void) // дополнение
{
    TSet res(MaxPower);
    res.BitField = ~BitField;
    return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	char sim;
	int k;
	istr >> sim;
	while(sim != '}')
    {
        istr >> k >> sim;
		s.BitField.GetBit(k);
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << "{";
	bool flag = false;
    for (int i = 0; i < s.MaxPower; i++)
    {
		if (s.BitField.GetBit(i))
		{
			if (!flag)
			{
				ostr << i;
				flag = true;
			}
			else
			{
				ostr << ", " << i;
			}
		}
    }
	ostr << "}";
    return ostr;
}
