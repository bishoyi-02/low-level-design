// Any library member should be able to search books by their title, author, subject category as well by the publication date.
// Each book will have a unique identification number and other details including a rack number which will help to physically locate the book.
// There could be more than one copy of a book, and library members should be able to check-out and reserve any copy. We will call each copy of a book, a book item.
// The system should be able to retrieve information like who took a particular book or what are the books checked-out by a specific library member.
// There should be a maximum limit (5) on how many books a member can check-out.
// There should be a maximum limit (10) on how many days a member can keep a book.
// The system should be able to collect fines for books returned after the due date.
// Members should be able to reserve books that are not currently available.
// The system should be able to send notifications whenever the reserved books become available, as well as when the book is not returned within the due date.
// Each book and member card will have a unique barcode. The system will be able to read barcodes from books and members’ library cards.

using namespace std;

enum BookFormat{
    HARDCOVER,
    PAPERBACK,
    AUDIO_BOOK,
    EBOOK,
    MAGAZINE
};

enum BookStatus{
    AVAILABLE,
    RESERVED,
};

enum ReservationStatus{
    WAITING,
    PENDING,
    CANCELLED
};

enum AccountStatus{
    ACTIVE,
    CLOSED,
    CANCELLED,
};

class Address{
    string streetAddress;
    string city;
    string state;
    string country;
    string zip;
};

class Person{
    string name;
    Address address;
    string email;
    string phone;
};

class Constants{
    int maxBooksIssuedToAUser=5;
    int maxLendingDays=10;
};

class Date{
    int year;
    int month;
    int date;
};

class Account{
    string id;
    string password;
    AccountStatus accountStatus;
    Person person;

    bool resetPassword();
};

class LibraryCard{
    string cardNumber;
    string barcode;
    Date issuedate;
    bool active;

    bool isActive();
};

class BarcodeReader{
    string id;
    Date registeredAt;
    bool active;

    bool isActive();
};

class Library{
    string name;
    Address address;
    
    Address getAddress();
};

class Member : public Account{
    Date dateOfMembership;
    int totalBooksCheckedOut=0;

    int getTotalBooksCheckedOut();
    bool reserveBookItem(BookItem bookItem);
    bool incrementTotalBooksCheckedOut();
    bool renewBookItem(BookItem bookItem);
    bool checkOutBookItem(BookItem bookItem){

    }
    bool checkForFine(BookItem bookItem);
    bool returnBookItem(BookItem bookItem);
    bool renewBookItem(BookItem bookItem);
};

class BookItem{
    string barCode;
    bool isReferenceOnly;
    Date borrowed;
    Date dueDate;
    double price;
    BookFormat bookFormat;
    BookStatus bookStatus;
    Date dateOfPurchase;
    Date publicationDate;

    bool checkOut();
};

class Librarian : public Account{
    bool addBookItem(BookItem bookItem);
    bool blockMember(Member member);
    bool unBlockMember(Member member);
};

class BookReservation{
    Date creationDate;
    ReservationStatus reservationStatus;
    string bookItemBarcode;
    int memberId;

    bool lendBook(string barcode, int memberid);
    void fetchReservationDetails(int memberId);
};

class BookLending{
    Date creationDate;
    Date dueDate;
    Date returnDate;
    string bookItemBarcode;
    Date getReturnDate();
    int memberId;

    void fetchBookLendingDetails(string bookItemBarcode);
};

class Fine{
    Date creationDate;
    string bookItemBarcode;
    int memberID;

    double collectFine(int memberID, int days);
};

class Book{
    string ISBN;
    string title;
    string subject;
    string publisher;
    string language;
    int numberOfPages;
    string authors[];
};

class Rack{
    int num;
    string locationIdentifier;
};

class Search{
    virtual Book searchByTitle(string title)=0;
    virtual Book* searchByAuthor(string author)=0;
    virtual Book* searchBySubject(string subject)=0;
    virtual Book* searchByPublicationDate(Date date)=0;
};

class Catalog : public Search{
    unordered_map<string,Book> bookTitles;
    unordered_map<string,Book*> bookAutheors;
    unordered_map<string,Book*> bookSubjects;
    unordered_map<Date,Book*> bookPubLicationDates;

    Book searchByTitle(string title) override{
        return bookTitles[title];
    }
    Book searchByAuthor(string author) override{
        return bookTitles[author];
    }
    Book searchBySubject(string subject) override{
        return bookTitles[subject];
    }
    Book searchByPublicationDate(Date date) override{
        return bookTitles[date];
    }
};


class FineTransaction{
    Date creationDate;
    double amount;

    bool initiateTransasction();
};

class CreditCardTransaction : public FineTransaction{
    string nameOnCard;
};

class ChequeTransasction : public FineTransaction{
    string bankName;
    string chequeNumber;
};

class CashTransaction : public FineTransaction{
    double cashTendered;
};

class Notification{
    int notificationID;
    Date createdOn;
    string content;

    bool sendNotification();
};

class PostalNotification : public Notification{
    Address address;
};

class EmailNotification : public Notification{
    string email;
};







