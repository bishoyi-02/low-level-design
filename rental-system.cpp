// The system will support the renting of different automobiles like cars, trucks, SUVs, vans, and motorcycles.
// Each vehicle should be added with a unique barcode and other details, including a parking stall number which helps to locate the vehicle.
// The system should be able to retrieve information like which member took a particular vehicle or what vehicles have been rented out by a specific member.
// The system should collect a late-fee for vehicles returned after the due date.
// Members should be able to search the vehicle inventory and reserve any available vehicle.
// The system should be able to send notifications whenever the reservation is approaching the pick-up date, as well as when the vehicle is nearing the due date or has not been returned within the due date.
// The system will be able to read barcodes from vehicles.
// Members should be able to cancel their reservations.
// The system should maintain a vehicle log to track all events related to the vehicles.
// Members can add rental insurance to their reservation.
// Members can rent additional equipment, like navigation, child seat, ski rack, etc.
// Members can add additional services to their reservation, such as roadside assistance, additional driver, wifi, etc.


// #include<iostream.h>
using namespace std;

enum BillItemType{
    BASE_CHARGE,
    ADDITIONAL_SERVICE,
    FINE,
    OTHER
};

enum VehicleLogType{
    ACCIDENT,
    FUELING,
    CLEANING_SERVICE,
    OIL_CHANGE,
    REPAIR,
    OTHER
};

enum VehicleType{
    VAN,
    CAR,
    TRUCK,
};

enum VanType{
    PASSENGER,
    CARGO,
};

enum CarType{
    ECONOMY,
    SUV,
    PREMIUM,
    LUXURY
};

enum TruckType{
    CARGO,
};

enum VehicleStatus{
    AVAILABLE,
    RESERVED,
    LOANED,
    LOST,
    OTHER
};

enum ReservationStatus{
    ACTIVE,
    PENDING,
    CONFIRMED,
    COMPLETED,
    CNACELLED
};

enum AccountStatus{
    ACTIVE,
    CLOSED,
    CANCELLED,
    BLOCKED,
    NONE
};

enum PaymentStatus{
    UNPAID,
    PENDING,
    COMPLETED,
    REFUNDED
};

class Address{
    string street_address;
    string city;
    string state;
    string pincode;
    string country;
};

class Person{
    string name;
    Address address;
    string email;
    string phone;
};

class Account{
    string id;
    string password;
    AccountStatus status=NONE;
    Person person;
};

class Member : public Account{
    int total_vehicles_reserved=0;
    string driverLicenseNumber;
    Date driverLicenseExpiry;
    VehicleReservation* getReservations();
};

class Receptionist : public Account{
    int driverId;
    Person person;
    Date joinedDate;
    bool searchMember();
};

class CarRentalLocation{
    string name;
    Address location;
    Address getLocation();
};

class CarRentalSystem{
    string name;
    Address locations[];
    bool addLocation(Address address);
};

class Date{
    int year;
    int date;
    int month;
};

class BarCode{
    string barcode;
    Date issuedAt;
    bool active;

    bool isActive();
}

class Vehicle{
    string licenseNumber;
    int stockNumber;
    int passengerCapacity;
    BarCode barCode;
    bool hasSunroof;
    ReservationStatus status;
    CarType model;
    Date manufacturingDate;
    int mileage;

    virtual bool reserveVehicle()=0;
    virtual bool returnVehicle()=0; 
};

class Car : public Vehicle{
    CarType type;
    bool reserveVehicle() override;
    bool returnVehicle() override;
};

class Van : public Vehicle{
    VanType type;
    bool reserveVehicle() override;
    bool returnVehicle() override;
};

class Truck : public Vehicle{
    TruckType type;
    bool reserveVehicle() override;
    bool returnVehicle() override;
};


class VehicleLog{
    string id;
    VehicleLogType type;
    string description;
    Date creationDate;

    bool update();
    VehicleLog* searchByLogType(VehicleLogType type);
};

class VehicleReservation{
    string reservationNumber;
    Date creationDate;
    ReservationStatus status;
    Date dueDate;
    Date returnDate;
    Address pickupLocationName;
    Address returnLocationName;
    VehicleLog vehicleLog;

    VehicleReservation fetchReservationDetails(string reservationNumber);
    AdditionalDriver* getAdditionalDrivers();
};

class AdditionalDriver{
    string driverId;
    Person person;
};

class Search{
    Vehicle* searchByType(VehicleType type);
    Vehicle* searchByModel(string type);
};

class VehcileInventory: public Search{
    map<VehicleType,vector<Vehicle>> vehicleTypes;
    map<string,vector<Vehicle>> vehicleModels ;

    Vehicle searchByType(Vehicle query){
        return vehicleTypes[query];
    }
    Vehicle searchByModel(String query){
        return vehicleModels[query];
    }
};

class Bill{
    double totalAmount;
    bool addBillItem();
};

class Payment{
    Date creationDate;
    double amount;
    PaymentStatus paymentStatus;
    bool initiateTransaction(); 
};


class CreditCardTransaction : public Payment{
    string nameOnCard;
    int cvv;
    Date expiryDate;
    int cardNumber;
};

class ChequeTransaction: public Payment{
    string chequeNUmber;
    string bankName;
};

class CashTransaction : public Payment{
    double cashTendered;
};

class Notification{
    int notificationId;
    Date createdOn;
    string content;
};

class SMSNotification: public Notification{
    int phone;
};

class EmailNotification: public Notification{
    string email;
};

class Service{
    string serviceId;
    bool addService();
};

class Driver : public Service{};
class RoadSideAssistance : public Service{};
class WiFi : public Service{};

class Equipment{
    string equipmentId;
    bool addEquipment();
};

class Navigation : public Equipment{};
class ChildSeat : public Equipment{};
class SkiRack : public Equipment{};

class RentalInsurance{
    string insuranceId;
    bool addInsurance();
};

class PersonalInsurance : public RentalInsurance{};
class BelongingInsurance : public RentalInsurance{};
class LiabilityInsurance : public RentalInsurance{}; 










