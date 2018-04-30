#include "../Header/header_for_all_files.hpp"

std::pair<bool, std::string> Conversion::convert_to_pair(const std::string &single_line)
{
    auto rest = single_line.substr(1, single_line.size());
    return std::make_pair(single_line[0] - '0', rest);
}
