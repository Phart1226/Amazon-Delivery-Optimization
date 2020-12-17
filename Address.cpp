#include "address.hpp"

// Default constructor will create a depot if not given any parameters
Address::Address() {
  x_pos = 0;
  y_pos = 0;
  prime_delivery = false;
}

// Constructor given coordinates
Address::Address(int x, int y) {
    x_pos = x;
    y_pos = y;
    prime_delivery = false;
}

// Constructor given coordinates and prime specification
Address::Address(int x, int y, bool prime) {
    x_pos = x;
    y_pos = y;
    prime_delivery = prime;
}

// Function for accessing x-coordinate
int Address::x() {
    return x_pos;
}

// Function for accessing y-coordinate
int Address::y() {
    return y_pos;
}

// Function for accessing prime indicator
bool Address::prime() {
    return prime_delivery;
}

// Returns the euclidean distance between this address and another address
double Address::distanceTo(Address address_in) {
    int dx = address_in.x() - x_pos;
    int dy = address_in.y() - y_pos;
    int radicand = pow(dx,2) + pow(dy,2);
    double l2_norm = sqrt(radicand);
    return l2_norm;
}
