#include "../Header/header_for_all_files.hpp"

std::mutex mtx_to_control_edit;
void Edit::make_basic_activity(Keep & keep, std::vector<Keep> & vector_with_all_object, const std::string day_name)
{
    LoadVector load_full_vector;
    vector_with_all_object.clear();
    load_full_vector.make_basic_activity(keep, vector_with_all_object, day_name);
    Helper::print_full_vector(vector_with_all_object);
    if(vector_with_all_object.empty())
    {
        std::cout << "Choosen day is empty\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }
    std::cout << "Which activity edit?: ";
    unsigned long long id_to_edit = StaticClassToTest::load_variable_with_limit<unsigned long long>(vector_with_all_object.size());
    if(OpenFile().size_of_file(day_name) > 10)
    {
        load_full_vector.make_basic_activity(keep, vector_with_all_object, day_name);
        id_to_edit = 1 + (vector_with_all_object.size()- id_to_edit);
    }
    this->clean_file(day_name);
    for(unsigned long long id = 0; id < vector_with_all_object.size(); id++)
    {
        if (id == id_to_edit-1)
            if (vector_with_all_object[id].get_variable_by_type<bool>() == 0)
                Helper::save_activites_to_selected_days(day_name, std::to_string(vector_with_all_object[id].get_variable_by_type<bool>()+1) + vector_with_all_object[id].get_variable_by_type<std::string>());
            else
                Helper::save_activites_to_selected_days(day_name, std::to_string(vector_with_all_object[id].get_variable_by_type<bool>()-1) + vector_with_all_object[id].get_variable_by_type<std::string>());
        else
            Helper::save_activites_to_selected_days(day_name, std::to_string(vector_with_all_object[id].get_variable_by_type<bool>()) + vector_with_all_object[id].get_variable_by_type<std::string>());
    }
    vector_with_all_object.clear();
    load_full_vector.make_basic_activity(keep, vector_with_all_object, day_name);
}

void Edit::clean_file(std::string name_of_file)const
{
    std::lock_guard<std::mutex> lck(mtx_to_control_edit);
    std::ofstream off(name_of_file, std::ofstream::trunc);
    off.close();
}
