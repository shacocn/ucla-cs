/* Set header file. */
#ifndef Set_h
#define Set_h
#include <string>

/* Type alias. */
using ItemType = int;

/* Global constants. */
const int DEFAULT_MAX_ITEMS = 250;

class Set
{
public:
    /* Default constructor. */
    Set();
    
    /* Copy constructor. */
    Set(const Set& other);
    
    /* Assignment operator. */
    Set& operator= (Set old);
    
    /* Returns true if set is empty, false if otherwise. */
    bool empty() const;
    
    /* Returns the size of the set. */
    int size() const;
    
    /* Inserts an item in its proper location within set. */
    bool insert(const ItemType& value);
    
    /* Returns true if item with value is successfully removed. */
    bool erase(const ItemType& value);
    
    /* Returns true if the set contains the specified value. */
    bool contains(const ItemType& value) const;
    
    /* Returns true if successfully sets value to one that is greater than exactly i elements. */
    bool get(int i, ItemType& value) const;
    
    /* Swaps contents of two sets and their sizes. */
    void swap(Set& other);
    
    /* Destructor. */
    ~Set();
private:
    // Structure that contains values and pointers to next node
    struct Node {
        ItemType value;
        Node *next;
        Node *prev;
    };
    
    // Head pointer that points to the dummy node
    Node *head;
};

/* Function declarations. */
void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif /* Set_h */
