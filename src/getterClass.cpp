#include "../Header/header_for_all_files.hpp"

std::string GetterClass::get_name_of_today()
{
    std::string today = CurrentTime().get_full_date();
    return today;
}
