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
    for (auto const& v : bt)
    {
        std::print("{} ", v);
    }
    std::println();

    std::print("standard reverse traversal: ");
    for (auto const& v : bt)
    {
        std::print("{} ", v);
    }
    std::println();

    std::print("In-order traversal: ");
    for (auto const& v : bt.in_order())
    {
        std::print("{} ", v);
    }
    std::println();

    std::print("Pre-order traversal: ");
    for (auto const& v : bt.pre_order())
    {
        std::print("{} ", v);
    }
    std::println();

    std::print("Post-order traversal: ");
    for (auto const& v : bt.post_order())
    {
        std::print("{} ", v);
    }
    std::println();

    std::print("Level-order traversal: ");
    for (auto const& v : bt.level_order())
    {
        std::print("{} ", v);
    }
    std::println();
}

int main2()
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

    binary_tree<int> tree{10, 5, 15, 3, 7, 12};

    std::cout << "In-Order Traversal: ";
    for (const auto& value : tree.in_order())
    {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    std::cout << "Pre-Order Traversal: ";
    for (const auto& value : tree.pre_order())
    {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    std::cout << "Post-Order Traversal: ";
    for (const auto& value : tree.post_order())
    {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    std::cout << "Level-Order Traversal: ";
    for (const auto& value : tree.level_order())
    {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    return 0;
}

#if 0
int main()
{
    rope r1("Hello, ");
    rope r2("World!");

    r1.concatenate(r2);
    std::println("Rope length: {}", r1.length());
    std::println("Rope size: {}", r1.size());

    std::println("{}", r1);
    std::println();
}
#endif

#if 0
template <typename T, std::size_t N>
class inplace_vector_iterator
{
public:
    //using iterator_concept = std::contiguous_iterator_tag;
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;

    inplace_vector_iterator() = default;
    explicit inplace_vector_iterator(pointer ptr, std::size_t offset = 0) :
        ptr_(ptr + offset)
    {
    }

    reference operator*() const
    {
        return *ptr_;
    }

    pointer operator->() const
    {
        return ptr_;
    }

    inplace_vector_iterator& operator++()
    {
        ++ptr_;
        return *this;
    }

    inplace_vector_iterator operator++(int)
    {
        inplace_vector_iterator tmp = *this;
        ++ptr_;
        return tmp;
    }

    inplace_vector_iterator& operator--()
    {
        --ptr_;
        return *this;
    }

    inplace_vector_iterator operator--(int)
    {
        inplace_vector_iterator tmp = *this;
        --ptr_;
        return tmp;
    }

    inplace_vector_iterator& operator+=(const difference_type offset)
    {
        ptr_ += offset;
        return *this;
    }

    difference_type operator+(const inplace_vector_iterator& other) const
    {
        return ptr_ + other.ptr_;
    }

    inplace_vector_iterator& operator-=(const difference_type offset)
    {
        ptr_ -= offset;
        return *this;
    }

    difference_type operator-(const inplace_vector_iterator& other) const
    {
        return ptr_ - other.ptr_;
    }

    reference operator[](const difference_type offset) const
    {
        return ptr_[offset];
    }

    bool operator==(const inplace_vector_iterator& other) const = default;
    auto operator<=>(const inplace_vector_iterator& other) const = default;

private:
    pointer ptr_{ nullptr };
};

//static_assert(std::bidirectional_iterator<inplace_vector_iterator<int, 10>>);
static_assert(std::same_as<std::iter_difference_t<inplace_vector_iterator<int, 10>>, std::ptrdiff_t>);

requires(I i, const I j, const std::iter_difference_t<I> n) {
            { i += n } -> std::same_as<I&>;
            { j +  n } -> std::same_as<I>;
            { n +  j } -> std::same_as<I>;
            { i -= n } -> std::same_as<I&>;
            { j -  n } -> std::same_as<I>;
            {  j[n]  } -> std::same_as<std::iter_reference_t<I>>;

        };

//static_assert(std::random_access_iterator<inplace_vector_iterator<int, 10>>);

class sub
{
public:
    using data_type = std::array<int, 2>;
    using T = int;
    //using iterator = data_type::iterator;

    using iterator = inplace_vector_iterator<T, 2>;
    using reverse_iterator = std::reverse_iterator<iterator>;

    iterator begin() { return iterator{ &data_[0] }; }
    iterator end() { return iterator{ &data_[2] }; }

    //reverse_iterator rbegin() { return std::reverse_iterator(end()); }
    //reverse_iterator rend() { return std::reverse_iterator(begin()); }

private:
    int data_[2] = { 1, 2 };
};
#endif

#if 0
int main()
{
    std::array arr{ 1, 2, 3, 4, 5, 6, 7 };
    auto* p = &arr[3];
    std::println("p[3] -> {}", p[-1]);

    auto pos = std::next(arr.begin(), 3);
    std::println("begin + 3 -> {}", *pos);

    auto pos2 = pos[2];
    std::println("pos[2] -> {}", pos2);

    auto pos3 = pos[-1];
    std::println("pos[-1] -> {}", pos3);

    return 0;

    return 0;
    inplace_vector<int, 10> v{ 1, 2, 3 };

    for (auto pos = v.rbegin(); pos != v.rend(); ++pos)
    {
        std::println("{}", *pos);
    }

    return 0; 
}
#endif

#if 0
    struct Iterator
    {
        // Iterator tags here...
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;    
        using reference = value_type&;

        Iterator() = default;
        explicit Iterator(pointer ptr) : m_ptr(ptr) {}
        // Iterator constructors here...

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        // Prefix increment
        Iterator& operator++() { m_ptr++; return *this; }  

        // Postfix increment
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };     

    private:
        pointer m_ptr{ nullptr };
    };
    using Reverse_Iterator = std::reverse_iterator<Iterator>;

    class iterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        iterator() = default;
        explicit iterator(pointer ptr) : ptr_(ptr) {}

        reference operator*() { return *ptr_; }
        pointer operator->() { return ptr_; }

        iterator& operator++() { ++ptr_; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++ptr_; return tmp; }

        iterator& operator--() { --ptr_; return *this; }
        iterator operator--(int) { iterator tmp = *this; --ptr_; return tmp; }

        /*iterator& operator+=(difference_type n) { ptr_ += n; return *this; }
        iterator& operator-=(difference_type n) { ptr_ -= n; return *this; }

        iterator operator+(difference_type n) const { return iterator(ptr_ + n); }
        iterator operator-(difference_type n) const { return iterator(ptr_ - n); }

        difference_type operator-(const iterator& other) const { return ptr_ - other.ptr_; }*/

        reference operator[](difference_type n) { return *(ptr_ + n); }

        bool operator==(const iterator& other) const = default;
        //auto operator<=>(const iterator& other) const = default;

    private:
        pointer ptr_{ nullptr };
    };
#endif
