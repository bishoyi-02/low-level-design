// Any non-member (guest) can search and view questions. However, to add or upvote a question, they have to become a member.
// Members should be able to post new questions.
// Members should be able to add an answer to an open question.
// Members can add comments to any question or answer.
// A member can upvote a question, answer or comment.
// Members can flag a question, answer or comment, for serious problems or moderator attention.
// Any member can add a bounty to their question to draw attention.
// Members will earn badges for being helpful.
// Members can vote to close a question; Moderators can close or reopen any question.
// Members can add tags to their questions. A tag is a word or phrase that describes the topic of the question.
// Members can vote to delete extremely off-topic or very low-quality questions.
// Moderators can close a question or undelete an already deleted question.
// The system should also be able to identify most frequently used tags in the questions.

enum VoteType{
    UPVOTE,DOWNVOTE,CLOSEVOTE,DELETEVOTE
};

enum AccountStatus{
    BLOCKED,ACTIVE,CLOSED
};

enum QuestionStatus{
    ACTIVE,BOUNTED,CLOSED,FLAGGED
};

class User{
    string id;
    Search searchObj;

    vector<Question> getQuestions(string searchString);
};

class Member : public User{
    Account account;
    vector<Badge> badges;

    void addQuestion(Question question);
    void addComment(Entity entity,Comment comment);
    void addAnswer(Question question,Answer answer);
    void vote(Entity entity,VoteType voteType);
    void addTag(Question question,Tag tag);
    void flag(Entity entity);
    vector<Badge> getBadges();
};

class Account{
    string name;
    Address address;
    string id;

    string username;
    string password;
    string email;

    AccountStatus accountStatus;
    int reputation;
};

class Moderator : public Member{
    bool closeQuestion(Question question);
    bool restoreQuestion(Question question);
};

class Admin : public Member{
    bool blockMember(Member member);
    bool unblockMember(Member member);
};

class Badge{
    string name;
    string desc;
};

class Entity{
    string id;
    Member creator;
    unordered_map<VoteType,int> votes;
    Date createdOn;
    vector<Comment> comments;

    vool flagEntity(Member member);
    vool voteEntity(VoteType voteType);
    vool addComment(Comment comment);
};

class Comment : public Entity{
    string message;
};

class Question : public Entity{
    string title;
    string desc;
    vector<EditHistory> editHistoryList;
    vector<Answer> answerList;
    vector<Tag> tags;
    QuestionStatus status;
    Bounty bounty;

    bool addQuestion();
    bool addTag(Tag tag);
    bool close();
};

class Bounty{
    int reputation;
    Date expiry;

    bool modifyReputation(int reputation);
};

class Answer : public Entity{
    string answer;
    bool isAccepted;
    bool addAnswer(Question question);
};

class Tag{
    string name;
    string desc;
};

class EditHistory{
    string id;
    Member creator;
    Date createdOn;
    Question prevQuestion;
    Question updatedQuestion;
};

class Search{
    vector<Question> search(string query); // return list of questions if the question contains query in it's title or desc.
};




