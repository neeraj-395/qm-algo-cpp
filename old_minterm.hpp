#include <iostream>
#include <bitset>
#include <vector>

struct Minterm 
{
    bool combined;
    const std::bitset<8> binary;
    const std::bitset<8> ignore;
    
    Minterm(const std::bitset<8>& bits=0, const std::bitset<8>& ignbits=0);
    
    bool can_combine_with(const Minterm& other) const;

    void set_combined_with(Minterm& other);

    Minterm combine_with(const Minterm& other) const;

    void print() const;
};

struct MintermGroup
{
    std::vector<Minterm> minterms;
    
    void add_minterm(const Minterm& min);
    
    void combine_with(MintermGroup& other, std::vector<Minterm>& new_min);

    void get_uncombined_terms(std::vector<Minterm>& uncombined);

    void print_group() const;
};