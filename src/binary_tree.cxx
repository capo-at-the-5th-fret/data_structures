export module data_structures:binary_tree;

import std;

namespace caff
{
    export template <typename T>
    struct binary_tree_node
    {
        T value{};
        binary_tree_node* left{ nullptr };
        binary_tree_node* right{ nullptr };
    };

    export template <typename T>
    class in_order_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const value_type*;
        using reference = const value_type&;
        using node = binary_tree_node<value_type>;

        explicit in_order_iterator(node* n = nullptr)
        {
            push_leftmost(n);
        }

        reference operator*() const
        {
            return stack_.top()->value;
        }

        pointer operator->() const
        {
            return std::addressof(stack_.top()->value);
        }

        in_order_iterator& operator++()
        {
            node* current = stack_.top();
            stack_.pop();

            if (current->right != nullptr)
            {
                push_leftmost(current->right);
            }

            return *this;
        }

        in_order_iterator operator++(int)
        {
            in_order_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const in_order_iterator& rhs) const = default;

    private:
        void push_leftmost(node* n)
        {
            while (n != nullptr)
            {
                stack_.push(n);
                n = n->left;
            }
        }

        std::stack<node*> stack_;
    };

    export template <typename T>
    class pre_order_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;
        using node = binary_tree_node<value_type>;

        explicit pre_order_iterator(node* n = nullptr)
        {
            if (n != nullptr)
            {
                stack_.push(n);
            }
        }

        reference operator*() const
        {
            return stack_.top()->value;
        }

        pointer operator->() const
        {
            return std::addressof(stack_.top()->value);
        }

        pre_order_iterator& operator++()
        {
            node* current = stack_.top();
            stack_.pop();

            if (current->right != nullptr)
            {
                stack_.push(current->right);
            }

            if (current->left != nullptr)
            {
                stack_.push(current->left);
            }

            return *this;
        }

        pre_order_iterator operator++(int)
        {
            pre_order_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const pre_order_iterator& rhs) const = default;

    private:
        std::stack<node*> stack_;
    };

    export template <typename T>
    class post_order_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        using node = binary_tree_node<value_type>;

        explicit post_order_iterator(node* n = nullptr)
        {
            push_leftmost(n);
        }

        reference operator*() const
        {
            return stack_.top()->value;
        }

        pointer operator->() const
        {
            return std::addressof(stack_.top()->value);
        }

        post_order_iterator& operator++()
        {
            node* current = stack_.top();
            stack_.pop();

            if (!stack_.empty() && (stack_.top()->left == current))
            {
                push_leftmost(stack_.top()->right);
            }

            return *this;
        }

        post_order_iterator operator++(int)
        {
            post_order_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const post_order_iterator& rhs) const = default;

    private:
        void push_leftmost(node* n)
        {
            while (n != nullptr)
            {
                stack_.push(n);

                if (n->left != nullptr)
                {
                    n = n->left;
                }
                else
                {
                    n = n->right;
                }
            }
        }

        std::stack<node*> stack_;
    };

    export template <typename T>
    class level_order_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        using node = binary_tree_node<value_type>;

        explicit level_order_iterator(node* n = nullptr)
        {
            if (n != nullptr)
            {
                queue_.push(n);
            }
        }

        reference operator*() const
        {
            return queue_.front()->value;
        }

        pointer operator->() const
        {
            return std::addressof(queue_.front()->value);
        }

        level_order_iterator& operator++()
        {
            node* current = queue_.front();
            queue_.pop();

            if (current->left != nullptr)
            {
                queue_.push(current->left);
            }

            if (current->right != nullptr)
            {
                queue_.push(current->right);
            }

            return *this;
        }

        level_order_iterator operator++(int)
        {
            level_order_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const level_order_iterator& rhs) const = default;

    private:
        std::queue<node*> queue_;
    };

    static_assert(std::forward_iterator<in_order_iterator<int>>);
    static_assert(std::forward_iterator<pre_order_iterator<int>>);
    static_assert(std::forward_iterator<post_order_iterator<int>>);
    static_assert(std::forward_iterator<level_order_iterator<int>>);

    export template<typename T>
    class binary_tree
    {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using referernce = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator = in_order_iterator<T>;
        //using const_iterator = in_order_iterator<binary_tree_node<T>>;
        //using reverse_iterator = std::reverse_iterator<iterator>;
        //using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        using node = binary_tree_node<T>;

        binary_tree() = default;

        binary_tree(std::initializer_list<T> values)
        {
            for (const T& value : values)
            {
                insert(value);
            }
        }

        binary_tree(const binary_tree& other) : size_{ other.size_ }
        {
            if (other.root_)
            {
                root_ = copy_nodes(other.root_);
            }
        }

        ~binary_tree()
        {
            clear();
        }

        binary_tree& operator=(const binary_tree& other)
        {
            if (this != &other)
            {
                clear_nodes(root_);
                size_ = other.size_;
                if (other.root_)
                {
                    root_ = copy_nodes(other.root_);
                }
                else
                {
                    root_ = nullptr;
                }
            }
            return *this;
        }

        friend bool operator==(const binary_tree& lhs, const binary_tree& rhs)
        {
            if (lhs.size_ != rhs.size_)
            {
                return false;
            }
            return compare_trees(lhs.root_, rhs.root_);
        }

        auto begin()
        {
            return iterator{ root_ };
        }

        auto begin() const
        {
            return iterator{ root_ };
        }

        auto end()
        {
            return iterator{ };
        }

        auto end() const
        {
            return iterator{ };
        }

        bool empty() const
        {
            return size_ == 0;
        }

        size_type size() const
        {
            return size_;
        }

        size_type height() const
        {
            return calculate_height(root_);
        }

        void clear()
        {
            clear_nodes(root_);
            root_ = nullptr;
            size_ = 0;
        }

        void insert(const T& value)
        {
            if (root_ == nullptr)
            {
                root_ = new node{ value };
            }
            else
            {
                insert_node(root_, value);
            }
            ++size_;
        }

        auto in_order() const
        {
            return std::ranges::subrange(in_order_iterator<T>{ root_ },
                in_order_iterator<T>{});
        }

        auto pre_order() const
        {
            return std::ranges::subrange(pre_order_iterator<T>{ root_ },
                pre_order_iterator<T>{});
        }

        auto post_order() const
        {
            return std::ranges::subrange(post_order_iterator<T>{ root_ },
                post_order_iterator<T>{});
        }

        auto level_order() const
        {
            return std::ranges::subrange(level_order_iterator<T>{ root_ },
                level_order_iterator<T>{});
        }

    private:
        static bool compare_trees(node* lhs, node* rhs)
        {
            if (lhs == nullptr && rhs == nullptr)
            {
                return true;
            }

            if (lhs == nullptr || rhs == nullptr)
            {
                return false;
            }

            if (lhs->value != rhs->value)
            {
                return false;
            }

            return compare_trees(lhs->left, rhs->left) &&
                compare_trees(lhs->right, rhs->right);
        }

        static void insert_node(node* current, const T& value)
        {
            if (value < current->value)
            {
                if (current->left == nullptr)
                {
                    current->left = new node{ value };
                }
                else
                {
                    insert_node(current->left, value);
                }
            }
            else
            {
                if (current->right == nullptr)
                {
                    current->right = new node{ value };
                }
                else
                {
                    insert_node(current->right, value);
                }
            }
        }

        static node* copy_nodes(node* current)
        {
            if (current == nullptr)
            {
                return nullptr;
            }

            node* new_node = new node{ current->value };
            new_node->left = copy_nodes(current->left);
            new_node->right = copy_nodes(current->right);
            return new_node;
        }

        static void clear_nodes(node* current)
        {
            if (current != nullptr)
            {
                clear_nodes(current->left);
                clear_nodes(current->right);
                delete current;
            }
        }

        static std::size_t calculate_height(node* current)
        {
            if (current == nullptr)
            {
                return 0;
            }
            auto left_height = calculate_height(current->left);
            auto right_height = calculate_height(current->right);
            return std::max(left_height, right_height) + 1;
        }

        node* root_{ nullptr };
        std::size_t size_{ 0 };
    };
}
