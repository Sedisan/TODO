#include "../Header/header_for_all_files.hpp"
std::mutex special_mutex_for_localtime;
std::string CurrentTime::temp_func_to_reduce_redundant(std::string flag)
{
    auto t = std::time(nullptr);
    std::lock_guard<std::mutex> lck_for_localtime(special_mutex_for_localtime);
    struct tm tm = *localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, flag.c_str());
    return oss.str();
}

void CurrentTime::get_and_set_date()
{
    this->full_data     =   temp_func_to_reduce_redundant("%d-%m-%Y");
    this->current_day   =   temp_func_to_reduce_redundant("%d");
    this->current_month =   temp_func_to_reduce_redundant("%m");
    this->current_year  =   temp_func_to_reduce_redundant("%y");
}

std::string CurrentTime::get_month()
{
    return this->current_month;
}

std::string CurrentTime::get_full_date()
{
    return this->full_data;
}

std::string CurrentTime::get_day()
{
    return this->current_day;
}

std::string CurrentTime::get_year()
{
    return this->current_year;
}
