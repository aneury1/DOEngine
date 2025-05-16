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

    const T remove(T nodeValue)
    {

      Node* prev = findPrev(nodeValue);
      Node* curr = find(nodeValue);
      T deleteValue = T();

      if (curr != nullptr) {
        Node * next = curr->next();
        prev->setNext(next);
        deleteValue = curr->data;
        delete curr;
        curr = nullptr;
        _len--;
      }

      return deleteValue;
    }

    Node* find(T nodeValue)
    {
      return findPrev(nodeValue)->next();
    }

    Node* findPrev(T nodeValue)
    {
        Node* curr = head;
        Node* prev = head;
        while (curr != nullptr){
          if(curr->data == nodeValue)
            break;
          prev = curr;
          curr = curr->next();
        }
        return prev;
    }

    const bool insertBefore(Node* node, T nodeValue)
    {
      Node* curr = head;
      Node* prev = head;
      if(curr != nullptr)
      {
        while (curr != nullptr)
        {
          if(curr->data == node->data)
          {
            Node* ne = new Node(nodeValue, curr);
            if(curr->data == prev->data) // If equals, means node is head
            {
              head = ne;
            }
            else
              prev->setNext(ne);
            _len++;
            break;
          }
          prev = curr;
          curr = curr->next();
        }
      }
      else
      {
          insert(nodeValue);
      }
      return true;
    }

    const bool insertAfter(Node* node, T nodeValue)
    {
      Node* curr = head;
      if(curr != nullptr)
      {
        while (curr != nullptr)
        {
          if(curr->data == node->data)
          {
            Node* ne = new Node(nodeValue, curr->next());
            curr->setNext(ne);
            _len++;
            break;
          }
          curr = curr->next();
        }
      }
      else
      {
          insert(nodeValue);
      }
      return false;
    } 

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
