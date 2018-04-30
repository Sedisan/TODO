#include "../Header/header_for_all_files.hpp"

void Printing::print_all_values(std::vector<Keep> st)
{
    auto res = this->get_all_data();
    auto status_of_activity = std::get<bool>(res);
    std::string temp_var;
    temp_var = status_of_activity == 0 ? "\033[1;33mPending\033[0m" : "\033[1;32mCompleted\033[0m";
    std::cout << std::get<unsigned long long>(res) + 1 << ". " << std::get<std::string>(res) << ' ';
    auto how_many_fill = (1 + StaticClassToTest::get_max_size_of_elements(st)-std::get<std::string>(res).size());
    std::cout.fill('-');
    std::cout.width(how_many_fill);
    if(how_many_fill > 2)
        std::cout <<"> " <<  temp_var << '\n';
    else
        std::cout << " " << temp_var << '\n';
    std::cout.fill(' ');
}

void Printing::allocate_this_object(Keep &keep)
{
    auto res = keep.get_all_data();
    this->set_all_values(std::get<unsigned long long>(res), std::get<std::string>(res), std::get<bool>(res));
}

void Printing::print_vector(std::vector<Keep> & vector_with_all_values)
{
    for(auto &k: vector_with_all_values){
        this->allocate_this_object(k);
        this->print_all_values(vector_with_all_values);
    }
}

std::string Printing::load_temp_day()
{
    std::cout << "Which day show? Press ctrl+c to exit program\n";
    unsigned long long get_selected_day = StaticClassToTest::load_variable_with_limit<unsigned long long>(this->segreagated_vector_by_days.size());
    return this->segreagated_vector_by_days[get_selected_day-1];
}

void PrintingForToday::make_basic_activity(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string day)
{
    std::cout << "Your planned activity for today:\n";
    std::thread thread_to_load;
    thread_to_load = std::thread(&PrintingForToday::refresh_load_today, this, std::ref(keep), std::ref(vector_with_all_object), std::ref(day));
    if(thread_to_load.joinable())
        thread_to_load.join();
    Helper::print_full_vector(vector_with_all_object);
}

void PrintingForToday::refresh_load_today(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string day) const
{
    std::vector<Keep> temp_vector;
    LoadVector().make_basic_activity(keep, vector_with_all_object, GetterClass::get_name_of_today());
    Helper::print_full_vector(temp_vector);
}
