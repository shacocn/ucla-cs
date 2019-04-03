#include <iostream>
#include <string>
using namespace std;

/* Base class Landmark. */
class Landmark
{
public:
    Landmark(string name) { m_name = name; m_color = "yellow"; };
    string name() const { return m_name; };
    virtual string color() const { return m_color; };
    virtual string icon() const = 0; // pure virtual function
    virtual ~Landmark() {};
private:
    string m_name;
    string m_color;
};

/* Derived class Restaurant. */
class Restaurant : public Landmark
{
public:
    Restaurant(string name, int cap) : Landmark(name) { m_icon = (cap < 40) ? "small knife/fork" : "large knife/fork"; };
    virtual string icon() const { return m_icon; };
    virtual ~Restaurant() { cout << "Destroying the restaurant " + name() << endl; };
private:
    string m_icon;
    string m_color;
};

/* Derived class Hospital. */
class Hospital : public Landmark
{
public:
    Hospital(string name) : Landmark(name), m_icon("H"), m_color("blue") {};
    virtual string icon() const { return m_icon; };
    virtual string color() const { return m_color; };
    virtual ~Hospital() { cout << "Destroying the hospital " + name() << endl; };
private:
    string m_icon;
    string m_color;
};

/* Derived class Hotel. */
class Hotel : public Landmark
{
public:
    Hotel(string name) : Landmark(name), m_icon("bed") {};
    virtual string icon() const { return m_icon; };
    virtual ~Hotel() { cout << "Destroying the hotel " + name() << endl; };
private:
    string m_icon;
};

/* Prints out the descriptions of the landmarks. */
void display(const Landmark* lm)
{
    cout << "Display a " << lm->color() << " " << lm->icon() << " icon for "
    << lm->name() << "." << endl;
}

/* Main function. */
int main()
{
    Landmark* landmarks[4];
    landmarks[0] = new Hotel("Westwood Rest Good");
    landmarks[1] = new Restaurant("Bruin Bite", 30);
    landmarks[2] = new Restaurant("La Morsure de l'Ours", 100);
    landmarks[3] = new Hospital("UCLA Medical Center");
    cout << "Here are the landmarks." << endl;
    for (int k = 0; k < 4; k++)
        display(landmarks[k]);
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete landmarks[k];
}
