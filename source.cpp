#include "linked_list.h"

#include <iostream>

int main() {
    linked_list <int> list;

    //test

    list.insert_node(45);
    list.insert_node(25);
    list.insert_node(4);
    list.print();
    list.delete_node(1);
    list.print();
    list.delete_node(1);
    list.print();
    list.delete_node(0);
    list.print();
    return 0;
}
