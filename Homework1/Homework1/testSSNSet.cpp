#include <iostream>
#include <cassert>
#include "SSNSet.h"
#include "Set.h"
using namespace std;

int main()
{
        SSNSet set;
        set.add(705105164);
        set.add(829508034);
        set.add(943808599);
        assert(set.size() == 3);

        Set s;
        assert(s.empty());
        ItemType x = 9876543;
        assert( !s.get(42, x)  &&  x == 9876543); // x unchanged by get failure
        s.insert(123456789);
        assert(s.size() == 1);
        assert(s.get(0, x)  &&  x == 123456789);
        cout << "Passed all tests" << endl;

}
