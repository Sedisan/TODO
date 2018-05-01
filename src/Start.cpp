#include "../Header/header_for_all_files.hpp"

void redict(std::shared_ptr<Object> &polymorphysm_general_object, Keep & keep, std::vector<Keep> & vector_with_all_object, const std::string day)
{
    polymorphysm_general_object->make_basic_activity(keep, vector_with_all_object, day);
}

void StartProgram::make_basic_activity(Keep &keep, std::vector<Keep> & vector_with_all_object, std::string day)
{
    this->start(vector_with_all_object);
}

void StartProgram::start(std::vector<Keep> & vector_with_all_object)
{
    std::cout << "Hello!\n"
              << "Today is: "<< GetterClass::get_name_of_today();
    if(!vector_with_all_object.empty())
        std::cout <<" and this is your today's planned activity:\n";
    else
        std::cout << " and please add something\n";
    Helper::print_full_vector(vector_with_all_object);
    for(;;)
    {
        Keep keep;

        std::cout   << "Select one of the operation:\n"
                    << "1. Add your TODO activity\n"
                    << "2. Edit your TODO activity\n"
                    << "3. Quick browse today's activity\n"
                    << "4. Browse another day activity\n"
                    << "5. Remove planned activity\n"
                    << "6. Open program location (Only for Windows)\n"
                    << "7. Exit program\n";

        std::cout << "Your choise: ";
        unsigned int choise = StaticClassToTest::load_variable<unsigned int>();
        Helper::refresh_screen();
        std::shared_ptr<Object> polymorphysm_general_object;
        switch(choise)
        {
        case 1:
        {
            std::cout << "Press 1 to add, or else number to back\n";
            unsigned int decision = StaticClassToTest::load_variable<unsigned int>();
            if (decision != 1)
            {
                continue;
                break;
            }
            polymorphysm_general_object = std::make_shared<Add>();
            redict(polymorphysm_general_object, keep, vector_with_all_object, GetterClass::get_name_of_today());
            break;
        }

        case 2:
        {
            std::cout << "Edit today activity? Press 1, to another day press 2. Press 3 to back\n";
            unsigned int decision = StaticClassToTest::load_variable<unsigned int>();
            if (decision != 1 && decision != 2)
            {
                continue;
                break;
            }
            polymorphysm_general_object = std::make_shared<Edit>();
            decision == 1 ?
            redict(polymorphysm_general_object, keep, vector_with_all_object, GetterClass::get_name_of_today()):
            redict(polymorphysm_general_object, keep, vector_with_all_object, Printing().print_base_with_select_day());
            break;
        }
        case 3:
        {
            polymorphysm_general_object = std::make_shared<PrintingForToday>();
            redict(polymorphysm_general_object, keep, vector_with_all_object, GetterClass::get_name_of_today());
            break;
        }
        case 4:
        {
            polymorphysm_general_object = std::make_shared<PrintingOnlyForSelectedDays>();
            redict(polymorphysm_general_object, keep, vector_with_all_object, Printing().print_base_with_select_day());
            break;
        }
        case 5:
        {
            std::cout << "Remove today activity? Press 1, to another day press 2. Press 3 to back\n";
            unsigned int decision = StaticClassToTest::load_variable<unsigned int>();
            if (decision != 1 && decision != 2)
            {
                continue;
                break;
            }
            polymorphysm_general_object = std::make_shared<Remove>();
            decision == 1 ?
            redict(polymorphysm_general_object, keep, vector_with_all_object, GetterClass::get_name_of_today()):
            redict(polymorphysm_general_object,keep, vector_with_all_object, Printing().print_base_with_select_day());
            break;
        }
        case 6:
        {
            #if defined(_WIN32) || defined(_WIN64)
                ShellExecute(NULL, "open", "", NULL, NULL, SW_SHOWDEFAULT);
            #else
                std::cout << "Browsing on your system is currently unavailable\n";
                std::this_thread::sleep_for(std::chrono::seconds(3));
            #endif // _WIN32
            break;
        }
        case 7:
            return;
        }
        if (choise != 3 && choise != 4)
            Helper::refresh_screen();
        if(choise < 6 && choise != 3 && choise != 4)
            std::cout << "Operation was successfull\n";
    }

}
