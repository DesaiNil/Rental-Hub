#include <bits/stdc++.h>
using namespace std;

class Vehicle {
protected:
    int vehicleID;
    string model;
    string make;
    double rentalPricePerDay;
    int totalAvailable;
    int currentlyRented;

public:
    Vehicle(int vehicleID, string model, string make, double rentalPricePerDay, int totalAvailable)
    {
        this->vehicleID = vehicleID;
        this->model = model;
        this->make = make;
        this->rentalPricePerDay = rentalPricePerDay;
        this->totalAvailable = totalAvailable;
        this->currentlyRented = 0;
    }

    virtual void getDetails() const  //cont need->important when working with objects that should not be modified, such as when passing them by reference to a function
    {
        cout << "Vehicle ID: " << vehicleID 
             << "\nModel: " << model 
             << "\nMake: " << make 
             << "\nPrice per Day: " << rentalPricePerDay 
             << "\nTotal Available: " << totalAvailable - currentlyRented << "\n";
    }

    void rent()
    {
        if (currentlyRented < totalAvailable)
         {
            currentlyRented++;
            cout << "Vehicle rented successfully.\n";
        } else {
            cout << "No vehicles available for rent.\n";
        }
    }

    void returnVehicle() 
    {
       if (currentlyRented > 0)
       {
        currentlyRented--;  // Make the vehicle available again
        cout << "Vehicle returned successfully.\n";
       } else {
        cout << "Error: All vehicles are already available.\n";
       }
    }

    bool checkAvailability() const 
    {
        return currentlyRented < totalAvailable;
    }

    virtual double calculateRent(int days)
    {
        return rentalPricePerDay * days;
    }

    int getVehicleID() const
     {
        return vehicleID;
    }
};

// class car

class Car : public Vehicle {
private:
    int numOfSeats;

public:
    public:
    Car(int id, string model, string make, double rentalPricePerDay, int totalAvailable, int numOfSeats) 
        : Vehicle(id, model, make, rentalPricePerDay, totalAvailable), numOfSeats(numOfSeats) {}

    void getDetails() const override  
    {
        cout<<"Vechile Type: Car"<<"\n";
        Vehicle::getDetails();
        cout << "Number of Seats: " << numOfSeats << "\n";
    }

    double calculateRent(int days) const 
     {
        double seatSurcharge = (numOfSeats > 2) ? (numOfSeats - 2) * 5 : 0;
        return (rentalPricePerDay + seatSurcharge) * days;
    }
    // override->
    // This ensures that the function is correctly overriding the calculateRent() method in the base class (Vehicle)
    // This tells the compiler that getDetails() is overriding the virtual function in the base class (Vehicle). If the base class function’s signature changes or doesn’t match, the compiler will give you an error..
};

// class bike

class Bike : public Vehicle {
private:
    double engineCapacity;

public:
    Bike(int id, string model, string make, double rentalPricePerDay, int totalAvailable, double engineCapacity) 
        : Vehicle(id, model, make, rentalPricePerDay, totalAvailable), engineCapacity(engineCapacity) {}

    void getDetails() const override
     {
        cout<<"Vechile Type: Bike"<<"\n";
        Vehicle::getDetails();
        cout << "Engine Capacity: " << engineCapacity << " liters\n";
    }

    double calculateRent(int days) const 
    {
        double capacitySurcharge = engineCapacity * 2;
        return (rentalPricePerDay + capacitySurcharge) * days;
    }
};

//class truck

class Truck : public Vehicle {
private:
    double loadCapacity;

public:
    Truck(int id, string model, string make, double rentalPricePerDay, int totalAvailable, double loadCapacity) 
        : Vehicle(id, model, make, rentalPricePerDay, totalAvailable), loadCapacity(loadCapacity) {}

    void getDetails() const override 
    {
        cout<<"Vechile Type: Truck"<<"\n";
        Vehicle::getDetails();
        cout << "Load Capacity: " << loadCapacity << " tons\n";
    }

    double calculateRent(int days) const 
     {
        double capacitySurcharge = loadCapacity * 10;
        return (rentalPricePerDay + capacitySurcharge) * days;
     }
};

int daysBetweenDates(const string& start, const string& end)
 {
    // The tm structure is part of C++’s <ctime> library and stores date and time information.
    // The {} initializes all the members of startDate and endDate to zero (safe initialization
    tm startDate = {}, endDate = {};
    // istringstream is used to parse the string input dates (start and end) and convert them into the tm structure format.
    // This allows us to extract date components like year, month, and day from the string.
    istringstream ssStart(start), ssEnd(end);
    // get_time() is a stream manipulator that extracts date/time information from the string and 
    //stores it in the tm structure (startDate and endDate).
    ssStart >> get_time(&startDate, "%Y-%m-%d");
    ssEnd >> get_time(&endDate, "%Y-%m-%d");
    // mktime() converts the tm structure into a time_t value, which represents the number of seconds since the epoch (January 1, 1970). 
    // This value allows easy date/time manipulation and comparison.
    time_t x = mktime(&startDate);
    time_t y = mktime(&endDate);
    //he static_cast<int> ensures that the final result is cast to an integer, 
    //representing the number of full days between the two dates.
    return static_cast<int>(difftime(y, x) / (60 * 60 * 24));
}

class Customer {
private:
    string customerID;
    string name;
    string licenseNumber;
    vector<int> rentalHistory;

public:
    Customer(string id, string name, string licenseNumber)
        : customerID(id), name(name), licenseNumber(licenseNumber) {}

    void rentVehicle(int rentalID) 
    {
        rentalHistory.push_back(rentalID);
        cout << name << " has rented vehicle with rental ID: " << rentalID << "\n";
    }

    void viewRentalHistory() const
     {
        cout << "Rental history for " << name << ":\n";
        if (rentalHistory.empty()) 
        {
            cout << "No rentals found.\n";
        } else {
            for (int rentalID : rentalHistory)
             {
                cout << "Rental ID: " << rentalID << "\n";
                cout<<  "licenseNumber : "<<licenseNumber<<"\n"; 
            }
        }
    }
    string getName() const 
    {
        return name;
    }
     string getCustomerID() const {  // Added getter method
        return customerID;
    }
};

class Rental {
private:
    int rentalID;
    Customer* customer;
    string rentalDate;        // Start date of rental
    string agreedReturnDate; // Return date specified at the time of rental
    string actualReturnDate; // Actual return date
    double penalty;
    double penaltyPerDay;

public:
    Vehicle* vehicle;

    Rental(int id, Vehicle* vehicle, Customer* customer, string rentalDate, string agreedReturnDate, double penaltyPerDay = 50.0)
        : rentalID(id), vehicle(vehicle), customer(customer), rentalDate(rentalDate), agreedReturnDate(agreedReturnDate), actualReturnDate(""), penalty(0.0), penaltyPerDay(penaltyPerDay) {}

    void setActualReturnDate(string returnDate) 
    {
        this->actualReturnDate = returnDate; // Capture actual return date
        calculatePenalty(); // Calculate penalties when the actual return date is set
    }

    // Calculate penalty based on agreed and actual return dates
    void calculatePenalty() {
        int lateDays = daysBetweenDates(agreedReturnDate, actualReturnDate); // Calculate late days
        if (lateDays > 0)
         {
            penalty = lateDays * penaltyPerDay; // Calculate penalty
        } else {
            penalty = 0.0; // No penalty if returned on time or early
        }
    }

    double calculateRent(int days) {
        return vehicle->calculateRent(days);
    }

    // Getter methods
    string getRentalDate() const { return rentalDate; }
    string getAgreedReturnDate() const { return agreedReturnDate; }
    double getPenalty() const { return penalty; }

    void getRentalDetails() const {
        cout << "Rental ID: " << rentalID << "\n";
        vehicle->getDetails();
        cout << "Customer: " << customer->getName() << "\n";
        cout << "Rental Date: " << rentalDate << "\n";
        cout << "Agreed Return Date: " << agreedReturnDate << "\n";
        if (!actualReturnDate.empty()) {
            cout << "Actual Return Date: " << actualReturnDate << "\n";
            cout << "Penalty: " << penalty << "\n";
        }
    }

    int getRentalID() const {
        return rentalID;
    }
};

Vehicle* findVehicleByID(vector<Vehicle*>& vehicles, int id) {
    for (Vehicle* vehicle : vehicles) {
        if (vehicle->getVehicleID() == id && vehicle->checkAvailability()) {
            return vehicle;
        }
    }
    return nullptr;
}

void printMenu() {
    cout << "\n=== Vehicle Rental System ===\n";
    cout << "1. View Available Vehicles\n";
    cout << "2. Rent a Vehicle\n";
    cout << "3. Return a Vehicle\n";
    cout << "4. View Rental History by Customer\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

// main function

int main() {
    vector<Vehicle*> vehicles;
    vector<Customer> customers;
    vector<Rental> rentals;
    int rentalIDCounter = 1;

    vehicles.push_back(new Car(1, "Model S", "Suzuki", 10000, 5, 4));
    vehicles.push_back(new Bike(2, "Ninja", "Kawasaki", 5000, 3, 1.2));
    vehicles.push_back(new Truck(3, "F-150", "Ford", 15000, 2, 5.0));

    int choice;

    while (true) {
        printMenu();
        cin >> choice;

        if (choice == 1) {
            cout << "\nAvailable Vehicles:\n";
            for (Vehicle* vehicle : vehicles) {
                if (vehicle->checkAvailability()) 
                {
                    vehicle->getDetails();
                    cout << "\n";
                }
            }
        } else if (choice == 2) {
            // Take customer input dynamically
            string customerName, licenseNumber, customerid;
            cout << "Enter customer name: ";
            cin.ignore();  // To avoid any leftover newlines in the input buffer i.e "\n"
            getline(cin, customerName);
            cout << "Enter customer ID: ";
            cin >> customerid;
            cout << "Enter customer license number: ";
            cin >> licenseNumber;

            customers.push_back(Customer(customerid, customerName, licenseNumber));
            Customer& currentCustomer = customers.back();

            cout << "\nEnter the vehicle ID to rent: ";
            int vehicleID;
            cin >> vehicleID;
            Vehicle* selectedVehicle =findVehicleByID(vehicles, vehicleID);
            if (selectedVehicle != nullptr) 
            {
              string rentalDate;
              string agreedReturnDate; // New variable for agreed return date
              cout << "Enter rental date (YYYY-MM-DD): ";
              cin >> rentalDate;
              cout << "Enter agreed return date (YYYY-MM-DD): "; // Prompt for agreed return date
              cin >> agreedReturnDate;
 
             selectedVehicle->rent();
             rentals.push_back(Rental(rentalIDCounter++, selectedVehicle, &currentCustomer, rentalDate, agreedReturnDate));
             currentCustomer.rentVehicle(rentalIDCounter - 1);
             cout << "Vehicle rented successfully!\n";
            } else {
            cout << "Vehicle not available for rent.\n";
            }
        }

      // Returning a vehicle
      else if (choice == 3) {
             cout << "\nEnter the rental ID to return: ";
             int rentalID;
             cin >> rentalID;

             bool found = false;
            for (Rental& rental : rentals)
             {
               if (rental.getRentalID() == rentalID) 
               {
                   string returnDate;
                   cout << "Enter actual return date (YYYY-MM-DD): "; // Prompt for actual return date
                   cin >> returnDate;

                   rental.setActualReturnDate(returnDate); // Set the actual return date
                   rental.getRentalDetails();

                   // Calculate total rent based on rental days
                   int rentalDays = daysBetweenDates(rental.getRentalDate(), rental.getAgreedReturnDate());
                   double totalRent = rental.calculateRent(rentalDays);
                   cout << "Total Rent for " << rentalDays << " day(s):  " << totalRent << "\n";

                   // Display penalty if applicable
                   double penalty = rental.getPenalty();
                   if (penalty > 0) 
                   {
                       cout << "Total Penalty for late return: " << penalty << "\n";
                       cout<< "Total Rent with Penalty: "<<totalRent + penalty <<"\n";
                   } 

                 // Properly mark vehicle as returned
                  rental.vehicle->returnVehicle();
                  found = true;
                  break;
               }
            } 

            if (!found)
             {
                 cout << "Rental ID not found.\n";
             }
        }

         else if (choice == 4) {
            cout << "Enter customer ID to view rental history: ";
            string customerID;
            cin >> customerID;

            bool found = false;
            for (Customer& customer : customers)
             {
                if (customerID == customer.getCustomerID()) 
                {
                    customer.viewRentalHistory();
                    found = true;
                    break;
                }
            }

            if (!found) 
            {
                cout << "Customer ID not found.\n";
            }
        } else if (choice == 5) {
            cout << "Exiting the program...\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    // Cleanup dynamically allocated memory
    for (Vehicle* vehicle : vehicles) {
        delete vehicle;
    }

    return 0;
}