<<<<<<< HEAD
=======
#include <iostream>
#include <cassert>

using namespace std;

/* Inconsequential somePredicate function. */
bool somePredicate(double x)
{
    return x < 0;
}

>>>>>>> origin/master
/* Return true if the somePredicate function returns true for at least one of the array elements, false otherwise. */
bool anyTrue(const double a[], int n)
{
    if (n <= 0)
        return false; // empty array
    if (n == 1)
        return somePredicate(a[0]); // one element leftover
    else
    {
        if (somePredicate(a[0])) // check first element
            return true;
        return anyTrue(a+1, n-1); // check rest of elements
    }
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
    if (n <= 0)
        return 0; // empty array
    if (n == 1)
    {
        if (somePredicate(a[0]))
            return 1;
        return 0;
    }
    else
    {
        if (somePredicate(a[0]))
            return 1 + countTrue(a+1, n-1); // add one if true
        return countTrue(a+1, n-1);
    }
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
    if (n <= 0)
        return -1; // empty array
    if (n == 1)
    {
        if (somePredicate(a[0]))
            return 0;
        return -1;
    }
    else
    {
        if (somePredicate(a[0]))
            return 0;
        return 1 + firstTrue(a+1, n-1);
    }
}

// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int positionOfMin(const double a[], int n)
{
    if (n <= 0)
        return -1; // no elements in array
    if (n == 1)
        return 0; // one element, has to be smallest
    else
    {
        int i = 1 + positionOfMin(a+1, n-1);
        if (a[0] < a[i])
            return 0;
        else
            return i;
    }
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
bool includes(const double a1[], int n1, const double a2[], int n2)
{
<<<<<<< HEAD
    if (n2 < 0 || n1 < 0)
=======
    if (n2 < 0)
>>>>>>> origin/master
        return false;
    if (n2 == 0)
        return true;
    if (n1 == 0)
        return false; // could not find all values in a1
    else
    {
        /* If the first elements of the two arrays are a match, then move on in both. */
        if (a2[0] == a1[0])
            return includes(a1+1, n1-1, a2+1, n2-1);
        
        /* If they are not, then only increment one element forward in a1 to compare to first element of a2 again. */
        return includes(a1+1, n1-1, a2, n2);
    }
}
<<<<<<< HEAD
=======


int main()
{
    /* Test anyTru function. */
    double empty[0];
    assert(anyTrue(empty, 0) == false); // empty array
    double arr[5] = { -1.0, 3.2, 4.5, 5.3, 6.7 };
    assert(anyTrue(arr, 5) == true); // first element negative
    arr[0] = 5.5;
    assert(anyTrue(arr, 5) == false); // all positive
    arr[4] = -1.1;
    assert(anyTrue(arr, 5) == true); // last element negative
    
    /* Test countTrue function. */
    assert(countTrue(empty, 0) == 0); // empty array
    arr[4] = 5.5;
    assert(countTrue(arr, 5) == 0); // none true
    arr[4] = -1.1;
    assert(countTrue(arr, 5) == 1); // one true
    arr[0] = -1.1;
    assert(countTrue(arr, 5) == 2); // two true
    arr[1] = -2.1;
    arr[2] = -4.3;
    arr[3] = -6.7;
    assert(countTrue(arr, 5) == 5); // all true
    
    /* Test firstTrue function. */
    assert(firstTrue(empty, 0) == -1); // empty array
    assert(firstTrue(arr, 5) == 0); // first element true
    arr[0] = 5.5;
    assert(firstTrue(arr, 5) == 1); // second element true
    arr[1] = 6;
    arr[2] = 3;
    arr[3] = 4;
    assert(firstTrue(arr, 5) == 4); // last element true
    
    /* Test positionOfMin function. */
    assert(positionOfMin(empty, 0) == -1); // empty array
    double arr2[5] = { 4, 3, 2, 4, 5 };
    assert(positionOfMin(arr2, 5) == 2); // in second pos
    arr2[0] = 0.0;
    assert(positionOfMin(arr2, 1) == 0); // one element array
    assert(positionOfMin(arr2, 5) == 0); // in pos 0
    
    double arr3[5] = { 3, 3, 4, 0, 6 };
    assert(positionOfMin(arr3, 5) == 3);
    arr3[3] = 8;
    assert(positionOfMin(arr3, 5) == 1);
    
    double arr4[5] = { 6, 7, 5, 5, 9 };
    assert(positionOfMin(arr4, 5) == 3); // two of the same
    
    /* Test includes function. */
    double arr5[7] = { 10, 50, 40, 20, 50, 40, 30 };
    double yes[3] = { 50, 20, 30 };
    assert(includes(arr5, 7, yes, 3));
    yes[1] = 40;
    yes[2] = 40;
    double no[3] = { 50, 30, 20 };
    assert(!includes(arr5, 7, no, 3));
    double no2[3] = { 10, 20, 20};
    assert(!includes(arr5, 7, no2, 3));
    
    cerr << "All tests passed." << endl;
}
>>>>>>> origin/master
