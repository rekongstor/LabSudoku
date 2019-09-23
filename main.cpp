#include <iostream>
#include "sudoku.h"

int main()
{
    using namespace std;
    sudoku S;

    S.load_file("input.txt");
     S.print();
     S.print_exp_sums();
    // cout << S.get_progress() << endl;
    S.calculate_step();


    system("pause");
    return 0;
}