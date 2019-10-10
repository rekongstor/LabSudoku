#include "cell.h"
#include <memory>

// default constructor
cell::cell() : num(0)
{
    memset(exp,1,9);
}
// copy constructor
cell::cell(const cell& a) : num(a.num)
{
    memcpy(exp,a.exp,9);
}
// copy cell
cell& cell::operator=(const cell& a)
{
    num = a.num;
    memcpy(exp,a.exp,9);
    return *this;
}
// set num 
cell& cell::operator=(const u8& n)
{
    num = n;
    memset(exp,0,9);   
    return *this;
}
// returns sum of exp 
u8 cell::operator+()
{
    u8 s=0;
    for (auto a:exp)
        s+=a;
    return s;
}
// returns num
u8 cell::operator*()
{
    return num;
}
// excludes num from exp
void cell::operator^=(const u8& n)
{
    exp[n] = 0;
}

void cell::operator-(const u8* _exp)
{
    for (u8 i=0;i<9;++i)
    {
        exp[i] *= (static_cast<u8>(1)-_exp[i]);
    }
}