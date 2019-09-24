#pragma once
using u8 = unsigned char;
class cell;

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
    workgroup(cell** work, u8 group_size);
    bool iterate_mask();
    bool is_empty();
    void calculate_wg();
    void print_mask();
};