#ifndef ADDRESSLIST_H
#define ADDRESSLIST_H

#include "address.hpp"
#include <vector>
#include <cmath>
#include <iostream>

class AddressList  {
    protected:
        std::vector<Address> addresses;
        bool is_member(Address address);
        bool Intersect(Address p1, Address q1, Address p2, Address q2);
        bool Intersect(int i1, int i2);

    public:
        AddressList();

        void add(Address address);
        void remove(int index);
        void remove(Address address);
        int members();
        void set(int index, Address address);
        Address get(int i);
        std::vector<Address> getAll();
        void print();
        
        double length();
        Address closest(Address address);
        void reverse(int start, int stop);
        void reverse();
};

#endif