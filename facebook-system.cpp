// Each member should be able to add information about their basic profile, work experience, education, etc.
// Any user of our system should be able to search other members, groups or pages by their name.
// Members should be able to send and accept/reject friend requests from other members.
// Members should be able to follow other members without becoming their friend.
// Members should be able to create groups and pages, as well as join already created groups, and follow pages.
// Members should be able to create new posts to share with their friends.
// Members should be able to add comments to posts, as well as like or share a post or comment.
// Members should be able to create privacy lists containing their friends. Members can link any post with a privacy list to make the post visible only to the members of that list.
// Any member should be able to send messages to other members.
// Any member should be able to add a recommendation for any page.
// The system should send a notification to a member whenever there is a new message or friend request or comment on their post.
// Members should be able to search through posts for a word.

enum ConnectionInvitationStatus{
    PENDING,ACCEPTED,REJECTED,CANCELLED
};

enum AccountStatus{
    ACTIVE,CLOSED,DISABLED,BLACKLISTED
};

enum Gender{
    LESBIAN,GAY,MALE,FEMALE,NON_BINARY,TRANSGENDER,BISEXUAL,QUEER
};

enum NotificationType{
    SMS,EMAIL
}

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
    AccountStatus status;

    bool resetPassword();
};

class Person{
    string name;
    string email;
    string phone;
    Address address;
    Account account;
};

class Member : public Person{ 
    string memberID;
    Date dateOfMembership;
    string name;

    Profile profile;
    vector<Member> memberFollows;
    vector<Member> memberConnections;
    vector<Page> pageFollows;
    vector<Member> memberSuggestions;
    vector<Post> posts;
    vector<Group> groupFollows;

    bool sendMessage(Message message);
    bool createPost(Post post);
    bool sharePost(Post post,Member member);
    bool sendConnectionInvitation(Invitation invitation);
    vector<Member> searchMemberSuggestions();
};

class Admin : public Person{
    void blockUser(Member member);
    void unblockUser(Member member);
    void enablePage(Page page);
    void disablePage(Page page);
};

class Invitation{
    Member memberInvited;
    ConnectionInvitationStatus status;
    Date createdOn;
    
    bool accept();
    bool reject();
};

class Profile{
    Blob profilePicture;
    Blob coverPhoto;
    Gender gender;
    vector<Work> workExperiences;
    vector<Education> educations;
    vector<Place> places;
    vector<Stat> stats;

    void addWorkExperience(Work work);
    void addEducation(Education education);
    void addPlace(Place place);
};

class Work{
    string title;
    string company;
    Address location;
    Date dateFrom;
    Date dateTo;
    string desc;
};

class Education{
    string school;
    string degree;
    Date dateFrom;
    Date dateTo;
    string spl;
};

class Place{
    Address address;
    Blob image;
};

class Stat{
    
};

class Page{
    string groupID;
    string namel
    string desc;
    int totMembers;
    vector<Member> members;
    vector<Post> posts;

    void addMember(Member member);
    void updateDesc(string desc);
    void addReccomendation(Recommendation recommendation);
};

class Recommendation{
    int rating;
    string desc;
    Date createdAt;

    bool acceptRecommendation();
};


class Group{
    vector<Member> members;
    Member groupAdmin;
};

class Post{
    string postID;
    string text;
    int totLikes;
    int totShares;
    vector<Comment> comments;
    Member owner;
};

class Message{
    string msgID;
    Member sentTo;
    string msgBody;
    Blob media;

    void addMember(member member);
};

class Comment{
    string commentID;
    string text;
    int totLikes;
    Member owner;
};

class Search{
    vector<Member> searchMember(string name);
    vector<Group> searchGroup(string name);
    vector<Page> searchPage(string name);
    vector<Post> searchPost(string name);
};

class SearchIndex : public Search{
    unordered_map<string,vector<Member>> memberNames;
    unordered_map<string,vector<Group>> groupNames;
    unordered_map<string,vector<Page>> pageNames;
    unordered_map<string,vector<Post>> postNames;

    void addMember(Member member){
        memberNames[member.getName()].push(member);
    }

    void addGroup(Group group);
    void addPost(Post post);
    void addPage(Page page);

    vector<Member> searchMember(string name){
        return memberNames[name];
    }
    vector<Post> searchPost(string name){
        return postNames[name];
    }
    vector<Group> searchGroup(string name){
        return groupNames[name];
    }
    vector<Page> searchPage(string name){
        return pageNames[name];
    }
};

class NotificationService{
    bool sendNotification(NotificationDomain notificationDomain){
        Notification notification;
        MessageAttribute messageAttribute;

        switch notificationDomain.getNotificationType(){
            case NotificationType::EMAIL:
                notification=EmailNotification();
                messageAttribute=MessageAttribute("fb-admin@gmail.com",notificationDomain.getMember().getPerson().getEmail(),notificationDomain.getContent());
            case NotificationType::SMS:
                notification=SMSNotification();
                messageAttribute=MessageAttribute("9833228212",notificationDomain.getMember().getPerson().getPhone(),notificationDomain.getContent());
        }
        notification.sendNotification(messageAttribute);
    }
};

class Notification{
    string id;
    Date createdOn;
    public:
        bool sendNotification(MessageAttribute);
};

class NotificationDomain{
    NotificationType type;
    Member member;
    string content;

    Member getMember();
    string getContent();
}

class MessageAttribute{
    string sentFrom;
    string sentTo;
    string content;

    public:
        MessageAttribute();
        MessageAttribute(string sentFrom,string sentTo,string content);
};

class EmailNotification : public Notification{};
class SMSNotification : public Notification{};