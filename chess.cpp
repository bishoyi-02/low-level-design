// The system should support two online players to play a game of chess.
// All rules of international chess will be followed.
// Each player will be randomly assigned a side, black or white.
// Both players will play their moves one after the other. The white side plays the first move.
// Players can’t cancel or roll back their moves.
// The system should maintain a log of all moves by both players.
// Each side will start with 8 pawns, 2 rooks, 2 bishops, 2 knights, 1 queen, and 1 king.
// The game can finish either in a checkmate from one side, forfeit or stalemate (a draw), or resignation.

enum GameStatus{
    ACTIVE,BLACKWIN,WHITEWIN,FORFEIT,STALEMATE,RESIGNATION
};

enum AccountStatus{
    ACTIVE,CLOSED,BLACKLISTED
};

enum Color{
    BLACK,WHITE
};

class Chess{
    ChessBoard chessBoard;
    vector<Player> player;
    Player currentPlayer;
    vector<Move> movesList;
    GameStatus status;

    bool playerMove(CellPosition fromPos,CellPosition toPos,Piece piece);
    bool endGame();
    void changeTurn();
};

class Player{
    Account account;
    Color color;
    Time timeLeft;
};

class Account{
    string username;
    string password;
    string name;
    string email;
    string phone;
};

class Time{ 
    int mins;
    int secs;
};

class ChessBoard{
    vector<vector<Cell>> board;

    void resetBoard();
    void updateBoard(Move move);
};

class Cell{
    Color color;
    Piece piece;
    CellPosition position;
};

class CellPosition{
    char ch;
    int i;
};

class Move{
    Player turn;
    Piece piece;
    Piece killedPiece;
    CellPosition startPos;
    CellPosition endPos;
};

class Piece{
    Color color;
    virtual bool move(CellPosition fromPos,CellPosition toPos)=0;
    virtual vector<CellPosition> possibleMoves(CellPosition fromPos)=0;
    virtual bool validate(CellPosition fromPos,CellPosition toPos)=0;
};

class King : public Piece{
    bool move(CellPosition fromPos,CellPosition toPos) override{};
    vector<CellPosition> possibleMoves(CellPosition fromPos)override{};
    virtual bool validate(CellPosition fromPos,CellPosition toPos)override{};
};

class Rook : public Piece{
    bool move(CellPosition fromPos,CellPosition toPos) override{};
    vector<CellPosition> possibleMoves(CellPosition fromPos)override{};
    virtual bool validate(CellPosition fromPos,CellPosition toPos)override{};
};




 



