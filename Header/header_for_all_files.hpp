#pragma once
#include <iostream>
#include <tuple>
#include <limits>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include <functional>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cstring>
#include <memory>
#if defined(_WIN32) || defined(_WIN64)
    #include <shellapi.h>
#endif // defined

class Keep;

class StaticClassToTest{
    public:
        static unsigned long long id;
        template<typename T>
        static T load_variable();
        static unsigned long long load_variable_with_decrease(unsigned long long max_to_load);
        inline static const std::string name_of_base = "base.txt";
        template<typename T>
        static T load_variable_with_limit(T &&limit)
        {
            T temp_var;
            temp_var = StaticClassToTest::validation(temp_var);
            while (temp_var > limit || temp_var < 1){
                std::cout << "Value to small or too high. Try again\n";
                temp_var = StaticClassToTest::validation(temp_var);
            }
            return temp_var;
        }
        static unsigned long long get_max_size_of_elements(std::vector<Keep> vector_with_all_object);
    private:
        template<typename T>
        static T validation(T &t);
        StaticClassToTest operator=(StaticClassToTest &other)
        {
            this->throw_error();
            return *this;
        }
        StaticClassToTest(const StaticClassToTest &obj)
        {
            this->throw_error();
        }
        void throw_error()
        {
            throw "StaticClassToTest's object can't be called\n";
        }
};

class Object
{
    public:
        virtual void make_basic_activity(Keep & keep, std::vector<Keep> & vector_with_all_object, const std::string day) = 0;
        virtual void make_basic_activity(Keep keep, std::vector<Keep> &&vector_with_all_object, std::string day) = delete;
};

class File
{
    public:
        virtual std::string do_it(std::string name_of_file, std::string what_save) = 0;
};

class SaveToFile: public File
{
    public:
        void save_without_append(std::string name_of_file, std::string what_save);
        void special_save_with_bool_at_first_position(std::string name_of_file, std::string what);
    private:
        std::string do_it(std::string name_of_file, std::string what_save) override;
};

class OpenFile: public File
{
    public:

        std::string get_all_lines_from_file(std::string name_of_file);
        std::vector<std::string> split_file_by_delimeter(std::string content_to_split,std::string delimeter);
        inline unsigned long long size_of_file(const std::string fname)
        {
            this->len_of_file = this->get_size_of_file(fname);
            return len_of_file;
        }

        inline bool does_file_exist(const std::string & fname) const
        {
            std::ifstream iff(fname);
            return iff.good();
        }
    private:
        std::string do_it(std::string name_of_file, std::string what_save) override; // Parameter what_save ensured only for polymorphysm needs
        unsigned long long len_of_file = 0;
        unsigned long long get_size_of_file(const std::string fname);
};


class AbsKeep
{
    public:
        AbsKeep(): status(0), description("Incomplete data"), unique_id(StaticClassToTest::id) {}

    protected:
        bool status;
        std::string description;
        unsigned long long unique_id;

};

class Keep:public AbsKeep
{
    public:

        explicit Keep(): AbsKeep() {}
        std::tuple<unsigned long long, std::string, bool> get_all_data();

        template<typename T>
        T get_variable_by_type();

        template<typename...Args>
        void set_all_values(Args...args)
        {
            std::tie(this->unique_id, this->description, this->status) = std::make_tuple(args...);
        }
    private:
        template<typename T>
        void set_variable(T t);
        friend std::ostream & operator<<(std::ostream &out, const Keep & keep);
};

class Time
{
    public:
        Time()
        {

        }
    protected:
        virtual void get_and_set_date()=0;

    protected:
        std::string current_day;
        std::string current_month;
        std::string current_year;
        std::string full_data;
};

class CurrentTime:public Time
{
    public:
        CurrentTime():Time(){
        this->get_and_set_date();
        }
        std::string get_full_date();
        std::string get_day();
        std::string get_year();
        std::string get_month();
    protected:
        void get_and_set_date();
    private:
        std::string temp_func_to_reduce_redundant(std::string flag);
};

class Printing: public Keep
{

    public:

        inline std::string print_base_with_select_day()
        {
            this->print_base();
            return this->load_temp_day();
        };

        void print_vector(std::vector<Keep> & keep);

    protected:
        template<typename T>
        void print_selected_variable(T var);
    private:
        void print_all_values(std::vector<Keep> vector_with_all_object);
        void print_base();
        unsigned short variable_to_comfort_view () const
        {
            return 10;
        }
        std::vector<std::string> segreagated_vector_by_days;
        std::string load_temp_day();
        void allocate_this_object(Keep &keep);
};

class PrintingOnlyForSelectedDays: public Keep, public Object
{
    public:
        PrintingOnlyForSelectedDays():Keep(){}
        void make_basic_activity(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string day) override;

};

class PrintingForToday: public Object
{
    public:
        void make_basic_activity(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string day) override;
    private:
        void refresh_load_today(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string day) const;
};

class Add: public Object
{
    public:
        Add() : unique_id(StaticClassToTest::id), value_inside("Incomplete TODO"), status_of_activity(0)
        {
            add();
        }

        void make_basic_activity(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string day) override;

    private:
        Keep keeper;
        int unique_id;
        std::string value_inside;
        unsigned char status_of_activity;
        void take_care_of_add(Keep &keep, const std::string &day);
        Keep get_keep() const
        {
            return keeper;
        }
        void add();
};

class Edit: public Object
{
    public:
        void make_basic_activity(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string day) override;
    private:
        void do_it(std::vector<Keep> & vector_with_all_object, std::string day_name, unsigned long long id_to_edit) const;
        void clean_file(std::string name_of_file) const;
};

class AbsBrowse
{
    public:
        virtual void browse_base()=0;
};

class Browse: public AbsBrowse
{
    public:
        virtual void browse_base();
};


class Remove: public Object
{

    public:
        void make_basic_activity(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string day) override;
    private:
        void clean_file(const std::string fname);
};

class Start
{
    public:
        virtual void start(std::vector<Keep> &vector_with_all_object) = 0;
};

class StartProgram: public Start, public Object
{
        void make_basic_activity(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string day) override;
    private:
        void start(std::vector<Keep> & vector_with_all_object);
};

class LoadVector: public Object
{
    public:
        void make_basic_activity(Keep &keep, std::vector<Keep> & vector_with_all_activity, std::string day) override;
    private:
        void reverse_load_vector(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string name_of_file);
        void classic_load_to_vector(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string name_of_file);
        std::vector<std::string> func_to_avoid_redundance(std::vector<Keep> & vector_with_all_object, std::string name_of_file);
        void allocate_Vector_With_Keep(Keep && keep, std::vector<Keep> &vec_with_all_objects, const std::string & description);
};

class Helper
{
    public:
        bool check_that_length_is_printable_for_user(const std::string name_of_file, unsigned const short limit=10);
        static void refresh_screen();
        static void save_activites_to_selected_days(std::string name_of_file, std::string what);
        static void print_full_vector(std::vector<Keep> & vector_with_all_values);
};

class Conversion
{
    public:
        static std::pair<bool, std::string> convert_to_pair(const std::string &single_line);
};

class GetterClass
{
    public:
        static std::string get_name_of_today();
};
