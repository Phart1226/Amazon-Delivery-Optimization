#include <iostream>

#include "address.hpp"
#include "addresslist.hpp"
#include "route.hpp"

int main() {
    Route deliveries;
    int numAddresses = 16;
    deliveries.RandomAdd(numAddresses); // adds a number of random numAddresses to the route

    //strategy 1 (day to day distance approach)
    //create max number of deliveries a truck can make in one day
    // run through addresses in route for each truck
    //make sure primes in route for that day are delivered
    //remove addresses that fall under that max distance from route
    //combine leftover addresses from both trucks into new list
    //generate the random new addresses for the next day and redistribute
    //repeat
    double maxDist = 130;
    int numDays;
    std::cout << "Days to simulate: ";
    std::cin >> numDays;

    int currentDay = 1;
    
    //run through a number of days with the two trucks and new orders coming in everyday
    while(currentDay <= numDays){
        std::cout<<std::endl;
        std::cout<<"Day "<<currentDay<<std::endl;
        deliveries.print();
        std::cout<< "Length of original route with only one truck: " << deliveries.length() << std::endl;
        std::cout<<std::endl;
        Route notDeliveredYest = deliveries.Prime(maxDist);
        deliveries = notDeliveredYest;
        deliveries.RandomAdd(numAddresses);
        currentDay++;
    }
    
    

    //strategy 2 (continous deliveries approach)
    //create function to actually make the truck "move"
    // run through addresses in route for each truck
    //at each addresses remove it, flip coin to see if new addresses is added
    //if addresses is added function to decide which truck it should go to
    //set max number of delivieries for a day
    //once that is hit take all orders back into one list and redistribute for next day
    //repeat

}