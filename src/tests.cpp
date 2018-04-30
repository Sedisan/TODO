#include "../Header/header_for_all_files.hpp"

template<typename T>
T StaticClassToTest::validation(T &t){

    std::cin >> t;
    while(!std::cin)
    {
        std::cout << "Incorrect data. Try again\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> t;
    }
    return t;
};

unsigned long long StaticClassToTest::id = 0;
template<>
unsigned int StaticClassToTest::load_variable<unsigned int>()
{
    unsigned int temp_var;
    temp_var = StaticClassToTest::validation(temp_var);
    return temp_var;
}
template<>
std::string StaticClassToTest::load_variable<std::string>()
{
    std::string temp_string;
    std::cin.ignore();
    while(true){
    std::getline(std::cin, temp_string);
    if (temp_string.size() < 50)
        break;
    std::cout << "Line overhead. Maximum line limit equal 50, your equal: " << temp_string.size() << '\n';
    }
    return temp_string;
}
template<>
bool StaticClassToTest::load_variable<bool>()
{
    bool temp_var;
    temp_var = StaticClassToTest::validation(temp_var);
    return temp_var;
}

template<>
unsigned long long StaticClassToTest::load_variable<unsigned long long>()
{
    unsigned long long temp_var;
    temp_var = StaticClassToTest::validation(temp_var);
    return temp_var;
}

unsigned long long StaticClassToTest::load_variable_with_decrease(unsigned long long max_to_load)
{
    unsigned long long temp_id;
    temp_id = StaticClassToTest::validation(temp_id);
    while (temp_id > max_to_load || temp_id < 1){
        std::cout << "Value to small or too high. Try again\n";
        temp_id = StaticClassToTest::validation(temp_id);
    }
    temp_id--;

    return temp_id;
}
std::string get_name_of_today();

unsigned long long StaticClassToTest::get_max_size_of_elements(std::vector<Keep> vector_with_all_element)
{
    unsigned long long m = 0;
    for(auto &n: vector_with_all_element)
        {
            if ((n.get_variable_by_type<std::string>()).size() > m)
                m = (n.get_variable_by_type<std::string>()).size();
        }
    return m;
}
