export module data_structures:doubly_linked_list;

import std;

namespace caff
{
    export class doubly_linked_list
    {
    public:
        doubly_linked_list() = default;

        doubly_linked_list(std::initializer_list<int> values)
        {
            insert(end(), values.begin(), values.end());
        }

        doubly_linked_list(const doubly_linked_list& other)
        {
            insert(end(), other.begin(), other.end());
        }

        ~doubly_linked_list()
        {
            clear();
        }
    
        doubly_linked_list& operator=(const doubly_linked_list& other)
        {
            if (this != &other)
            {
                clear();
                insert(end(), other.begin(), other.end());
            }

            return *this;
        }

        doubly_linked_list& operator=(std::initializer_list<int> values)
        {
            clear();
            insert(end(), values.begin(), values.end());
            return *this;
        }

        class list_node;

        class iterator
        {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = int;
            using difference_type = std::ptrdiff_t;
            using pointer = int*;
            using reference = int&;

            using node_pointer = list_node*;

            iterator() = default;

            iterator(node_pointer n, doubly_linked_list* list) : node_{ n },
                list_{ list }
            {
            }

            bool operator==(const iterator& other) const = default;

            reference operator*() const
            {
                return node_->value;
            }

            pointer operator->() const
            {
                return std::addressof(node_->value);
            }

            iterator& operator--()
            {
                if (node_ != nullptr)
                {
                    node_ = node_->prev;
                }
                else
                {
                    node_ = list_->tail_;
                }
                return *this;
            }

            iterator operator--(int)
            {
                iterator temp{ *this };
                --(*this);
                return temp;
            }

            iterator& operator++()
            {
                if (node_ != nullptr)
                {
                    node_ = node_->next;
                }
                return *this;
            }

            iterator operator++(int)
            {
                iterator temp{ *this };
                ++(*this);
                return temp;
            }

            node_pointer node() const
            {
                return node_;
            }

            doubly_linked_list* list() const
            {
                return list_;
            }

        private:
            node_pointer node_{ nullptr };
            doubly_linked_list* list_{ nullptr };
        };

        class const_iterator
        {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = const int;
            using difference_type = std::ptrdiff_t;
            using pointer = const int*;
            using reference = const int&;

            using node_pointer = const list_node*;

            const_iterator() = default;

            const_iterator(node_pointer n, const doubly_linked_list* list) :
                node_{ n }, list_{ list }
            {
            }

            const_iterator(const iterator& pos) : node_{ pos.node() },
                list_{ pos.list() }
            {
            }

            bool operator==(const const_iterator& other) const = default;

            reference operator*() const
            {
                return node_->value;
            }

            pointer operator->() const
            {
                return std::addressof(node_->value);
            }

            const_iterator& operator--()
            {
                if (node_ != nullptr)
                {
                    node_ = node_->prev;
                }
                else
                {
                    node_ = list_->tail_;
                }
                return *this;
            }

            const_iterator operator--(int)
            {
                const_iterator temp{ *this };
                --(*this);
                return temp;
            }

            const_iterator& operator++()
            {
                if (node_ != nullptr)
                {
                    node_ = node_->next;
                }
                return *this;
            }

            const_iterator operator++(int)
            {
                const_iterator temp{ *this };
                ++(*this);
                return temp;
            }

            node_pointer node() const
            {
                return node_;
            }

            const doubly_linked_list* list() const
            {
                return list_;
            }

        private:
            node_pointer node_{ nullptr };
            const doubly_linked_list* list_{ nullptr };
        };

        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        iterator begin()
        {
            return iterator{ head_, this };
        }

        iterator end()
        {
            return iterator{ nullptr, this };
        }

        const_iterator begin() const
        {
            return const_iterator{ head_, this };
        }

        const_iterator end() const
        {
            return const_iterator{ nullptr, this };
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator{ end() };
        }

        reverse_iterator rend()
        {
            return reverse_iterator{ begin() };
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator{ end() };
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator{ begin() };
        }

        bool empty() const
        {
            return head_ == nullptr && tail_ == nullptr;
        }

        std::size_t size() const
        {
            return size_;
        }

        void clear()
        {
            auto* node = head_;
            head_ = nullptr;
            tail_ = nullptr;
            size_ = 0;

            while (node != nullptr)
            {
                auto* temp = node;
                node = node->next;
                delete temp;
            }
        }

        iterator insert(const_iterator pos, int value)
        {
            auto* new_node = new list_node
            {
                .value = value,
                .prev = nullptr,
                .next = nullptr
            };

            // the new node is the new head_
            if (pos == begin())
            {
                if (head_ != nullptr)
                {
                    new_node->next = head_;
                    head_->prev = new_node;
                }

                head_ = new_node;

                if (tail_ == nullptr)
                {
                    tail_ = head_;
                }
                ++size_;
                return iterator{ head_, this };
            }
            // the new node is the new tail_
            else if (pos == end())
            {
                if (tail_ != nullptr)
                {
                    new_node->prev = tail_;
                    tail_->next = new_node;
                }

                tail_ = new_node;

                //assert(head_ != nullptr);
                if (head_ == nullptr)
                {
                    head_ = tail_;
                }
                ++size_;
                return iterator{ tail_, this };
            }
            else
            {
                for (auto current_pos = std::next(begin()); current_pos != end();
                    ++current_pos)
                {
                    // found the insertion position
                    if (current_pos == pos)
                    {
                        auto* prev_node = current_pos.node()->prev;
                        auto* next_node = current_pos.node();

                        new_node->prev = prev_node;
                        new_node->next = next_node;

                        prev_node->next = new_node;
                        next_node->prev = new_node;
                    
                        ++size_;
                        return current_pos;
                    }
                }
            }

            // should never happen
            return end();
        }

        template <std::input_iterator InputIt>
        requires (std::same_as<std::iter_value_t<InputIt>, int>)
        iterator insert(const_iterator pos, InputIt first, InputIt last)
        {
            if (first == last)
            {
                // TODO: use const_cast on pos.node()?
                for (auto current_pos = begin(); current_pos != end();
                    ++current_pos)
                {
                    if (current_pos == pos)
                    {
                        return current_pos;
                    }
                }

                // should never happen
                return end();
            }

    #if 0
            // construct the new nodes, keeping track of the first, last and count
            auto* first_node = new list_node{ .value = *first, .next = nullptr };
            auto* last_node = first_node;
            std::size_t new_node_count{ 1 };
            
            for (auto pos = std::next(first); pos != last; ++pos)
            {
                auto* new_node = new list_node{ .value = *pos, .next = nullptr };
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
            #endif

            // should never happen
            return end();
        }

        iterator erase(const_iterator pos)
        {
            // erase the head
            if (pos == begin())
            {
                if (auto* old_head = head_; old_head != nullptr)
                {
                    head_ = old_head->next;
                    if (head_ != nullptr)
                    {
                        head_->prev = nullptr;
                    }
                    else
                    {
                        tail_ = nullptr;
                    }

                    delete old_head;
                }

                --size_;
                return begin();
            }
            // erase the tail
            else if (pos.node() == tail_)
            {
                if (auto* old_tail = tail_; old_tail != nullptr)
                {
                    tail_ = old_tail->prev;
                    if (tail_ != nullptr)
                    {
                        tail_->next = nullptr;
                    }
                    else
                    {
                        head_ = nullptr;
                    }

                    delete old_tail;
                }

                --size_;
                return rbegin().base();
            }
            else
            {
                for (auto current_pos = begin(); current_pos != end();
                    ++current_pos)
                {
                    // found the erase position
                    if (current_pos == pos)
                    {
                        auto* current_node = current_pos.node();
                        auto* prev_node = current_node->prev;
                        auto* next_node = current_node->next;

                        if (prev_node != nullptr)
                        {
                            prev_node->next = next_node;
                        }
                        if (next_node != nullptr)
                        {
                            next_node->prev = prev_node;
                        }

                        delete current_node;

                        --size_;
                        return iterator{ next_node, this};
                    }
                }
            }

            return end();
        }

        void push_back(int value)
        {
            insert(end(), value);
        }

        void push_front(int value)
        {
            insert(begin(), value);
        }

    private:
        struct list_node
        {
            int value{ 0 };
            list_node* prev{ nullptr };
            list_node* next{ nullptr };
        };

        list_node* head_{ nullptr };
        list_node* tail_{ nullptr };
        std::size_t size_{ 0 };
    };

    export bool operator==(const doubly_linked_list& lhs, const doubly_linked_list& rhs)
    {
        return std::ranges::equal(lhs, rhs);
    }

    export auto operator<=>(const doubly_linked_list& lhs, const doubly_linked_list& rhs)
    {
        return std::lexicographical_compare_three_way(lhs.begin(), lhs.end(),
            rhs.begin(), rhs.end());
    }
}

export template <>
struct std::formatter<caff::doubly_linked_list>
{
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const caff::doubly_linked_list& list, FormatContext& ctx) const
    {
        // TODO: Use range formatter?
        auto out = ctx.out();
        out = std::format_to(out, "[");

        if (auto pos = list.begin(); pos != list.end())
        {
            out = std::format_to(out, "{}", *pos);
            ++pos;

            for (; pos != list.end(); ++pos)
            {
                out = std::format_to(out, ", {}", *pos);
            }
        }

        return std::format_to(out, "]");
    }
};
