// The system should support the booking of different room types like standard, deluxe, family suite, etc.
// Guests should be able to search the room inventory and book any available room.
// The system should be able to retrieve information, such as who booked a particular room, or what rooms were booked by a specific customer.
// The system should allow customers to cancel their booking - and provide them with a full refund if the cancelation occurs before 24 hours of the check-in date.
// The system should be able to send notifications whenever the booking is nearing the check-in or check-out date.
// The system should maintain a room housekeeping log to keep track of all housekeeping tasks.
// Any customer should be able to add room services and food items.
// Customers can ask for different amenities.
// The customers should be able to pay their bills through credit card, check or cash..

enum RoomStyle{
    STANDARD,
    DELUXE,
    FAMILY_SUITE,
};

enum RoomStatus{
    AVAILABLE,
    RESERVED,
    OCCUPIED,
    NOT_AVAILABLE,
    NONE
};

enum BookingStatus{
    REQUESTED,
    PENDING,
    CONFIRMED,
    CHECKED_IN,
    CHECKED_OUT,
    CANCELLED,
    NONE
};

enum AccountStatus{
    ACTIVE,
    CLOSED,
    BLOCKED,
    CANCELLED,
};

enum AccountType{
    MEMBER,
    GUEST,
    MANAGER,
    RECEPTIONIST
};

enum PaymentStatus{
    PENDING,
    COMPLETED,
    REFUNDED
};

enum Currency{
    DOLLAR,
    WON,
    INR,
    POUNDS,
    EURO,
}

class Address{
    string streetAddress;
    string city;
    string state;
    string zip;
    string country;
};

class Date{
    int year;
    int month;
    int date;
}

class Account{
    string id;
    string password;
    AccountStatus status;
};

class Person{
    string name;
    Address address;
    string email;
    string phone;
    Account account;
};

class Member : public Person{
    int totalRoomsCheckedIn=0;
    RoomBooking roomBookings[];
    RoomBooking* getBookings();
    bool createBooking();
};

class Receptionist : public Person{
    bool  createBooking();
    void searchMember(string name);
};


class HouseKeeper : public Person{
    RoomHouseKeeping roomHouseKeeping;
}

class RoomBooking{
    int reservationNumber;
    Date startDate;
    int durationInDays;
    BookingStatus bookingStatus;
    int guestId=0;
    Room room;
    Invoice invoice;
    Notification notifications[];
};

class Invoice{
    double amount;
    bool createBill();
};

class InvoiceItem{
    double amount;
    bool updateAmount();
};

class Search{
    Room* search(RoomStyle style, Date startDate, int duration);
};

class Room{
    string roomNumber;
    RoomStyle roomStyle;
    RoomStatus roomStatus;
    BookingPrice bookingPrice;
    bool isSmoking;
    RoomKey keys[];
    RoomHouseKeeping houseKeepingLogs[];

    bool isRoomAvailable();
    bool checkIn();
    bool checkOut();
};

class RoomKey{
    int keyId;
    string barCode;
    Date issuedAt;
    bool isMaster;

    void assignRoom(Room room);
    bool isActive();
};

class RoomHouseKeeping{
    string description;
    Date startDate;
    int duration;
    Room assignedRooms[];
};

class BookingPrice{
    Currency currency;
    int amount;
};


class Server : public Person{
    void addRoomCharge(Room room , int room_charge);
};

class Notification{
    int notificationId;
    Date createdOn;
    string content;
    bool send();
};

class PostalNotification : public Notification{
    Address address;
};

class EmailNotification : public Notification{
    string email;
};

class BillTransaction{
    Date creationDate;
    double amount;
    PaymentStatus paymentStatus;

    bool inititateTransaction();
};

class CreditCardTransaction : public BillTransaction{
    string nameOnCard;
    string zipCode;
};

class ChequeTransaction : public BillTransaction{
    string checkNumber;
    string bankName;
};

class CashTransaction : public BillTransaction{
    double cashTendered;
};

class RoomCharge{
    Date issuedAt;
    bool addVoiceItem();
};

class Amenity : public RoomCharge{
    string name;
    string description;
};

class RoomService : public RoomCharge{
    bool isChargeable;
    Date requestTime;
};

class KitchenService : public RoomCharge{
    string description;
};





