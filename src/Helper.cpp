#include "../Header/header_for_all_files.hpp"

bool Helper::check_that_length_is_printable_for_user(const std::string name_of_file, unsigned const short limit)
{

    auto len_of_file = OpenFile().size_of_file(name_of_file);
    if (len_of_file < limit)
    {
        return false;
    }
    else
    {
        std::cout << "Warning, number of activity equal: "<< len_of_file<<"\nDo you want to force program to print all (press 0) or rather print all 7 days?(press any other number)\n";
        if(StaticClassToTest::load_variable<unsigned long long>() == 0)
        {
            return 0;
        }

    }
    return 1;

}

void Helper::refresh_screen()
{
    #ifdef _WIN32
        std::system("cls");
    #elifdef _WIN64
        std::system("cls");
    #else
        std::system("clear");
    #endif // _WIN32
}
void Helper::save_activites_to_selected_days(std::string name_of_file, std::string activity)
{
    SaveToFile save;
    save.special_save_with_bool_at_first_position(name_of_file, activity);
}

void Helper::print_full_vector(std::vector<Keep> & vector_with_all_object)
{
    Printing print;
    print.print_vector(vector_with_all_object);
}
