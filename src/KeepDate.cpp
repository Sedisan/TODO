#include "../Header/header_for_all_files.hpp"
template<>
void Keep::set_variable<>(std::string arg)
{
    this->description = arg;
}
template<>
void Keep::set_variable<>(unsigned long long arg)
{
    this->unique_id = arg;
}
template<>
void Keep::set_variable<>(bool arg)
{
    this->status = arg;
}

template<>
unsigned long long Keep::get_variable_by_type<unsigned long long>()
{
    return this->unique_id;
}

template<>
std::string Keep::get_variable_by_type<std::string>()
{
    return this->description;
}

template<>
bool Keep::get_variable_by_type<bool>()
{
    return this->status;
}

std::ostream & operator<<(std::ostream &os, const Keep &keep)
{

    os << keep.unique_id << ". " << keep.description << " " << keep.status << '\n';
    return os;

}

std::tuple<unsigned long long, std::string, bool> Keep::get_all_data()
{
    return std::make_tuple<>(unique_id, description, status);
}
