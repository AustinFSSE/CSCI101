# CSCI101
This repository will contain my final project for my Computer Science 101 course.

C++ Standard Version: 201703

g++.exe (GCC) 11.2.0

nothing else should be needed. 

Maurice used to work in IT but decided it was time for a career change.  He opened a restaurant called MessiJoes. You will be creating a program to help manage the restaurant operations. Your program must take reservations and check customers in when they arrive. You will also need to manage the orders by allowing for order entry and marking an order as completed. The final functionality should calculate and enter payment for customer bills. The program must meet the following requirements:

You will need to create a struct to manage a reservation. A reservation will be for a certain time, have the customer name, and the number of people.
You will need to create a struct to manage a table.  Tables have a size that determines the maximum number of people that can sit at them.  When a reservation is checked in, the group will be assigned to a table that is large enough to hold the group. You should also keep track of the number of people currently seated at the table and if the table is free to be used or if it is currently being used. Each table should have a table number.
You will need to create an enumeration to manage the menu items.  The menu will consist of the following items.

  
You will need to create a struct to manage an order.  The order needs to be associated with a table and a customer reservation. It should contain an array of menu items that represents the items ordered by the customers at that table. It should also have the number of items ordered (1 per person in the party). There are booleans that represent if the order is complete meaning that it has been delivered to the table and if it has been paid.
You will need to create arrays to manage the tables, reservations, and orders.
The restaurant has 20 tables

     
The largest party the restaurant can handle for a reservation is 10 people. For an order, the max number of items ordered is also 10 (1 per person).
There can be 50 reservations at most.
There is 1 order per reservation, so there are also, at most, 50 orders.
The main UI for the program will be a menu that has the following options
Make Reservation
This option collects information and adds a reservation to the system.
Check-in for reservation. 
This option displays all reservations that haven't yet checked in and allows you to check in the reservation and assign it to a table.
Enter Order
Enters an order for a table.
Complete Order
Marks an order as completed which means it has been delivered to a table and is ready to be paid for.
Calculate and pay the bill
Calculates the bill based on the menu prices listed above with the menu items.  A 20% tip and 10% tax should be added to the final total. The tip amount is calculated based on the subtotal without the tax added in.
Close the restaurant
This option will only show up if there are no pending reservations and there are no outstanding orders (orders that are not completed and not paid for), and when chosen, it exits the program.
You must have at least 3 functions.  Any functions pulled from class demos do not count toward the 3.
You can create additional structs/arrays as needed, but you cannot use classes, pointers, vectors, or other constructs not covered during the semester.
