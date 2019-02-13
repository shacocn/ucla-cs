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
