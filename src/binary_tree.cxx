export module data_structures:binary_tree;

import std;

namespace caff
{
    template <typename T>
    struct binary_tree_node
    {
        T value{};
        binary_tree_node* left{ nullptr };
        binary_tree_node* right{ nullptr };
    };

    template <typename T>
    class in_order_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        using node = binary_tree_node<T>;

        explicit in_order_iterator(node* root = nullptr)
        {
            push_leftmost(root);
        }

        reference operator*() const
        {
            return stack_.top()->value;
        }

        pointer operator->() const
        {
            return &stack_.top()->value;
        }

        in_order_iterator& operator++()
        {
            node* current = stack_.top();
            stack_.pop();
            if (current->right)
            {
                push_leftmost(current->right);
            }
            return *this;
        }

        in_order_iterator operator++(int)
        {
            in_order_iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const in_order_iterator&) const = default;

    private:
        void push_leftmost(node* root)
        {
            while (root)
            {
                stack_.push(root);
                root = root->left;
            }
        }

        std::stack<node*> stack_;
    };

    template <typename T>
    class pre_order_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        using node = binary_tree_node<T>;

        explicit pre_order_iterator(node* root = nullptr)
        {
            if (root)
            {
                stack_.push(root);
            }
        }

        reference operator*() const
        {
            return stack_.top()->value;
        }

        pointer operator->() const
        {
            return &stack_.top()->value;
        }

        pre_order_iterator& operator++()
        {
            node* current = stack_.top();
            stack_.pop();
            if (current->right)
            {
                stack_.push(current->right);
            }
            if (current->left)
            {
                stack_.push(current->left);
            }
            return *this;
        }

        pre_order_iterator operator++(int)
        {
            pre_order_iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const pre_order_iterator&) const = default;

    private:
        std::stack<node*> stack_;
    };

    template <typename T>
    class post_order_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        using node = binary_tree_node<T>;

        explicit post_order_iterator(node* root = nullptr)
        {
            push_leftmost(root);
        }

        reference operator*() const
        {
            return stack_.top()->value;
        }

        pointer operator->() const
        {
            return &stack_.top()->value;
        }

        post_order_iterator& operator++()
        {
            node* current = stack_.top();
            stack_.pop();

            if (!stack_.empty() && stack_.top()->left == current)
            {
                push_leftmost(stack_.top()->right);
            }

            return *this;
        }

        post_order_iterator operator++(int)
        {
            post_order_iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const post_order_iterator&) const = default;

    private:
        std::stack<node*> stack_;

        void push_leftmost(node* root)
        {
            while (root)
            {
                stack_.push(root);
                if (root->left)
                {
                    root = root->left;
                }
                else
                {
                    root = root->right;
                }
            }
        }
    };

    template <typename T>
    class level_order_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        using node = binary_tree_node<T>;

        explicit level_order_iterator(node* root = nullptr)
        {
            if (root)
            {
                queue_.push(root);
            }
        }

        reference operator*() const
        {
            return queue_.front()->value;
        }

        pointer operator->() const
        {
            return &queue_.front()->value;
        }

        level_order_iterator& operator++()
        {
            node* current = queue_.front();
            queue_.pop();
            if (current->left)
            {
                queue_.push(current->left);
            }
            if (current->right)
            {
                queue_.push(current->right);
            }
            return *this;
        }

        level_order_iterator operator++(int)
        {
            level_order_iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const level_order_iterator&) const = default;

    private:
        std::queue<node*> queue_;
    };

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
        using reverse_iterator = std::reverse_iterator<iterator>;

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

        friend bool operator==(const binary_tree& lhs, const binary_tree& rhs);

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
        void insert_node(node* current, const T& value)
        {
            if (value < current->value)
            {
                if (!current->left)
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
                if (!current->right)
                {
                    current->right = new node{ value };
                }
                else
                {
                    insert_node(current->right, value);
                }
            }
        }

        node* copy_nodes(node* current)
        {
            if (!current)
            {
                return nullptr;
            }

            node* new_node = new node{ current->value };
            new_node->left = copy_nodes(current->left);
            new_node->right = copy_nodes(current->right);
            return new_node;
        }

        void clear_nodes(node* current)
        {
            if (current)
            {
                clear_nodes(current->left);
                clear_nodes(current->right);
                delete current;
            }
        }

        std::size_t calculate_height(node* current) const
        {
            if (!current)
            {
                return 0;
            }
            std::size_t left_height = calculate_height(current->left);
            std::size_t right_height = calculate_height(current->right);
            return std::max(left_height, right_height) + 1;
        }

        node* root_{ nullptr };
        std::size_t size_{ 0 };
    };

    template <typename T>
    bool operator==(const binary_tree<T>& lhs, const binary_tree<T>& rhs)
    {
        if (lhs.size_ != rhs.size_)
        {
            return false;
        }
        return compare_trees(lhs.root_, rhs.root_);
    }
}

template<typename T, typename CharT>
struct std::formatter<caff::binary_tree<T>, CharT>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const caff::binary_tree<T>& tree, FormatContext& ctx) const
    {
        // TODO: Use range formatter?
        auto out = ctx.out();
        out = std::format_to(out, "[");

        if (auto pos = tree.begin(); pos != tree.end())
        {
            out = std::format_to(out, "{}", *pos);
            ++pos;

            for (; pos != tree.end(); ++pos)
            {
                out = std::format_to(out, ", {}", *pos);
            }
        }

        return std::format_to(out, "]");
    }
};
    
#if 0
    template <typename T>
    class binary_tree
    {
    public:
        binary_tree() = default;

        explicit binary_tree(const T& value)
            : root_{new node{value}}, size_{1}
        {
        }

        binary_tree(std::initializer_list<T> values)
            : binary_tree()
        {
            for (const auto& value : values)
            {
                insert(value);
            }
        }

        ~binary_tree()
        {
            clear(root_);
        }

        void insert(const T& value)
        {
            if (root_ == nullptr)
            {
                root_ = new node{value};
                size_ = 1;
            }
            else
            {
                insert(value, root_);
                ++size_;
            }
        }

        std::size_t size() const
        {
            return size_;
        }

        class in_order_iterator;
        class pre_order_iterator;
        class post_order_iterator;
        class level_order_iterator;

        in_order_iterator begin_in_order() const
        {
            return in_order_iterator(root_);
        }

        in_order_iterator end_in_order() const
        {
            return in_order_iterator(nullptr);
        }

        pre_order_iterator begin_pre_order() const
        {
            return pre_order_iterator(root_);
        }

        pre_order_iterator end_pre_order() const
        {
            return pre_order_iterator(nullptr);
        }

        post_order_iterator begin_post_order() const
        {
            return post_order_iterator(root_);
        }

        post_order_iterator end_post_order() const
        {
            return post_order_iterator(nullptr);
        }

        level_order_iterator begin_level_order() const
        {
            return level_order_iterator(root_);
        }

        level_order_iterator end_level_order() const
        {
            return level_order_iterator(nullptr);
        }

        auto pre_order() const
        {
            return std::ranges::subrange(begin_pre_order(), end_pre_order());
        }

        auto in_order() const
        {
            return std::ranges::subrange(begin_in_order(), end_in_order());
        }

        auto post_order() const
        {
            return std::ranges::subrange(begin_post_order(), end_post_order());
        }

        auto level_order() const
        {
            return std::ranges::subrange(begin_level_order(), end_level_order());
        }

    private:
        struct node
        {
            T value_;
            node* left_{nullptr};
            node* right_{nullptr};
        };

        void insert(const T& value, node* current)
        {
            if (value < current->value_)
            {
                if (current->left_)
                {
                    insert(value, current->left_);
                }
                else
                {
                    current->left_ = new node{value};
                }
            }
            else
            {
                if (current->right_)
                {
                    insert(value, current->right_);
                }
                else
                {
                    current->right_ = new node{value};
                }
            }
        }

        void clear(node* current)
        {
            if (current)
            {
                clear(current->left_);
                clear(current->right_);
                delete current;
            }
        }

        node* root_{nullptr};
        std::size_t size_{0};

    public:
        class in_order_iterator
        {
        public:
            using iterator_category = std::input_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = const T*;
            using reference = const T&;

            explicit in_order_iterator(node* root = nullptr)
            {
                while (root)
                {
                    stack_.push(root);
                    root = root->left_;
                }
            }

            reference operator*() const
            {
                return stack_.top()->value_;
            }

            pointer operator->() const
            {
                return &stack_.top()->value_;
            }

            in_order_iterator& operator++()
            {
                node* current = stack_.top();
                stack_.pop();
                if (current->right_)
                {
                    current = current->right_;
                    while (current)
                    {
                        stack_.push(current);
                        current = current->left_;
                    }
                }
                return *this;
            }

            in_order_iterator operator++(int)
            {
                in_order_iterator temp = *this;
                ++(*this);  // Use prefix version to advance
                return temp;
            }

            bool operator==(const in_order_iterator& other) const = default;

        private:
            std::stack<node*> stack_;
        };

        static_assert(std::input_iterator<in_order_iterator>);

        class pre_order_iterator
        {
        public:
            using iterator_category = std::input_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = const T*;
            using reference = const T&;

            explicit pre_order_iterator(node* root = nullptr)
            {
                if (root)
                {
                    stack_.push(root);
                }
            }

            reference operator*() const
            {
                return stack_.top()->value_;
            }

            pointer operator->() const
            {
                return &stack_.top()->value_;
            }

            pre_order_iterator& operator++()
            {
                node* current = stack_.top();
                stack_.pop();
                if (current->right_)
                {
                    stack_.push(current->right_);
                }
                if (current->left_)
                {
                    stack_.push(current->left_);
                }
                return *this;
            }

            pre_order_iterator operator++(int)
            {
                pre_order_iterator temp = *this;
                ++(*this);
                return temp;
            }

            bool operator==(const pre_order_iterator& other) const = default;

        private:
            std::stack<node*> stack_;
        };

        static_assert(std::input_iterator<pre_order_iterator>);

        class post_order_iterator
        {
        public:
            using iterator_category = std::input_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;

            post_order_iterator(node* root)
            {
                if (root) stack_.push(root);
            }

            reference operator*()
            {
                return stack_.top()->value_;
            }

            post_order_iterator& operator++()
            {
                if (stack_.empty()) return *this;

                node* current = stack_.top();
                if (!visited_.empty() && visited_.top() == current)
                {
                    visited_.pop();
                    stack_.pop();
                }
                else
                {
                    if (current->right_) stack_.push(current->right_);
                    if (current->left_) stack_.push(current->left_);
                    visited_.push(current);
                }
                return *this;
            }

            bool operator!=(const post_order_iterator& other) const
            {
                return (stack_.empty() != other.stack_.empty());
            }

        private:
            std::stack<node*> stack_;
            std::stack<node*> visited_;
        };

        class post_order_iterator
        {
        public:
            using iterator_category = std::input_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = const T*;
            using reference = const T&;

            explicit post_order_iterator(node* root = nullptr)
            {
                push_leftmost(root);
            }

            reference operator*() const
            {
                return stack_.top()->value_;
            }

            pointer operator->() const
            {
                return &stack_.top()->value_;
            }

            post_order_iterator& operator++()
            {
                node* current = stack_.top();
                stack_.pop();

                if (!stack_.empty() && stack_.top()->left_ == current)
                {
                    push_leftmost(stack_.top()->right_);
                }

                return *this;
            }

            post_order_iterator operator++(int)
            {
                post_order_iterator temp = *this;
                ++(*this);
                return temp;
            }

            bool operator==(const post_order_iterator& other) const = default;

        private:
            std::stack<node*> stack_;

            void push_leftmost(node* root)
            {
                while (root)
                {
                    stack_.push(root);
                    if (root->left_)
                    {
                        root = root->left_;
                    }
                    else
                    {
                        root = root->right_;
                    }
                }
            }
        };

        static_assert(std::input_iterator<post_order_iterator>);

        class level_order_iterator
        {
        public:
            using iterator_category = std::input_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;

            level_order_iterator(node* root)
            {
                if (root) queue_.push(root);
            }

            reference operator*()
            {
                return queue_.front()->value_;
            }

            level_order_iterator& operator++()
            {
                if (queue_.empty()) return *this;

                node* current = queue_.front();
                queue_.pop();
                if (current->left_) queue_.push(current->left_);
                if (current->right_) queue_.push(current->right_);
                return *this;
            }

            bool operator!=(const level_order_iterator& other) const
            {
                return (queue_.empty() != other.queue_.empty());
            }

        private:
            std::queue<node*> queue_;
        };


        class level_order_iterator
        {
        public:
            using iterator_category = std::input_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = const T*;
            using reference = const T&;

            explicit level_order_iterator(node* root = nullptr)
            {
                if (root)
                {
                    queue_.push(root);
                }
            }

            reference operator*() const
            {
                return queue_.front()->value_;
            }

            pointer operator->() const
            {
                return &queue_.front()->value_;
            }

            level_order_iterator& operator++()
            {
                node* current = queue_.front();
                queue_.pop();
                if (current->left_)
                {
                    queue_.push(current->left_);
                }
                if (current->right_)
                {
                    queue_.push(current->right_);
                }
                return *this;
            }

            level_order_iterator operator++(int)
            {
                level_order_iterator temp = *this;
                ++(*this);
                return temp;
            }

            bool operator==(const level_order_iterator& other) const = default;

        private:
            std::queue<node*> queue_;
        };

        static_assert(std::input_iterator<level_order_iterator>);
    };
}

template <typename T>
struct std::formatter<caff::binary_tree<T>> : std::formatter<std::string>
{
    template <typename FormatContext>
    auto format(const caff::binary_tree<T>& tree, FormatContext& ctx)
    {
        std::string result;
        std::ostringstream oss;
        tree.in_order_traversal(oss);
        return std::formatter<std::string>::format(oss.str(), ctx);
    }
};
#endif