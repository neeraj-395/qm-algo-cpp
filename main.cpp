#include "minterm.hpp"
#include "parse_minterm.hpp"

int main(int argc, char* const* argv) {

    MintermData min_data = parse_minterm_args(argc, argv);
    
    std::vector<Minterm> minterms;
    std::vector<Minterm> prime_implicants;
    MintermGroup groups[min_data.var_count + 1];

    for(const uint &term: min_data.one_terms) {
        minterms.emplace_back(term, false);
    }

    for(const uint &term: min_data.dont_terms) {
        minterms.emplace_back(term, true);
    }

    do {

        for (const Minterm& min : minterms) {
            groups[min.term_bit_count].add_minterm(min);
        }

        minterms.clear();

        for(uint i=0; i < min_data.var_count; ++i) {
            if (!groups[i].minterms.empty() && !groups[i + 1].minterms.empty()) {
                groups[i].combine_with(groups[i + 1], minterms);
            }
        }

        for(const MintermGroup& group : groups) {
            group.get_uncombined_terms(prime_implicants);
        }

        for(MintermGroup& group : groups) {
            group.minterms.clear();
        }
        
    } while(!minterms.empty());

    std::cout << "::: Prime Implicants :::\n";
    for(const Minterm& prime: prime_implicants) {
        prime.print();
    }
    std::cout << "\n::: Ignored bits are represented by dashes '_'\n";

    return 0;
}