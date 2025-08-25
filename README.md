# Rental Hub

**Rental Hub** is a simple C++ console application for managing vehicle rentals. It allows renting and returning vehicles, tracking rental history, and calculating rent and penalties for late returns.  

---

## Project Overview

Rental Hub is a small, single-executable project designed to demonstrate basic rental management using object-oriented C++ programming. It currently supports **Cars, Bikes, and Trucks** and maintains in-memory records of vehicles, customers, and rental transactions.

---

## Functionality

- Rent and return vehicles with availability checks.
- Calculate rent based on vehicle type and rental duration.
- Track customer rental history.
- Compute penalties for late returns.
- Display detailed vehicle and rental information.

---

## Classes

### Vehicle (Base Class)
- Fields: `vehicleID`, `model`, `make`, `rentalPricePerDay`, `totalAvailable`, `currentlyRented`
- Responsibilities: hold common vehicle data, check availability, rent/return vehicles, calculate basic rent.
- Key Methods: `getDetails()`, `rent()`, `returnVehicle()`, `checkAvailability()`, `calculateRent(int days)`

### Car (Derived from Vehicle)
- Extra Field: `numOfSeats`
- Responsibilities: car-specific details and rent calculation with seat-based surcharge.
- Key Methods: overrides `getDetails()` and `calculateRent(int days)`

### Bike (Derived from Vehicle)
- Extra Field: `engineCapacity`
- Responsibilities: bike-specific details and rent calculation with engine-capacity surcharge.
- Key Methods: overrides `getDetails()` and `calculateRent(int days)`

### Truck (Derived from Vehicle)
- Extra Field: `loadCapacity`
- Responsibilities: truck-specific details and rent calculation with load-capacity surcharge.
- Key Methods: overrides `getDetails()` and `calculateRent(int days)`

### Customer
- Fields: `customerID`, `name`, `licenseNumber`, `rentalHistory` (list of rental IDs)
- Responsibilities: track customer identity and rental history
- Key Methods: `rentVehicle(int rentalID)`, `viewRentalHistory()`

### Rental
- Fields: `rentalID`, pointer to `Vehicle`, pointer to `Customer`, `rentalDate`, `agreedReturnDate`, `actualReturnDate`, `penalty`, `penaltyPerDay`
- Responsibilities: manage rental transactions, compute rent and penalties, display rental details
- Key Methods: `setActualReturnDate()`, `calculatePenalty()`, `calculateRent(int days)`, `getRentalDetails()`

### Helper Functions
- `daysBetweenDates(start, end)` — calculates days between two `YYYY-MM-DD` dates.
- `findVehicleByID(vehicles, id)` — finds an available vehicle by ID.

---

## Tech Stack

- **Language:** C++
- **Compiler:** GCC (MinGW / MSYS2) or Microsoft Visual C++ (MSVC)
- **Platform:** Windows (PowerShell commands used for examples)

---

## How to Run

1. **Compile the source code:**  
   ```powershell
   g++ rental.cpp -o rental.exe

#Author
Nilesh Desai
