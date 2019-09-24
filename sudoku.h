#pragma once
#include "cell.h"

class sudoku
{
    cell grid[9][9];
    float progress;

public:
    sudoku();

    void clear();

    void insert_num(u8 row, u8 column, u8 num);
    void load_file(const char* file_name);

    void print();
    void print_exp_sums();

    float get_progress(); 
    void calculate_all();   
    bool calculate_step();

private:
    void add_num(u8 row, u8 column, u8 num);
    void recalculate_exp(u8 row, u8 column, u8 num);
    void recalculate_progress();
    bool calculate_work(cell** work);
};