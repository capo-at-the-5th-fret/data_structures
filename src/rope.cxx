export module data_structures:rope;

import std;

namespace caff
{
    export class rope_node
    {
    public:
        explicit rope_node(const std::string& val) 
            : value(val), left(nullptr), right(nullptr), weight(val.size()) 
        {
        }

        rope_node(rope_node* l, rope_node* r)
            : left(l), right(r), weight(l->weight + (r ? r->weight : 0)) 
        {
        }

        std::string value{};
        rope_node* left{nullptr};
        rope_node* right{nullptr};
        std::size_t weight{0};
    };

    export class rope
    {
    public:
        rope(const std::string& str)
            : root_(new rope_node(str)), size_(str.size()) 
        {
        }

        ~rope()
        {
            delete_tree(root_);
        }

        void concatenate(const rope& other)
        {
            root_ = join(root_, other.root_);
            size_ += other.size_;
        }

        char operator[](std::size_t index) const
        {
            return get(root_, index);
        }

        std::size_t length() const
        {
            return length(root_);
        }

        std::size_t size() const
        {
            return size_;
        }

    private:
        rope_node* join(rope_node* left, rope_node* right)
        {
            return new rope_node(left, right);
        }

        void delete_tree(rope_node* node)
        {
            if (!node) 
            {
                return;
            }
            delete_tree(node->left);
            delete_tree(node->right);
            delete node;
        }

        char get(rope_node* node, std::size_t index) const
        {
            if (!node) 
            {
                return '\0';
            }
            if (index < node->weight)
            {
                if (node->left) 
                {
                    return get(node->left, index);
                }
                return node->value[index];
            }
            else
            {
                return get(node->right, index - node->weight);
            }
        }

        std::size_t length(rope_node* node) const
        {
            if (!node) 
            {
                return 0;
            }
            return node->weight + (node->right ? length(node->right) : 0);
        }

        rope_node* root_{nullptr};
        std::size_t size_{0};
    };

}

namespace std
{
    export template <>
    struct formatter<caff::rope>
    {
        constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
        {
            return ctx.end();
        }

        auto format(const caff::rope& r, format_context& ctx) const -> decltype(ctx.out())
        {
            for (std::size_t index = 0; index < r.length(); ++index)
            {
                ctx.out() = r[index];
            }
            return ctx.out();
        }
    };
}
