#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
#include <iterator>
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    list<Goat> trip;            //
    int choice = main_menu();   //

    while (choice != 4) {
        if (choice == 1) {
            add_goat(trip, names, colors);
        }
        else if (choice == 2) {
            delete_goat(trip);
        }
        else if (choice == 3) {
            display_trip(trip);
        }
        cout << "\n";
        choice = main_menu();
    }

    return 0;
}

int main_menu() {
    int choice;
    
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "Choice --> ";
    
    do {
        cin >> choice;
        if (choice < 1 || choice > 4) {
            cout << "Invalid number. Please enter 1, 2, 3, or 4.\n";
            cout << "Choice --> ";
        }
    } while (choice < 1 || choice > 4);

    return choice;

}

// Function to allow the user to input an integer to select a goat
int select_goat(list<Goat> trip) {
    int choice;

    display_trip(trip);

    cout << "Select a goat number to delete.\n";
    cout << "Choice --> ";

    // Validate the user's choice
    do {
        cin >> choice;
        if (choice < 1 || choice > trip.size()) {
            cout << "Invalid number. Please enter one of the numbers from the list.\n";
            cout << "Choice --> ";
        }
    } while (choice < 1 || choice > trip.size());

    return choice;
}

void add_goat(list<Goat>& trip, string names[], string colors[]) {
    string name = names[rand() % SZ_NAMES];     // Randomly select a name from the array
    string color = colors[rand() % SZ_COLORS];  // Randomly select a color from the array
    int age = rand() % (MAX_AGE + 1);           // Randomly select an age between 0 and MAX_AGE (inclusive)

    Goat newGoat(name, age, color);             // Create a new goat using the name, age, and color
    trip.push_back(newGoat);                    // Add the new goat to the trip using list's push_back() function
    cout << "Successfully added a goat.\n";
}

void delete_goat(list<Goat>& trip) {
    if (trip.empty()) {
        cout << "No goats are currently in the trip.\n";
        cout << "No goats have been deleted.\n";
        return;
    }

    int index = select_goat(trip);  // Ask the user what goat to delete

    auto it = trip.begin();         // Create an iterator at the beginning of the list
    advance(it, index - 1);         // Advance the iterator to the position where we want to delete (1-based index)

    trip.erase(it);                 // Delete the goat using the list's erase() function and the iterator
}

void display_trip(list<Goat> trip) {
    if (trip.empty()) {
        cout << "No goats are currently in the trip.\n";
        return;
    }
    
    int index = 1;
    // Traverse the list using a range-based for loop
    for (Goat goat : trip) {
        cout << "\t[" << index << "] " << goat.get_name() << " (" << goat.get_age() << ", " << goat.get_color() << ")\n";
        ++index;
    }
}