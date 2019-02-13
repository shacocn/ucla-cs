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
    if (n2 < 0 || n1 < 0)
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
