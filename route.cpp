#include "route.hpp"

//method to preform greedy route optimization
void Route::greedyRoute() {
    AddressList route;
    Address depot;
    Address index = depot;

    while(members() > 1) {
        remove(index); //removes address of interest from the address list, this method is defined in the addresslist class
        Address closest_to = closest(index); //finds address closest to address of intrest 
        route.add(closest_to); // adds that address to the new route
        index = closest_to; // sets desired address to the closest address to previous desried address
    }
    addresses = route.getAll(); // sets order of old addresses to new route 
}

//Route optimization algorithm 
bool Route::KernighanLin() {
    bool finished = true;
    for (int start = 0; start < addresses.size()-3; start++) {
        int end_offset = 0;
        if (start == 0) {
            end_offset = 1;
        } else {
            end_offset = 0;
        }

        for (int end = start + 2; end < addresses.size()-end_offset-1; end++) {
            if (Intersect(start,end)) {
                double old_length = length();
                reverse(start+1, end);
                if( length() >= old_length ) {
                    reverse(start+1, end);
                }
                finished = false;
            }
        }
    }
    if (!finished) {
        KernighanLin();
    }
    return finished;
}

//Method to optimize the set of addresses for two trucks
void Route::TwoTrucks() {
    Route truck1, truck2;

    for (int i = 0; i < addresses.size()/2; i++) {
        truck1.add( addresses.at(i) );
    }
    for (int i = addresses.size()/2; i < addresses.size(); i++) {
        truck2.add( addresses.at(i) );
    }

    int offset = 0;

    for (int i1 = 0; i1 < truck1.members()-1; i1++) {
        if (i1 == 0) {
            offset = 1;
        } else if (i1 == truck1.members()-2) {
            offset = 1;  
        } else {
            offset = 0;
        }
        for (int i2 = offset; i2 < truck2.members()-1-offset; i2++) {
            Address p1 = truck1.get(i1);
            Address q1 = truck1.get(i1+1);
            Address p2 = truck2.get(i2);
            Address q2 = truck2.get(i2+1);
            if (Intersect(p1, q1, p2, q2)) {
                truck1.set(i1+1, q2);
                truck2.set(i2+1, q1);
            }

        }
    }
    truck1.KernighanLin();
    truck2.KernighanLin();

    
     std::cout << "The original length was: " << length() << ".\n";

     std::cout << "The route for Truck 1 is:\n";
     truck1.print();
     std::cout << "The length of Truck 1's route is: " << truck1.length() << ".\n";
     std::cout << "The route for Truck 2 is:\n";
     truck2.print();
     std::cout << "The length of Truck 2's route is: " << truck2.length() << ".\n";

}

Route Route::Prime(int maxDistDay) {
    Route truck1, truck2;
    //adds first half of addresses to truck 1
    for (int i = 0; i < addresses.size()/2; i++) {
        truck1.add( addresses.at(i) );
    }
    //adds second half od addresses to truck 2
    for (int i = addresses.size()/2; i < addresses.size(); i++) {
        truck2.add( addresses.at(i) );
    }

    int offset = 0;

    for (int i1 = 0; i1 < truck1.members()-1; i1++) {
        if (i1 == 0) {
            offset = 1;
        } else if (i1 == truck1.members()-2) {
            offset = 1;  
        } else {
            offset = 0;
        }
        for (int i2 = offset; i2 < truck2.members()-1-offset; i2++) {
            Address p1 = truck1.get(i1);
            Address q1 = truck1.get(i1+1);
            Address p2 = truck2.get(i2);
            Address q2 = truck2.get(i2+1);
            if (Intersect(p1, q1, p2, q2) && (!q1.prime()) && (!q2.prime())) {
                truck1.set(i1+1, q2);
                truck2.set(i2+1, q1);
            }

        }
    }

    truck1.greedyRoute();
    truck2.greedyRoute();
    truck1.KernighanLin();
    truck2.KernighanLin();
    
    //optimize route for amazon prime based on maxDistance for the day
    Route truck1New = truck1.ReorderRoute(maxDistDay);
    Route truck2New = truck2.ReorderRoute(maxDistDay);

    std::cout << "Route assigned to Truck 1:\n";
    truck1New.print();
    std::cout << "The length of Truck 1's route is " << truck1New.length() << "." << std::endl;
    std::cout << std::endl << "Route assigned to Truck 2:\n";
    truck2New.print();
    std::cout << "The length of Truck 2's route is " << truck2New.length() << "." << std::endl;

    //Salvage addresses from original truck routes that were not made today to add for next day
    Route endOfDay;
    truck1.addresses.insert(truck1.addresses.end()-1, truck2.addresses.begin()+1, truck2.addresses.end()-1); //combines left over addresses from both trucks into a new addresses list without the depots
    truck1.remove(Address (0,0)); //remove depot locations from the not hit yet locations
    endOfDay.addresses = truck1.addresses;
    return endOfDay;


}

//Creates an addresslist of random addresses and are randomly flagged as prime or not prime
void Route::RandomAdd(int numAdd) {

    while(numAdd > 0){
        bool prime = false; // prime default false

        // generates number -1 to -100 and 1 to 100 and averages them to get x and y coordinate
        int xVal = (-(int((rand()/ (RAND_MAX +1.0))*100)) + (int((rand()/ (RAND_MAX +1.0))*100)))/2;
        int yVal= (-(int((rand()/ (RAND_MAX +1.0))*100)) + (int((rand()/ (RAND_MAX +1.0))*100)))/2;

        if((rand() % 100) >= 70){
            prime = true;
        }
        add(Address (xVal, yVal, prime));
        numAdd--;
    }

}

//reorder addresses with all prime addresses gauranteed to get delivered during the day
Route Route::ReorderRoute(double dayDist){
    Route newDay;
    double newRouteDist;
    newDay.add(get(0)); // add depot to newDay route
    for(int spot = 0; spot < members()-1; spot++){

        //check if addresses is flagged as prime
         if(get(spot).prime()){
             newDay.add(get(spot));
             remove(spot); //removes address from original route
             spot--;
         }
    }
    //optimize for length
    newRouteDist = newDay.length();
    

    //add nonprime addresses in until maxdistance is reached
    while(newRouteDist <= dayDist){

        if(members() > 1){//check to make sure there are still addresses to get from original route
            Address newAdd = get(1); //get addresses from orginial route after the depot
            newDay.add(newAdd);
            
            //optimize/check new optimized distance
            newDay.greedyRoute();
            newDay.KernighanLin();
            if(newDay.length() < dayDist){
                remove(newAdd); //removes address from original route
                newRouteDist = newDay.length(); //set new optimized length of route
                
            }
            else{
                //remove address that caused distance to go over max
                newDay.remove(newAdd);
                //reoptimize
                newDay.greedyRoute();
                newDay.KernighanLin();
                break;
            }
        }
        else
            break;
    }

    return newDay;
}
