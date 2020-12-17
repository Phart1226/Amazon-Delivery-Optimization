# Amazon-Delivery-Optimization
This was my final project for COE 322 Scientific Computation class in the Fall 2020 Semester. It is a twist on the traditional Traveling Salesman Problem that uses Kernighan-Lin route optimization to simulate the desired number of days' routes of a theoretical Amazon distribution center with Amazon Prime priority shipping.

# Running the Code
A User Interface has not been developed for this code yet, so to run the code simply downloade the all the cpp files and run them from your terminal of choice using the command:

To compile the code
```
g++ -o test main.cpp Address.cpp address.hpp addresslist.cpp addresslist.hpp route.cpp route.hpp
```
Then to execute the code
```
test
```
# Output
Enter the number of days you would like to simulate and the optimized delivery routes for each truck for each day will appear in the output. 
Any [x,y] coordinate with an * beside it represents an Amazon Prime delivery.

# Report
Make sure to read the Project Report pdf in this repository for a detailed descripition of the problem I was trying to tackle, the methods I used, the challenges I faced while coding the solution and how I overcame them, as well as next steps and improvements I would make to the code.

