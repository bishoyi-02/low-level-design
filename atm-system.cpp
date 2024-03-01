// The main components of the ATM that will affect interactions between the ATM and its users are:

// Card reader: to read the users’ ATM cards.
// Keypad: to enter information into the ATM e.g. PIN. cards.
// Screen: to display messages to the users.
// Cash dispenser: for dispensing cash.
// Deposit slot: For users to deposit cash or checks.
// Printer: for printing receipts.
// Communication/Network Infrastructure: it is assumed that the ATM has a communication infrastructure to communicate with the bank upon any transaction or activity.
// The user can have two types of accounts: 1) Checking, and 2) Savings, and should be able to perform the following five transactions on the ATM:

// Balance inquiry: To see the amount of funds in each account.
// Deposit cash: To deposit cash.
// Deposit check: To deposit checks.
// Withdraw cash: To withdraw money from their checking account.
// Transfer funds: To transfer funds to another account.

enum TransactionType{
    BALANCE_INQUIRY,DEPOSIT_CASH,DEPOSIT_CHECK,WITHDRAW,TRANSFER
};

enum TransactionStatus{
    SUCCESS,FAILURE,BLOCKED,FULL
};

enum CustomerStatus{
    ACTIVE,BLOCKED,BLACKLISTED,CLOSED
};

class Address{
    string street;
    string city;
    string state;
    string country;
    string zip;
};

class Customer{
    string name;
    Address address;
    string email;
    string phone;
    CustomerStatus status;
    Account account;
    Card card;

    bool makeTransaction(Transasction transaction);
    void getBillingAddress();

};

class Card{
    string cardNumber;
    string customerName;
    Date cardExpiry;
    string pin;

    void getBillingAddress();
};

class Account{
    string accountNumber;
    double totalBalance;
    double availableBalance;

    double getAvailableBalance();
};

class SavingAccount : public Account{
    double withdrawLimit;
};

class CheckingAccount : public Account{
    string debitCardNumber;
};

class Bank{
    string name;
    string bankCode;

    string getBankCode();
    void addATM(ATM atm);
};

class ATM{
    string id;
    Address location;

    CashDispenser cashDispenser;
    Keypad keypad;
    Screen screen;
    Printer printer;
    CheckDepositSlot checkDepositSlot;
    CashDepositSlot cashDepositSlot;

    bool authenticateUser();
    bool makeTransaction(Customer customer , Transaction transaction);
};

class CashDispenser{
    int totalFiveDollarBills;
    int totalTwentyDollarBills;

    void dispenseCash(int amount);
    bool canDispenseCash();
};

class Keypad{
    void getInput();
};

class Screen{
    void showMessage();
    void getInput();
};

class Printer{
    void printRecipt();
};

class DepositSlot{
    double totalAmount;
    double getTotalAmount();
};

class CheckDepositSlot : public DepositSlot{
    double getCheckAmount();
};

class CashDepositSlot : public DepositSlot{
    bool recieveBill();
};

class Transaction{
    string id;
    Date creationDate;
    TransactionStatus status;

    bool makeTransaction();
};

class BalanceInquiry : public Transaction{
    string accountID;

    Account getAccount();
};

class Deposit : public Transaction{
    double amount;

    int getAmount();
};

class CheckDeposit : public Deposit{
    string checkNumber;
    string backCode;
};

class CashDeposit : public Deposit{
    double cashDepositLimit;
};

class WithDraw : Transaction{
    double amount;

    double getAmount();
};

class Transfer : Transaction{
    string sourceAccount;
    string destAccount;
    double amount;

    Account getDestAccount();
};






