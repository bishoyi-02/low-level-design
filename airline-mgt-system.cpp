// Customers should be able to search for flights for a given date and source/destination airport.
// Customers should be able to reserve a ticket for any scheduled flight. Customers can also build a multi-flight itinerary.
// Users of the system can check flight schedules, their departure time, available seats, arrival time, and other flight details.
// Customers can make reservations for multiple passengers under one itinerary.
// Only the admin of the system can add new aircrafts, flights, and flight schedules. Admin can cancel any pre-scheduled flight (all stakeholders will be notified).
// Customers can cancel their reservation and itinerary.
// The system should be able to handle the assignment of pilots and crew members to flights.
// The system should be able to handle payments for reservations.
// The system should be able to send notifications to customers whenever a reservation is made/modified or there is an update for their flights.

enum FlightStatus{
    ACTIVE,SCHEDULED,CANCELLED,LANDED,DEPARTED,IN_AIR
};

enum PaymentStatus{
    UNPAID,COMPLETED,CANCELLED,REFUNDED
};

enum ReservationStatus{
    REQUESTED,PENDING,CONFIRMED,CANCELLED
};

enum SeatClass{
    ECONOMY,BUISNESS,FIRST_CLASS
};

enum SeatType{
    REGULAR,EMERGENCY_EXIT,ACCESIBLE,DELUXE
};

enum AccountStatus{
    ACTIVE,BLOCKED,INACTIVE
};

class Address{
    string street;
    string state;
    string city;
    string country;
    string zip;
};

class Account{
    string id;
    string password;
    AccountStatus status;

    bool resetPassword();
};

class Person{
    string name;
    Address address;
    string email;
    string phone;
    Account account;
};

class Customer : public Person{
    string frequentFlyerNumber;

    vector<Itinerary> getItineraries();
};

class Admin : public Person{
    bool addAircraft();
    bool addFlight();
    bool blockUser();
};

class Crew : public Person{
    vector<Flight> getFlights();
};

class FrontDeskOfficer{
    bool createItinerary();
};

class Passenger{
    string name;
    string passportNumber;
    DateTime dateOfBirth;

    string getPassportNumber();
};

class Airport{
    string name;
    Address address;
    string code;
    vector<Flight> flights;
    vector<Airline> airline;

    vector<Flight> getFlights();
    vector<Airline> getAirlines();
};

class Airline{
    vector<Aircraft> aircrafts;

    vector<Aircraft> getAircrafts();
};

class Aircraft{
    string name;
    string model;
    DateTime manufacturingYear;
    vector<Flight> flights;

    vector<Flight> getFlights();
};

class Seat{
    string seatNumber;
    SeatType type;
    SeatClass seatClass;
};

class FlightSeat : public Seat{
    double fare;

    double getFare();
};

class Schedule{
    Time departureTime;
};

class WeeklySchedule : public Schedule{
    int dayOfWeek;
};

class CustomSchedule : public Schedule{
    DateTime customDate;
};

class Flight{
    string flightNumber;
    Airport departure;
    Airport arrival;
    int durationInMins;

    vector<WeeklySchedule> weeklySchedules;
    vector<CustomSchedule> customSchedules;
    vector<FlightInstance> flightInstances;
};

class FlightInstance{
    Time departureTime;
    string gate;
    string runway;
    FlightStatus status;
    Aircraft aircraft;

    bool cancel();
    bool updateStatus(FlightStatus status);
};

class FlightReservation{
    string reservationNumber;
    Flight flight;
    unordered_map<Passenger,FlightSeat> seatMap;
    DateTime creationDate;
    ReservationStatus status;

    void getReservationDetails(string reservationNumber);
    vector<Passenger> getPassengers();
};

class Itinerary{
    string id;
    Airport startingAirport;
    Airport destinationAirport;
    Date creationDate;
    vector<FlightReservation> reservations;

    vector<FlightReservation> getReservations();
    bool makeReservations();
    bool makePayment();
};

class Payment{
    double fare;
    string id;
    PaymentStatus status;

    bool  initPayment();
};

class CreditCardTransaction : public Payment{};

class ChequeTransaction : public Payment{};

class CashTransaction : public Payment{};

class Notification{
    string id;
    string content;
    DateTime createdOn;

    bool send();
};

class SMSNotification : public Notification{};

class EmailNotification : public Notification{};



