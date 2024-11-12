#include "WeddingGuest.h"
#include <iostream>

//default constructor for a Node:
Node::Node()
{
    first = "Lionel";
    last = "Messi";
    age = 100;
    next = NULL;
}

//default constructor for a WeddingGuest list:
WeddingGuest::WeddingGuest()
{
    head = NULL;
}

//destructor for a WeddingGuest list:
WeddingGuest::~WeddingGuest()
{
    Node *remove = head;
    while(remove != NULL)
    {
        Node *n = remove->next; //these 3 lines.
        delete remove; //have to be.
        remove = n; //in this precise order.
    } //close while loop.
    std::cout << "destructor called" << std::endl;
    head = NULL;
}

//copy constructor for a WeddingGuest list:
WeddingGuest::WeddingGuest(const WeddingGuest& rhs)
{
    if(rhs.head == NULL)
    {
        head = rhs.head;
    }
    else
    {
        Node *current = rhs.head; //existing list.
        Node *n = new Node; //n = new Node for copy.
        n->first = current->first;
        n->last = current->last;
        n->age = current->age;
        head = n;
        current = current->next;
        while(current != NULL)
        {
            Node *x = new Node;
            n->next = x;
            n = x;
            x->first = current->first;
            x->last = current->last;
            x->age = current->age;
            current = current->next;
        } //close loop.
    } //close else.
}

//assignment operator for WeddingGuest list:
const WeddingGuest& WeddingGuest::operator=(const WeddingGuest& rhs)
{
    if(&rhs == this)
    {
        return *this;
    }
    else
    {
        Node *remove;
        remove = head;
        while(remove != NULL)
        {
            Node *n = remove->next;
            delete remove;
            remove = n;
        } //close while loop.
        if(rhs.head == NULL)
        {
            head = rhs.head;
        }
        else
        {
            Node *current = rhs.head;
            Node *n = new Node;
            n->first = current->first;
            n->last = current->last;
            n->age = current->age;
            head = n;
            current = current->next;
            while(current != NULL)
            {
                Node *x = new Node;
                n->next = x;
                n = x;
                x->first = current->first;
                x->last = current->last;
                x->age = current->age;
                current = current->next;
            } //close nested while loop.
        } //close nested else.
    } //close outer else.
    return *this;
}

//helper: void printList() const:
void WeddingGuest::printList() const
{
    Node *current = head;
    int counter = 0;
    while(current != NULL)
    {
        std::cout << "Node: " << counter << std::endl;
        std::cout << "current address: " << current << std::endl;
        std::cout << "data: " << current->first << " " << current->last << " " << current->age << std::endl;
        std::cout << "next address: " << current->next << std::endl;
        std::cout << "-----------" << std::endl;
        current = current->next;
        counter++;
    }
}

//bool noGuests() const:
bool WeddingGuest::noGuests() const
{
    if(guestCount() == 0) //if empty.
    {
        return true;
    }
    else //if not empty.
    {
        return false;
    }
}

//int guestCount() const:
int WeddingGuest::guestCount() const
{
    Node *current = head;
    int counter = 0;
    while(current != NULL)
    {
        current = current->next;
        counter++;
    }
    return counter;
}

//bool inviteGuest():
bool WeddingGuest::inviteGuest(const std::string& firstName, const std::string& lastName, const GuestType& value)
{
    bool flag = true;
    Node *newGuest = new Node;
    newGuest->last = lastName;
    newGuest->first = firstName;
    newGuest->age = value;
            
    //PATH 1: IF THE LIST IS COMPLETELY EMPTY, NEW NODE:
    if(head == NULL) //if empty...create new Node & make head point to it.
    {
        head = newGuest;
        flag = true;
    } //close path 1.
    
    //PATH 2: only 1 Node in list.
    else if(guestCount() == 1)
    {
        if(head->last == newGuest->last) //same last name.
        {
            if(head->first == newGuest->first) //duplicate.
            {
                flag = false;
            }
            else //insert Node based on firstName abc order.
            {
                if(newGuest->first < head->first) //before 1st.
                {
                    newGuest->next = head;
                    head = newGuest;
                }
                else //after 1st.
                {
                    head->next = newGuest;
                }
            }
        }
        else //look at last names.
        {
            if(newGuest->last < head->last)
            {
                newGuest->next = head;
                head = newGuest;
            }
            else
            {
                head->next = newGuest;
            }
        }
    } //close PATH 2: only 1 Node in list.
    else if (invitedToTheWedding(firstName, lastName))
    {
        flag = false;
    }

    //PATH 3: 2 Nodes or more.
    else
    {
        bool flagTwo = false;
        bool flagThree = false;
        Node *current = head;
        Node *preNode = NULL;
        while(current != NULL)
        {
            //for same last diff first.
            while(newGuest->last == current->last)
            {
                if(newGuest->first < current->first)
                {
                    if(preNode == NULL)
                    {
                        newGuest->next = head;
                        head = newGuest;
                        flag = true;
                        flagTwo = true;
                        break; //inserted node
                    }
                    else
                    {
                        preNode->next = newGuest;
                        newGuest->next = current;
                        flag = true;
                        flagTwo = true;
                        break; //inserted node.
                    }
                }
                else if(current->next == NULL && newGuest->first > current->first)
                {
                    current->next = newGuest;
                    flag = true;
                    flagTwo = true;
                    break;
                }
                else
                {
                    preNode = current;
                    current = current->next;
                }
            } //no more same last names.
            
            
            if(flagTwo == true) //no need to keep traversing.
            {
                break; //bc found right place to insert.
            }
            
            //diff last names, look at last names.
            while(current != NULL)
            {
                if(newGuest->last < current->last)
                {
                    if(preNode == NULL)
                    {
                        newGuest->next = head;
                        head = newGuest;
                        flag = true;
                        flagThree = true;
                        break; //inserted node
                    }
                    else
                    {
                        preNode->next = newGuest;
                        newGuest->next = current;
                        flag = true;
                        flagThree = true;
                        break;
                    }
                }
                else if(current->next == NULL && newGuest->last > current->last)
                {
                    current->next = newGuest;
                    flag = true;
                    flagThree = true;
                    break;
                }
                else
                {
                    preNode = current;
                    current = current->next;
                }
            } //close while for diff last, diff first.
            if(flagThree == true)
            {
                break;
            }
        } //at end of list.
    } //end outer else.
    return flag;
}

//bool alterGuest:
bool WeddingGuest::alterGuest(const std::string& firstName, const std::string& lastName, const GuestType& value)
{
    bool flag = false;
    Node *current = head;
    while(current != NULL)
    {
        if(current->first == firstName && current->last == lastName)
        {
            current->age = value;
            //make current age point to the value in para. which is another age.
            flag = true;
            break;
        }
        else
        {
            flag = false;
            current = current->next; //shift.
        }
    }
    return flag;
}

//bool inviteOrAlterGuest():
bool WeddingGuest::inviteOrAlter(const std::string& firstName, const std::string& lastName, const GuestType& value)
{
    bool flag = false;
    Node *current = head;
    while(current != NULL)
    {
        if(current->first == firstName && current->last == lastName) //make current node's age point to new value.
        {
            current->age = value;
            flag = true;
            break;
        }
        else //shift.
        {
            current = current->next;
        }
        //at end of list with no duplicate, so invite said guest.
        inviteGuest(firstName, lastName, value);
        flag = true;
    } //close while loop.
    return flag;
}

//bool crossGuestOff():
bool WeddingGuest::crossGuestOff(const std::string& firstName, const std::string& lastName)
{
    bool flag = false;
    Node *current = head;
    Node *prev = head;
    Node *t = NULL;
    while(current != NULL)
    {
        if(current->first == firstName && current->last == lastName)
        {
            if(current == head)
            {
                t = head;
                head = head->next;
                flag = true;
                delete t;
                prev = NULL;
                t = NULL;
                current = NULL;
                break;
            }
            else
            {
                t = current;
                prev->next = current->next;
                flag = true;
                delete t;
                prev = NULL;
                t = NULL;
                current = NULL;
                break;
            }
        }
        else
        {
            flag = false;
            prev = current;
            current = current->next;
        }
    }
    return flag;
}

//bool invitedToTheWedding():
bool WeddingGuest::invitedToTheWedding(const std::string& firstName, const std::string& lastName) const
{
    bool flag = false;
    Node *current = head;
    while(current != NULL)
    {
        if(current->first == firstName && current->last == lastName)
        {
            flag = true;
            break;
        }
        else
        {
            flag = false;
        }
        current = current->next;
    }
    return flag;
}

//bool matchInvitedGuest():
bool WeddingGuest::matchInvitedGuest(const std::string& firstName, const std::string& lastName, GuestType& value) const
{
    bool flag = false;
    Node *current = head;
    while(current != NULL)
    {
        if(current->first == firstName && current->last == lastName)
        {
            //set value(parameter) to value/age in list of full name.
            value = current->age;
            flag = true;
            break; //exit loop
        }
        else
        {
            current = current->next;
            flag = false;
        }
    } //close while loop.
    return flag;
}

//bool verifyGuestOnTheList():
bool WeddingGuest::verifyGuestOnTheList(int i, std::string& firstName, std::string& lastName, GuestType & value) const
{
    bool flag = false;
    Node *current = head;
    int counter = 0;
    if(0 <= i < guestCount())
        //i has to be greater than or equal to 0 bc counting indexes.
    {
        while(current != NULL)
        {
            if(counter == i) //verified.
            {
                firstName = current->first;
                lastName = current->last;
                value = current->age;
                flag = true;
                break;
            }
            counter = counter + 1; //shift index.
            current = current->next; //move to next node.
        }
    }
    else
    {
        flag = false;
    }
    return flag;
}

//void swapWeddingGuests():
void WeddingGuest::swapWeddingGuests(WeddingGuest &other)
{
    Node *n = head; //n for current list.
    head = other.head; //other list.
    other.head = n;
    n = NULL;
}

//bool joinGuests(): couldnt not figure out, return dummy values.
bool joinGuests(const WeddingGuest & odOne, const WeddingGuest & odTwo, WeddingGuest & odJoined)
{
    return false;
}

//void attestGuests(): solved but not fully understand.
void attestGuests(const std::string& fsearch, const std::string& lsearch, const WeddingGuest& odOne, WeddingGuest& odResult)
{
    /*
    WeddingGuest r; //for result?
    int size = odOne.guestCount();
    
    //loop to traverse through odOne list:
    for(int i = 0; i < size; i++)
    {
        std::string f;
        std::string l;
        GuestType v;
        
        //remember, verify gets data in stores in parameters.
        odOne.verifyGuestOnTheList(i, f, l, v);
        if(((f == fsearch) || (f == "*")) && ((l == lsearch) || (l == "*")))
        {
            r.inviteGuest(f, l, v);
        }
    } //close for loop.
    odResult = r;
    */
    std::cout << "attestGuests() called but not fully implemented" << std::endl;
}
