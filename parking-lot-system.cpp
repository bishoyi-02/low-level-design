// ParkingLot: Our system will have only one object of this class. 
// This can be enforced by using the Singleton pattern. In software 
// engineering, the singleton pattern is a software design pattern 
// that restricts the instantiation of a class to only one object.

// An everyday analogy for the singleton pattern is a car key. 
// Just as there's one key that starts your car, the singleton 
// pattern ensures there's only one key to open a special door in
//  your favorite store. No matter how many shoppers there are, 
//  only one person at a time can access the hidden treasure. 


// REQUIRMENTS
// The parking lot should have multiple floors where customers can park their cars.
// The parking lot should have multiple entry and exit points.
// Customers can collect a parking ticket from the entry points and can pay the parking fee at the exit points on their way out.
// Customers can pay the tickets at the automated exit panel or to the parking attendant.
// Customers can pay via both cash and credit cards.
// Customers should also be able to pay the parking fee at the customer’s info portal on each floor. If the customer has paid at the info portal, they don’t have to pay at the exit.
// The system should not allow more vehicles than the maximum capacity of the parking lot. If the parking is full, the system should be able to show a message at the entrance panel and on the parking display board on the ground floor.
// Each parking floor will have many parking spots. The system should support multiple types of parking spots such as Compact, Large, Handicapped, Motorcycle, etc.
// The Parking lot should have some parking spots specified for electric cars. These spots should have an electric panel through which customers can pay and charge their vehicles.
// The system should support parking for different types of vehicles like car, truck, van, motorcycle, etc.
// Each parking floor should have a display board showing any free parking spot for each spot type.
// The system should support a per-hour parking fee model. For example, customers have to pay $4 for the first hour, $3.5 for the second and third hours, and $2.5 for all the remaining hours.

enum VehicleType{
    CAR,TRUCK,BIKE,VAN
};
enum ParkingSpotType{
    HANDICAPPED, COMPACT, LARGE, ELECTRIC
};
enum AccountStatus{
    ACTIVE, BLOCKED, BANNED, ARCHIVED
};
enum ParkingTicketStatus{
    ACTIVE, PAID, LOST
};

enum PaymentStatus{
    PENDING,PAID,CANCELLED,REFUND
};

class Address{
    string city;
    string state;
    string country;
    string zip;
    string street;
};

class Vehicle{
    string numberPlate;
    string registeredUser;
    string brand;
    string model;
    string color;
    VehicleType vehicleType;

    void assignTicket(ParkingTicket parkingTicket);
}

class Person{
    string name;
    Address address;
    string email;
    string phone;
};

class Account{
    string username;
    string password;
    Person person;
    AccountStatus accountStatus;

    bool resetPassword();
};

class Admin : public Account{
    bool addParkingFloor(ParkingFloor parkingFloor);
    bool addParkingSpot(ParkingFloor parkingFloor, ParkingSpot parkingSpot);
    bool addParkingDisplayBoard(ParkingFloor parkingFloor,DisplayBoard displayBoard);
    bool addCustomerInfoPanel(EntrancePanel entrancePanel);
    bool addExitPanel(ExitPanel exitPanel);
};

class ParkingAttendant : public Account{
    void processTicket(int ticketNumber);
};

class ParkingFloor{
    string name;
    unordered_set<ParkingSpot> handicappedSpots;
    unordered_set<ParkingSpot> compactSpots;
    unordered_set<ParkingSpot> largeSpots;
    unordered_set<ParkingSpot> motorbikeSpots;
    unordered_set<ParkingSpot> electricSpots;
    DisplayBoard parkingDisplayBoard;

    bool addParkingSpot(ParkingSpot parkingSpot);
    bool assignvehicleToSpot(Vehicle vehicle);
    bool updateDisplayBoard();
    bool freeSpot(ParkingSpot parkingSpot);
};

class ParkingSpot{
    int number;
    bool free;
    Vehicle vehicle;
    ParkingSpotType parkingSpotType;

    //constructor
    public:
    ParkingSpot();
    ParkingSpot(int number, ParkingSpotType parkingSpotType);

    bool isFree();
    void assignVehicle(Vehicle vehicle);
    void removeVehicle(Vehicle vehicle);
};

class HandicappedSpot : public ParkingSpot{
    HandicappedSpot(int number){
        ParkingSpot(number,ParkingSpotType::HANDICAPPED);
    }
};

class CompactSpot : public ParkingSpot{
    CompactSpot(int number){
        ParkingSpot(number,ParkingSpotType::COMPACT);
    }
};

class LargeSpot : public ParkingSpot{
    LargeSpot(int number){
        ParkingSpot(number,ParkingSpotType::LARGE);
    }
};

class ElectricSpot : public ParkingSpot{
    ElectricSpot(int number){
        ParkingSpot(number,ParkingSpotType::ELECTRIC);
    }

    ElectricPanel electricPanel;
};

class ElectricPanel{
    int paidForMinutesl
    DateTime chargingStartTime;

    bool cancelCharging();
};

class DisplayBoard{
    string id;
    HandicappedSpot handicappedFreeSpot;
    CompactSpot compactFreeSpot;
    ElectricSpot electricFreeSpot;
    LargeSpot largeFreeSpot;
    void showEmptySpotNumber();

};

class EntrancePanel{
    string id;

    bool printTicket();
}

class ExitPanel{
    string id;
    bool scanTicket();
    bool processPayment();
};

class ParkingTicket{
    string id;
    Date issuedAt;
    Date payedAt;
    double amount;
    status ParkingTicketStatus;
};

// Singleton Pattern

class ParkingLot{
    private:
        ParkingLot()=default; 
        ParkingLot(string name,Address address);
        ParkingLot(ParkingLot&)=delete; // prevent cloning
    public:
        static ParkingLot& getInstance(string name,Address address){
            static ParkingLot instance=ParkingLot(name,address);
            return instance;
        }
        string name;
        Address address;
        int compactSpotCount;
        int electricSpotCount;
        int largeSpotCount;
        int handicappedSpotCount;
        Mutex lock;

        vector<EntrancePanel> entrancePanels;
        vector<ExitPanel> exitPanels;
        vector<ParkingFloor> parkingFloors;
        unordered_set<ParkingTicket> activeTickets;

        ParkingTicket getParkingTicket(Vehicle vehicle){
            lock.acquire();
            ticket=ParkingTicket();
            vehicle.assignTicket(ticket);
            ticket.saveInDB;
            activeTickets.insert(ticket);
            lock.release();
        }

        bool isFull(VehicleType type);
        void incrementSpotCount(VehicleType type);
        void addParkingFloor(ParkingFloor floor);
        void addEntrancePanel(EntrancePanel panel);
        void addExitPanel(ExitPanel panel);
};

class Payment{
    Date creationDate;
    double amount;
    PaymentStatus status;

    bool initiateTransaction();
};

class CreditCardTransaction : public Payment{
    string name;
};

class CashTransaction : public Payment{
    double cashTendered;
};


