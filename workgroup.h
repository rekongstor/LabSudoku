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

public:
    workgroup(cell** work, u8 group_size);
    bool iterate_mask();
    void print_mask();
};