export module data_structures:inplace_vector;

import std;

namespace caff
{
    export template <typename T, std::size_t N>
    class inplace_vector
    {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        inplace_vector() = default;

        inplace_vector(std::initializer_list<T> init_list)
        {
            for (auto& elem : init_list)
            {
                if (size_ >= N)
                {
                    throw std::length_error("Exceeded max capacity.");
                }
                data_[size_++] = elem;
            }
        }

        size_type size() const
        {
            return size_;
        }

        constexpr size_type max_size() const
        {
            return N;
        }

        reference operator[](size_type index)
        {
            if (index >= size_)
            {
                throw std::out_of_range("Index out of range.");
            }
            return data_[index];
        }

        const_reference operator[](size_type index) const
        {
            if (index >= size_)
            {
                throw std::out_of_range("Index out of range.");
            }
            return data_[index];
        }

        void push_back(const T& value)
        {
            if (size_ >= N)
            {
                throw std::length_error("Exceeded max capacity.");
            }
            data_[size_++] = value;
        }

        void pop_back()
        {
            if (size_ == 0)
            {
                throw std::underflow_error("No elements to pop.");
            }
            --size_;
        }

        void clear()
        {
            size_ = 0;
        }

        bool empty() const
        {
            return size_ == 0;
        }

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

            iterator& operator+=(difference_type n) { ptr_ += n; return *this; }
            iterator& operator-=(difference_type n) { ptr_ -= n; return *this; }

            iterator operator+(difference_type n) const { return iterator(ptr_ + n); }
            iterator operator-(difference_type n) const { return iterator(ptr_ - n); }

            difference_type operator-(const iterator& other) const { return ptr_ - other.ptr_; }

            reference operator[](difference_type n) { return *(ptr_ + n); }

            bool operator==(const iterator& other) const = default;
            //auto operator<=>(const iterator& other) const = default;

        private:
            pointer ptr_{ nullptr };
        };

        class const_iterator
        {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = const T;
            using difference_type = std::ptrdiff_t;
            using pointer = value_type*;
            using reference = value_type&;

            const_iterator() = default;
            explicit const_iterator(pointer ptr) : ptr_(ptr) {}

            reference operator*() const { return *ptr_; }
            pointer operator->() const { return ptr_; }

            const_iterator& operator++() { ++ptr_; return *this; }
            const_iterator operator++(int) { const_iterator tmp = *this; ++ptr_; return tmp; }

            const_iterator& operator--() { --ptr_; return *this; }
            const_iterator operator--(int) { const_iterator tmp = *this; --ptr_; return tmp; }

            const_iterator& operator+=(difference_type n) { ptr_ += n; return *this; }
            const_iterator& operator-=(difference_type n) { ptr_ -= n; return *this; }

            const_iterator operator+(difference_type n) const { return const_iterator(ptr_ + n); }
            const_iterator operator-(difference_type n) const { return const_iterator(ptr_ - n); }

            difference_type operator-(const const_iterator& other) const { return ptr_ - other.ptr_; }

            reference operator[](difference_type n) const { return *(ptr_ + n); }

            bool operator==(const const_iterator& other) const = default;
            //auto operator<=>(const const_iterator& other) const = default;

        private:
            pointer ptr_{ nullptr };
        };

        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        iterator begin() { return iterator(data_); }
        iterator end() { return iterator(data_ + size_); }
        const_iterator begin() const { return const_iterator(data_); }
        const_iterator end() const { return const_iterator(data_ + size_); }
        const_iterator cbegin() const { return const_iterator(data_); }
        const_iterator cend() const { return const_iterator(data_ + size_); }
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
        const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
        const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
        const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

    private:
        value_type data_[N];
        size_type size_{ 0 };

        static_assert(N <= 10, "Max capacity is 10");
    };
}

export template <typename T, std::size_t N>
struct std::formatter<caff::inplace_vector<T, N>>
{
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const caff::inplace_vector<T, N>& v, FormatContext& ctx) const
    {
        // TODO: Use range formatter?
        auto out = ctx.out();
        out = std::format_to(out, "[");

        if (auto pos = v.begin(); pos != v.end())
        {
            out = std::format_to(out, "{}", *pos);
            ++pos;

            for (; pos != v.end(); ++pos)
            {
                out = std::format_to(out, ", {}", *pos);
            }
        }

        return std::format_to(out, "]");
    }
};
