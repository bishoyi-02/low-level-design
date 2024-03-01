// The system should keep track of all cricket-playing teams and their matches.
// The system should show live ball-by-ball commentary of cricket matches.
// All international cricket rules should be followed.
// Any team playing a tournament will announce a squad (a set of players) for the tournament.
// For each match, both teams will announce their playing-eleven from the tournament squad.
// The system should be able to record stats about players, matches, and tournaments.
// The system should be able to answer global stats queries like, “Who is the highest wicket taker of all time?”, “Who has scored maximum numbers of 100s in test matches?”, etc.
// The system should keep track of all ODI, Test and T20 matches.

enum MatchFormat{
    ODI,TEST,T20
};

enum MatchResult{
    LIVE,FINISHED,DRAW,CANCELLED
};

enum UmpireType{
    FIELD,RESERVED,TV
};

enum WicketType{
    BOLD,CAUGHT,RUNOUT,HIT_WICKET,LBW,TIMEOUT,RETIRED_HURT
};

enum BallType{
    NORMAL,WIDE,WICKET,NO_BALL
};

enum RunType{
    NORMAL,FOUR,SIX,LEG_BYE,NO_BALL
};

class Person{
    string name;
    int age;
    int experience;
};

class Player{
    Person person;
    PlayerStat playerStat;
    vector<Contract> contracts;

    bool addContract(Contract contract);
};

class Admin{
    Person person;

    void addMatch(Match match);
    void addTournament(Tournament tournament);
    void addTeam(Team team);
};


class Umpire{
    Person person;

    void assignMatch(Match match);
};

class Referee{
    Person person;
    
    void assignMatch(Match match);
};

class Commentator{
    Person person;

    void assignMatch(Match match);
};

class Coach{
    Person person;
    Contract coachContract;
    void assignTeam(Team team);
};

class Contract{
    DateTime startDate;
    DateTime endDate;

    bool cancelContract();
};

class Tournament{
    Date startDate;
    TournamentPointsTable pointsTable;

    bool addTeam(Team team);
};

class TournamentPointsTable{
    unordered_map<Team,double> teamPoints;
    Date lastUpdated; 
};

class Team{
    string name;
    vector<Player> players;
    Coach coach;
    vector<News> news;

    void addTournamentSquad(TournamentSquad squad);
    void addPlayer(Player player);
    void addNews(News news);
};

class News{
    Blob image;
    DateTime date;
    string content;
};

class TournamentSquad{
    vector<Player> players;
    vector<TournamentStat> tournamentStats;

    void addPlayer(Player player);
};

class Stat{
    Date createdOn;
    Date lastUpdated;

    bool saveStat();
    bool modifyStat();
};

class TournamentStat : public Stat{};
class TeamStat : public Stat{};
class MatchStat : public Stat{};
class PlayerStat : public Stat{};

class StatQuery{
    string question;
    string answerl
    Date lastUpdated;

    bool updateStatAnswer();
}


class Playing11{
    vector<Player> players;
    Player twelthMan;
    TeamStat teamStat;

    void addPlayer(Player player);
};

class Over{
    int number;
    vector<Ball> balls;

    void addBalls(Ball ball);
};

class Ball{
    Player balledBy;
    Player playedBy;
    BallType type;
    Wicket wicket;
    Run runs;
    Commentary commentary;

    bool addCommentary();
};

class Wicket{
    WicketType type;
    Player playedOut;
    Player caughtOut;
    Player runOut;
    Player stumpedBy;
};

class Run{
    int totRuns;
    RunType type;
};

class Commentary{
    string text;
    DateTime createdAt;
    Commentator createdBy;
};

class Inning{
    int number;
    DateTime startTime;
    vector<Over> overs;

    void addOver(Over over);
};

class Match{
    int number;
    DateTime startTime;
    MatchResult result;
    
    vector<Team> teams;
    vector<Inning> innings;
    vector<Umpire> umpires;
    vector<Commentator> commentators;
    vector<MatchStat> matchStats;

    void assignStadium(Stadium stadium);
    void assignUmpire(Umpire umpire);
};


class ODI : public Match{};

class Test : public Match{};

class T20 : public Match{};

class Stadium{
    string name;
    Address address;
    int maxCap;
};
