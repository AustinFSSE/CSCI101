#include <iostream>
#include <string.h>
#include <iomanip>
#include <ctype.h>
using namespace std;

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
	{
		cout << "Enter a name for the reservation: "; cin >> reservation.firstName >> reservation.lastName;
		do { 
			cout << "\nEnter the number of people in the party: "; cin >> reservation.reservationSize;
			if (cin.fail())
			{
				if (reservation.reservationSize > 10)
				{
					cout << "The maximum party size is 10. Try again :(" << endl;
				}
				if (isdigit(reservation.reservationSize) == 0)
				{
					cout << "\nYou must enter an integer.\n";
				}
				cin.clear();
				cin.ignore(1200, '\n');

			}
				
		} while (reservation.reservationSize > 10 || isdigit(reservation.reservationSize) == 0);
		cout << "\nEnter the time for the reservation in HH:MM AM/PM: "; cin >> reservation.time >> reservation.amORpm;
		reservation.checkedIn = false;
	}
}

void confirmReservation()
{
	int response = 0;
	char choice = 0;
	do {
		cout << "\nPlease Confirm the reservation:";
		cout << "\nReservation Name: " << reservation.firstName << " " << reservation.lastName;
		cout << "\nReservation Time: " << reservation.time << " " << reservation.amORpm;
		cout << "\nNumber in Party: " << reservation.reservationSize;
		cout << "\nIs this information correct [Y]es, [N]o (make changes), [C]ancel? ";
		cin >> choice;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1200, '\n');
			cout << "You must enter a letter (Y/N/C) and the entry must be captialized.\n";
		}
		if (choice == 'Y')
		{
			reservations[numReservations] = reservation;
			numReservations++;
		}
		else if (choice == 'N')
		{
			cout << "What would you like to change?\n"
				<< "1. Name\n"
				<< "2. Time\n"
				<< "3. Number of people";
			cin >> response;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1200, '\n');
				cout << "Enter an integer to the corresponding option.\n";
			}
			switch (response)
			{
			case 1:
				cout << "Enter a name for the reservation: ";
				cin >> reservation.firstName >> reservation.lastName;
				break;
			case 2:
				cout << "Enter a time for the reservation: ";
				cin >> reservation.time >> reservation.amORpm;
				break;
			case 3:
				cout << "Enter how the size of your party: ";
				cin >> reservation.reservationSize;
			}
		}
		else if (choice == 'C')
		{
			cout << "Reservation successfully canceled! Good bye!";
		}
		else {
			cout << "Invalid choice. You must enter Y or N or C.";
		}
	} while (choice == 'N');

}

void checkInReservation()
{
	int chosenReservation = 0;
	int selectedTable = 0;
	
	if (numReservations > 0) {
		cout << "Select the reservation you would like to check in:\n";
		for (int i = 0; i < numReservations; i++)
		{
			if (!reservations[i].checkedIn)
			{
				cout << i + 1 << ". "
					
					<< reservations[i].firstName << " "
					<< reservations[i].lastName << " - "
					<< reservations[i].time << " "
					<< reservations[i].amORpm << ", "
					<< reservations[i].reservationSize << " people\n";
			}
		}
		cin >> chosenReservation;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1200, '\n');
			cout << "Enter an integer to the corresponding reservation.\n";
		}
		reservations[chosenReservation - 1].checkedIn = true;
		cout << "Reservation checked in successfully!\n";
		cout << "Choose a table to be seated:\n";
		for (int j = 0; j <= numTables; j++)
		{
			if (orders[j].table.available && orders[j].table.size >= reservations[chosenReservation - 1].reservationSize)
			{
				cout << orders[j].table.tableNumber << ". " << orders[j].table.size << " people\n";	
				cin >> selectedTable;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1200, '\n');
					cout << "Enter an integer to the corresponding table number.\n";
				}
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
	for (int i = 0; i < numTables; i++)
	{
		if (orders[i].isReady == false && orders[i].table.numberOfPeople > 0)	
		{
			cout << orders[i].table.tableNumber << ". Table for " << orders[i].table.numberOfPeople << " people.\n";
		}
	}
	cin >> tableToOrder;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1200, '\n');
		cout << "Enter an integer to the corresponding table number.\n";
	}
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
	for (int i = 0; i < 50; i++)
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
	orders[selectedTable - 1].paid = true;
	orders[selectedTable - 1].table.available = true;
	orders[selectedTable - 1].complete = false;
	orders[selectedTable - 1].isReady = false;
	numOrders -= orders[selectedTable - 1].table.numberOfPeople;
}

int main() 
{
	
	int i;
	int response;

	for (int i = 0; i < numTables; i++)
	{

		//tables[i] = {i + 1, 2, 0, true}

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
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1200, '\n');
			cout << "Enter an integer between 1 and 6\n";
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
			cout << "Store is now closed. Good Bye!";
		}
	} while (response != 6);
	
}
