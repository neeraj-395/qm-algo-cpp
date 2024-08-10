#include "minterm.hpp"

static int set_bit_count(int n)
{
    uint count=0; while(n) {count += (n & 1); n >>= 1;} return count;
}

Minterm::Minterm(const uint& t, bool dontc, const uint& ign)
        :term(t), dont_care(dontc), ignore(ign), combined(0),
         term_bit_count(set_bit_count(t)) {}

bool Minterm::can_combine_with(const Minterm& other) const {
    return set_bit_count(term ^ other.term) == 1 && ignore == other.ignore;
}

bool Minterm::is_combine_exist(const Minterm& other) const {
    return (term ^ other.term) < ignore;
}

void Minterm::set_combined_with(Minterm& other) {
    combined = other.combined = true;
}

Minterm Minterm::combine_with(const Minterm& other) const {
    return Minterm((term & other.term), (dont_care && other.dont_care), 
                   (term ^ other.term) ^ ignore);
}

void Minterm::print() const {
    std::cout << "::: binary: " << std::bitset<8>(term) 
              << ", ignored: " << std::bitset<8>(ignore)
              << ", don't-care: " << dont_care
              << ", combined: " << combined << "\n";
}

/* MintermGroup method definations */
    
void MintermGroup::add_minterm(const Minterm& min) {
    minterms.emplace_back(min.term, min.dont_care, min.ignore);
}

void MintermGroup::combine_with(MintermGroup& other, std::vector<Minterm>& new_min) {
    for (Minterm& min1 : minterms) {
        for (Minterm& min2 : other.minterms) {
            if (!min1.can_combine_with(min2)) continue;
            min1.set_combined_with(min2);

            if(min1.is_combine_exist(min2)) continue;
            new_min.push_back(min1.combine_with(min2));
        }
    }
}

void MintermGroup::get_uncombined_terms(std::vector<Minterm>& uncombined) const {
    for (const Minterm& min: minterms) {
        if(!min.combined && !min.dont_care) uncombined.emplace_back(min);
    }
}

void MintermGroup::print_group() const {
    std::cout << "\n::: Minterm Group :::\n";
    for(const Minterm& min : minterms) min.print();
}