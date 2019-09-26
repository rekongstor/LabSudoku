#pragma once
using u8 = unsigned char;
/**
 * @brief Stuct which contains information about a specific cell in the grid of the sudoku
 * 
 */
struct cell
{
    /**
     * @brief Contains a value of cell [1-9] or 0 if there's no value yet
     * 
     */
    u8 num;
    /**
     * @brief Contains all possible values of cell. 0 = not possible; 1 = possible
     * 
     */
    u8 exp[9];
    /**
     * @brief Construct a new cell object
     * 
     */
    cell();
    /**
     * @brief Copy-Construct a new cell object
     * 
     */
    cell(const cell&);
    /**
     * @brief Copies an existing cell data into this cell.
     * 
     * @return cell& - reference to this cell
     */
    cell& operator=(const cell&);
    /**
     * @brief Sets a cell value
     * 
     * @return cell& - reference to this cell
     */
    cell& operator=(const u8&);
    /**
     * @brief Returns a sum of exp[]
     * 
     * @return u8 sum
     */
    u8 operator+();
    /**
     * @brief Returns num 
     * 
     * @return u8 num
     */
    u8 operator*();
    /**
     * @brief Excludes value from exp[]
     * 
     * @param value Excluding number [0-9]
     */
    void operator^=(const u8& value);
    /**
     * @brief Deletes a set of possible values from cell exp[]
     * 
     * @param exp_group A set to exclude u8[9]
     */
    void operator-(const u8* exp_group);
};