#include <iostream>
#include <bitset>
#include "cell.h"
#include "workgroup.h"
#include "exc.h"

workgroup::workgroup(cell** _work, u8 size)
{
    for (u8 i=0;i<9;++i)
        exp_group[i]=0;
    for (auto& w:wg)
        w=nullptr;

    for (u8 i=0;i<9;++i)
    {
        work[i]=_work[i];
    }
    group_size=size;
    generate_mask();
    generate_wg_from_mask();
    for (u8 i=0;i<group_size;++i)
        for (u8 j=0;j<9;++j)
            exp_group[j] = exp_group[j] || wg[i]->exp[j];
}


void workgroup::generate_mask()
{
    u8 i = 0; // нулевой бит будет первым
    mask = 0;
    do 
        mask += 1<<i++;
    while (i<group_size);
}

// TODO: make faster iteration
bool workgroup::iterate_mask()
{
    // decode mask and fill bits
    for (u8 i=0;i<10;++i)
        bits[i] = (mask>>i) & 1;

    int k=9,gs=1;
    while (bits[--k]==0);

    while (bits[--k]==1)
        ++gs;
    k=0;

    if (gs==group_size)
    {   // step up
        while (k<group_size-1)
            bits[k++]=1;

        while (bits[k]==0) ++k;

        while (bits[k]==1)
            bits[k++]=0;
            
        bits[k] = 1;
    }
    else
    {
        while (gs < group_size)
            gs+=bits[k++];
        
        if (k<10)
        {
            bits[k-1]=0;
            bits[k]=1;
        }
    }

    mask = 0;
    for (u8 i=0;i<10;++i)
        mask+=bits[i]<<i;
    


    generate_wg_from_mask(); // regenerate wg

    for (u8 i=0;i<9;++i)
        exp_group[i]=0;
    for (u8 i=0;i<group_size;++i)
        for (u8 j=0;j<9;++j)
            exp_group[j] = exp_group[j] || wg[i]->exp[j];
    
    if (mask>1<<9)
        return false;
    return true;
}

void workgroup::generate_wg_from_mask()
{
    auto tmp_mask = mask;
    for (u8 i=0;i<group_size;++i)
    {
        for (u8 j=0;j<9;++j)
        {
            if ((tmp_mask>>j) & 1)
            {
                tmp_mask-=1<<j;
                wg[i] = work[j];
                j=9;
            }
        }
    }
}

bool workgroup::calculate_wg()
{
    bool change_flag = false;
    u8 exsum = get_exp_sum();
    u8 vsum = get_val_sum();
    if (exsum<=group_size && exsum+vsum<9)
    {
        change_flag = true;
        for (u8 i=0;i<9;++i)
        {
            if (!((mask>>i)&1))
                *work[i]-exp_group;
        }
    }
    return change_flag;
}

u8 workgroup::get_exp_sum()
{
    u8 n=0;
    for (u8 i:exp_group)
        n += i;
    return n;
}

void workgroup::print_mask()
{
    std::cout << std::bitset<9>(mask) << std::endl;
}

bool workgroup::is_empty()
{
    for (u8 i=0;i<group_size;++i)
        if (wg[i]->num)
            return false;
    return true;
}

u8 workgroup::get_val_sum()
{
    u8 v=0;
    for (u8 i=0;i<9;++i)
    {
        if (work[i]->num)
            ++v;
    }
    return v;
}

void workgroup::issolvable()
{
    int numbers[] = {0,0,0,0,0,0,0,0,0};
    for (int i=0;i<9;++i)
    {
        if (work[i]->num !=0)
            if (++(numbers[work[i]->num-1])>1)
                throw exc_notsolvable{"Not solvable sudoku"};
    }
}