#ifndef ROUTE_H
#define ROUTE_H

#include "address.hpp"
#include "addresslist.hpp"
#include <cmath>
#include <iostream>

class Route: public AddressList {
    public:
        void greedyRoute();
        bool KernighanLin();
        void TwoTrucks();
        Route Prime(int maxDistDay);
        void RandomAdd(int numAdd);
        Route ReorderRoute(double dayDist);
};

#endif