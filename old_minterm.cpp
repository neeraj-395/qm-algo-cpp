#include "minterm.hpp"

Minterm::Minterm(const std::bitset<8>& bs, const std::bitset<8>& ibs)
        : binary(bs), ignore(ibs), combined(false) {}

bool Minterm::can_combine_with(const Minterm& other) const {
    std::bitset<8> tmp = (binary ^ other.binary);
    return tmp.count() == 1 && ignore == other.ignore 
           && tmp.to_ulong() > ignore.to_ulong();
}

void Minterm::set_combined_with(Minterm& other) {
    this->combined = other.combined = true;
}

Minterm Minterm::combine_with(const Minterm& other) const {
    return Minterm((binary & other.binary), 
                   (binary ^ other.binary) ^ ignore);
}

void Minterm::print() const {
    std::cout << "::: binary: " << binary 
              << ", ignored: " << ignore
              << ", combined: " << combined << "\n";
}

/* Minterm group methods defination */
    
void MintermGroup::add_minterm(const Minterm& min) {
    minterms.emplace_back(min.binary, min.ignore);
}

void MintermGroup::combine_with(MintermGroup& other, std::vector<Minterm>& new_min) {
    for (Minterm& min1 : minterms) {
        for (Minterm& min2 : other.minterms) {
            if (min1.can_combine_with(min2)) {
                new_min.push_back(min1.combine_with(min2));
                min1.set_combined_with(min2);
            }
        }
    }
}

void MintermGroup::get_uncombined_terms(std::vector<Minterm>& uncombined) {
    for (const Minterm& min: minterms) {
        if(!min.combined) uncombined.emplace_back(min);
    }
}

void MintermGroup::print_group() const {
    std::cout << "\n::: Minterm Group :::\n";
    for(const Minterm& min : minterms) min.print();
}

uint set_bit_count(int n)
{
    uint count=0; while(n) {count += (n & 1); n >>= 1;} return count;
}