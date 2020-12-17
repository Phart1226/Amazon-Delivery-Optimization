#ifndef ADDRESS_H
#define ADDRESS_H

#include <cmath>

class Address {
    private:
        int x_pos, y_pos;
        bool prime_delivery;
    public:
        Address();
        Address(int x, int y);
        Address(int x, int y, bool prime);

        int x();
        int y();
        bool prime();
        double distanceTo(Address address);
};

#endif