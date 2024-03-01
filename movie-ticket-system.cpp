// It should be able to list the cities where affiliate cinemas are located.
// Each cinema can have multiple halls and each hall can run one movie show at a time.
// Each Movie will have multiple shows.
// Customers should be able to search movies by their title, language, genre, release date, and city name.
// Once the customer selects a movie, the service should display the cinemas running that movie and its available shows.
// The customer should be able to select a show at a particular cinema and book their tickets.
// The service should show the customer the seating arrangement of the cinema hall. The customer should be able to select multiple seats according to their preference.
// The customer should be able to distinguish between available seats and booked ones.
// The system should send notifications whenever there is a new movie, as well as when a booking is made or canceled.
// Customers of our system should be able to pay with credit cards or cash.
// The system should ensure that no two customers can reserve the same seat.
// Customers should be able to add a discount coupon to their payment.


// Concurrency
// How to handle concurrency; such that no two users 
// are able to book the same seat?

// We can use transactions in SQL databases to avoid any clashes. 
// For example, if we are using SQL server we can utilize 
// Transaction Isolation Levels to lock the rows before we update them. 
// Note: within a transaction, if we read rows we get a write-lock 
// on them so that they can’t be updated by anyone else. 

// ‘Serializable’ is the highest isolation level and guarantees safety 
// from Dirty, Nonrepeatable, and Phantoms reads.

// Once the above database transaction is successful, we can safely 
// assume that the reservation has been marked successfully and no 
// two customers will be able to reserve the same seat.

enum BookingStatus{
    REQUESTED,
    PENDING,
    CONFIRMED,
    CANCELLED
};

enum SeatType{
    REGULAR,
    PREMIU,
    EMERGENCY_EXIT
};

enum AccountStatus{
    ACTIVE,
    BLOCKED,
    ARCHIVED
};

enum PaymentStatus{
    UNPAID,
    PENDING,
    COMPLETED,
    FILLED
};

class Address{
    string streetAddress;
    string city;
    string state;
    string country;
    string zip;
};

class Account{
    string id;
    string password;
    AccountStatus accountStatus;
};

class Date{
    int year;
    int month;
    int day;
};

class Time{
    int hrs;
    int mins;
    int secs;
};

class Person{
    string name;
    Address address;
    string email;
    string phone;
    Account account;
};

class Customer : public Person{
    bool makeBooking(Booking booking);
    Booking* getBookings();
};

class Admin : public Person{
    bool addMovie(Movie movie);
    bool addShow(Show show);
    bool blockUser(Customer customer);
};

class FrontDeskOfficer : public Person{
    bool createBooking(Booking booking);
};

class Guest{
    bool registerAccount();
};

class Show{
    string showID;
    Date createdOn;
    Time startTime;
    Time endTime;
    CinemaHall playedAt;
    Movie movie;
};

class Movie{
    string title;
    string description;
    int durationInMins;
    string language;
    Date releaseDate;
    string country;
    string* genre;
    string movieAddedBy;

    Show* getShows();
};

class Booking{
    string bookingNumber;
    int numberOfSeats;
    Date createdOn;
    BookingStatus bookingStatus;
    Show show;
    Payment payment;
    ShowSeat* showSeats;

    bool makePayment(Payment payment);
    bool cancel();
    bool assignSeats(ShowSeat* seats);
};

class ShowSeat : public CinemaHallSeat{
    string seatID;
    bool isReserved;
    int price;
};

class Payment{
    int amount;
    Date createdOn;
    string transactionID;
    PaymentStatus paymentStatus;
};

class Cinema{
    string name;
    Address address;
    int totalCinemaHalls;
};

class CinemaHall{
    string name;
    int totalSeats;
    ShowSeat* seats;
    Show* shows;
};

class CinemaHallSeat{
    string cinemaHallID;
    SeatType seatType;
};

class Search{
    virtual Show searchByTitle(string title)=0;
    virtual Show searchByLanguage(string language)=0;
    virtual Show searchByGenre(string genre)=0;
    virtual Show searchByReleaseDate(Date date)=0;
    virtual Show searchByTitle(string title)=0;  
};

class Catalog : public Search{
    unordered_map<string,Show*> movieTitles;
    unordered_map<string,Show*> movieLanguages;
    unordered_map<string,Show*> movieGenres;
    unordered_map<Date,Show*> movieReleaseDates;
    unordered_map<string,Show*> movieCities;

    Show* searchByTitle(string title){
        return movieTitles[title];
    }
    Show* searchBylanguage(string language){
        return movieTitles[language];
    }
    Show* searchByTitle(string genre){
        return movieTitles[genre];
    }
    Show* searchByTitle(Date date){
        return movieTitles[date];
    }
    Show* searchByTitle(string city){
        return movieTitles[city];
    }

};

class Notifcation{
    string notificationID;
    Date createdOn;
    string content;

    bool sendNotification();
};

class EmailNotification : public Notifcation{
    string email;
};

class SMSNotification : public Notifcation{
    string phone;
};

class CreditCardTransaction : public Payment{
    string creditCardNumber;
};

class CashTransaction : public Payment{
    double cashTendered;
};



