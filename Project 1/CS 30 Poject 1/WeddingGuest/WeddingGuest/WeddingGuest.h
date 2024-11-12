#ifndef WeddingGuest_h
#define WeddingGuest_h
#include <string>

typedef int GuestType;

struct Node
{
    std::string first;
    std::string last;
    GuestType age;
    Node *next;
public:
    Node();
}; //end Node struct.

class WeddingGuest
{
public:
    Node *head;
public:
//default constructor:
    WeddingGuest();
//copy constructor:
    WeddingGuest(const WeddingGuest& rhs);
//destructor:
    ~WeddingGuest();
//assigment operator function:
    const WeddingGuest& operator=(const WeddingGuest& rhs);
//helper function: void printList() const:
    void printList() const;
//bool noGuests() const:
    bool noGuests() const;
//int guestCount() const:
    int guestCount() const;
//bool inviteGuest():
    bool inviteGuest(const std::string& firstName, const std::string& lastName, const GuestType& value);
//bool alterGuest():
    bool alterGuest(const std::string& firstName, const std::string& lastName, const GuestType& value);
//bool inviteOrAlter():
    bool inviteOrAlter(const std::string& firstName, const std::string& lastName, const GuestType& value);
//bool crossGuestOff():
    bool crossGuestOff(const std::string& firstName, const std::string& lastName);
//bool invitedToTheWedding() const:
    bool invitedToTheWedding(const std::string& firstName, const std::string& lastName) const;
//bool matchInvitedGuest() const:
    bool matchInvitedGuest(const std::string& firstName, const std::string& lastName, GuestType& value) const;
//bool verifyGuestOnTheList const:
    bool verifyGuestOnTheList(int i, std::string& firstName, std::string& lastName, GuestType & value) const;
//void swapWeddingGuests():
    void swapWeddingGuests(WeddingGuest &other);
}; //end WeddingGuest class.

//NON-MEMBER FUNCTIONS:
//bool joinGuests(): //not solved. couldnt figure out.
bool joinGuests(const WeddingGuest & odOne, const WeddingGuest & odTwo, WeddingGuest & odJoined);

//void attestGuests():
void attestGuests(const std::string& fsearch, const std::string& lsearch, const WeddingGuest& odOne, WeddingGuest& odResult);

#endif /* WeddingGuest.h */
