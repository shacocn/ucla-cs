// Set header file

#ifndef newSet_h
#define newSet_h
#include <string>

// type alias
using ItemType = int;

// global constants
const int DEFAULT_MAX_ITEMS = 250;

// class definition
class Set
{
public:
    // Create an empty set (i.e., one with no items).
    Set();
    
    // Constructor that creats a Set with max of numItems values
    Set(int numItems);
    
    // Copy constructor
    Set(const Set &old);
    
    // Assignment operator
    Set &operator= (const Set& src);
    
    // Return true if the set is empty, otherwise false.
    bool empty() const { return (m_items == 0); };
    
    // Return the number of items in the set.
    int size() const { return m_items; };
    
    // Insert value into the set if it is not already present.  Return
    // true if the value was actually inserted.  Leave the set unchanged
    // and return false if the value was not inserted (perhaps because it
    // was already in the set or because the set has a fixed capacity and
    // is full).
    bool insert(const ItemType& value);
    
    // Remove the value from the set if present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.
    bool erase(const ItemType& value);
    
    // Return true if the value is in the set, otherwise false.
    bool contains(const ItemType& value) const;
    
    // If 0 <= i < size(), copy into value the item in the set that is
    // strictly greater than exactly i items in the set and return true.
    // Otherwise, leave value unchanged and return false.
    bool get(int i, ItemType& value) const;
    
    // Exchange the contents of this set with the other one.
    void swap(Set& other);
    
    // Destructor
    ~Set();
    
private:
    ItemType *m_arr;
    int m_items;
    int m_maxItems;
    
    // returns index of value or -1 if not found
    int indexOf(ItemType value) const;
    
    // shifts all array elements starting at the startingIndex to the right
    void shiftRight(int startingIndex);
    
    // shifts all array elements starting at the startingIndex to the left
    void shiftLeft(int startingIndex);
};

#endif /* newSet_h */
