#include <iostream>
#include <cstring>

using namespace std;

class Event
{
protected:
    char eventName[50];

public:
    Event()
    {
        chooseEventType();
    }

    ~Event()
    {
        cout << "Event '" << eventName << "' destroyed.\n";
    }

    void chooseEventType()
    {
        int choice;
        cout << "Choose Event Type:\n";
        cout << "1. Birthday Party\n2. Wedding Ceremony\n3. Engagement\n4. Family Gathering\n5. School Event\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            strcpy_s(eventName, "Birthday Party");
            break;
        case 2:
            strcpy_s(eventName, "Wedding Ceremony");
            break;
        case 3:
            strcpy_s(eventName, "Engagement");
            break;
        case 4:
            strcpy_s(eventName, "Family Gathering");
            break;
        case 5:
            strcpy_s(eventName, "School Event");
            break;
        default:
            cout << "Invalid choice.\n";
            strcpy_s(eventName, "Birthday Party");
        }
    }

    void display() {
        cout << "Event Type: " << eventName << "\n";
    }
};

class Attendees : public Event {
protected:
    int numberOfAttendees;

public:
    Attendees() {
        cout << "Enter Number of Attendees: ";
        cin >> numberOfAttendees;
    }

    ~Attendees() {
        cout << "Attendees for '" << eventName << "' class destroyed.\n";
    }

    void display() {
        Event::display();
        cout << "Number of Attendees: " << numberOfAttendees << "\n";
    }
};

class VenueHall : public Attendees {
protected:
    int hallNumber;

public:
    VenueHall() : hallNumber(0) {
        suggestHall();
    }

    ~VenueHall() {
        cout << "Venue Hall suggestion for '" << eventName << "' destroyed.\n";
    }

    void display() {
        Attendees::display();
        cout << "Suggested Hall Number: \n " << hallNumber << "\n";
    }

private:
    void suggestHall() {
        if (numberOfAttendees <= 50) {
            hallNumber = 1;
        }
        else if (numberOfAttendees <= 150) {
            hallNumber = 2;
        }
        else if (numberOfAttendees <= 500) {
            hallNumber = 3;
        }
        else {
            cout << "Invalid choice. Too many attendees. Unable to suggest a hall.\n";
        }
    }
};

class Budget : public VenueHall {
protected:
    double userBudget;

public:
    Budget() {
        enterBudget();
    }

    ~Budget() {
        cout << "Budget for '" << eventName << "' class destroyed.\n";
    }

    void display() {
        VenueHall::display();
        cout << "User's Budget: Rs" << userBudget << "\n";
    }

    void menu() {
        char choice;
        do {
            cout << "Press 0 to go back to the menu. Otherwise, enter any other number to display the deal. To end the program, type 'E': \n ";
            cin >> choice;

            if (toupper(choice) == 'E') {
                cout << "Ending the program. Thank you!\n";
                exit(0);
            }
            else if (choice == '0') {
                chooseEventType();
            }
            else {
                displayDeal();
            }
        } while (true);
    }

private:
    void enterBudget() {
        cout << "Enter Your Budget (Rs10000, Rs30000, Rs50000, Rs100000): Rs\n";
        cin >> userBudget;
    }

    void displayDeal() {

        cout << "Deal: ";
        if (userBudget <= 10000) {
            cout << "Decor and Food\n";
        }
        else if (userBudget <= 30000) {
            cout << "Decor, Photography, and Food\n";
        }
        else if (userBudget <= 50000) {
            cout << "Decor, Photography, Music, and Food\n";
        }
        else if (userBudget >= 100000) {
            cout << "Decor, Photography, Food, Live Music Performance\n";
        }
        else {
            cout << "No valid deal for the entered budget.\n";
        }
    }
};

template <typename T>
class DataBook {
private:
    T** data;
    int size;
    int currentIndex;

public:
    DataBook(int sz) : size(sz), currentIndex(0)
    {
        data = new T * [size];
    }

    ~DataBook() {
        for (int i = 0; i < currentIndex; ++i) {
            delete data[i];
        }
        delete[] data;
    }

    void addEvent(T* event) {
        if (currentIndex < size) {
            data[currentIndex++] = event;
        }
        else {
            cout << "Data book is full. Cannot add more events.\n";
        }
    }

    void displayEvents() {
        for (int i = 0; i < currentIndex; ++i) {
            data[i]->display();
            data[i]->menu();
            cout << "------------------------------------------------\n";
        }
    }
};

int main()
{
    cout << "//*****************//\n";

    cout << "WELCOME TO SAIRA EVENT MANAGEMENT SYSTEM\n";

    int bookSize;

    cout << "\nEnter the size of the data book: ";
    cin >> bookSize;

    DataBook<Budget> eventBook(bookSize); //object of databook<called eventBook 

    for (int i = 0; i < bookSize; ++i) {
        Budget* newEvent = new Budget();
        eventBook.addEvent(newEvent);
    }

    eventBook.displayEvents();

    return 0;
}