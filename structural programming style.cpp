#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// Struct to represent a vehicle
struct Vehicle {
    string licensePlate;
    string vehicleType;
};

// Struct to represent a parked vehicle
struct ParkedVehicle {
    Vehicle vehicle;
};

// Struct to represent an unparked vehicle
struct UnparkedVehicle {
    Vehicle vehicle;
    double fee;
};

// Struct to represent a parking lot
struct ParkingLot {
    int availableSpaces;
    double parkingRate;
};

// Function to park a vehicle
void parkVehicle(ParkingLot& parkingLot, Vehicle& vehicle, ParkedVehicle& parkedVehicle) {
    if (parkingLot.availableSpaces == 0) {
        throw runtime_error("No available parking spaces.");
    }

    cout << "Parking a vehicle..." << endl;
    parkingLot.availableSpaces--;

    parkedVehicle.vehicle = vehicle;

    cout << "Vehicle parked." << endl;
}

// Function to unpark a vehicle
void unparkVehicle(ParkingLot& parkingLot, Vehicle& vehicle, UnparkedVehicle& unparkedVehicle) {
    if (parkingLot.availableSpaces == 0) {
        throw runtime_error("No vehicle is currently parked.");
    }

    cout << "Unparking the vehicle..." << endl;
    double duration = 30.0;  // Calculate the duration of parking in minutes (fixed duration for simplicity)
    double fee = parkingLot.parkingRate * duration / 60.0;  // Calculate the fee based on the duration
    parkingLot.availableSpaces++;

    unparkedVehicle.vehicle = vehicle;
    unparkedVehicle.fee = fee;

    cout << "Vehicle unparked." << endl;
}

int main() {
    int parkingSpaces;
    double parkingRate;

    cout << "Enter the number of parking spaces: ";
    cin >> parkingSpaces;

    if (parkingSpaces <= 0) {
        cout << "Invalid number of parking spaces. Exiting the program." << endl;
        return 1;
    }

    cout << "Enter the parking rate per hour: ";
    cin >> parkingRate;

    ParkingLot parkingLot;
    parkingLot.availableSpaces = parkingSpaces;
    parkingLot.parkingRate = parkingRate;

    string licensePlate;
    string vehicleType;

    cout << "Enter the license plate: ";
    cin >> licensePlate;

    cout << "Enter the vehicle type: ";
    cin >> vehicleType;

    Vehicle vehicle;
    vehicle.licensePlate = licensePlate;
    vehicle.vehicleType = vehicleType;

    try {
        ParkedVehicle parkedVehicle;
        parkVehicle(parkingLot, vehicle, parkedVehicle);
        cout << "Parked Vehicle License Plate: " << parkedVehicle.vehicle.licensePlate << endl;
        cout << "Parked Vehicle Type: " << parkedVehicle.vehicle.vehicleType << endl;

        cout << "Available Parking Spaces: " << parkingLot.availableSpaces << endl;

        cout << "Enter the license plate of the vehicle to unpark: ";
        cin >> licensePlate;

        Vehicle unparkedVehicle;
        unparkedVehicle.licensePlate = licensePlate;

        try {
            UnparkedVehicle unparked;
            unparkVehicle(parkingLot, unparkedVehicle, unparked);
            cout << "Unparked Vehicle License Plate: " << unparked.vehicle.licensePlate << endl;
            cout << "Unparked Vehicle Type: " << unparked.vehicle.vehicleType << endl;
            cout << "Parking Fee: $" << unparked.fee << endl;
        } catch (const runtime_error& error) {
            cout << "Error: " << error.what() << endl;
        }

        cout << "Available Parking Spaces: " << parkingLot.availableSpaces << endl;
    } catch (const runtime_error& error) {
        cout << "Error: " << error.what() << endl;
    }

    return 0;
}
