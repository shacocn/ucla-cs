// SSNSet implementation file

#include "SSNSet.h"
#include "Set.h"
#include <iostream>
using namespace std;

SSNSet::SSNSet()
{
    // do nothing.
}

// Add an SSN to the SSNSet.  Return true if and only if the SSN
// was actually added.
bool SSNSet::add(unsigned long ssn)
{
    return m_set.insert(ssn);
}

// Return the number of SSNs in the SSNSet.
int SSNSet::size() const
{
    return m_set.size();
}

// Write every SSN in the SSNSet to cout exactly once, one per
// line.  Write no other text.
void SSNSet::print() const
{
    for (int i = 0; i < m_set.size(); i++)
    {
        unsigned long value = 0;
        m_set.get(i, value);
        cout << value << endl;
    }
}
