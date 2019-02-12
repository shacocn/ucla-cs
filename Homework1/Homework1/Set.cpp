// Set implementation file

#include "Set.h"
#include <iostream>

using namespace std;

// Insert value into the set if it is not already present.  Return
// true if the value was actually inserted.  Leave the set unchanged
// and return false if the value was not inserted (perhaps because it
// was already in the set or because the set has a fixed capacity and
// is full).
bool Set::insert(const ItemType& value)
{
    if (contains(value) || m_items >= DEFAULT_MAX_ITEMS)
        return false; // not inserted

    int insertLocation = 0; // default location
    for (int i = 0; i < m_items; i++)
    {
        if (value < m_arr[i])
        {
            insertLocation = i;
            break;
        }
        /* if value is greater than the current word, then you would have to insert it after the current word (this accounts for the situation in which the value is already the greatest in the array.
         */
        insertLocation = i + 1;
    }
    shiftRight(insertLocation);
    m_arr[insertLocation] = value;
    m_items++;
    return true;
}

// Remove the value from the set if present.  Return true if the
// value was removed; otherwise, leave the set unchanged and
// return false.
bool Set::erase(const ItemType& value)
{
    int valueIndex = indexOf(value);
    if (valueIndex == -1)
        return false; // value is not present
    shiftLeft(valueIndex);
    m_items--;
    return true;
}

// Return true if the value is in the set, otherwise false.
bool Set::contains(const ItemType& value) const
{
    return (indexOf(value) != -1);
}

// If 0 <= i < size(), copy into value the item in the set that is
// strictly greater than exactly i items in the set and return true.
// Otherwise, leave value unchanged and return false.
bool Set::get(int i, ItemType& value) const
{
    if (i >= m_items || i < 0)
        return false; // impossible scenario

    value = m_arr[i];
    return true;
}

// Exchange the contents of this set with the other one.
void Set::swap(Set& other)
{
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        // swap items
        ItemType temp = m_arr[i];
        m_arr[i] = other.m_arr[i];
        other.m_arr[i] = temp;
    }

    // swap number of items variable
    int temp = m_items;
    m_items = other.m_items;
    other.m_items = temp;
}

// returns index of value or -1 if not found
int Set::indexOf(ItemType value) const
{
    for (int i = 0; i < size(); i++)
    {
        if (m_arr[i] == value)
            return i;
    }
    return -1;
}

// shifts all array elements starting at the startingIndex to the right
void Set::shiftRight(int startingIndex)
{
    for (int i = m_items; i > startingIndex; i--)
        m_arr[i] = m_arr[i - 1];
}

// shifts all array elements starting at the startingIndex to the left
void Set::shiftLeft(int startingIndex)
{
    for (int i = startingIndex; i < m_items; i++)
        m_arr[i] = m_arr[i + 1];
}
