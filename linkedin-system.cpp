// Each member should be able to add information about their basic profile, experiences, education, skills, and accomplishments.
// Any user of our system should be able to search for other members or companies by their name.
// Members should be able to send or accept connection requests from other members.
// Any member will be able to request a recommendation from other members.
// The system should be able to show basic stats about a profile, like the number of profile views, the total number of connections, and the total number of search appearances of the profile.
// Members should be able to create new posts to share with their connections.
// Members should be able to add comments to posts, as well as like or share a post or comment.
// Any member should be able to send messages to other members.
// The system should send a notification to a member whenever there is a new message, connection invitation or a comment on their post.
// Members will be able to create a page for a Company and add job postings.
// Members should be able to create groups and join any group they like.
// Members should be able to follow other members or companies.

enum ConnectionInvitationStatus{
    PENDING,ACCEPTED,REJECTED
};

enum AccountStatus{
    ACTIVE,BLOCKED,BANNED
};

enum Proficiency{
    EXPERT,INTERMEDIATE,BEGINNER
};

class Address{
    string street;
    string city;
    string state;
    string country;
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

class Member : Person{
    Date dateOfMembership;
    string headline;
    Blob photo;
    vector<Member> memberSuggestions;
    vector<Member> memberFollows;
    vector<Member> memberConnections;
    vector<Post> savedPosts;
    vector<Company> companyFollows;
    vector<Group> groupFollows;
    Profile profile;

    bool sendMessage(string message);
    bool createPost(Post post);
    bool sharePost(Post post,Member member);
    bool sendConnectionInvitation(ConnectionInvitation invitation);
};

class ConnectionInvitation{
    Date createdOn;
    ConnectionInvitationStatus status;
    Member sendTo;

    void acceptConnection();
    void rejectConnection();
};

class Admin{
    bool blockUser(Member member);
    bool unblockUser(Member member);
};

class Profile{
    string summary;
    vector<Experience> experiences;
    vector<Education> educations;
    vector<string> skills;
    vector<Accomplishment> accomplishments;
    vector<Recommendation> recommendations;
    vector<Stat> stats;
    
    bool addExperience(Experience experience);
    bool addEducation(Education education);
    bool addSkill(Skill skill);
    bool addAccomplishment(Accomplishment accomplishment);
    bool addRecommendation(Recommendation recommendation);
};

class Experience{
    string title;
    Company company;
    Address location;
    Date dateFrom;
    Date dateTo;
    string description;
};

class Education{
    string title;
    string school;
    string degree;
    Date fromYear;
    Date toYear;
    string desc;
};

class Skill{
    string name;
    Proficiency proficiency;
};

class Accomplishment{
    string title;
    Date date;
    string desc;
};

class Recommendation{
    int memberID;
    Date createdOn;
    string desc;

    bool accept();
    bool reject();
};

class Stat{
    int totViews;
    int totConnections;
    int searchAppearances;
};

class Company{
    string naem;
    string desc;
    CompanyType type;
    int companySize;

    vector<JobPosting> activeJobPostings;
};

class JobPosting{
    Date dateOfPosting;
    string desc;
    EmploymentType type;
    Address location;
    bool isFullfilled;
};

class Group{
    string name;
    string desc;
    int totMembers;
    vector<Member> members;

    bool addMember(Member member);
    bool removeMember(Member member);
    bool updateDesc(string desc);
};

class Post{
    string text;
    int totLikes;
    int totShares;
    Member owner;
    vector<Comment> comments;
};

class Comment{
    string content;
    Member Commentor;
    int likes;

    bool updateText(string content);
};

class Message{
    Member sentTo;
    string messageBody;
    Blob media;

    bool sendMessage();
};

class Search{
    virtual vector<Member> searchMember(string name)=0;
    virtual vector<Company> searchCompany(string name)=0;
    virtual vector<Job> searchJob(string name)=0;
};

class SearchIndex: public Search{
    unordered_map<string,vector<Member>> memberNames;
    unordered_map<string,vector<Company>> companyNames;
    unordered_map<string,vector<JobPosting>> jobTiltes;

    void addMember(Member member){
        memberNames[member.get_name()].push(member);    
    }

    bool addCompany(Company company);
    bool addJobPosting(JobPosting jobPosting);

    vector<Member> searchMember(string name) override{};
    vector<Company> searchCompany(string name) override{};
    vector<Job> searchJob(string name) override{};
};  

class Notification{
    string notificationID;
    string content;
    Date createdOn;

    bool send();
};

class SMSNotification : public Notification{
    string phone;
};

class emailNotification : public Notification{
    string email;
};