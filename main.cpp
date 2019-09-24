#include <iostream>
#include "sudoku.h"

int main()
{
    using namespace std;
    sudoku S;

    //S.load_file("input.txt");
    S.load_file("input2.txt");
    S.print();
    for (u8 i=0;i<9;++i)
    {
        S.calculate_step();
    }
    S.print();


    system("pause");
    return 0;
}