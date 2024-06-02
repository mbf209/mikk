#include <iostream>
#include <string>
#include <stdexcept>

class Vehicle {
private:
    std::string licensePlate;
    std::string vehicleType;

public:
    Vehicle(const std::string& plate, const std::string& type)
        : licensePlate(plate), vehicleType(type) {}

    std::string getLicensePlate() const {
        return licensePlate;
    }

    std::string getVehicleType() const {
        return vehicleType;
    }
};

class ParkedVehicle {
private:
    Vehicle vehicle;

public:
    ParkedVehicle(const Vehicle& v)
        : vehicle(v) {}

    const Vehicle& getVehicle() const {
        return vehicle;
    }
};

class UnparkedVehicle {
private:
    Vehicle vehicle;
    double fee;

public:
    UnparkedVehicle(const Vehicle& v, double f)
        : vehicle(v), fee(f) {}

    const Vehicle& getVehicle() const {
        return vehicle;
    }

    double getFee() const {
        return fee;
    }
};

class ParkingLot {
private:
    int availableSpaces;
    Vehicle* parkedVehicle;
    double parkingRate;

public:
    ParkingLot(int spaces, double rate)
        : availableSpaces(spaces), parkedVehicle(nullptr), parkingRate(rate) {}

    ParkedVehicle park(const Vehicle& vehicle) {
        if (parkedVehicle != nullptr) {
            throw std::runtime_error("A vehicle is already parked.");
        }

        std::cout << "Parking a vehicle..." << std::endl;
        parkedVehicle = new Vehicle(vehicle);
        availableSpaces--;

        std::cout << "Vehicle parked." << std::endl;
        return ParkedVehicle(*parkedVehicle);
    }

    UnparkedVehicle unpark(const Vehicle& vehicle) {
        if (parkedVehicle == nullptr) {
            throw std::runtime_error("No vehicle is currently parked.");
        }

        if (vehicle.getLicensePlate() != parkedVehicle->getLicensePlate()) {
            throw std::runtime_error("Invalid license plate. Vehicle is not parked.");
        }

        std::cout << "Unparking the vehicle..." << std::endl;
        double duration = calculateDuration();  // Calculate the duration of parking in minutes
        double fee = calculateFee(duration);    // Calculate the fee based on the duration
        UnparkedVehicle unparkedVehicle(*parkedVehicle, fee);
        delete parkedVehicle;
        parkedVehicle = nullptr;
        availableSpaces++;

        std::cout << "Vehicle unparked." << std::endl;
        return unparkedVehicle;
    }

    int getAvailableSpaces() const {
        return availableSpaces;
    }

    double getParkingRate() const {
        return parkingRate;
    }

    ~ParkingLot() {
        if (parkedVehicle != nullptr) {
            delete parkedVehicle;
            parkedVehicle = nullptr;
        }
    }

private:
    double calculateDuration() const {
        // You can implement the logic to calculate the duration of parking here
        // For simplicity, we'll assume a fixed duration of 30 minutes
        return 30.0;  // 30 minutes
    }

    double calculateFee(double duration) const {
        // You can implement any fee calculation logic here based on the duration
        // For simplicity, we'll use a flat rate per minute
        return parkingRate * duration / 60.0;
    }
};

int main() {
    int parkingSpaces;
    double parkingRate;

    std::cout << "Enter the number of parking spaces: ";
    std::cin >> parkingSpaces;

    if (parkingSpaces <= 0) {
        std::cout << "Invalid number of parking spaces. Exiting the program." << std::endl;
        return 1;
    }

    std::cout << "Enter the parking rate per hour: ";
    std::cin >> parkingRate;

    ParkingLot parkingLot(parkingSpaces, parkingRate);

    std::string licensePlate;
    std::string vehicleType;

    std::cout << "Enter the license plate: ";
    std::cin >> licensePlate;

    std::cout << "Enter the vehicle type: ";
    std::cin >> vehicleType;

    Vehicle vehicle(licensePlate, vehicleType);

    try {
        ParkedVehicle parkedVehicle = parkingLot.park(vehicle);
        std::cout << "Parked Vehicle License Plate: " << parkedVehicle.getVehicle().getLicensePlate() << std::endl;
        std::cout << "Parked Vehicle Type: " << parkedVehicle.getVehicle().getVehicleType() << std::endl;

        std::cout << "Available Parking Spaces: " << parkingLot.getAvailableSpaces() << std::endl;

        std::cout << "Enter the license plate of the vehicle to unpark: ";
        std::cin >> licensePlate;

        Vehicle unparkedVehicle(licensePlate, "");  // Only license plate is needed for unparking

        try {
            UnparkedVehicle unparked = parkingLot.unpark(unparkedVehicle);
            std::cout << "Unparked Vehicle License Plate: " << unparked.getVehicle().getLicensePlate() << std::endl;
            std::cout << "Unparked Vehicle Type: " << unparked.getVehicle().getVehicleType() << std::endl;
            std::cout << "Parking Fee: $" << unparked.getFee() << std::endl;
        } catch (const std::runtime_error& error) {
            std::cout << "Error: " << error.what() << std::endl;
        }

        std::cout << "Available Parking Spaces: " << parkingLot.getAvailableSpaces() << std::endl;
    } catch (const std::runtime_error& error) {
        std::cout << "Error: " << error.what() << std::endl;
    }

    return 0;
}
