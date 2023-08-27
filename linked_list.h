#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

template <class T>
class linked_list {
public: 
    linked_list();
    ~linked_list();

    void push_back(const T&);
    void push_front(const T&);
    void insert(int, const T&);
    int get(int) const;
    void delete_node(int);
    void print() const;
    void print_reverse() const;
    bool search(const T&) const;

private:
    class node {
    public:
        T m_data = 0;
        node* m_next = nullptr;
        node* m_prev = nullptr;

        node(int);
    };
    node* m_start;
    node* m_end;
    size_t m_size;
};

template <class T>
linked_list <T>::node::node(int data)
    : m_data{data}
{}

template <class T>
linked_list <T>::linked_list() 
    : m_start{ nullptr }, m_end{ nullptr }, m_size{ 0 }
{}

template <class T>
linked_list <T>::~linked_list() {
    if (m_start != nullptr) {
        node* tmp = m_start;

        while (tmp->m_next != nullptr) {
            tmp = tmp->m_next;
            delete tmp->m_prev;
        }
        delete tmp;
    }
}

template <class T>
void linked_list <T>::push_back(const T& data) {
    node* created_node = new node{ data };
   
    if (m_start == nullptr) {
        m_start = created_node;
        m_end = created_node;
        ++m_size;
        return;
    }

    node* tmp = m_start;
    while (tmp->m_next != nullptr) {
        tmp = tmp->m_next;
    }
    
    created_node->m_prev = tmp;
    tmp->m_next = created_node;
    m_end = created_node;
    ++m_size;
}

template <class T>
void linked_list <T>::push_front(const T& data) {
    node* created_node = new node{ data  };
    
    if (m_start == nullptr) {
        m_start = created_node;
        m_end = created_node; 
        ++m_size;
        return;
    }
    
    created_node->m_next = m_start;
    m_start->m_prev = created_node;
    m_start = created_node;
}

template <class T>
void linked_list <T>::insert(int index, const T& data) {
    if (index < 0) {
        throw std::runtime_error("Error: none valid index!");
    }
    node* created_node = new node{ data };

    if (m_start == nullptr) {
        m_start = created_node;
        m_end = created_node;
        ++m_size;
        return;
    }

    node* tmp = m_start;
    for (int i = 0; i < m_size; ++i) {
        if (i == index) {
            if (tmp->m_prev != nullptr || (tmp->m_prev != nullptr && tmp->m_next != nullptr)){
                node* next = tmp;
                node* prev = tmp->m_prev;
                next->m_prev = created_node;
                prev->m_next = created_node;
                created_node->m_next = next;
                created_node->m_prev = prev;
            }
            else { 
                node* next = tmp;
                node* prev = nullptr;
                next->m_prev = created_node;
                created_node->m_next = next;
                created_node->m_prev = prev;
                m_start = created_node;
            }
            ++m_size;
            return;
        } 
        tmp = tmp->m_next;
    }
    throw std::runtime_error("Error: this index out of range!");
}

template <class T>
int linked_list <T>::get(int index) const {
    if (index < 0) {
        throw std::runtime_error("Error: none valid index type!");
    }
    node* tmp = m_start;
    for (int i = 0; i < m_size; ++i) {
        if (i == index) {
            return tmp->m_data;
        }
        tmp = tmp->m_next;
    }
    throw std::runtime_error("Error: index out of range!");
}

template <class T>
void linked_list <T>::delete_node(int index) {
    if (index < 0) {
        throw std::runtime_error("Error: none valid index");
    }
    if (m_start == nullptr) {
        throw std::runtime_error("Error: list is empty");
    }
    node* tmp = m_start;
    int i = 0;
    while (i != index && tmp->m_next != nullptr) {
        tmp = tmp->m_next;
        ++i;
    }
    
    if (i != index) {
        throw std::runtime_error("Error: this " + std::to_string(index) + " index out of range");
    }

    if (tmp->m_prev != nullptr && tmp->m_next != nullptr) {
        (tmp->m_prev)->m_next = tmp->m_next;
        (tmp->m_next)->m_prev = tmp->m_prev;
    }
    else if (tmp->m_prev != nullptr) {
        m_end = tmp->m_prev;
        (tmp->m_prev)->m_next = tmp->m_next;
    }
    else if (tmp->m_next != nullptr) {
        m_start = tmp->m_next;
        (tmp->m_next)->m_prev = tmp->m_prev;
    }
    else {
        m_start = nullptr;
    }
    delete tmp;
    --m_size;
}

template <class T>
void linked_list <T>::print() const {
    node* tmp = m_start;
    
    if (m_start == nullptr) {
        std::cout << "List is empty" << std::endl;
        return;
    }

    int i = 0;
    std::cout << "size: " << m_size << std::endl;
    while (tmp->m_next != nullptr) {
        std::cout << "index: " << i << ", data: " << tmp->m_data << std::endl;
        tmp = tmp->m_next;    
        ++i;
    }
    std::cout << "index: " << i << ", data: " << tmp->m_data << std::endl;
}

template <class T>
void linked_list <T>::print_reverse() const {
    if (m_size == 0) {
        std::cout << "List is empty" << std::endl;
        return;
    }
    node* tmp = m_end;
    int i = m_size - 1;
    for (; i >= 0; --i) {
        std::cout << "index: " << i << ", data: " << tmp->m_data << std::endl;
        tmp = tmp->m_prev;
    }
}

template <class T>
bool linked_list <T>::search(const T& data) const {
    node* tmp = m_start;

    while (tmp->m_next != nullptr) {
        if (tmp->m_data == data) {
            return true;
        }
        tmp = tmp->m_next;
    }
    if (tmp->m_data == data) {
        return true;
    }
    return false;
}


