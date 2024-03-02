/*
* 
* Austin Martin
* 3/1/2024
* This program prompts the user to select from a menu of options
* that will guide the user through a simple process of creating a reservation
* checking in that reservation, ordering food, completing the order, and then paying the bill
* 
*/
#include <iostream>
#include <string.h>
#include <iomanip>
#include <ctype.h>
using namespace std;


// Validation function for letters
bool isValidLetterInput(char input) {
	return (input == 'Y' || input == 'N' || input == 'C');
}

// Validation function for menu choices
bool isValidMenuChoice(int choice, int maxChoice) {
	return (choice >= 1 && choice <= maxChoice);
}




enum MenuItem {
	VEGGIE_BURGER = 35,
	HAMBURGER = 45,
	FRIED_CHICKEN_SLIDERS = 38,
	HAMBURGER_SLIDERS = 38,
	VEGGIE_SLIDERS = 38,
	HADDOCK_SANDWICH = 38,
	BLT = 42,
	FAUX_BLT = 42,
	CHICKEN_BURRITO = 42,
	FALAFEL_WRAP = 42,
	CHEESE_PIZZA = 59,
	PEPPERONI_PIZZA = 59,
	FAUX_MEAT_AND_CHIPS = 77,
	FISH_AND_CHIPS = 77
} item;

struct Reservations {
	string time;
	string amORpm;
	string firstName;
	string lastName;
	int reservationSize;
	bool checkedIn = false;
} reservation;

struct Tables {
	int tableNumber;
	int size;
	int numberOfPeople;
	bool available = true;
} table;

struct Orders {
	Reservations reservation;
	Tables table;
	MenuItem items[10];
	string entreName[10];
	bool isReady = false;
	bool complete = false;
	bool paid = false;
} order;


//---- Global Variables ----//
Reservations reservations[50];
Tables tables[20];
Orders orders[50];
int numReservations = 0;
int numTables = 20;
int numOrders = 0;
//-------------------------//

void welcomeMessage()
{
	cout << "\nWelcome to Messijoes!\n"
		<< "1. Make Reservation\n"
		<< "2. Check-in Reservation\n"
		<< "3. Enter Order\n"
		<< "4. Complete Order\n"
		<< "5. Calculate and Pay Bill\n"
		<< "6. Close the restaruant.\n";
}

void createReservation() {

	if (numReservations > 50)
	{
		cout << "You are at the maximum reservations!" << endl;
	}
	else
	{												// reservation is the object storing data for firstName and lastName //				
		cout << "Enter a name for the reservation: "; cin >> reservation.firstName >> reservation.lastName; 

		do{											// reservation is the object storing data for reservationSize //
		cout << "\nEnter the number of people in the party: "; cin >> reservation.reservationSize;
			// when reservationSize is not an integer isDigit returns 0 //
		if (reservation.reservationSize < 1 || reservation.reservationSize > 10)
		{
			cout << "Party size mush be atleast 1 person and no bigger than 10 people.";
			cin.clear();
			cin.ignore(1200, '\n');
		}
		
		if (!cin >> reservation.reservationSize)
		{
			cout << "Invalid input. Please enter an integer between 1 and 10: ";
			cin.clear();
			cin.ignore(1200, '\n');
		}
		} while (reservation.reservationSize < 1 || reservation.reservationSize > 10);
		
		cout << "\nEnter the time for the reservation in HH:MM AM/PM: "; cin >> reservation.time >> reservation.amORpm;
		reservation.checkedIn = false;
		
	}
}

void confirmReservation()
{
	int i = 0;
	int response = 0;
	char choice = 0;
	// the do while statement will allow the user to make infinitely many changes until they are
	// happy with the details within the reservation
	do {
		cout << "\nPlease Confirm the reservation:";
		cout << "\nReservation Name: " << reservation.firstName << " " << reservation.lastName;
		cout << "\nReservation Time: " << reservation.time << " " << reservation.amORpm;
		cout << "\nNumber in Party: " << reservation.reservationSize;
		cout << "\nIs this information correct [Y]es, [N]o (make changes), [C]ancel? ";
		cin >> choice;
		choice = toupper(choice); // Convert to uppercase

		if (!isValidLetterInput(choice)) {
			cout << "Invalid input. Please enter 'Y', 'N', or 'C': ";
		}
		else if (choice == 'Y')
		{
			reservations[i] = reservation;
			numReservations++;
		}
		else if (choice == 'N')
		{
			cout << "What would you like to change?\n"
				<< "1. Name\n"
				<< "2. Time\n"
				<< "3. Number of people\n";
			cin >> response;
			while (!cin >> response || response < 1 || response > 3)
			{
				cout << "Enter an integer to the corresponding option.\n";
				cin.clear();
				cin.ignore(1200, '\n');
				
			}
			switch (response)
			{
			case 1:
				cout << "Enter a name for the reservation: \n" << endl;
				cin >> reservation.firstName >> reservation.lastName;
				break;
			case 2:
				cout << "Enter a time for the reservation:\n" << endl;
				cin >> reservation.time >> reservation.amORpm;
				break;
			case 3:
				cout << "Enter how the size of your party:\n" << endl;
				cin >> reservation.reservationSize;
				while (!cin >> reservation.reservationSize || reservation.reservationSize < 1 || reservation.reservationSize > 10) {
					cout << "Invalid input. Please enter an integer between 1 and 10: ";
					cin.clear();
					cin.ignore(1200, '\n');
				}
			}
		}
		else if (choice == 'C')
		{
			cout << "Reservation successfully canceled! Good bye!";
		}
		else {
			cout << "Invalid choice. You must enter Y or N or C.";
		}
	} while (choice == 'N' || !isValidLetterInput(choice));

}

void checkInReservation()
{
	int chosenReservation = 0;
	int selectedTable = 0;
	
	if (numReservations > 0) {
		cout << "Select the reservation you would like to check in:\n";
		for (int i = 0; i < numReservations; i++)
		{
			if (!reservations[i].checkedIn) // only display reservations that are not checked in
			{
				cout << i + 1 << ". "
					
					<< reservations[i].firstName << " "
					<< reservations[i].lastName << " - "
					<< reservations[i].time << " "
					<< reservations[i].amORpm << ", "
					<< reservations[i].reservationSize << " people\n";
			}
		}
		do {
			cin >> chosenReservation;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1200, '\n');
				cout << "Enter an integer to the corresponding reservation.\n";
			}
		} while (!cin.fail());

		reservations[chosenReservation - 1].checkedIn = true;	
		cout << "Reservation checked in successfully!\n";	
		numReservations--;	
		cout << "Choose a table to be seated:\n";
		for (int j = 0; j <= numTables; j++) // only display tables that are greater in size and available to be sat at
		{
			if (orders[j].table.available && orders[j].table.size >= reservations[chosenReservation - 1].reservationSize)
			{
				cout << orders[j].table.tableNumber << ". " << orders[j].table.size << " people\n";	
				do {
					cin >> selectedTable;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1200, '\n');
						cout << "Enter an integer to the corresponding table number.\n";
					}
				} while (!cin.fail());
			}
			else { cout << "\nThere are no tables available to be sat.\n"; }
		}
		
		orders[selectedTable - 1].table.available = false;

		// this sets the size of the table equal to the size of the reservation
		orders[selectedTable - 1].table.numberOfPeople = reservations[chosenReservation - 1].reservationSize;

	}
	else { cout << "You must make a reservation first." << endl; }
}

void createOrder()
{
	int j = 0;
	int entreSelection;
	int tableToOrder;
	cout << "Please select the table that is ready to order: \n";
	for (int i = 0; i < numTables; i++) // only display tables that are sat with guests
	{
		if (orders[i].isReady == false && orders[i].table.numberOfPeople > 0) 
		{
			cout << orders[i].table.tableNumber << ". Table for " << orders[i].table.numberOfPeople << " people.\n";
		}
	}
	do {
		cin >> tableToOrder;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1200, '\n');
			cout << "Enter an integer to the corresponding table number.\n";
		}
	} while (!cin.fail());
	if (numOrders < 51)
	{
		while (j < orders[tableToOrder-1].table.numberOfPeople)
		{
			cout << "Please choose for entre number " << j + 1 << ":\n";
			cout << "1: Veggie Burger\n"
				<< "2: Hamburger\n"
				<< "3: Fired Chicken Sliders\n"
				<< "4: Hamburger Sliders\n"
				<< "5: Veggie Sliders\n"
				<< "6: Haddock Sandwhich\n"
				<< "7: BLT\n"
				<< "8: Faux BLT\n"
				<< "9: Chicken Burrito\n"
				<< "10: Falafel Wrap\n"
				<< "11: Cheese Pizza\n"
				<< "12: Perpperoni Pizza\n"
				<< "13: Faux Meat adn chips\n"
				<< "14: Fish and Chips\n";
			cin >> entreSelection;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1200, '\n');
				cout << "Enter an integer between 1 and 14\n";
			}
			switch (entreSelection)
			{
				// static cast allows the program to grab the value stored at each enumeration 
				// by casting the enum variable first then we save that variable to a separate array
				// this array will be used in calculate bill and pay funct.
			case 1:
				entreSelection = VEGGIE_BURGER;
				orders[tableToOrder - 1].items[j] = static_cast<MenuItem>(entreSelection); 
				orders[tableToOrder - 1].entreName[j] = "Veggie Burger";
				numOrders++;
				break;
			case 2:
				entreSelection = HAMBURGER;
				orders[tableToOrder - 1].items[j] = static_cast<MenuItem>(entreSelection);
				orders[tableToOrder - 1].entreName[j] = "Hamburger";
				numOrders++;
				break;
			case 3:
				entreSelection = FRIED_CHICKEN_SLIDERS;
				
				orders[tableToOrder - 1].items[j] = static_cast<MenuItem>(entreSelection);
				orders[tableToOrder - 1].entreName[j] = "Fried Chicken Sliders";
				numOrders++;
				break;
			case 4:
				entreSelection = HAMBURGER_SLIDERS;
				orders[tableToOrder - 1].items[j] = static_cast<MenuItem>(entreSelection);
				orders[tableToOrder - 1].entreName[j] = "Hamburger Sliders";
				numOrders++;
				break;
			case 5:
				entreSelection = VEGGIE_SLIDERS;
				orders[tableToOrder - 1].items[j] = static_cast<MenuItem>(entreSelection);
				orders[tableToOrder - 1].entreName[j] = "Veggie Sliders";
				numOrders++;
				break;
			case 6:
				entreSelection = HADDOCK_SANDWICH;
				orders[tableToOrder - 1].items[j] = static_cast<MenuItem>(entreSelection);
				orders[tableToOrder - 1].entreName[j] = "Haddock Sandwhich";
				numOrders++;
				break;
			case 7:
				entreSelection = BLT;
				orders[tableToOrder - 1].items[j] = static_cast<MenuItem>(entreSelection);
				orders[tableToOrder - 1].entreName[j] = "BLT";
				numOrders++;
				break;
			case 8:
				entreSelection = FAUX_BLT;
				orders[tableToOrder - 1].items[j] = static_cast<MenuItem>(entreSelection);
				orders[tableToOrder - 1].entreName[j] = "Faux BLT";
				numOrders++;
				break;
			case 9:
				entreSelection = CHICKEN_BURRITO;
				orders[tableToOrder - 1].items[j] = static_cast<MenuItem>(entreSelection);
				orders[tableToOrder - 1].entreName[j] = "Chicken Burrito";
				numOrders++;
				break;
			case 10:
				entreSelection = FALAFEL_WRAP;
				orders[tableToOrder - 1].items[j] = static_cast<MenuItem>(entreSelection);
				orders[tableToOrder - 1].entreName[j] = "Falafel Wrap";
				numOrders++;
				break;
			case 11:
				entreSelection = CHEESE_PIZZA;
				orders[tableToOrder - 1].items[j] = static_cast<MenuItem>(entreSelection);
				orders[tableToOrder - 1].entreName[j] = "Cheese Pizza";
				numOrders++;
				break;
			case 12:
				entreSelection = PEPPERONI_PIZZA;
				orders[tableToOrder - 1].items[j] = static_cast<MenuItem>(entreSelection);
				orders[tableToOrder - 1].entreName[j] = "Pepperoni Pizza";
				numOrders++;
				break;
			case 13:
				entreSelection = FAUX_MEAT_AND_CHIPS;
				orders[tableToOrder - 1].items[j] = static_cast<MenuItem>(entreSelection);
				orders[tableToOrder - 1].entreName[j] = "Faux Meat and Chips";
				numOrders++;
				break;
			case 14:
				entreSelection = FISH_AND_CHIPS;
				orders[tableToOrder - 1].items[j] = static_cast<MenuItem>(entreSelection);
				orders[tableToOrder - 1].entreName[j] = "Fish and Chips";
				numOrders++;
				break;
			}
			j++;
		}	
	}else {
		cout << "The restaurant is completely full!! Have people spend pay their bill and leave." << endl;
	}
	orders[tableToOrder - 1].isReady = true;	
	cout << "\n" << numOrders; 
	// this a checker that I created to be sure the program was logically processing everything
	// Also numOrders can not be higher than 50 at any given time
}	

void completeOrder()
{
	int chosenTable;
	for (int i = 0; i < numTables; i++)
	{
		if (orders[i].table.numberOfPeople > 0 && orders[i].complete == false)	
		{
			cout << orders[i].table.tableNumber << ". Table for " << orders[i].table.numberOfPeople << endl;
			
		}
	}
	cin >> chosenTable;
	cout << "Here is your order: " << endl;
	for (int i = 0; i < orders[chosenTable - 1].table.numberOfPeople; i++)
	{
		cout << "\t" << orders[chosenTable - 1].entreName[i] << ": $" << orders[chosenTable - 1].items[i] << endl;

	}
	orders[chosenTable - 1].complete = true;
}

void calculateBill()
{
	double subtotal;
	double taxes = 0.10;
	double tip = 0.20;
	int selectedTable;
	for (int i = 0; i < 50; i++) // selecting between tables that are ready to pay
	{
		if (orders[i].complete == true && orders[i].paid == false)
		{
			cout << orders[i].table.tableNumber <<
				". Table for " <<
				orders[i].table.numberOfPeople << endl;
		}
	}
	cin >> selectedTable;

	// calculate subtotal
	for (int i = 0; i < orders[selectedTable - 1].table.numberOfPeople; i++)
	{
		subtotal += orders[selectedTable - 1].items[i];
	}
	cout << "Here is your order: " << endl;
	for (int i = 0; i < orders[selectedTable - 1].table.numberOfPeople; i++)
	{
		cout << "\t" << orders[selectedTable - 1].entreName[i] << ": $" << orders[selectedTable - 1].items[i] << endl;

	}
	cout << "\tSubtotal: $" << subtotal << endl;
	cout << "\tTip: $" << subtotal * tip << endl;
	cout << "\tTaxes: $" << subtotal * taxes << endl;
	cout << "\tTotal: $" << fixed << setprecision(2) << ((subtotal*tip) + (subtotal*taxes) + (subtotal)) << endl;
	orders[selectedTable - 1].paid = true; // resetting values
	orders[selectedTable - 1].table.available = true; // resetting values
	orders[selectedTable - 1].complete = false; // resetting values
	orders[selectedTable - 1].isReady = false; // resetting values
	numOrders -= orders[selectedTable - 1].table.numberOfPeople; // resetting values
}

int main() 
{
	
	int i;
	int response;

	for (int i = 0; i < numTables; i++)
	{

		// tables[i] = {i + 1, 2, 0, true}

		if (i < 8)
		{
			table.tableNumber = i + 1;
			table.size = 2;
			table.numberOfPeople = 0;
			table.available = true;
			orders[i].table = table;
		}
		else if (i < 14)
		{
			table.tableNumber = i + 1;
			table.size = 4;
			table.numberOfPeople = 0;
			table.available = true;
			orders[i].table = table;
		}
		else if (i < 18)
		{
			table.tableNumber = i + 1;
			table.size = 6;
			table.numberOfPeople = 0;
			table.available = true;
			orders[i].table = table;
		}
		else {
			table.tableNumber = i + 1;
			table.size = 10;
			table.numberOfPeople = 0;
			table.available = true;
			orders[i].table = table;
		}
	}
	do {
		welcomeMessage();
		cin >> response;
		if (cin.fail() || !isValidMenuChoice(response, 6)) {
			cout << "Invalid input. Please enter an integer between 1 and 6." << endl;
			cin.clear();
			cin.ignore(1200, '\n');
			continue;
		}
		switch (response)
		{
		case 1:
			createReservation();
			confirmReservation();
			break;
		case 2:
			checkInReservation();
			break;
		case 3:
			createOrder();
			break;
		case 4:
			completeOrder();
			break;
		case 5:
			calculateBill();
			break;
		case 6:
			if (numOrders == 0 && numReservations == 0)
			{
				cout << "Store is now closed. Good Bye!";
			}
			else if (numOrders > 0)
			{
				cout << "You still have orders in the restuarant!";
			}
			else
			{
				cout << "Store is closed! Good Bye!";
			}
		}
	} while (response != 6);
	
}
