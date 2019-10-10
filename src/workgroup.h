#pragma once
using u8 = unsigned char;
class cell;

/**
 * @brief The workgroup helper oject which contains data to recalculate possible values of 9 cells
 * 
 */
class workgroup
{
    cell* work[9];
    cell* wg[9];
    u8 exp_group[9];
    u8 group_size;
    unsigned long mask;

    void generate_mask();
    void generate_wg_from_mask();
    u8 get_exp_sum();
    u8 get_val_sum();

public:
    /**
     * @brief Construct a new workgroup object. Sets the default mask for the 
     * workgroup in format xxxxxxxxx (e.g 000000111) with sum of '1's = group size
     * 
     * @param work A pointer to the set of cells &cell[9]
     * @param group_size A pointer to the group size to calculate
     */
    workgroup(cell** work, u8 group_size);
    /**
     * @brief Iterates the mask of the workgroup
     * 
     * @return true Iteration was successfull
     * @return false No more iterations are possible for the workgroup
     */
    bool iterate_mask();
    /**
     * @brief Whether the cells in the workgroup are empty (don't contain num value) or not
     * 
     * @return true All cells are empty
     * @return false One or more cells already have a value
     */
    bool is_empty();
    /**
     * @brief Perform calculations on the workgroup and fills cells with numbers if possible
     * 
     * @return true At least one cell was modified (cell::exp values)
     * @return false No cells were modified (cell::exp values)
     */
    bool calculate_wg();
    /**
     * @brief Prints current mask of the workgroup
     * 
     */
    void print_mask();
    
    /**
     * @brief Sudoku is solvable
     * 
     */
    void issolvable();
};