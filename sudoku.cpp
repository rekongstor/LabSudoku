#include "sudoku.h"
#include "workgroup.h"
#include <iostream>
#include <fstream>

using namespace std;

sudoku::sudoku() : progress(0.f)
{
    clear();
}

void sudoku::clear()
{
    progress = 0.f;
    u8 i,j,k;
    cell clean;
    for (i=0;i<9;++i)
        for (j=0;j<9;++j) 
            grid[i][j] = 0; // 0 means no number
    for (i=0;i<9;++i)
        for (j=0;j<9;++j) 
            for (k=0;k<9;++k) 
                grid[i][j] = clean;
}

void sudoku::insert_num(u8 r,u8 c,u8 n)
{
    add_num(r,c,n);
    recalculate_progress();
}

void sudoku::load_file(const char* file_name)
{
    ifstream file;
    file.open(file_name);
    int row,col,num;
    while (!file.eof())
    {
        file >> row;
        file >> col;
        file >> num;
        add_num(row,col,num);
    }
    file.close();
}

void sudoku::print()
{
    u8 i,j;
    for (i=0;i<9;++i)
    {
        for (j=0;j<9;++j)
            cout << static_cast<char>((*grid[i][j] == (u8)0) ? ('.') : ('0' + *grid[i][j])) << " ";
        cout << endl;
    }
    cout << endl;
}

void sudoku::print_exp_sums()
{
    u8 i,j,k,s;
    for (i=0;i<9;++i)
    { 
        for (j=0;j<9;++j)
        {
            cout << static_cast<int>(+grid[i][j]) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

float sudoku::get_progress()
{
    return progress;
}

void sudoku::calculate_all()
{
 0;
}

void sudoku::calculate_step()
{
    cell* work[9];

    // заполним таблицу указателями на клетки одной строки
    int i,j;

    for (i=0;i<9;++i)
    {
        for (j=0;j<9;++j)
            work[j] = &grid[i][j];
        calculate_work(work);
    }

    // // заполним таблицу указателями на клетки одного столбца
    for (j=0;j<9;++j)
    {
        for (i=0;i<9;++i)
            work[i] = &grid[i][j];
        calculate_work(work);
    }

    // // заполним таблицу указателями на клетки одного квадрата
    for (i=0;i<9;i++)
    {
        for (j=0;j<9;j++)
            work[j] = &grid[i/3*3 + j/3][i%3*3 + j%3];
        calculate_work(work);
    }
    
}

/* 
Тут самое сложное - нужно сформировать группы из нескольких чисел. Сначала из двух, потом
из трёх, заканчивая восьмью. В таких группах будут некоторые возможные числа exp, которые
сформируют коллекцию из возможных чисел. Если размер exp коллекции не превысит размер группы,
то в остальных числах из группы нужно будет удалить exp числа коллекции. 
*/
void sudoku::calculate_work(cell** work)
{
    u8 group_size = 2; // начинаем с workgroup = 2
    do 
    {
        // сначала формируем необходимого размера workgroup. На каждой итерации их 
        // будет по количеству сочетаний из 9 по group_size (всего до 501 за весь while)
        workgroup w(work, group_size); // создаём workgroup с нужным количеством элементов
        do
        {
            if (w.is_empty())
                w.calculate_wg();
        } while (w.iterate_mask());
        
    } 
    while (++group_size<8); // заканчиваем на workgroup равном 8
}

void sudoku::add_num(u8 r,u8 c,u8 n)
{
    grid[r][c] = n;
    recalculate_exp(r,c,n);
}

void sudoku::recalculate_exp(u8 r, u8 c, u8 n)
{
    // recalculatin row numbers
    u8 rc;
    for (rc=0;rc<9;++rc)
        grid[r][rc] ^= n-1; // n-1 because [1;9] interval converts to [0;8] interval
    
    // recalculating column numbers
    for (rc=0;rc<9;++rc)
        grid[rc][c] ^= n-1;

    // recalculating square
    u8 rr;
    for (rc=r/3*3;rc<(r/3+1)*3;++rc)
        for (rr=c/3*3;rr<(c/3+1)*3;++rr)
            grid[rc][rr] ^= n-1;

    // cell recalculate by itself on =
}

void sudoku::recalculate_progress()
{
    progress = 0.f;
    u8 i,j;
    for (i=0;i<9;++i)
        for (j=0;j<9;++j)
            progress+=+grid[i][j];
    progress = 1.f-(progress/729.f);
}

