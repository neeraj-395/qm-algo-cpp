#include <iostream>
#include <bitset>
#include <vector>

struct Minterm 
{
    bool combined;
    bool dont_care;
    const uint term;
    const uint ignore;
    const uint term_bit_count;
    
    Minterm(const uint& term=0, bool dont_care=0, const uint& ignore=0);
    
    bool can_combine_with(const Minterm& other) const;

    bool is_combine_exist(const Minterm& other) const;
    
    Minterm combine_with(const Minterm& other) const;

    void set_combined_with(Minterm& other);
    
    void print() const;
};

struct MintermGroup
{
    std::vector<Minterm> minterms;
    
    void add_minterm(const Minterm& min);
    
    void combine_with(MintermGroup& other, std::vector<Minterm>& new_min);

    void get_uncombined_terms(std::vector<Minterm>& uncombined) const;

    void print_group() const;
};