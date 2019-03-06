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
