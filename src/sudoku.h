#pragma once
#include "cell.h"
#include "exc.h"

/**
 * @brief The main class which contains sudoku information and functions
 * 
 */
class sudoku
{
    cell grid[9][9];
    float progress;

public:
    /**
     * @brief Construct a new sudoku object
     * 
     */
    sudoku();
    /**
     * @brief Clears sudoku object
     * 
     */
    void clear();
    /**
     * @brief Inserts a number in the cell at the position of grid
     * 
     * @param row A row to insert the cell [0-8]
     * @param column A column to insert the cell [0-8]
     * @param num A number to insert [1-9]
     */
    void insert_num(u8 row, u8 column, u8 num);
    /**
     * @brief Loads a file in a format "[%d %d %d ]", row, col, num for each cell
     * 
     * @param file_name A path to the file
     */
    void load_file(const char* file_name);
    /**
     * @brief Prints sudoku values into the standart output
     * 
     */
    void print();
    /**
     * @brief Prints sudoku sums of possible values into the standart output
     * 
     */
    void print_exp_sums();
    /**
     * @brief Get the progress on the sudoku (% of solved cells including possible values solutions)
     * 
     * @return float The progress floating number [0.0-1.0]
     */
    float get_progress(); 
    /**
     * @brief Tries to fully calculate sudoku
     * 
     */
    void calculate_all();
    /**
     * @brief Tries to calculate one step of sudoku
     * 
     * @return true The sudoku object was modified after calculation
     * @return false The sudoku object was NOT modified after calculation
     */
    bool calculate_step();

private:
    void add_num(u8 row, u8 column, u8 num);
    void recalculate_exp(u8 row, u8 column, u8 num);
    void recalculate_progress();
    bool calculate_work(cell** work);
};