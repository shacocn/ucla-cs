#include <iostream>
#include <cassert>
using namespace std;

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    /* Base cases. */
    if (n2 < 0 && n1 < 0)
        return 0; // impossible scenario!
    if (n2 == 0)
        return 1; // combo found. increment count by one.
    if (n1 == 0)
        return 0; // ran out of room in a1, combo not found.
    else
    {
        /* If the first elements match, do two checks: for the first check, move down one element (marking the first element in a2 as found) and search for the rest of the  elements in the remainder of a1. For the second check, hold on to the value of the first element in a2 and move on in a1 to see if that value crops up again. If it comes up again, that means that there is a possibility for another match. Each time a pair is found, do both checks to catch all repeats. */
        if (a2[0] == a1[0])
        {
            return countIncludes(a1+1, n1-1, a2+1, n2-1) + countIncludes(a1+1, n1-1, a2, n2);
        }
        return countIncludes(a1+1, n1-1, a2, n2);
    }
}

// Exchange two doubles
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > divider come before all the other elements,
// and all the elements whose value is < divider come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= divider, or n if there is no such element, and firstLess is
// set to the index of the first element that is < divider, or n
// if there is no such element.
void divide(double a[], int n, double divider,
            int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;
    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < divider)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > divider)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
    /* For each iteration of this function, the first element in the array gets placed in its proper location. We then reorder the first half of the array (which is all guaranteed to be larger or equal to that first element--the divider) and then reorder the second half of the array. */
    if (n <= 1)
        return; // do nothing
    else
    {
        int firstNotGreater, firstLess;
        divide(a, n, a[n/2], firstNotGreater, firstLess);
        order(a, firstNotGreater); // order first half
        order(a + firstLess, n - firstLess); // order second half
    }
}

void print(double arr[], int n)
{
    for (int i = 0; i < n; i++)
        cerr << arr[i] << " ";
    cerr << endl << "--------------------------" << endl;
}

int main()
{
    /* Testing countIncludes function. */
    double arr[7] = { 10, 50, 40, 20, 50, 40, 30 };
    double test[3] = { 10, 20, 40 };
    assert(countIncludes(arr, 7, test, 3) == 1);
    
    test[0] = 10;
    test[1] = 40;
    test[2] = 30;
    assert(countIncludes(arr, 7, test, 3) == 2);
    
    test[0] = 20;
    test[1] = 10;
    test[2] = 40;
    assert(countIncludes(arr, 7, test, 3) == 0);
    
    test[0] = 50;
    test[1] = 40;
    test[2] = 30;
    assert(countIncludes(arr, 7, test, 3) == 3);
    
    double arr2[7] = { 5, 5, 3, 2, 5, 3, 2 };
    double test2[2] = { 5, 3 };
    assert(countIncludes(arr2, 7, test2, 2) == 5);
    
    /* Testing order function. */
    order(arr, 7);
    print(arr, 7);
    order(test, 3);
    print(test, 3);
    order(arr2, 7);
    print(arr2, 7);
    
    double arr3[10] = { 3, 6, 2, 6, 1, 9, 3, 2, 7, 3 };
    double arr4[10] = { 2, 7, 2, 8, 9, 7, 3, 1, 2, 3 };
    order(arr3, 10);
    order(arr4, 10);
    print(arr3, 10);
    print(arr4, 10);
    
    double arr5[20] = { 9, 8, 2, 3, 4, 5, 9, 2, 1, 4, 3, 8, 6, 8, 4, 2, 5, 3, 1, 6 };
    order(arr5, 20);
    print(arr5, 20);
    
    cerr << "All tests passed." << endl;
}
