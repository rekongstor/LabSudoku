#pragma once
using u8 = unsigned char;

struct cell
{
    u8 num; // cell value
    u8 exp[9]; // expected values
    cell(); // default constructor
    cell(const cell&); // copy constructor
    cell& operator=(const cell&); // copy cell
    cell& operator=(const u8&); // set num 
    u8 operator+(); // returns sum of exp 
    u8 operator*(); // returns num
    void operator^=(const u8&); // excludes num from exp
};