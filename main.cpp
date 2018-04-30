#include "Header/header_for_all_files.hpp"
int main()
{
    auto number_of_user_cores = std::thread::hardware_concurrency();
    std::thread thread_to_load;
    std::vector<Keep> vector_with_all_activity;
    Keep keep;
    std::shared_ptr<Object> polymorphysism_start(new LoadVector());
    thread_to_load = std::thread([&](){polymorphysism_start->make_basic_activity(keep, vector_with_all_activity, GetterClass::get_name_of_today());});
    try{

        if(thread_to_load.joinable())
            thread_to_load.join();
        polymorphysism_start = std::make_shared<StartProgram>();
        polymorphysism_start->make_basic_activity(keep, vector_with_all_activity, GetterClass::get_name_of_today());
    }
    catch(...){}
    std::cout << "Thanks for using program!\n";

    return 0;
}
