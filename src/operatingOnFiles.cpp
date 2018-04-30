#include "../Header/header_for_all_files.hpp"

typedef std::vector<Keep> vec;
std::mutex mutex_for_control_file;
std::string SaveToFile::do_it(std::string name_of_file, std::string what_save)
{
    std::ofstream off(name_of_file, std::ios_base::app);

    off << what_save << '\n';
    off.close();
    return "1";
}

void SaveToFile::save_without_append(std::string name_of_file, std::string what_save)
{
    std::ofstream off(name_of_file);
    off << what_save << '\n';
    off.close();
}

void SaveToFile::special_save_with_bool_at_first_position(std::string name_of_file, std::string what)
{
    std::lock_guard<std::mutex> lck(mutex_for_control_file);
    if (what[0] == '0' || what[0] == '1')
    {
        if (OpenFile().does_file_exist(name_of_file) == 0)
        {
            this->do_it(StaticClassToTest::name_of_base, name_of_file);
        }
        this->do_it(name_of_file, what);
    }
    else
    {
        std::cerr << "Problem with save to file...\n";
        fflush(NULL);
        throw "Problem with save";
    }
}

std::string OpenFile::do_it(std::string name_of_file, std::string what_save="")
{
    if (what_save != "")
        throw "Unexpected argument";
    //auto res =
    std::ifstream iff(name_of_file);
    if (!iff)
        return "0";
    this->len_of_file = this->get_size_of_file(name_of_file);
    std::cout << "Size equal: " << len_of_file << '\n';
    auto res = this->get_all_lines_from_file(name_of_file);

    iff.close();
    return "1";
}

std::string OpenFile::get_all_lines_from_file(std::string name_of_file)
{

    std::ifstream iff(name_of_file);
    if (!iff)
    {
        throw "Problem with get file\n";
    }
    auto res = iff.rdbuf();
    //iff.close();
    std::ostringstream iss;
    iss << res;
    //return std::string((std::istreambuf_iterator<char>(iff)), std::istreambuf_iterator<char>());
    return iss.str();
}

std::vector<std::string> OpenFile::split_file_by_delimeter(std::string content_to_split,std::string delimeter)
{

    std::vector<std::string> temp_vector;
    temp_vector.reserve(this->len_of_file);
    std::string::size_type pos = 0;
    std::string::size_type prev = 0;

    while((pos = content_to_split.find(delimeter, prev)) != std::string::npos)
    {
        temp_vector.push_back(content_to_split.substr(prev, pos - prev));
        prev = pos + delimeter.size();
    }

    if (prev != content_to_split.size())
        temp_vector.push_back(content_to_split.substr(prev));

    return temp_vector;

}

unsigned long long OpenFile::get_size_of_file(const std::string fname)
{
    std::ifstream iff(fname);
    auto res = std::count((std::istreambuf_iterator<char>(iff)), std::istreambuf_iterator<char>(), '\n');
    iff.close();
    return res;
}

void Printing::print_base()
{
    OpenFile open;
    if (open.does_file_exist(StaticClassToTest::name_of_base) == 0)
        return;

    std::string file = open.get_all_lines_from_file(StaticClassToTest::name_of_base);
    auto res = open.split_file_by_delimeter(file, "\n");
    auto shorter = this->variable_to_comfort_view();
    if (Helper().check_that_length_is_printable_for_user(StaticClassToTest::name_of_base, shorter))
    {
        std::reverse(res.end()-7, res.end());
        std::copy(res.end()-7, res.end(), std::back_inserter(this->segreagated_vector_by_days));
    }
    else
        this->segreagated_vector_by_days = res;
    for(unsigned int i = 0; i < this->segreagated_vector_by_days.size(); i++)
        std::cout << i + 1 << " " << this->segreagated_vector_by_days[i] << '\n';
}

void PrintingOnlyForSelectedDays::make_basic_activity(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string day)
{
    LoadVector().make_basic_activity(keep, vector_with_all_object, day);
    Helper::print_full_vector(vector_with_all_object);
}

void LoadVector::make_basic_activity(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string name_of_file)
{
    this->reverse_load_vector(keep, vector_with_all_object, name_of_file);
}

void LoadVector::reverse_load_vector(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string name_of_file)
{
    if (!Helper().check_that_length_is_printable_for_user(name_of_file))
    {
        this->classic_load_to_vector(keep, vector_with_all_object, name_of_file);
        return;
    }
    if (OpenFile().does_file_exist(name_of_file) == 0)
        return;
    auto after_split = this->func_to_avoid_redundance(vector_with_all_object, name_of_file);
    for(unsigned long long i = after_split.size()-1; i >= after_split.size()-7; i--)
        this->allocate_Vector_With_Keep(std::move(keep), vector_with_all_object, after_split[i]);

}

void LoadVector::classic_load_to_vector(Keep & keep, std::vector<Keep> & vector_with_all_object, std::string name_of_file)
{

    if (OpenFile().does_file_exist(name_of_file) == 0)
    {
        std::cout << "You don't have any planned activity\n";
        return;
    }
    auto after_split = this->func_to_avoid_redundance(vector_with_all_object, name_of_file);
    for(auto &n: after_split)
        this->allocate_Vector_With_Keep(std::move(keep), vector_with_all_object, n);

    if (vector_with_all_object.empty())
    {
        std::cout << "You've removed all every planned activity\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

std::vector<std::string> LoadVector::func_to_avoid_redundance(std::vector<Keep> & vector_with_all_object, std::string name_of_file)
{
    OpenFile o;
    StaticClassToTest::id = 0;
    if(!vector_with_all_object.empty())
        vector_with_all_object.clear();
    std::lock_guard<std::mutex> lck(mutex_for_control_file);
    std::string con_of_file = o.get_all_lines_from_file(name_of_file);
    auto after_split = o.split_file_by_delimeter(con_of_file, "\n");
    return after_split;
}

void LoadVector::allocate_Vector_With_Keep(Keep && keep, std::vector<Keep> &vec_with_all_objects, const std::string & n)
{
    auto res = Conversion::convert_to_pair(n);
    keep.set_all_values(StaticClassToTest::id, res.second, res.first);
    vec_with_all_objects.push_back(std::move(keep));
    StaticClassToTest::id++;
}
