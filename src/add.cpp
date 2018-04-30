#include "../Header/header_for_all_files.hpp"
std::mutex mutex_for_control_add;
void Add::add()
{
    mutex_for_control_add.lock();
    std::cout << "Enter description: ";
    mutex_for_control_add.unlock();
    this->value_inside = StaticClassToTest::load_variable<std::string>();
    keeper.set_all_values(this->unique_id, this->value_inside, this->status_of_activity);
    StaticClassToTest::id++;
}

void Add::take_care_of_add(Keep & keep, const std::string &day)
{
    keep = this->get_keep();
    std::lock_guard<std::mutex> lck(mutex_for_control_add);
    Helper::save_activites_to_selected_days(day, std::to_string(keep.get_variable_by_type<bool>()) + keep.get_variable_by_type<std::string>());
}

void Add::make_basic_activity(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string day)
{
    this->take_care_of_add(keep, day);
}
