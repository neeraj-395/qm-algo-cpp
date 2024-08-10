#include "parse_minterm.hpp"

#include <string>
#include <sstream>
#include <getopt.h>
#include <set>

MintermData::MintermData(const std::vector<uint>& ot, const std::vector<uint>& dt,
                         const uint& vc): one_terms(ot), dont_terms(dt), var_count(vc) {}

void print_usage(const std::string &prog_name)
{
    std::cerr << "Usage: " << prog_name << " -m <terms> -d <terms>\n";
    std::cerr << "Example: " << prog_name << " -m 1,2,3 -d 4,5,6\n";
}

void parse_terms(const std::string& arg, std::set<uint>& terms) 
{
    std::string item;
    std::stringstream ss(arg);
  
    while(getline(ss, item, ','))
    {
        try { terms.insert(static_cast<uint>(std::stoi(item))); } 
        catch (const std::invalid_argument &e) {
            std::cerr << "Invalid input '" << item
                      << "'. All terms must be positive integers.\n";
            exit(EXIT_FAILURE);
        }
    }
}

MintermData parse_minterm_args(const int& argc, char* const* argv) {
    std::set<uint> one_terms, dont_terms;
    
    int opt = getopt(argc, argv, "m:d:h");
    do {
        switch (opt)
        {
            case 'm':
                parse_terms(optarg, one_terms);
                break;
            case 'd':
                parse_terms(optarg, dont_terms);
                break;
            case 'h':
            case '?':
            default:
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    } while((opt = getopt(argc, argv, "m:d:h")) != -1);

    uint var_count = 0;
    uint max_val = std::max(one_terms.empty() ? 0 : *(one_terms.rbegin()),
                            dont_terms.empty() ? 0 : *(dont_terms.rbegin()));

    while(max_val > 0) { max_val >>= 1; ++var_count; }

    std::vector<uint> ones(one_terms.begin(), one_terms.end());
    std::vector<uint> donts(dont_terms.begin(), dont_terms.end());

    return MintermData(ones, donts, var_count);
}