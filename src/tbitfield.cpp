#include "tbitfield.h"

TBitField::TBitField(int len){
    if (len < 0) throw "Negative length";
    memLen = (len + sizeof(TELEM)*8 - 1)/(sizeof(TELEM)*8);
    bitLen = len;
    pMem = new TELEM[memLen];
    for (int i = 0; i < memLen; i++){
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
 
    pMem = new TELEM[bf.memLen];
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    for (int i = 0; i < bf.memLen; ++i) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField(){
      delete[] pMem;
      pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
      if (n < 0 || n >= bitLen) 
          throw "Index out of range";
      return static_cast<int>(n / (sizeof(TELEM) * 8));

}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
      if (n < 0 || n >= bitLen) 
          throw "Index out of range";
      return static_cast<TELEM>(1 << (n % (sizeof(TELEM) * 8)));

}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return bitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= bitLen) throw "Index out of range";
    pMem[GetMemIndex(n)] |=  GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= bitLen) {
        throw "Index out of range";
    }
    pMem[GetMemIndex(n)] &=  ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= bitLen) {
        throw "Index out of range";
    }
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0 ? 1 : 0;
}

// битовые операции
TBitField& TBitField::operator=(const TBitField& other) // присваивание
{
    if (this != &other)
    {
        delete[] pMem;
        bitLen = other.bitLen;
        memLen = other.memLen;
        pMem = new TELEM[other.memLen];
        for (int i = 0; i < other.memLen; ++i) {
            pMem[i] = other.pMem[i];
        }
    }
    return *this;
}


int TBitField::operator==(const TBitField& other) const // сравнение
{
    for (int i = 0; i < other.memLen; ++i) {
        if (pMem[i] != other.pMem[i]) {
            return 0;
        }
    } return 1;
}


int TBitField::operator!=(const TBitField& other) const // сравнение
{
    if (bitLen != other.bitLen) {
        return 1;
    }
    for (int i = 0; i < other.memLen; ++i) {
        if (pMem[i] != other.pMem[i]) {
            return 1;
        }
    } return 0;
}
TBitField TBitField::operator|(const TBitField& other) // операция "или"
{
    int len = bitLen;
    if (other.bitLen > len)
    {
        len = other.bitLen;
    }
    TBitField res(len);
    for (int i = 0; i <memLen; i++)
        res.pMem[i] = pMem[i];
    for (int i = 0; i < other.memLen; i++)
        res.pMem[i] |= other.pMem[i];
    return res;
}

TBitField TBitField::operator&(const TBitField& other) // операция "и"
{
    int len = bitLen;
    if (other.bitLen > len)
    {
        len = other.bitLen;
    }
    TBitField res(len);
    for (int i = 0; i < memLen; i++)
        res.pMem[i] = pMem[i];
    for (int i = 0; i < other.memLen; i++)
        res.pMem[i] &= other.pMem[i];
    return res;
}



TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(bitLen); 
    for (int i = 0; i < memLen; ++i) {
        res.pMem[i] = ~pMem[i]; 
    }
    int bitsInEnd = bitLen % (sizeof(TELEM) * 8);
    if (bitsInEnd != 0) {
        res.pMem[memLen - 1] &= (1 << bitsInEnd) - 1;
    }
    return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  TELEM bit;
  for (int i = 0; i < bf.bitLen; i++)
  {
    istr >> bit;
    bit == 0 ? bf.ClrBit(i):bf.SetBit(i);
  }
  return istr;

}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.bitLen; i++){
      ostr << bf.GetBit(i);
      if (i % 8 == 0 && i != 0) {
          ostr << ' ';
      }
  }
  ostr << endl;
  return ostr;
}
