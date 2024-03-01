// Users should be able to add new products to sell.
// Users should be able to search for products by their name or category.
// Users can search and view all the products, but they will have to become a registered member to buy a product.
// Users should be able to add/remove/modify product items in their shopping cart.
// Users can check out and buy items in the shopping cart.
// Users can rate and add a review for a product.
// The user should be able to specify a shipping address where their order will be delivered.
// Users can cancel an order if it has not shipped.
// Users should get notifications whenever there is a change in the order or shipping status.
// Users should be able to pay through credit cards or electronic bank transfer.
// Users should be able to track their shipment to see the current state of their order.

enum OrderStatus{
    UNSHIPPED,SHIPPED,COMPLETED,CANCELLED
};

enum AccountStatus{
    ACTIVE,BLOCKED,INACTIVE
};

enum ShipmentStatus{
    PENDING,SHIPPED,DELIVERED
};

enum PaymentStatus{
    UNPAID,PENDING,PAID,CANCELLED,REFUNDED
};

enum ShipmentMethod{
    SHIP,FLIGHT,TRAIN
};

enum NotificationType{
    SMS,EMAIL
};

class Address{
    string street;
    string city;
    string state;
    string zip;
    string country;
};

class Account{
    string username;
    string password;
    string name;
    string email;
    vector<Address> addresses;
    AccountStatus accountStatus;
    vector<CreditCard> creditCards;
    vector<BankAccount> bankAccounts;

    void resetPassword();
};

class Customer{
    ShoppingCart cart;
    Order order;

    ShoppingCart getShoppingCart();
    void addItemToCart(Item item);
    void removeItemFromCart(Item item);
};

class Guest : public Customer{
    void registerAccount();
};

class User : public Customer{
    Account account;
};

class Buyer : public User{
    void addProduct(Product product);
    void placeOrder(Order order);
};

class Seller : public User{
    void addProductToStock(Product product);
};  

class Admin{
    Account account;

    bool blockUser(Account account);
    bool addNewProductCategory(ProductCategory productCategory);
    bool modifyProductCategory(ProductCategory productCategory);
};

class ProductCategory{
    string name;
    string desc;
};

class ProductReview{
    int rating;
    string review;
    Buyer reviewer;
};

class Product{
    string id;
    string name;
    string desc;
    int price;
    ProductCategory productCategory;
    Seller seller;
    int availableCount;

    vector<ProductReview> productReviews;
    int getAvailableCount();
    bool updatePrice();
};

class Item{
    string id;
    int quantity;
    int price;

    bool updateQuantity(int quantity);
};

class ShoppingCart{
    vector<Item> items;
    
    bool addItem(Item item);
    bool removeItem(Item item);
    bool updateItemCount(Item item);

    vector<Item> getitems();
    bool checkout(); 
    double getCartValue();
};

class OrderLog{
    int id;
    OrderStatus status;
    DateTime creationDate;
};

class Order{
    int orderid;
    OrderStatus status;
    DateTime orderDate;
    vector<OrderLog> orderLogs;
    vector<Item> orderItems;
    Buyer buyer;

    bool sendForShipment();
    bool makePayment(Payment payment);
    bool  addOrderLog(OrderLog orderlog);
    OrderStatus placeOrder();
    OrderStatus trackOrder();
};

class Payment{
    string id;
    PaymentStatus status;
    double amount;

    bool processPayment();
};

class CreditCardTransaction : public Payment{};

class ElectronicBankTransaction : public Payment{};

class CreditCard{
    string nameOnCard;
    string cardNumber;
    int cvv;
};

class ElectronicBankTransfer{
    string bankName;
    string routingNumber;
    string accountNumber;
};

class ShipmentLog{
    string id;
    DateTime shipmentDate;
    DateTime estimatedArrival;
    ShipmentMethod shipmentMethod;
    vector<ShipmentLog> shipmentLogs;

    void addShipmentLog(ShipmentLog shipmentLog);
};

class Notification{
    string id;
    DateTime createdOn;

    bool sendNotification(MessageAttribute msgAttribute);
};

class SMSNotification: public Notification{
    bool sendNotification(MessageAttribute msgAttribute);
}; 

class EmailNotification: public Notification{
    bool sendNotification(MessageAttribute msgAttribute);
}; 

class MessageAttribute{
    string content;
    string to;
    string from;
    public:
    MessageAttribute();
    MessageAttribute(string from,string to,string content);
};

class NotificationService{
    bool send(NotificationDomain notificationDomain){
        Notification notification;
        MessageAttribute messageAttribute;

        switch(notificationDomain.getNotificationType()){

            case NotificationType::EMAIL:
                notification= EmailNotification();
                messageAttribute =  MessageAttribute("abc@gmail.com",notificationDomain.getUser().getEmail(),notificationDomain.getContent());
            case NotificationType::SMS:
                notification=SMSNotification();
                messageAttribute = MessageAttribute("123456",notificationDomain.getUser().getEmail(),notificationDomain.getContent());
            
        }

        notification.sendNotification(messageAttribute);
    }
};

class NotificationDomain{
    string notificationID;
    NotificationType type;
    string content;
    User user;

    public:
        User getUser();
        string getContent();
};


class Search{
    virtual vector<Product> searchProductByName(string name)=0;
    virtual vector<Product> searchProductByCategory(ProductCategory category)=0;
};

class Catalog : public Search{
    unordered_map<string,vector<Product>> productNames;
    unordered_map<ProductCategory,vector<Product>> productCategory;
    
    vector<Product> searchProductByName(string name) override{
        return productNames[name];
    }

    vector<Product> searchProductByCategory(ProductCategory category) override{
        return productCategory[category];
    }
};


