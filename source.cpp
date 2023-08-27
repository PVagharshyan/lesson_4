#include "linked_list.h"
#include <iostream>

int main() {
    linked_list <int> list;
    linked_list <int> list_1;

    //test
    
    list.push_back(10);
    list.push_back(12);
    list.push_back(13);
    list.push_back(15);
    list.print();
    list.insert(1, 25);
    list.print();
    return 0;
}
