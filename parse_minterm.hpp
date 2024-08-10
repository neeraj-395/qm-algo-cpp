#include <iostream>
#include <vector>

struct MintermData 
{
    const uint var_count;
    const std::vector<uint> one_terms;
    const std::vector<uint> dont_terms;

    MintermData(const std::vector<uint>& one_terms, 
                const std::vector<uint>& dont_terms,
                const uint& var_count);
};

MintermData parse_minterm_args(const int& argc, char* const* argv);