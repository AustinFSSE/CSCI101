#include <iostream>
#include <string.h>
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
	int numItems;
	bool complete = false;
	bool paid = false;
} order;

Reservations reservations[50];
Tables tables[20];
Orders orders[50];

struct Bills
{
	Tables tables;
	Orders order;
	int subtotal;
	int taxes = 0.07;
	int tip = 0.20;
	int total;
} bill;

int numReservations = 0;
int numTables = 20;
int numOrders = 50;

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

	if (numReservations >= 50)
	{
		cout << "You are at the maximum reservations!" << endl;
	}
	else
	{
		cout << "Enter a name for the reservation: "; cin >> reservation.firstName >> reservation.lastName;
		cout << "\nEnter the number of people in the party: "; cin >> reservation.reservationSize;
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
		reservations[chosenReservation - 1].checkedIn = true;
		cout << "Reservation checked in successfully!\n";
		cout << "Choose a table to be seated:\n";
		for (int j = 0; j <= numTables; j++)
		{
			if (tables[j].available && tables[j].size >= reservations[chosenReservation - 1].reservationSize)
			{
				cout << tables[j].tableNumber << ". " << tables[j].size << " people\n";
			}
		}
		cin >> selectedTable;
		tables[selectedTable - 1].available = false;

		// this sets the size of the table equal to the size of the reservation
		order.table.tableNumber = selectedTable;
		tables[selectedTable - 1].numberOfPeople = reservations[chosenReservation - 1].reservationSize;
	}
	else { cout << "You must make a reservation first." << endl; }
}

void createOrder()
{
	int entreSelection;
	int tableToOrder;
	cout << "Please select the table that is ready to order: \n";
	for (int i = 0; i < numTables; i++)
	{
		if (tables[i].numberOfPeople > 0)
		{
			cout << tables[i].tableNumber << ". Table for " << tables[i].numberOfPeople << " people.\n";
		}
	}
	cin >> tableToOrder;

	// adding table number and number of people inside the table array to the order object inside the Orders struct
	order.table.tableNumber = tables[tableToOrder - 1].tableNumber;
	order.table.numberOfPeople = tables[tableToOrder - 1].numberOfPeople;
	if (numOrders < 51)
	{
		for (int j = 0; j < order.table.numberOfPeople; j++)
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

			switch (entreSelection)
			{
			case 1:
				entreSelection = VEGGIE_BURGER;
				order.items[j] = static_cast<MenuItem>(entreSelection);
				numOrders++;
				break;
			case 2:
				entreSelection = HAMBURGER;
				order.items[j] = static_cast<MenuItem>(entreSelection);
				numOrders++;
				break;
			case 3:
				entreSelection = FRIED_CHICKEN_SLIDERS;
				order.items[j] = static_cast<MenuItem>(entreSelection);
				numOrders++;
				break;
			case 4:
				entreSelection = HAMBURGER_SLIDERS;
				order.items[j] = static_cast<MenuItem>(entreSelection);
				numOrders++;
				break;
			case 5:
				entreSelection = VEGGIE_SLIDERS;
				order.items[j] = static_cast<MenuItem>(entreSelection);
				numOrders++;
				break;
			case 6:
				entreSelection = HADDOCK_SANDWICH;
				order.items[j] = static_cast<MenuItem>(entreSelection);
				numOrders++;
				break;
			case 7:
				entreSelection = BLT;
				order.items[j] = static_cast<MenuItem>(entreSelection);
				numOrders++;
				break;
			case 8:
				entreSelection = FAUX_BLT;
				order.items[j] = static_cast<MenuItem>(entreSelection);
				numOrders++;
				break;
			case 9:
				entreSelection = CHICKEN_BURRITO;
				order.items[j] = static_cast<MenuItem>(entreSelection);
				numOrders++;
				break;
			case 10:
				entreSelection = FALAFEL_WRAP;
				order.items[j] = static_cast<MenuItem>(entreSelection);
				numOrders++;
				break;
			case 11:
				entreSelection = CHEESE_PIZZA;
				order.items[j] = static_cast<MenuItem>(entreSelection);
				numOrders++;
				break;
			case 12:
				entreSelection = PEPPERONI_PIZZA;
				order.items[j] = static_cast<MenuItem>(entreSelection);
				numOrders++;
				break;
			case 13:
				entreSelection = FAUX_MEAT_AND_CHIPS;
				order.items[j] = static_cast<MenuItem>(entreSelection);
				numOrders++;
				break;
			case 14:
				entreSelection = FISH_AND_CHIPS;
				order.items[j] = static_cast<MenuItem>(entreSelection);
				numOrders++;
				break;
			}

		}
		orders[tableToOrder] = order;
	}
		
	
}

void completeOrder()
{
	int chosenTable;
	for (int i = 0; i < 20; i++)
	{
		if (orders[i].table.numberOfPeople > 0 )
		{
			cout << "Table Number: " << orders[i].table.tableNumber << " Table for " << orders[i].table.numberOfPeople << "\n";
		}
	}
	cin >> chosenTable;
	orders[chosenTable - 1].complete = true;
}

int main() 
{
	
	int i;
	int response;

	for (int i = 0; i < numTables; i++)
	{

		//tbales[i] = {i + 1, 2, 0, true}

		if (i < 8)
		{
			table.tableNumber = i + 1;
			table.size = 2;
			table.numberOfPeople = 0;
			table.available = true;
			tables[i] = table;
		}
		else if (i < 14)
		{
			table.tableNumber = i + 1;
			table.size = 4;
			table.numberOfPeople = 0;
			table.available = true;
			tables[i] = table;
		}
		else if (i < 18)
		{
			table.tableNumber = i + 1;
			table.size = 6;
			table.numberOfPeople = 0;
			table.available = true;
			tables[i] = table;
		}
		else {
			table.tableNumber = i + 1;
			table.size = 10;
			table.numberOfPeople = 0;
			table.available = true;
			tables[i] = table;
		}
	}
	do {
		welcomeMessage();
		cin >> response;

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
			//calculateBil();
			//payBill();
			break;
		case 6:
			cout << "Store is now closed. Good Bye!";
		}
	} while (response != 6);
}