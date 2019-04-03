// Set header file

#ifndef Set_h
#define Set_h
#include <string>

// type alias
using ItemType = std::string;

// global constants
const int DEFAULT_MAX_ITEMS = 250;

// class definition
class Set
{
public:
    // Create an empty set (i.e., one with no items).
    Set() { m_items = 0; };

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

private:
    ItemType m_arr[DEFAULT_MAX_ITEMS];
    int m_items;

    // returns index of value or -1 if not found
    int indexOf(ItemType value) const;

    // shifts all array elements starting at the startingIndex to the right
    void shiftRight(int startingIndex);

    // shifts all array elements starting at the startingIndex to the left
    void shiftLeft(int startingIndex);
};


#endif /* Set_h */
