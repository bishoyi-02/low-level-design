// The restaurant will have different branches.
// Each restaurant branch will have a menu.
// The menu will have different menu sections, containing different menu items.
// The waiter should be able to create an order for a table and add meals for each seat.
// Each meal can have multiple meal items. Each meal item corresponds to a menu item.
// The system should be able to retrieve information about tables currently available to seat walk-in customers.
// The system should support the reservation of tables.
// The receptionist should be able to search for available tables by date/time and reserve a table.
// The system should allow customers to cancel their reservation.
// The system should be able to send notifications whenever the reservation time is approaching.
// The customers should be able to pay their bills through credit card, check or cash.
// Each restaurant branch can have multiple seating arrangements of tables.

enum ReservationStatus{
    REQUESTED,PENDING,CONFIRMED,CHECKED_IN,CANCELLED
};

enum SeatType{
    REGULAR,KID,ACCESSIBLE,HANDICAPPED
};

enum OrderStatus{
    RECEIVED,PREPARING,COMPLETED,CANCELLED
};

enum TableStatus{
    FREE,RESERVED,OCCUPIED
};

enum AccountStatus{
    ACTIVE,CLOSED,CANCELLED,BLOCKED
};

enum PaymentStatus{
    PENDING,COMPLETED,CANCELLED,REFUNDED
};

class Address{
    string street;
    string city;
    string state;
    string country;
    string zip;
};

class Account{
    string id;
    string password;
    Address address;
    AccountStatus status;

    void resetPassword();
};

class Person{
    string name;
    string email;
    string phone;
};

class Employee : public Person{
    string id;
    Date joinedAt;
    Account account;
};

class Receptionist : public Employee{
    void createReservation();
    void searchCustomer(string name);
};

class Manager : public Employee{
    void addEmployee();
};

class Chef : public Employee{
    void takeOrder();
};

class Waiter : public Employee{
    void createOrder();
};

class Customer : public Person{
    DateTime lastVisited;
};

class Kitchen{
    string name;
    vector<Chef> assignedChefs;

    void assignChef(Chef chef);
};

class Branch{
    string name;
    Address address;
    Kitchen kitchen;

    void addTableChart(TableChart tableChart);
};

class Restaurant{
    string name;
    vector<Branch> branches;

    void addBranch(Branch branch);
};

class TableChart{
    string id;
    string tableChartImage;

    void print();
};

class Table{
    string tableID;
    int maxCapacity;
    string locationID;
    TableStatus status;
    vector<TableSeat> seats;

    bool isTableFree();
    bool addReseration();
    vector<Table> search(int capacity,DateTime startTime);
};

class TableSeat{
    int tableSeatNumber;
    SeatType seatType= SeatType::REGULAR;

    void updateSeatType(SeatType seatType);
};

class Reservation{
    string reservationID;
    DateTime timeOfReservation;
    int peopleCount;
    ReservationStatus status;
    DateTime checkInTime;
    Customer customer;
    vector<Table> tables;
    vector<Notification> notifications;

    void updatePeopleCount(int count);
};

class MenuItem{
    string id;
    string title;
    string description;
    double price;

    void updatePrice(double price);
};

class MenuSection{
    string id;
    string title;
    string desc;
    vector<MenuItem> menuItems;

    void addMenuItem(MenuItem item);
};

class Menu{
    string menuID;
    string title;
    string desc;
    vector<MenuSection> menuSections;

    void addMenuSection(MenuSection menuSection);
    void print();
};

class MealItem{
    string mealItemID;
    int quantity;
    MenuItem menuItem;

    void updateQuanity(int quantity);
};

class Meal{
    string mealID;
    vector<MenuItem>  menuItems;

    void addMealItem(MenuItem menuItem);
};

class Check{
    string id;
    double amount;
    double tax;
    double tip;
    bool isPaid;

    void createBill();
};

class Order{
    string id;
    OrderStatus status;
    DateTime CreationtTime;
    vector<Meal> meals;
    Table table;
    Waiter eaiter;
    Chef chef;
    Check check;

    void addMeal(Meal meal);
    void removeMeal(Meal meal);
    OrderStatus getStatus();
    void setStatus(OrderStatus status);
}   

class Notification{
    string id;
    DateTime createdOn;
    string content;

    bool send();
};

class PostalNotification : public Notification{
    string phone;
};

class EmailNotification : public Notification{
    string email;
};

class Payment{
    string id;
    double amount;
    DateTime createdOn;

    bool initTransaction();
};  

class CreditCardTransaction : public Payment{
    string name;
};

class ChequeTransaction : public Payment{
    string id;
}

class CashTransaction : public Payment{
    double cashTendered;
}


