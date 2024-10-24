#include <doctest/doctest.h>

import data_structures;

TEST_CASE("inplace_vector tests")
{
    caff::inplace_vector<int, 3> v = { 1, 2, 3 };

    for (auto e : v)
    {
        int y = e;
    }
}