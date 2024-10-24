import std;
import data_structures;

using namespace caff;

int main()
{
    inplace_vector<int, 5> vec = {1, 2, 3};
    vec.push_back(4);
    vec.push_back(5);

    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        std::print("{} ", vec[i]);
    }
    std::println();

    vec.pop_back();
    vec.push_back(6);

    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        std::print("{} ", vec[i]);
    }
    std::println();
}
