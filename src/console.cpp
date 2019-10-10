#include <iostream>
#include "sudoku.h"
#include "exc.h"

int EntryPoint()
{
    using namespace std;
    sudoku S;

    //S.load_file("input.txt");
    S.load_file("input3.txt");
    cout << "Unsolved sudoku" << endl;
    S.print();
    // for (u8 i=0;i<9;++i)
    // {
    //     S.calculate_step();
    // }
    try {
        S.calculate_all();
        cout << endl << "Solved sudoku" << endl;
        S.print();
    }
    catch (exc_notsolvable)
    {
        cout << "Sudoku can't be solved" << endl;
    }


    system("pause");
    return 0;
}