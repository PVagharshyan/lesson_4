#pragma once

#include <iostream>
#include <string>

template <class T>
class linked_list {
public: 
    linked_list();
    ~linked_list();

    void insert_node(const T&);
    void delete_node(int);
    void print() const;
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
};

template <class T>
linked_list <T>::node::node(int data)
    : m_data{data}
{}

template <class T>
linked_list <T>::linked_list() 
    : m_start{nullptr}
{}

template <class T>
linked_list <T>::~linked_list() {
    if (m_start != nullptr) {
        node* tmp = m_start;

        while (tmp->m_next == nullptr) {
            tmp = tmp->m_next;
            delete tmp->m_prev;
        }
        delete tmp;
    }
}

template <class T>
void linked_list <T>::insert_node(const T& data) {
    node* created_node = new node{ data };
   
    if (m_start == nullptr) {
        m_start = created_node;
        return;
    }

    node* tmp = m_start;
    while (tmp->m_next != nullptr) {
        tmp = tmp->m_next;
    }
    
    created_node->m_prev = tmp;
    tmp->m_next = created_node;
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
    bool flag = false;
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
}

template <class T>
void linked_list <T>::print() const {
    node* tmp = m_start;
    
    if (m_start == nullptr) {
        std::cout << "List is empty" << std::endl;
        return;
    }

    int i = 0;
    while (tmp->m_next != nullptr) {
        std::cout << "index: " << i << ", data: " << tmp->m_data << std::endl;
        tmp = tmp->m_next;    
    }
    std::cout << "index: " << i << ", data: " << tmp->m_data << std::endl;
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


