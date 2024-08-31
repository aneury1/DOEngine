#pragma once

#include <cstddef>
namespace doengine
{
template <class T>
class LinkList
{
  public:
    struct Node
    {
      private:
        Node* _next;

      public:
        T data;

        Node* next() const
        {
            return _next;
        };

        void setNext(Node* node)
        {
            _next = node;
        }

        Node(T d = T(), Node* n = nullptr) : data{d}, _next{n}
        {
        }
    };

    LinkList()
    {
        head = nullptr;
        _len = 0;
    }

    ~LinkList()
    {
        destroy();
    }

    void destroy()
    {
        if (head != nullptr)
        {
            auto next = head->next();
            delete head;
            head = next;

            _len--;
            destroy();
        }
    }

    void insert(T d)
    {
        Node* ne = new Node(d, nullptr);
        if (!head)
            head = ne;
        else
        {
            Node* curr = head;
            while (curr->next() != nullptr)
                curr = curr->next();
            curr->setNext(ne);
        }
        _len++;
    }

    const Node* const remove(T nodeValue)
    {
        return nullptr;
    } // TODO to be done later

    const Node* find(T nodeValue)
    {
        return nullptr;
    } // TODO to be done later

    const bool insertBefore(Node* node, T nodeValue)
    {
        return false;
    } // TODO to be done later

    const bool insertAfter(Node* node, T nodeValue)
    {
        return false;
    } // TODO to be done later

    std::size_t getLength() const
    {
        return _len;
    }

    Node* getHead()
    {
        return head;
    }

  private:
    Node* head = {nullptr};
    std::size_t _len;
};

} // namespace doengine