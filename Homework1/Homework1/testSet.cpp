// main program

#include <iostream>
#include <cassert>
#include "SSNSet.h"
#include "Set.h"
using namespace std;

int main()
{
    Set set;

    assert(set.empty());
    assert(set.size() == 0);

    set.insert("Z");
    set.insert("E");
    set.insert("J");
    set.insert("A");
    set.insert("K");

    assert(set.size() == 5);
    assert(!set.empty());

    set.erase("E");
    set.erase("K");

    assert(set.size() == 3);
    assert(!set.contains("I"));
    assert(set.contains("Z"));
    assert(set.contains("A"));

    Set newSet;
    newSet.insert("hello");
    newSet.insert("hi");
    newSet.insert("how");
    newSet.insert("are");
    newSet.insert("you");

    set.swap(newSet);

    assert(newSet.size() == 3);
    assert(set.size() == 5);
    assert(newSet.contains("Z"));
    assert(set.contains("hello"));
    assert(set.contains("you"));

    Set ss;
    ss.insert("lavash");
    ss.insert("roti");
    ss.insert("chapati");
    ss.insert("injera");
    ss.insert("roti");
    ss.insert("matzo");
    ss.insert("injera");
    assert(ss.size() == 5);  // duplicate "roti" and "injera" were not added
    string x;
    ss.get(0, x);
    assert(x == "chapati");  // "chapati" is greater than exactly 0 items in ss
    ss.get(4, x);
    assert(x == "roti");  // "roti" is greater than exactly 4 items in ss
    ss.get(2, x);
    assert(x == "lavash");  // "lavash" is greater than exactly 2 items in ss

    Set ss1;
    ss1.insert("laobing");
    Set ss2;
    ss2.insert("matzo");
    ss2.insert("pita");
    ss1.swap(ss2);
    assert(ss1.size() == 2  &&  ss1.contains("matzo")  &&  ss1.contains("pita")  &&
           ss2.size() == 1  &&  ss2.contains("laobing"));

    Set ss3;
    ss3.insert("dosa");
    assert(!ss3.contains(""));
    ss3.insert("tortilla");
    ss3.insert("");
    ss3.insert("focaccia");
    assert(ss3.contains(""));
    ss3.erase("dosa");
    assert(ss3.size() == 3  &&  ss3.contains("focaccia")  &&  ss3.contains("tortilla")  &&
           ss3.contains(""));
    string v;
    assert(ss3.get(1, v)  &&  v == "focaccia");
    assert(ss3.get(0, v)  &&  v == "");

      cerr << "All tests suceeded." << endl;
 }
