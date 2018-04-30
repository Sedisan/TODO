#include "../Header/header_for_all_files.hpp"

std::mutex mtx_to_control_remove;
void Remove::make_basic_activity(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string selected_day)
{
    vector_with_all_object.clear();
    LoadVector load_full_vector;
    LoadVector().make_basic_activity(keep, vector_with_all_object, selected_day);
    Helper::print_full_vector(vector_with_all_object);
    if(vector_with_all_object.empty())
    {
        std::cout << "Choosen day is empty\n";
        return;
    }
    std::cout << "Which activity remove?: ";
    unsigned long long id_to_remove = StaticClassToTest::load_variable_with_limit<unsigned long long>(vector_with_all_object.size());
    if(OpenFile().size_of_file(selected_day) > 10)
    {
        load_full_vector.make_basic_activity(keep, vector_with_all_object, selected_day);
        id_to_remove = 1 + (vector_with_all_object.size()- id_to_remove);
    }
    vector_with_all_object.erase(vector_with_all_object.begin() + (id_to_remove -1));
    this->clean_file(selected_day);
    for(unsigned long long id = 0; id < vector_with_all_object.size(); id++)
    {
        Helper::save_activites_to_selected_days(selected_day, std::to_string(vector_with_all_object[id].get_variable_by_type<bool>()) + vector_with_all_object[id].get_variable_by_type<std::string>());
    }
    vector_with_all_object.clear();
    load_full_vector.make_basic_activity(keep, vector_with_all_object, selected_day);
}

void Remove::clean_file(std::string name_of_file)
{
    std::lock_guard<std::mutex> lck(mtx_to_control_remove);
    std::ofstream off(name_of_file, std::ofstream::trunc);
    off.close();
}
