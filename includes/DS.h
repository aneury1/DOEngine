#pragma once

#include <functional>

namespace doengine::DS
{

template <typename T>
struct BinaryTree
{
    BinaryTree* left;
    BinaryTree* right;
    T value;
    BinaryTree() : value{0}, left{nullptr}, right{nullptr}
    {
    }

    void set_value(T va)
    {
        value = va;
    }
    BinaryTree(T start) : value{start}, left{nullptr}, right{nullptr}
    {
    }

    BinaryTree<T> visitFromLeft(std::function<void(T)> visitor)
    {

        if (left)
        {
            left->visitFromLeft(visitor);
        }
        if (right)
        {
            right->visitFromLeft(visitor);
        }
        visitor(value);
    }

    BinaryTree<T> insert(T value)
    {
        if (value == this->value)
            return *this;
        if (value < this->value)
        {
            if (left)
            {
                left->insert(value);
            }
            else
            {
                left = new BinaryTree<T>(value);
            }
        }
        else
        {
            if (right)
            {
                right->insert(value);
            }
            else
            {
                right = new BinaryTree<T>(value);
            }
        }
        return *this;
    }
};

}; // namespace doengine::DS