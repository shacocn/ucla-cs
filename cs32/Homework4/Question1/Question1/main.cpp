#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MenuItem
{
public:
    MenuItem(string nm) : m_name(nm) {}
    virtual ~MenuItem() {}
    string name() const { return m_name; }
    virtual bool add(MenuItem* m) = 0;
    virtual const vector<MenuItem*>* menuItems() const = 0;
private:
    string m_name;
};

class PlainMenuItem : public MenuItem   // PlainMenuItem allows no submenus
{
public:
    PlainMenuItem(string nm) : MenuItem(nm) {}
    virtual bool add(MenuItem* m) { return false; }
    virtual const vector<MenuItem*>* menuItems() const { return nullptr; }
};

class CompoundMenuItem : public MenuItem  // CompoundMenuItem allows submenus
{
public:
    CompoundMenuItem(string nm) : MenuItem(nm) {}
    virtual ~CompoundMenuItem();
    virtual bool add(MenuItem* m) { m_menuItems.push_back(m); return true; }
    virtual const vector<MenuItem*>* menuItems() const { return &m_menuItems; }
private:
    vector<MenuItem*> m_menuItems;
};

CompoundMenuItem::~CompoundMenuItem()
{
    for (int k = 0; k < m_menuItems.size(); k++)
        delete m_menuItems[k];
}

void listAll(const MenuItem* m, string path) // two-parameter overload
{
    /* If there are no submenus, just print out the current name and return. */
    if (m->menuItems() == nullptr)
        cerr << path + m->name() << endl;
    else
    {
        /* Print out name of current class as long as the name is not an empty string. */
        if (m->name() != "")
        {
            path = path + m->name();
            cout << path << endl;
        }
        
        /* Then, go through each of the submenus and print out the names of the submenus. */
        for (vector<MenuItem*>::const_iterator it = m->menuItems()->begin(); it != m->menuItems()->end(); it++)
        {
            /* Add a blackslash if the current name is not an empty string. */
            if (m->name() == "")
                listAll(*it, path);
            else
                listAll(*it, path + '/');
        }
    }
}

void listAll(const MenuItem* m)  // one-parameter overload
{
    if (m != nullptr)
        listAll(m, "");
}

int main()
{
    CompoundMenuItem* cm0 = new CompoundMenuItem("New");
    cm0->add(new PlainMenuItem("Window"));
    CompoundMenuItem* cm1 = new CompoundMenuItem("File");
    cm1->add(cm0);
    cm1->add(new PlainMenuItem("Open"));
    cm1->add(new PlainMenuItem("Exit"));
    CompoundMenuItem* cm2 = new CompoundMenuItem("Help");
    cm2->add(new PlainMenuItem("Index"));
    cm2->add(new PlainMenuItem("About"));
    CompoundMenuItem* cm3 = new CompoundMenuItem("");  // main menu bar
    cm3->add(cm1);
    cm3->add(new PlainMenuItem("Refresh"));  // no submenu
    cm3->add(new CompoundMenuItem("Under Development")); // no submenus yet
    cm3->add(cm2);
    CompoundMenuItem* cm4 = new CompoundMenuItem("");
    cm1->add(cm4);
    cm4->add(new PlainMenuItem("Zian's Special"));
    listAll(cm1);
    delete cm1;
}
