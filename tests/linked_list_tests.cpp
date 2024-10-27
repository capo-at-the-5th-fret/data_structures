#include <doctest/doctest.h>
import data_structures;

TEST_CASE("linked_list_node")
{
    using namespace caff;

    SUBCASE("default constructor")
    {
        linked_list_node<int> n;

        REQUIRE(n.value == 0);
        REQUIRE(n.next == nullptr);
    }
}

TEST_CASE("linked_list")
{
    using namespace caff;

    SUBCASE("member types")
    {
        using test_type = linked_list<int>;

        static_assert(std::is_same_v<test_type::value_type, int>);
        static_assert(std::is_same_v<test_type::size_type, std::size_t>);
        static_assert(std::is_same_v<test_type::difference_type, std::ptrdiff_t>);
        static_assert(std::is_same_v<test_type::reference, int&>);
        static_assert(std::is_same_v<test_type::const_reference, const int&>);
        static_assert(std::is_same_v<test_type::pointer, int*>);
        static_assert(std::is_same_v<test_type::const_pointer, const int*>);
        static_assert(std::is_same_v<test_type::iterator, linked_list_iterator<int>>);
        static_assert(std::is_same_v<test_type::const_iterator, linked_list_const_iterator<int>>);
        static_assert(std::is_same_v<test_type::reverse_iterator, std::reverse_iterator<linked_list_iterator<int>>>);
        static_assert(std::is_same_v<test_type::const_reverse_iterator, std::reverse_iterator<linked_list_const_iterator<int>>>);
    }

    SUBCASE("default constructor")
    {
        linked_list<int> list;
        REQUIRE(list.empty());
        REQUIRE(list.size() == 0);
    }

    SUBCASE("initializer_list constructor")
    {
        const linked_list list{ 1, 2, 3 };

        REQUIRE(list.size() == 3);

        const auto values = list | std::ranges::to<std::vector>();
        REQUIRE(values.size() == 3);
        REQUIRE(values[0] == 1);
        REQUIRE(values[1] == 2);
        REQUIRE(values[2] == 3);
    }

    SUBCASE("copy constructor")
    {
        const linked_list other{ 1, 2, 3 };
        const linked_list list{ other };

        const auto values = list | std::ranges::to<std::vector>();
        REQUIRE(values.size() == 3);
        REQUIRE(values[0] == 1);
        REQUIRE(values[1] == 2);
        REQUIRE(values[2] == 3);
    }

    SUBCASE("assignment operator")
    {
        SUBCASE("assign to empty list")
        {
            linked_list<int> list;

            SUBCASE("assign from linked_list")
            {
                list = linked_list{ 4, 5 };

                const auto values = list | std::ranges::to<std::vector>();
                REQUIRE(values.size() == 2);
                REQUIRE(values[0] == 4);
                REQUIRE(values[1] == 5);
            }

            SUBCASE("assign from initializer_list")
            {
                list = { 4, 5 };

                const auto values = list | std::ranges::to<std::vector>();
                REQUIRE(values.size() == 2);
                REQUIRE(values[0] == 4);
                REQUIRE(values[1] == 5);
            }
        }

        SUBCASE("assign to single element list")
        {
            linked_list list{ 1 };

            SUBCASE("assign from linked_list")
            {
                list = linked_list{ 4, 5 };

                const auto values = list | std::ranges::to<std::vector>();
                REQUIRE(values.size() == 2);
                REQUIRE(values[0] == 4);
                REQUIRE(values[1] == 5);
            }

            SUBCASE("assign from initializer_list")
            {
                list = { 4, 5 };

                const auto values = list | std::ranges::to<std::vector>();
                REQUIRE(values.size() == 2);
                REQUIRE(values[0] == 4);
                REQUIRE(values[1] == 5);
            }
        }

        SUBCASE("assign to multi-element list")
        {
            linked_list list{ 1, 2, 3 };

            SUBCASE("assign from linked_list")
            {
                list = linked_list{ 4, 5 };

                const auto values = list | std::ranges::to<std::vector>();
                REQUIRE(values.size() == 2);
                REQUIRE(values[0] == 4);
                REQUIRE(values[1] == 5);
            }

            SUBCASE("assign from initializer_list")
            {
                list = { 4, 5 };

                const auto values = list | std::ranges::to<std::vector>();
                REQUIRE(values.size() == 2);
                REQUIRE(values[0] == 4);
                REQUIRE(values[1] == 5);
            }
        }
    }

    SUBCASE("front")
    {
        linked_list list{ 1, 2, 3 };

        SUBCASE("non-const list")
        {
            REQUIRE(list.front() == 1);
        }

        SUBCASE("const list")
        {
            auto& const_list = std::as_const(list);
            REQUIRE(const_list.front() == 1);
        }
    }

    SUBCASE("begin")
    {
        SUBCASE("empty list")
        {
            linked_list<int> list;

            SUBCASE("non-const list")
            {
                auto pos = list.begin();
                static_assert(std::same_as<decltype(pos),
                    linked_list_iterator<int>>);
                REQUIRE(pos == list.end());
            }

            SUBCASE("const list")
            {
                auto& const_list = std::as_const(list);

                auto pos = const_list.begin();
                static_assert(std::same_as<decltype(pos),
                    linked_list_const_iterator<int>>);
                REQUIRE(pos == const_list.end());

                SUBCASE("cbegin")
                {
                    auto pos = const_list.cbegin();
                    static_assert(std::same_as<decltype(pos),
                        linked_list_const_iterator<int>>);
                    REQUIRE(pos == const_list.end());
                }
            }
        }

        SUBCASE("non-empty list")
        {
            linked_list list{ 1, 2, 3 };

            SUBCASE("non-const list")
            {
                auto pos = list.begin();
                static_assert(std::same_as<decltype(pos),
                    linked_list_iterator<int>>);
                REQUIRE(pos != list.end());
                REQUIRE(*pos == 1);
            }

            SUBCASE("const list")
            {
                auto& const_list = std::as_const(list);

                auto pos = const_list.begin();
                static_assert(std::same_as<decltype(pos),
                    linked_list_const_iterator<int>>);
                REQUIRE(pos != const_list.end());
                REQUIRE(*pos == 1);

                SUBCASE("cbegin")
                {
                    pos = const_list.cbegin();
                    static_assert(std::same_as<decltype(pos),
                        linked_list_const_iterator<int>>);
                    REQUIRE(pos != const_list.end());
                    REQUIRE(*pos == 1);
                }
            }
        }
    }

    SUBCASE("end")
    {
        SUBCASE("empty list")
        {
            linked_list<int> list;

            SUBCASE("non-const list")
            {
                auto pos = list.end();
                static_assert(std::same_as<decltype(pos),
                    linked_list_iterator<int>>);
                REQUIRE(pos == list.end());
            }

            SUBCASE("const list")
            {
                auto& const_list = std::as_const(list);

                auto pos = const_list.end();
                static_assert(std::same_as<decltype(pos),
                    linked_list_const_iterator<int>>);
                REQUIRE(pos == const_list.end());

                SUBCASE("cend")
                {
                    auto pos = const_list.cend();
                    static_assert(std::same_as<decltype(pos),
                        linked_list_const_iterator<int>>);
                    REQUIRE(pos == const_list.end());
                }
            }
        }

        SUBCASE("non-empty list")
        {
            linked_list list{ 1, 2, 3 };

            SUBCASE("non-const list")
            {
                auto pos = list.end();
                static_assert(std::same_as<decltype(pos),
                    linked_list_iterator<int>>);
                REQUIRE(pos == list.end());
            }

            SUBCASE("const list")
            {
                auto& const_list = std::as_const(list);

                auto pos = const_list.end();
                static_assert(std::same_as<decltype(pos),
                    linked_list_const_iterator<int>>);
                REQUIRE(pos == const_list.end());

                SUBCASE("cend")
                {
                    pos = const_list.cend();
                    static_assert(std::same_as<decltype(pos),
                        linked_list_const_iterator<int>>);
                    REQUIRE(pos == const_list.end());
                }
            }
        }
    }

    SUBCASE("empty")
    {
        linked_list<int> list;
        REQUIRE(list.empty() == true);
        
        list.push_front(1);
        REQUIRE(list.empty() == false);
    }

    SUBCASE("size")
    {
        linked_list<int> list;
        REQUIRE(list.size() == 0);

        list.push_front(1);
        REQUIRE(list.size() == 1);

        list.push_front(2);
        REQUIRE(list.size() == 2);

        list.pop_front();    
        REQUIRE(list.size() == 1);

        list.pop_front();    
        REQUIRE(list.size() == 0);
    }

    SUBCASE("clear")
    {
        linked_list list{ 1, 2, 3 };
        list.clear();
        REQUIRE(list.empty());

        list.clear();
        REQUIRE(list.empty());
    }

    SUBCASE("insert")
    {
        SUBCASE("insert into empty list")
        {
            linked_list<int> list;

            SUBCASE("insert at begin")
            {
                list.insert(list.begin(), 1);
                const auto values = list | std::ranges::to<std::vector>();
                REQUIRE(values.size() == 1);
                REQUIRE(values[0] == 1);
            }

            SUBCASE("insert at end")
            {
                list.insert(list.end(), 1);
                const auto values = list | std::ranges::to<std::vector>();
                REQUIRE(values.size() == 1);
                REQUIRE(values[0] == 1);
            }
        }

        SUBCASE("insert into single element list")
        {
            linked_list list{ 1 };

            SUBCASE("insert at begin")
            {
                list.insert(list.begin(), 0);
                const auto values = list | std::ranges::to<std::vector>();
                REQUIRE(values.size() == 2);
                REQUIRE(values[0] == 0);
                REQUIRE(values[1] == 1);
            }

            SUBCASE("insert at end")
            {
                list.insert(list.end(), 0);
                const auto values = list | std::ranges::to<std::vector>();
                REQUIRE(values.size() == 2);
                REQUIRE(values[0] == 1);
                REQUIRE(values[1] == 0);
            }
        }

        SUBCASE("insert into non-empty list")
        {
            linked_list list{ 1, 2, 3 };

            SUBCASE("insert 0 at front")
            {
                list.insert(list.begin(), 0);

                const auto values = list | std::ranges::to<std::vector>();
                REQUIRE(values.size() == 4);
                REQUIRE(values[0] == 0);
                REQUIRE(values[1] == 1);
                REQUIRE(values[2] == 2);
                REQUIRE(values[3] == 3);
            }

            SUBCASE("insert 4 at end")
            {
                list.insert(list.end(), 4);

                const auto values = list | std::ranges::to<std::vector>();
                REQUIRE(values.size() == 4);
                REQUIRE(values[0] == 1);
                REQUIRE(values[1] == 2);
                REQUIRE(values[2] == 3);
                REQUIRE(values[3] == 4);
            }

            SUBCASE("insert 5 at begin() + 2")
            {
                list.insert(std::next(list.begin(), 2), 5);

                const auto values = list | std::ranges::to<std::vector>();
                REQUIRE(values.size() == 4);
                REQUIRE(values[0] == 1);
                REQUIRE(values[1] == 2);
                REQUIRE(values[2] == 5);
                REQUIRE(values[3] == 3);
            }
        }
    }

    SUBCASE("erase")
    {
        SUBCASE("erase from single element list")
        {
            linked_list list{ 1 };
            list.erase(list.begin());
            REQUIRE(list.empty());
        }

        SUBCASE("erase from multi-element list")
        {
            linked_list list{ 1, 2, 3 };

            SUBCASE("erase from front")
            {
                list.erase(list.begin());

                const auto values = list | std::ranges::to<std::vector>();
                REQUIRE(values.size() == 2);
                REQUIRE(values[0] == 2);
                REQUIRE(values[1] == 3);
            }

            SUBCASE("erase from middle")
            {
                list.erase(std::next(list.begin()));

                const auto values = list | std::ranges::to<std::vector>();
                REQUIRE(values.size() == 2);
                REQUIRE(values[0] == 1);
                REQUIRE(values[1] == 3);
            }

            SUBCASE("erase from end")
            {
                list.erase(std::next(list.begin(), 2));

                const auto values = list | std::ranges::to<std::vector>();
                REQUIRE(values.size() == 2);
                REQUIRE(values[0] == 1);
                REQUIRE(values[1] == 2);
            }
        }
    }

    SUBCASE("push_front")
    {
        SUBCASE("push to empty list")
        {
            linked_list<int> list;
            list.push_front(1);
            REQUIRE(list.size() == 1);
            REQUIRE(list.front() == 1);
        }

        SUBCASE("push to single element list")
        {
            linked_list list{ 1 };
            list.push_front(0);

            const auto values = list | std::ranges::to<std::vector>();
            REQUIRE(values.size() == 2);
            REQUIRE(values[0] == 0);
            REQUIRE(values[1] == 1);
        }

        SUBCASE("push to multi-empty list")
        {
            linked_list list{ 1, 2, 3 };
            list.push_front(0);

            const auto values = list | std::ranges::to<std::vector>();
            REQUIRE(values.size() == 4);
            REQUIRE(values[0] == 0);
            REQUIRE(values[1] == 1);
            REQUIRE(values[2] == 2);
            REQUIRE(values[3] == 3);
        }
    }

    SUBCASE("pop_front")
    {
        SUBCASE("pop from single element list")
        {
            linked_list list{ 1 };
            list.pop_front();
            REQUIRE(list.empty());
        }

        SUBCASE("pop from multi-element list")
        {
            linked_list list{ 1, 2, 3 };
            list.pop_front();

            const auto values = list | std::ranges::to<std::vector>();
            REQUIRE(values.size() == 2);
            REQUIRE(values[0] == 2);
            REQUIRE(values[1] == 3);
        }
    }

    SUBCASE("equality operator")
    {
        linked_list list{ 1, 2, 3 };

        const std::array test_values =
        {
            std::make_tuple(linked_list<int>{ }, false),
            std::make_tuple(linked_list<int>{ 1 }, false),
            std::make_tuple(linked_list<int>{ 1, 2 }, false),
            std::make_tuple(linked_list<int>{ 1, 2, 3 }, true),
            std::make_tuple(linked_list<int>{ 1, 2, 3, 4 }, false)
        };

        for (int i = 0; const auto& [ other, expected ] : test_values)
        {
            CAPTURE(i);
            REQUIRE((list == other) == expected);
            ++i;
        }
    }

    SUBCASE("three-way comparison operator")
    {
        const linked_list list = { 1, 3, 5 };

        const std::vector<std::tuple<decltype(list), std::strong_ordering>> tests =
        {
            { { }, std::strong_ordering::greater },
            { { 0 }, std::strong_ordering::greater },
            { { 1 }, std::strong_ordering::greater },
            { { 2 }, std::strong_ordering::less },
            { { 0, 3 }, std::strong_ordering::greater },
            { { 1, 2 }, std::strong_ordering::greater },
            { { 1, 3 }, std::strong_ordering::greater },
            { { 1, 4 }, std::strong_ordering::less },
            { { 2, 3 }, std::strong_ordering::less },
            { { 0, 3, 5 }, std::strong_ordering::greater },
            { { 1, 2, 5 }, std::strong_ordering::greater },
            { { 1, 3, 4 }, std::strong_ordering::greater },
            { { 1, 3, 5 }, std::strong_ordering::equal },
            { { 1, 3, 6 }, std::strong_ordering::less },
            { { 1, 4, 5 }, std::strong_ordering::less },
            { { 2, 3, 5 }, std::strong_ordering::less },
            { { 0, 3, 5, 0 }, std::strong_ordering::greater },
            { { 1, 2, 5, 0 }, std::strong_ordering::greater },
            { { 1, 3, 4, 0 }, std::strong_ordering::greater },
            { { 1, 3, 5, 0 }, std::strong_ordering::less },
            { { 1, 3, 6, 0 }, std::strong_ordering::less },
            { { 1, 4, 5, 0 }, std::strong_ordering::less },
            { { 2, 3, 5, 0 }, std::strong_ordering::less }
        };

        for (int i = 0; const auto& [test_value, expected] : tests)
        {
            CAPTURE(i);

            const auto result = (list <=> test_value);
            REQUIRE(result == expected);
            i++;
        }
    }
}