// Any user of our system should be able to buy and sell stocks.
// Any user can have multiple watchlists containing multiple stock quotes.
// Users should be able to place stock trade orders of the following types: 1) market, 2) limit, 3) stop loss and, 4) stop limit.
// Users can have multiple ‘lots’ of a stock. This means that if a user has bought a stock multiple times, the system should be able to differentiate between different lots of the same stock.
// The system should be able to generate reports for quarterly updates and yearly tax statements.
// Users should be able to deposit and withdraw money either via check, wire, or electronic bank transfer.
// The system should be able to send notifications whenever trade orders are executed.

enum ReturnStatus{
    SUCCESS,FAIL,INSUFFICIENT_FUNDS,INSUFFICIENT_QUANTITY
};

enum OrderStatus{
    OPEN,FILLED,CANCELLED
};

enum TimeEnforcementType{
    ON_THE_OPEN,ON_THE_CLOSE,IMMEDIATE_OR_CANCEL
};

enum AccountStatus{
    ACTIVE,CLOSED,BLACKLISTED,BANNED
};

class Address{
    string street;
    string city;
    string state;
    string country;
    string zip;
};

class Constants{
    int MONEY_TRANSFER_LIMIT=100000;
};

