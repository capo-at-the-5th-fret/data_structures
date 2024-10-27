export module data_structures:linked_list;

import std;

namespace caff
{
    export template <typename T>
    struct linked_list_node
    {
        T value{ 0 };
        linked_list_node* next{ nullptr };
    };

    export template <typename T>
    struct linked_list_iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = value_type*;
        using reference = value_type&;

        using node_pointer = linked_list_node<value_type>*;

        linked_list_iterator() = default;

        explicit linked_list_iterator(node_pointer n) : node_{ n }
        {
        }

        friend bool operator==(const linked_list_iterator& lhs,
            const linked_list_iterator& rhs) = default;

        reference operator*() const
        {
            return node_->value;
        }

        pointer operator->() const
        {
            return std::addressof(node_->value);
        }

        linked_list_iterator& operator++()
        {
            if (node_ != nullptr)
            {
                node_ = node_->next;
            }
            return *this;
        }

        linked_list_iterator operator++(int)
        {
            linked_list_iterator tmp{ *this };
            ++*this;
            return tmp;
        }

        node_pointer node() const
        {
            return node_;
        }

    private:
        node_pointer node_{ nullptr };
    };

    export template <typename T>
    struct linked_list_const_iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const value_type*;
        using reference = const value_type&;

        using node_pointer = const linked_list_node<value_type>*;

        linked_list_const_iterator() = default;

        explicit linked_list_const_iterator(node_pointer n) : node_{ n }
        {
        }

        linked_list_const_iterator(const linked_list_iterator<value_type>& pos)
            : node_{ pos.node() }
        {
        }

        friend bool operator==(const linked_list_const_iterator& lhs,
            const linked_list_const_iterator& rhs) = default;

        reference operator*() const
        {
            return node_->value;
        }

        pointer operator->() const
        {
            return std::addressof(node_->value);
        }

        linked_list_const_iterator& operator++()
        {
            if (node_ != nullptr)
            {
                node_ = node_->next;
            }
            return *this;
        }

        linked_list_const_iterator operator++(int)
        {
            linked_list_const_iterator tmp{ *this };
            ++*this;
            return tmp;
        }

        node_pointer node() const
        {
            return node_;
        }

    private:
        node_pointer node_{ nullptr };
    };

    static_assert(std::forward_iterator<linked_list_iterator<int>>);
    static_assert(std::forward_iterator<linked_list_const_iterator<int>>);

    // NOTE: This is not as efficient as std::forward_list, which uses
    // functions like before_begin() and insert_after() to help insert
    // elements without having to traverse nodes to find the insertion
    // point.
    export template <typename T>
    class linked_list
    {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator = linked_list_iterator<value_type>;
        using const_iterator = linked_list_const_iterator<value_type>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        using node = linked_list_node<value_type>;

        linked_list() = default;

        linked_list(std::initializer_list<T> values)
        {
            insert(end(), values.begin(), values.end());
        }

        linked_list(const linked_list& other)
        {
            insert(end(), other.begin(), other.end());
        }

        ~linked_list()
        {
            clear();
        }
    
        linked_list& operator=(const linked_list& other)
        {
            if (this != std::addressof(other))
            {
                clear();
                insert(end(), other.begin(), other.end());
            }

            return *this;
        }

        linked_list& operator=(std::initializer_list<T> values)
        {
            clear();
            insert(end(), values.begin(), values.end());
            return *this;
        }

        reference front()
        {
            return head_->value;
        }

        const_reference front() const
        {
            return head_->value;
        }

        iterator begin()
        {
            return iterator{ head_ };
        }

        const_iterator begin() const
        {
            return const_iterator{ head_ };
        }

        const_iterator cbegin() const
        {
            return const_iterator{ head_ };
        }

        iterator end()
        {
            return iterator{ nullptr };
        }

        const_iterator end() const
        {
            return const_iterator{ nullptr };
        }

        const_iterator cend() const
        {
            return const_iterator{ nullptr };
        }

        bool empty() const
        {
            return head_ == nullptr;
        }

        std::size_t size() const
        {
            return size_;
        }

        void clear()
        {
            auto* node = head_;
            head_ = nullptr;
            size_ = 0;
            
            while (node != nullptr)
            {
                auto* tmp = node;
                node = node->next;
                delete tmp;
            }
        }

        iterator insert(const_iterator pos, const T& value)
        {
            auto* new_node = new node
            {
                .value = value,
                .next = nullptr
            };

            // the new node is the new head_
            if (pos == begin())
            {
                new_node->next = head_;
                head_ = new_node;
                ++size_;
                return begin();
            }
            else
            {
                for (auto current_pos = begin(); current_pos != end();
                    ++current_pos)
                {
                    // next is the insert position; insert the new node in between
                    // the current and the next
                    if (current_pos.node()->next == pos.node())
                    {
                        new_node->next = current_pos.node()->next;
                        current_pos.node()->next = new_node;
                        ++size_;
                        return current_pos++;
                    }
                }
            }

            // should never happen
            return end();
        }

        template <std::input_iterator InputIt>
        requires (std::same_as<std::iter_value_t<InputIt>, T>)
        iterator insert(const_iterator pos, InputIt first, InputIt last)
        {
            if (first == last)
            {
                // TODO: use const_cast on pos.node()?
                for (auto current_pos = begin(); current_pos != end();
                    ++current_pos)
                {
                    if (current_pos.node() == pos.node())
                    {
                        return iterator{ current_pos.node() };
                    }
                }

                // should never happen
                return end();
            }

            // construct the new nodes, keeping track of the first, last and count
            auto* first_node = new node{ .value = *first, .next = nullptr };
            auto* last_node = first_node;
            std::size_t new_node_count{ 1 };
            
            for (auto pos = std::next(first); pos != last; ++pos)
            {
                auto* new_node = new node{ .value = *pos, .next = nullptr };
                last_node->next = new_node;
                last_node = new_node;
                ++new_node_count;
            }

            // the new nodes are inserted at the front
            if (pos == begin())
            {
                last_node->next = head_;
                head_ = first_node;
                size_ += new_node_count;
                return begin();
            }
            else
            {
                for (auto current_pos = begin(); current_pos != end();
                    ++current_pos)
                {
                    // next is the insert position; insert the new nodes in between
                    // the current and the next
                    if (current_pos.node()->next == pos.node())
                    {
                        last_node->next = current_pos.node()->next;
                        current_pos.node()->next = first_node;
                        size_ += new_node_count;
                        return current_pos++;
                    }
                }
            }

            // should never happen
            return end();
        }

        iterator erase(const_iterator pos)
        {
            // erase the head
            if (pos == begin())
            {
                auto* temp = head_;
                head_ = temp->next;
                delete temp;
                --size_;
                return begin();
            }
            else
            {
                for (auto current_pos = begin(); current_pos != end();
                    ++current_pos)
                {
                    // next is the erase position; delete the next, then set the
                    // current next to the next of the next
                    if (current_pos.node()->next == pos.node())
                    {
                        auto* temp = current_pos.node()->next;
                        current_pos.node()->next = temp->next;
                        delete temp;
                        --size_;
                        return current_pos++;
                    }
                }
            }

            return end();
        }

        void push_front(const T& value)
        {
            insert(begin(), value);
        }

        void pop_front()
        {
            erase(begin());
        }

        friend bool operator==(const linked_list& lhs, const linked_list& rhs)
        {
            return std::ranges::equal(lhs, rhs);
        }

        friend auto operator<=>(const linked_list& lhs, const linked_list& rhs)
        {
            return std::lexicographical_compare_three_way(
                lhs.begin(), lhs.end(),
                rhs.begin(), rhs.end()
            );
        }

    private:
        node* head_{ nullptr };
        std::size_t size_{ 0 };
    };
}
