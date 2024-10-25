#include <doctest/doctest.h>
import data_structures;

TEST_CASE("binary_tree_node")
{
    using namespace caff;

    SUBCASE("default constructor")
    {
        binary_tree_node<int> n;

        REQUIRE(n.value == 0);
        REQUIRE(n.left == nullptr);
        REQUIRE(n.right == nullptr);
    }
}

TEST_CASE("binary_tree")
{
    using namespace caff;

    SUBCASE("member types")
    {
        using test_type = binary_tree<int>;

        static_assert(std::is_same_v<test_type::value_type, int>);
        static_assert(std::is_same_v<test_type::size_type, std::size_t>);
        static_assert(std::is_same_v<test_type::difference_type, std::ptrdiff_t>);
        static_assert(std::is_same_v<test_type::referernce, int&>);
        static_assert(std::is_same_v<test_type::const_reference, const int&>);
        static_assert(std::is_same_v<test_type::pointer, int*>);
        static_assert(std::is_same_v<test_type::const_pointer, const int*>);
        static_assert(std::is_same_v<test_type::iterator, in_order_iterator<int>>);
    }

    SUBCASE("default constructor")
    {
        binary_tree<int> tree;
        REQUIRE(tree.empty());
        REQUIRE(tree.size() == 0);
    }

    SUBCASE("initializer_list constructor")
    {
        const binary_tree tree{ 4, 2, 6, 1, 3, 5, 7 };

        REQUIRE(tree.size() == 7);

        const auto values = tree | std::ranges::to<std::vector>();
        REQUIRE(values.size() == 7);
        REQUIRE(values[0] == 1);
        REQUIRE(values[1] == 2);
        REQUIRE(values[2] == 3);
        REQUIRE(values[3] == 4);
        REQUIRE(values[4] == 5);
        REQUIRE(values[5] == 6);
        REQUIRE(values[6] == 7);
    }

    SUBCASE("copy structure")
    {   
        const binary_tree other{ 4, 2, 6, 1, 3, 5, 7 };
        const binary_tree tree{ other };

        const auto values = tree | std::ranges::to<std::vector>();
        REQUIRE(values.size() == 7);
        REQUIRE(values[0] == 1);
        REQUIRE(values[1] == 2);
        REQUIRE(values[2] == 3);
        REQUIRE(values[3] == 4);
        REQUIRE(values[4] == 5);
        REQUIRE(values[5] == 6);
        REQUIRE(values[6] == 7);
    }

    SUBCASE("assignment operator")
    {
        const binary_tree other{ 3, 5, 4 };
        binary_tree tree{ 4, 2, 6, 1, 3, 5, 7 };

        tree = other;

        const auto values = tree | std::ranges::to<std::vector>();
        REQUIRE(values.size() == 3);
        REQUIRE(values[0] == 3);
        REQUIRE(values[1] == 4);
        REQUIRE(values[2] == 5);
    }

    SUBCASE("equality operator")
    {
        binary_tree tree{ 4, 2, 6, 1, 3, 5, 7 };

        std::array test_values =
        {
            std::make_tuple(binary_tree<int>{ }, false),
            std::make_tuple(binary_tree<int>{ 1 }, false),
            std::make_tuple(binary_tree<int>{ 2, 4, 6, 1, 3, 5, 7 }, false),
            std::make_tuple(binary_tree<int>{ 4, 2, 6, 1, 3, 5, 7 }, true),
            std::make_tuple(binary_tree<int>{ 4, 2, 6, 1, 3, 5, 7, 8 }, false)
        };

        for (int i = 0; const auto& [ other, expected ] : test_values)
        {
            CAPTURE(i);
            REQUIRE((tree == other) == expected);
            ++i;
        }
    }

    SUBCASE("empty")
    {
        binary_tree<int> tree;
        REQUIRE(tree.empty() == true);
        
        tree.insert(1);
        REQUIRE(tree.empty() == false);
    }

    SUBCASE("size")
    {
        binary_tree<int> tree;
        REQUIRE(tree.size() == 0);
        
        tree.insert(1);
        REQUIRE(tree.size() == 1);

        tree.insert(2);
        REQUIRE(tree.size() == 2);

        tree.insert(3);
        REQUIRE(tree.size() == 3);
    }

    SUBCASE("height")
    {
        const std::array test_values =
        {
            std::make_tuple(binary_tree<int>{ }, std::size_t{ 0 }),
            std::make_tuple(binary_tree<int>{ 1 }, std::size_t{ 1 }),
            std::make_tuple(binary_tree<int>{ 2, 1 }, std::size_t{ 2 }),
            std::make_tuple(binary_tree<int>{ 2, 3 }, std::size_t{ 2 }),
            std::make_tuple(binary_tree<int>{ 2, 1, 3 }, std::size_t{ 2 }),
            std::make_tuple(binary_tree<int>{ 1, 2, 3, 4, 5 }, std::size_t{ 5 })
        };

        for (int i = 0;const auto& [ tree, expected_height ] : test_values)
        {
            CAPTURE(i);
            REQUIRE(tree.height() == expected_height);
            ++i;
        }
    }

    SUBCASE("clear")
    {
        binary_tree tree{ 4, 2, 6, 1, 3, 5, 7 };
        tree.clear();
        REQUIRE(tree.empty());

        tree.clear();
        REQUIRE(tree.empty());
    }

    SUBCASE("traversal order")
    {
        // For the binary tree:
        //      10
        //     /  \
        //    5    15
        //   / \   /
        //  3   7 12
        // In-Order: 3, 5, 7, 10, 12, 15
        // Pre-Order: 10, 5, 3, 7, 15, 12
        // Post-Order: 3, 7, 5, 12, 15, 10
        // Level-Order: 10, 5, 15, 3, 7, 12

        const binary_tree tree{ 10, 5, 15, 3, 7, 12 };

        SUBCASE("in-order")
        {
            const std::array expected{ 3, 5, 7, 10, 12, 15 };
            
            auto actual = tree.in_order() | std::ranges::to<std::vector>();
            REQUIRE(std::ranges::equal(actual, expected));
        }

        SUBCASE("pre-order")
        {
            const std::array expected{ 10, 5, 3, 7, 15, 12 };
            
            auto actual = tree.pre_order() | std::ranges::to<std::vector>();
            REQUIRE(std::ranges::equal(actual, expected));
        }

        SUBCASE("post-order")
        {
            const std::array expected{ 3, 7, 5, 12, 15, 10 };
            
            auto actual = tree.post_order() | std::ranges::to<std::vector>();
            REQUIRE(std::ranges::equal(actual, expected));
        }

        SUBCASE("level-order")
        {
            const std::array expected{ 10, 5, 15, 3, 7, 12 };
            
            auto actual = tree.level_order() | std::ranges::to<std::vector>();
            REQUIRE(std::ranges::equal(actual, expected));
        }
    }
}