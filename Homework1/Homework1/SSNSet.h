// SSNSet header file

#ifndef SSNSet_h
#define SSNSet_h
#include "Set.h"

class SSNSet
{
public:
    // Create an empty SSN set.
    SSNSet();

    // Add an SSN to the SSNSet.  Return true if and only if the SSN
    // was actually added.
    bool add(unsigned long ssn);

    // Return the number of SSNs in the SSNSet.
    int size() const;

    // Write every SSN in the SSNSet to cout exactly once, one per
    // line.  Write no other text.
    void print() const;

private:
    Set m_set;
};

#endif /* SSNSet_h */
