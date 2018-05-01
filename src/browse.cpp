#include "../Header/header_for_all_files.hpp"

void Browse::make_basic_activity(Keep &keep, std::vector<Keep> & vector_with_all_activity, std::string day)
{

    std::string var_to_split = OpenFile().get_all_lines_from_file(StaticClassToTest::name_of_base);
    auto splitted_vector = OpenFile().split_file_by_delimeter(var_to_split, "\n");
    std::cout << "Enter day(only day's number e.g. 30) you want to find: ";
    unsigned int temp_variable_to_load = StaticClassToTest::load_variable_with_limit<unsigned int>(31);
    std::string string_representation = std::to_string(temp_variable_to_load);
    char first = '0';
    if (temp_variable_to_load > 10)
        first = string_representation[0];
    auto number_of_lines = OpenFile().size_of_file(StaticClassToTest::name_of_base) + 1;
    bool found = false;
    unsigned long long counter = 0;
    for(unsigned long long start_from = 0; start_from < number_of_lines; start_from += 28){
        auto number = std::find_if(splitted_vector.begin() + counter ,splitted_vector.end(), [&](auto x)
                      {
                      counter++;
                      if (temp_variable_to_load > 10){
                          if(string_representation[0]-'0' == x[0]-'0' && string_representation[1]-'0' == x[1]-'0')
                            return true;
                            }
                      else{
                        if(first == x[0])
                            return true;
                        }
                      return false;
                      });
    if(number != std::end(splitted_vector)){
        std::cout << "Number: " << *number << " " << "was found at the: " << counter << " position" << '\n';
        found = true;
        }

    }
    if(!found)
        std::cout << "Day not found\n";
}
