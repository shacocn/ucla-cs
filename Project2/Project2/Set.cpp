/* Set implementation file. */
#include "Set.h"
#include <iostream>

using namespace std;

// |||||||||||||||||
// MEMBER FUNCTIONS
// |||||||||||||||||

/* Constructor. */
Set::Set()
{
    Node *p = new Node; // dummy node.
    head = p;
    p->next = p;
    p->prev = p;
}

/* Copy constructor. */
Set::Set(const Set& other)
{
    /* First insert a dummy node. */
    Node *p = new Node;
    head = p;
    p->next = p;
    p->prev = p;
    
    /* For every node of other, create a duplicate node with the same values for this set using the insert() function. */
    for (Node *ptr = other.head->next; ptr != other.head; ptr = ptr->next)
        insert(ptr->value);
}

/* Assignment operator. */
Set& Set::operator= (Set old)
{
    /* Uses the copy-swap idiom, which works in essence like this:
     - the parameter is taken by value which uses the copy constructor to make a local copy of the old Set.
     - the values of the old set and the new set are swapped using the swap function we already implemented.
     - once the function finishes, the local copy of old gets destroyed and the function returns this object.
     */
    swap(old);
    return *this;
}

/* Destructor. */
Set::~Set()
{
    Node *p = head->next; // point to first node
    while (p != head)
    {
        Node *temp = p->next; // hold onto address of next node
        delete p;
        p = temp;
    }
    
    /* Now remove the dummy node. */
    delete head;
}

/* Checks for an empty set. */
bool Set::empty() const
{
    return (head == head->next);
}

/* Returns the size of the set (excluding dummy node). */
int Set::size() const
{
    int count = 0;
    for (Node* p = head->next; p != head; p = p->next)
        count++;
    return count;
}

/* Insert value into the set if it is not already present. */
bool Set::insert(const ItemType& value)
{
    /* When the loop finishes, ptr will point to the node that should follow the new node. */
    Node *ptr = head->next;
    while (ptr != head)
    {
        if (ptr->value == value) // duplicate found.
            return false;
        if (ptr->value > value)
            break;
        ptr = ptr->next;
    }
    
    /* We now need to insert a node before the node pointed to by ptr by changing the next and previous pointers of the previous and following nodes. */
    Node *before = ptr->prev; // stores original previous node.
    Node *newNode = new Node; // new node to be inserted.
    newNode->value = value;
    newNode->next = ptr;
    newNode->prev = before;
    ptr->prev = newNode;
    before->next = newNode;
    return true; // successful insertion
}

/* Remove the value from the set if present.  Return true if the value was removed; otherwise, leave the set unchanged and return false. */
bool Set::erase(const ItemType& value)
{
    Node *p = head->next;
    
    /* Traverse the list until either the end is reached or the node value is found. */
    while (p != head && p->value != value)
        p = p->next;
    
    if (p == head)
        return false; // value not present; erase failed.
    
    /* Now, p points to the node that needs to be removed. That means that we adjust the next and previous pointers of the previous and following nodes to remove p from the situation. */
    Node *before = p->prev;
    Node *after = p->next;
    before->next = after;
    after->prev = before;
    delete p; // free memory at p
    return true; // erase successful.
}

/* Return true if the value is in the set, otherwise false. */
bool Set::contains(const ItemType& value) const
{
    for (Node *p = head->next; p != head; p = p->next)
    {
        if (p->value == value)
            return true;
    }
    return false;
}

/* If 0 <= i < size(), copy into value the item in the set that is strictly greater than exactly i items in the set and return true. Otherwise, leave value unchanged and return false. */
bool Set::get(int i, ItemType& value) const
{
    if (i >= size() || i < 0)
        return false; // impossible scenario

    /* At the end of the loop, p will point to the node that is greater than i items in the set. Change value to that node's value and return true. */
    Node *p = head->next;
    for (int k = 0; k < i; k++)
        p = p->next;
    value = p->value;
    return true; // successful retrieval.
}

/* Exchange the contents of this set with the other one. */
void Set::swap(Set& other)
{
    /* Swap what the two head pointers point to. */
    Node *tempNode = other.head;
    other.head = head;
    head = tempNode;
}

// |||||||||||||||||||||
// NON-MEMBER FUNCTIONS
// |||||||||||||||||||||

/* When this function returns, result contains one copy of each of the values that appear in s1 or s2 or both and no other values.
 */
void unite(const Set& s1, const Set& s2, Set& result)
{
    Set newSet;
    ItemType value;
    
    /* Add all values from s1 into the new set. */
    for (int i = 0; i < s1.size(); i++)
    {
        s1.get(i, value);
        newSet.insert(value);
    }
    
    /* Add all values from s2 if they do not exist already. */
    for (int j = 0; j < s2.size(); j++)
    {
        s2.get(j, value);
        if (!newSet.contains(value))
            newSet.insert(value);
    }
    /* Swap the new set with result so old values from result are erased. The new set will be destructed after block ends. */
    result.swap(newSet);
}

/* When this function returns, result must contain one copy of each of the values that appear in s1 but not s2, and must not contain any other values.
 */
void subtract(const Set& s1, const Set& s2, Set& result)
{
    Set newSet;
    ItemType value;
    
    /* For each item in s1, if it does not appear in s2, then add it to the new set. */
    for (int i = 0; i < s1.size(); i++)
    {
        s1.get(i, value);
        if (!s2.contains(value))
            newSet.insert(value);
    }
    
    /* Place the values of the new set into result. */
    result.swap(newSet);
}
