#include "linked_list.h"
#include <iostream>

int main() {
    linked_list <int> list;
    linked_list <int> list_1;

    //test
    
    list.insert_node(10);
    list.insert_node(12);
    list.insert_node(13);
    list.insert_node(15);
    list.print();
    list_1.print();
    
    return 0;
}
