// tester.cpp
// To test HW 1 Problem 5, uncomment the following line:
 #define TESTNEW

#ifdef TESTNEW
#include "newSet.h" // ItemType should be a type alias for int
#else
#include "Set.h"    // ItemType should be a type alias for int
#endif

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>
#include <type_traits>
using namespace std;

const ItemType DUMMY = 123;
const ItemType DEFAULT = 0;
const ItemType ARRAY[6] = { 10, 20, 30, 40, 50, 60 };

void testone(int n);

int main()
{
    cout << "Enter test number: ";
    int n;
    cin >> n;
    testone(n);
    cout << "Passed" << endl;
}

bool isPermutation(const Set& s, const ItemType a[], int n)
{
    if (s.size() != n)
        return false;
    vector<ItemType> b(n);
    for (int i = 0; i < n; i++)
        s.get(i, b[i]);
    for (int j = 0; j < n; j++)
    {
        int i;
        for (i = j; i < n; i++)
        {
            if (a[j] == b[i])
            {
                ItemType t = b[j];
                b[j] = b[i];
                b[i] = t;
                break;
            }
        }
        if (i == n)
            return false;
    }
    return true;
}

const int SPEC_MAX = 250;

void testone(int n)
{
    Set s;
    switch (n)
    {
        default: {
            cout << "Bad argument" << endl;
        } break; case  1: {
            assert((is_same<decltype(&Set::empty), bool (Set::*)() const>::value));
        } break; case  2: {
            assert((is_same<decltype(&Set::size), int (Set::*)() const>::value));
        } break; case  3: {
            assert((is_same<decltype(&Set::contains),
                    bool (Set::*)(const ItemType&) const>::value));
        } break; case  4: {
            assert((is_same<decltype(&Set::get),
                    bool (Set::*)(int, ItemType&) const>::value));
        } break; case  5: {
            assert(s.empty());
        } break; case  6: {
            assert(s.size() == 0);
        } break; case  7: {
            assert(!s.erase(DEFAULT)  &&  s.size() == 0);
        } break; case  8: {
            assert(!s.contains(DEFAULT));
        } break; case  9: {
            ItemType x = DUMMY;
            assert(!s.get(0, x));
        } break; case 10: {
            ItemType x = DUMMY;
            s.get(0, x);
            assert(x == DUMMY);
        } break; case 11: {
            assert(s.insert(DUMMY));
        } break; case 12: {
            s.insert(DUMMY);
            assert(!s.empty());
        } break; case 13: {
            s.insert(DUMMY);
            assert(s.size() == 1);
        } break; case 14: {
            s.insert(DUMMY);
            assert(s.contains(DUMMY));
        } break; case 15: {
            s.insert(DUMMY);
            ItemType x = DEFAULT;
            assert(s.get(0, x));
        } break; case 16: {
            s.insert(DUMMY);
            ItemType x = DEFAULT;
            s.get(0, x);
            assert(x == DUMMY);
        } break; case 17: {
            assert(s.insert(DUMMY)  &&  !s.insert(DUMMY));
        } break; case 18: {
            s.insert(DUMMY);
            s.insert(DUMMY);
            assert(s.size() == 1);
        } break; case 19: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            assert(!s.empty()   &&  s.size() == 2);
        } break; case 20: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            ItemType x = DUMMY;
            s.get(0, x);
            assert(x == ARRAY[0]);
        } break; case 21: {
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            ItemType x = DUMMY;
            s.get(0, x);
            assert(x == ARRAY[0]);
        } break; case 22: {
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            ItemType x = DUMMY;
            s.get(0, x);
            ItemType y = DUMMY;
            s.get(1, y);
            assert(x == ARRAY[0]  &&  y == ARRAY[1]);
        } break; case 23: {
            s.insert(ARRAY[3]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[4]);
            s.insert(ARRAY[2]);
            assert(s.size() == 5);
        } break; case 24: {
            s.insert(ARRAY[3]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[4]);
            s.insert(ARRAY[2]);
            ItemType x;
            for (int k = 0; k < 5; k++)
            {
                s.get(k, x);
                assert(x == ARRAY[k]);
            }
        } break; case 25: {
            s.insert(ARRAY[1]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            assert(s.size() == 2);
        } break; case 26: {
            s.insert(ARRAY[1]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            ItemType x;
            for (int k = 0; k < 2; k++)
            {
                s.get(k, x);
                assert(x == ARRAY[k]);
            }
        } break; case 27: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[4]);
            assert(s.erase(ARRAY[3]));
        } break; case 28: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[4]);
            s.erase(ARRAY[3]);
            assert(s.size() == 4);
        } break; case 29: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[4]);
            assert(s.erase(ARRAY[0])  &&  s.size() == 4);
        } break; case 30: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[4]);
            assert(s.erase(ARRAY[4])  &&  s.size() == 4);
        } break; case 31: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[0]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[1]);
            assert(s.erase(ARRAY[1])  &&  s.size() == 2);
        } break; case 32: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[1]);
            s.erase(ARRAY[3]);
            assert(isPermutation(s, ARRAY, 3));
        } break; case 33: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[3]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[3]);
            s.erase(ARRAY[3]);
            assert(isPermutation(s, ARRAY, 3));
        } break; case 34: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            assert(!s.erase(ARRAY[4]));
        } break; case 35: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            s.erase(ARRAY[4]);
            assert(s.size() == 4);
        } break; case 36: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.erase(ARRAY[0]);
            s.erase(ARRAY[1]);
            assert(s.size() == 0);
        } break; case 37: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            ItemType x;
            assert(!s.get(-1, x));
        } break; case 38: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            ItemType x = DUMMY;
            s.get(-1, x);
            assert(x == DUMMY);
        } break; case 39: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            ItemType x;
            assert(! s.get(3, x));
        } break; case 40: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            ItemType x = DUMMY;
            s.get(3, x);
            assert(x == DUMMY);
        } break; case 41: {
            s.insert(DEFAULT);
            ItemType x = DUMMY;
            s.get(0, x);
            assert(s.size() == 1  &&  x == DEFAULT);
        } break; case 42: {
            s.insert(DEFAULT);
            s.erase(DEFAULT);
            assert(s.size() == 0  &&  !s.contains(DEFAULT));
        } break; case 43: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.erase(ARRAY[1]);
            assert(!s.contains(DEFAULT));
        } break; case 44: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.erase(ARRAY[1]);
            assert(s.contains(ARRAY[2]));
        } break; case 45: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.erase(ARRAY[2]);
            assert(s.size() == 2  &&  !s.contains(ARRAY[2]));
        } break; case 46: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.erase(ARRAY[1]);
            s.insert(ARRAY[2]);
            s.insert(ARRAY[3]);
            assert(s.size() == 3  &&  s.contains(ARRAY[2])  &&
                   s.contains(ARRAY[3]));
        } break; case 47: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2;
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                s.swap(s2);
                assert(s.size() == 2  &&  s2.size() == 3);
            }
        } break; case 48: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2;
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                s.swap(s2);
                for (int k = 0; k < 3; k++)
                {
                    assert(!s.contains(ARRAY[k]));
                    assert(s2.contains(ARRAY[k]));
                }
                for (int k = 3; k < 5; k++)
                {
                    assert(s.contains(ARRAY[k]));
                    assert(!s2.contains(ARRAY[k]));
                }
            }
        } break; case 49: {
            for (int k = 0; k < SPEC_MAX; k++)
                assert(s.insert(k));
            assert(s.size() == SPEC_MAX);
        } break; case 50: {
            for (int k = 0; k < SPEC_MAX; k++)
                assert(s.insert(k));
            ItemType x = SPEC_MAX;
            assert(!s.insert(x)  &&  s.size() == SPEC_MAX  &&  !s.contains(x));
        } break; case 51: {
            assert(s.insert(DUMMY));
            for (int k = 0; k < 10*SPEC_MAX; k++)
                assert(!s.insert(DUMMY));
            assert(s.size() == 1);
        } break; case 52: {
            ItemType x;
            for (int k = 0; k < SPEC_MAX; k++)
                assert(s.insert(k));
            assert(!s.insert(SPEC_MAX));
            s.erase(0);
            assert(s.insert(SPEC_MAX+1));
            assert(!s.insert(SPEC_MAX+2));
#ifdef TESTNEW
        } break; case 53: {
            // This test checked that swap executes the same number of
            // statements no matter how many items are in the sequences
        } break; case 54: {
            const int CAPACITY = 2;
            Set s2(CAPACITY);
            for (int k = 0; k < CAPACITY; k++)
                assert(s2.insert(k));
            assert(! s2.insert(CAPACITY));
        } break; case 55: {
            const int CAPACITY = SPEC_MAX*2;
            Set s2(CAPACITY);
            for (int k = 0; k < CAPACITY; k++)
                assert(s2.insert(k));
            assert(! s2.insert(CAPACITY));
        } break; case 58: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2(s);
                s2.insert(ARRAY[3]);
                assert(s2.size() == s.size()+1);
            }
        } break; case 59: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2(s);
                s2.insert(ARRAY[3]);
                assert(isPermutation(s2, ARRAY, 4));
            }
        } break; case 60: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            s.insert(ARRAY[2]);
            {
                Set s2(s);
                s2.insert(ARRAY[3]);
                assert(isPermutation(s, ARRAY, 3));
            }
        } break; case 61: {
            {
                Set s2;
                Set s3(s2);
                assert(s2.size() == 0  &&  s3.size() == 0);
                s2.insert(ARRAY[0]);
                s3.insert(ARRAY[1]);
                assert(s2.size() == 1  &&  s3.size() == 1);
                ItemType x;
                s2.get(0, x);
                assert(x == ARRAY[0]);
                s3.get(0, x);
                assert(x == ARRAY[1]);
            }
        } break; case 62: {
            {
                Set s2(2);
                s2.insert(ARRAY[0]);
                s2.insert(ARRAY[1]);
                Set s3(s2);
                assert(!s3.insert(ARRAY[2]));
            }
        } break; case 63: {
            {
                Set s2;
                Set s3;
                s3.insert(ARRAY[0]);
                s3.insert(ARRAY[1]);
                assert(s3.size() == 2);
                s3 = s2;
                assert(s3.size() == 0);
                s2.insert(ARRAY[2]);
                s3.insert(ARRAY[3]);
                assert(s2.size() == 1  &&  s3.size() == 1);
                ItemType x;
                s2.get(0, x);
                assert(x == ARRAY[2]);
                s3.get(0, x);
                assert(x == ARRAY[3]);
            }
        } break; case 64: {
            {
                Set s2;
                Set s3;
                s3.insert(ARRAY[0]);
                s3.insert(ARRAY[1]);
                assert(s3.size() == 2);
                s2 = s3;
                assert(s2.size() == 2  &&  s3.size() == 2);
                s2.insert(ARRAY[2]);
                s3.insert(ARRAY[3]);
                assert(s2.size() == 3  &&  s3.size() == 3);
                assert(isPermutation(s2, ARRAY, 3));
                ItemType a[3] = { ARRAY[0], ARRAY[1], ARRAY[3] };
                assert(isPermutation(s3, a, 3));
            }
        } break; case 65: {
            // This test checked that the assignment operator doesn't just
            // copy a pointer.
        } break; case 66: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            {
                Set s2;
                s2.insert(ARRAY[2]);
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                s2 = s;
                s2.insert(ARRAY[5]);
                assert(s2.size() == s.size()+1);
            }
        } break; case 67: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            {
                Set s2;
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                s2.insert(ARRAY[5]);
                s2 = s;
                s2.insert(ARRAY[2]);
                assert(isPermutation(s2, ARRAY, 3));
            }
        } break; case 68: {
            s.insert(ARRAY[0]);
            s.insert(ARRAY[1]);
            {
                Set s2;
                s2.insert(ARRAY[3]);
                s2.insert(ARRAY[4]);
                s2.insert(ARRAY[5]);
                s2 = s;
                s2.insert(ARRAY[2]);
                assert(isPermutation(s, ARRAY, 2));
            }
        } break; case 69: {
            {
                // This test checked that self-assignment doesn't change the
                // number of items in existence.
            }
        } break; case 70: {
            {
                Set s2;
                s2.insert(ARRAY[0]);
                s2.insert(ARRAY[1]);
                s2.insert(ARRAY[2]);
                s2 = s2;
                s2.insert(ARRAY[3]);
                assert(isPermutation(s2, ARRAY, 4));
            }
#endif
        }
    }
}

// ---------------------------------------------------------------------

//// main program
//
//#include <iostream>
//#include <cassert>
//#include "Set.h"
//using namespace std;
//int main()
//
//{
//    /* Testing initial set conditions */
//    Set set;
//    assert(set.size() == 0 && set.empty());
//
//    /* Testing insert() function. */
//    set.insert("first");
//    assert(set.size() == 1); // empty list insertion
//    set.insert("second");
//    assert(set.size() == 2); // one element in list insertion
//    set.insert("third");
//    set.insert("abracadabra");
//    set.insert("third"); // error: duplicate.
//    set.insert("abracadabraa");
//    assert(set.size() == 5);
//
//    /* Testing contains() function. */
//    assert(set.contains("first") && set.contains("second"));
//    assert(!set.contains("not there")); // error: should not exist
//
//    /* Testing erase() function. */
//    set.erase("first");
//    assert(set.size() == 4);
//    set.erase("abracadabraa");
//    assert(set.size() == 3);
//    set.erase("not there"); // error: does not exist
//    assert(set.size() == 3); // unchanged size
//    set.erase("second");
//    set.erase("third");
//    set.erase("abracadabra");
//    set.erase("empty list"); // error: erasing from empty list
//
//    /* Insert fresh values for the set. */
//    set.insert("a");
//    set.insert("b");
//    set.insert("d");
//    set.insert("c");
//
//    /* Testing get() function. */
//    ItemType value;
//    set.get(1, value);
//    assert(value == "b");
//    set.get(2, value);
//    assert(value == "c");
//    set.get(0, value);
//    assert(value == "a"); // first item
//    set.get(set.size(), value);
//    assert(value == "a"); // unchanged: size() is too big
//    set.get(set.size() - 1, value);
//    assert(value == "d");
//    set.erase("d");
//    set.erase("c");
//    set.erase("b");
//    assert(set.size() == 1);
//    set.get(1, value);
//    assert(value == "d"); // unchanged: 1 is too big
//    set.erase("a"); // empty set
//    assert(set.size() == 0);
//    set.get(0, value);
//    assert(value == "d"); // unchanged: empty set
//
//    /* Insert fresh values for set. */
//    set.insert("aloha");
//    set.insert("hello");
//    set.insert("bonjour");
//    set.insert("ciao");
//    set.insert("nihao");
//    set.insert("hola");
//    assert(set.size() == 6);
//
//    /* Create a new set. */
//    Set newSet;
//    newSet.insert("crazy");
//    newSet.insert("fool");
//    newSet.insert("friend");
//    assert(newSet.size() == 3);
//
//    /* Testing swap() function. */
//    set.swap(newSet);
//    assert(newSet.size() == 6 && set.size() == 3);
//    assert(newSet.contains("ciao") && newSet.contains("aloha"));
//    assert(set.contains("friend") && set.contains("fool") && set.contains("crazy"));
//
//    /* Testing copy constructor. */
//    Set copySet = newSet;
//    assert(copySet.size() == 6);
//    assert(copySet.contains("ciao") && copySet.contains("aloha"));
//
//    /* Testing assignment operator. */
//    newSet.insert("some");
//    newSet.insert("more");
//    newSet.insert("values");
//    assert(newSet.size() == 9);
//    copySet = newSet;
//    assert(copySet.size() == 9);
//    assert(copySet.contains("some") && copySet.contains("more") && copySet.contains("values"));
//    assert(newSet.size() == 9); // original set remains unchanged
//
//    /* Testing unite() function. */
//    Set s1;
//    Set s2;
//    Set result;
//    unite(s1, s2, result); // unite empty sets
//    assert(result.size() == 0); // should be empty still
//
//    /* Insert new values. */
//    s1.insert("a");
//    s1.insert("b");
//    s1.insert("c");
//    s1.insert("d");
//    s1.insert("e");
//    s2.insert("a");
//    s2.insert("b");
//    s2.insert("c");
//    s2.insert("f");
//    s2.insert("g");
//
//    unite(s1, s2, result);
//    assert(result.size() == 7); // regular case
//    unite(s1, s1, result);
//    assert(result.size() == s1.size()); // same array, same size
//    unite(s2, s2, result); // same array, same size
//    assert(result.size() == s2.size());
//    unite(result, result, result); // alias
//    assert(result.size() == s2.size()); // shouldn't change
//
//    /* Testing subtract() function. */
//    subtract(s1, s2, result); // regular case
//    assert(result.size() == 2);
//    assert(result.contains("d"));
//    s1 = result;
//    s2 = result;
//    subtract(s1, s2, result); // same values
//    assert(result.size() == 0); // empty set
//    s1.erase("d");
//    s1.erase("e");
//    s2.erase("d");
//    s2.erase("e");
//    subtract(s1, s2, result); // empty sets
//    assert(result.size() == 0); // empty set
//    s1.insert("a");
//    s1.insert("b");
//    s1.insert("c");
//    s1.insert("d");
//    s2.insert("a");
//    s2.insert("b");
//    subtract(s1, s2, result); // regular case
//    assert(result.size() == 2);
//    subtract(s1, result, result); // aliasing
//    assert(result.size() == 2); // should still work
//    subtract(result, result, result); // all the same
//    assert(result.size() == 0); // empty
//
//    cerr << "All tests succeeded." << endl;
//}
