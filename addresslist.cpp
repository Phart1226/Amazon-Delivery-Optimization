#include "addresslist.hpp"

using std::max;
using std::min;

// PROTECTED FUNCTIONS

// Determines if points p, q, and r are on the same line segment
bool onSegment(Address p, Address q, Address r) {
  if (q.x() <= max(p.x(), r.x()) && q.x() >= min(p.x(), r.x()) &&
      q.y() <= max(p.y(), r.y()) && q.y() >= min(p.y(), r.y())) {
    return true;
  }
  return false;
}

// Determines the orientation of the points p, q, and r in that order
int orientation(Address p, Address q, Address r) {
  int val = (q.y() - p.y())*(r.x() - q.x()) -
            (q.x() - p.x()) * (r.y() - q.y());

  if (val == 0) return 0; // case if points are collinear
  return (val > 0) ? 1:2; // return 1 if orientation clockwise
                          // 2 if orientation counterclockwise
}

// Function determiens whether the line segment between p1 and q1 intersects with the line segment between p2 and q2
bool AddressList::Intersect(Address p1, Address q1, Address p2, Address q2) {
  // Calculate orientation of combinations
  int o1 = orientation(p1, q1, p2); 
  int o2 = orientation(p1, q1, q2); 
  int o3 = orientation(p2, q2, p1); 
  int o4 = orientation(p2, q2, q1);

  // Check orientations
  if (o1 != o2 && o3 != o4) return true;

  // Check special cases
  if (o1 == 0 && onSegment(p1, p2, q1)) return true;
  if (o2 == 0 && onSegment(p1, q2, q1)) return true;
  if (o3 == 0 && onSegment(p2, p1, q2)) return true;
  if (o4 == 0 && onSegment(p2, q1, q2)) return true;

  // By default, segments do not Intersect
  return false;
}

// Function returns whether the given address is present in this address list
bool AddressList::is_member(Address address) {
    for (int i = 0; i < addresses.size(); i++) {
        if ( (addresses.at(i).x() == address.x() ) && addresses.at(i).y() == address.y() ) {
            return true;
        }
    }
    return false;
}

bool AddressList::Intersect(int i1, int i2) {
  // Retrieve points
  Address p1 = addresses.at(i1);
  Address q1 = addresses.at(i1+1);
  Address p2 = addresses.at(i2);
  Address q2 = addresses.at(i2+1);

  // Calculate orientation of combinations
  int o1 = orientation(p1, q1, p2); 
  int o2 = orientation(p1, q1, q2); 
  int o3 = orientation(p2, q2, p1); 
  int o4 = orientation(p2, q2, q1);

  // Check orientations
  if (o1 != o2 && o3 != o4) return true;

  // Check special cases
  if (o1 == 0 && onSegment(p1, p2, q1)) return true;
  if (o2 == 0 && onSegment(p1, q2, q1)) return true;
  if (o3 == 0 && onSegment(p2, p1, q2)) return true;
  if (o4 == 0 && onSegment(p2, q1, q2)) return true;

  // By default, segments do not Intersect
  return false;
}

// CONSTRUCTORS

AddressList::AddressList() {
    Address depot;
    addresses.push_back(depot); // place a depot at the 'beginning' of the list
    addresses.push_back(depot); // place a depot at the 'end' of the list
}

// PUBLIC FUNCTIONS

// Adds an address to the list
void AddressList::add(Address address) {
    if ( !(is_member(address)) ) {
        addresses.insert(addresses.end()-1, address);
    }
}

// Removes an address from the list given its index
void AddressList::remove(int index) {
    addresses.erase(addresses.begin() + index);
}

// Removes an address from the list given a copy of the address
void AddressList::remove(Address address) {
    for (int i = 0; i < addresses.size(); i++) {
        if ( (addresses.at(i).x() == address.x() ) && addresses.at(i).y() == address.y() ) {
            addresses.erase(addresses.begin() + i);
        }
    }
}

// Returns the number of addresses in route
int AddressList::members() {
    return addresses.size();
}

// Sets the address at a given index to a new address
void AddressList::set(int index, Address address) {
    addresses.at(index) = address;
}

// Returns the address object at index i
Address AddressList::get(int i) {
    return addresses.at(i);
}

// Returns the entire address vector
std::vector<Address> AddressList::getAll() {
    return addresses;
}

// Prints all of the member addresses in order
void AddressList::print() {
    for(int i = 0; i < addresses.size(); i++) {
        if(addresses.at(i).prime())
            std::cout << '[' << addresses.at(i).x() << ',' << addresses.at(i).y() << "]" << "*" << std::endl;
        else
            std::cout << '[' << addresses.at(i).x() << ',' << addresses.at(i).y() << "]\n";
    }
}

// Returns the length of the entire route using euclidean distances
double AddressList::length() {
    double total_distance = 0;
    for (int i = 1; i < addresses.size(); i++) {
        total_distance = total_distance + addresses.at(i-1).distanceTo( addresses.at(i) );
    }
    return total_distance;
}

// Returns the address closest to a given address not in the list
Address AddressList::closest(Address address) {
    double closeDist = address.distanceTo(addresses.at(addresses.size()-1));
    int closeDistSpot = addresses.size()-1;

    for(int spot = 0; spot < addresses.size(); spot++) {
        if (address.distanceTo(addresses.at(spot)) < closeDist) {
            closeDist = address.distanceTo(addresses.at(spot));
            closeDistSpot = spot;
        }
    }
    return addresses.at(closeDistSpot);
}

// Reverses the order of all addresses inbetween the indexes start and stop
void AddressList::reverse(int start, int stop) {
    std::vector<Address> new_addresses;
    for (int i = 0; i < start; i++) {
        new_addresses.push_back( addresses.at(i) );
    }
    for (int i = stop; i >= start; i--) {
        new_addresses.push_back( addresses.at(i) );
    }
    for (int i = stop+1; i < addresses.size(); i++) {
        new_addresses.push_back( addresses.at(i) );
    }
    addresses = new_addresses;
}

// Reverses the order of the entire list
void AddressList::reverse() {
    std::vector<Address> reversed(addresses.size());
    for (int i = 0; i < addresses.size(); i++) {
        reversed.at(addresses.size()-i-1) = addresses.at(i);
    }
    addresses = reversed;
}
