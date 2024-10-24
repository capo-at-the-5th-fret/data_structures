import std;
import data_structures;

using namespace caff;

int main()
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

    binary_tree bt{10, 5, 15, 3, 7, 12};
    static_assert(std::same_as<decltype(bt), binary_tree<int>>);

    std::print("standard traversal: ");
    std::println("{}", bt);

    std::print("In-order traversal: ");
    std::println("{}", bt.in_order());

    std::print("Pre-order traversal: ");
    std::println("{}", bt.pre_order());

    std::print("Post-order traversal: ");
    std::println("{}", bt.post_order());

    std::print("Level-order traversal: ");
    std::println("{}", bt.level_order());
}
