#pragma once
#include <iostream>

template<class T>
class TListDouble
{
    struct node
    {
        T data;
        node* prev;
        node* next;
        node(T data_, node* next_ = 0, node* prev_ = 0) :data(data_), next(next_), prev(prev_) {}
    };

    ///<summary>support function</summary>
    ///<param name="pointer">after this pointer to insert</param>
    ///<param name="x">inserted element</param>
    void addOther(node*& pointer, int x)
    {
        node* temp = pointer;
        bool f = false;
        while (temp->next && !f)
        {
            if (temp->next->data <= x)
                temp = temp->next;
            else
                f = true;
        }
        node* n_node = new node(x);
        node* t_n = temp->next;
        temp->next = n_node;
        n_node->next = t_n;
    }

    node* head;

public:

    class Iterator
    {
    public:
        node* current_node;

        Iterator() :current_node(head) { }
        Iterator(node* p_node) :current_node(p_node) { }

        Iterator& operator=(node* p_node)
        {
            this->current_node = p_node;
            return *this;
        }

        Iterator& operator++()
        {
            if (current_node)
                current_node = current_node->next;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++* this;
            return iterator;
        }
        bool operator!=(const Iterator& iterator) { return current_node != iterator.current_node; }
        int operator*() { return current_node->data; }
    };

    TListDouble();
    ~TListDouble();
    TListDouble(const TListDouble<T>& obj);

    TListDouble<T>& operator=(const TListDouble<T>& obj);

    bool isEmpty();
    void addAfterCur(Iterator cur_aa, T elem);
    void addBeforeCur(Iterator cur_ab, T elem);
    void deleteAfterCur(Iterator cur_da);
    void deleteBeforeCur(Iterator cur_db);

    node* get_head() const  { return head; }

    Iterator begin()        { return Iterator(head->next); }
    Iterator end()          { return Iterator(0); }

    template<class T>
    friend TListDouble<T> merge(TListDouble<T>& list_1, TListDouble<T>& list_2);

    template<class T>
    friend TListDouble<T> merge_order(TListDouble<T>& list_1, TListDouble<T>& list_2);
};

template<class T>
inline TListDouble<T>::TListDouble() 
    : head(new node(0)) {}

template<class T>
inline TListDouble<T>::~TListDouble()
{
    while (head)
    {
        node* p = head;
       	head = head->next;
        p->next = 0;
        delete p;
        p = 0;
    }
}

template<class T>
inline TListDouble<T>::TListDouble(const TListDouble<T>& obj)
{
    head = new node(0);
    node* last = head;
    
    for (node* temp = obj.get_head()->next; temp != nullptr; temp = temp->next)
    {
        node* new_node = new node(temp->data);
        new_node->next = last->next;
        last->next = new_node;
        new_node->prev = last;
        if (new_node->next != NULL)
            new_node->next->prev = new_node;

        last = new_node;
    }
}

template<class T>
inline TListDouble<T>& TListDouble<T>::operator=(const TListDouble<T>& obj)
{
    while (head)
    {
        node* p = head;
        head = head->next;
        p->next = 0;
        delete p;
        p = 0;
    }

    head = new node(0);
    node* last = head;

    for (node* temp = obj.get_head()->next; temp != nullptr; temp = temp->next)
    {
        node* new_node = new node(temp->data);
        new_node->next = last->next;
        last->next = new_node;
        new_node->prev = last;
        if (new_node->next != NULL)
            new_node->next->prev = new_node;

        last = new_node;
    }

    return *this;
}

template<class T>
inline bool TListDouble<T>::isEmpty()
{
    return head->next;
}

template<class T>
inline void TListDouble<T>::addAfterCur(Iterator cur_aa, T elem)
{
    node* new_node = new node(elem);
    new_node->next = cur_aa.current_node->next;
    cur_aa.current_node->next = new_node;
    new_node->prev = cur_aa.current_node;
    if (new_node->next != NULL)
        new_node->next->prev = new_node;
}

template<class T>
inline void TListDouble<T>::addBeforeCur(Iterator cur_ab, T elem)
{
    node* new_node = new node(elem);
    new_node->next = cur_ab.current_node->next;
    cur_ab.current_node->next = new_node;
    new_node->prev = cur_ab.current_node;
    if (new_node->next != NULL)
        new_node->next->prev = new_node;
}

template<class T>
inline void TListDouble<T>::deleteAfterCur(Iterator cur_da)
{
    node* del = cur_da.current_node->next;
    cur_da.current_node->next = cur_da.current_node->next->next;
    if(cur_da.current_node->next)
        cur_da.current_node->next->prev = cur_da.current_node;
    del->next = nullptr;
    del->prev = nullptr;
    delete del;
    del = nullptr;

}

template<class T>
inline void TListDouble<T>::deleteBeforeCur(Iterator cur_db)
{
    if (head->next == cur_db.current_node) 
    {
        node* del = head;
        head = head->next;
        head->prev = nullptr;
        T value = del->data;
        del->next = nullptr;
        del->prev = nullptr;
        delete del;
        del = nullptr;
    }
    else 
    {
        node* del = cur_db.current_node->prev;
        del->prev->next = del->next;
        del->next->prev = del->prev;
        T value = del->data;
        del->next = nullptr;
        del->prev = nullptr;
        delete del;
        del = nullptr;
    }
}