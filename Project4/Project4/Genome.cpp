#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream> // used to open files

using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_name;
    string m_dna;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence) : m_name(nm), m_dna(sequence) {}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
    string line = "", name = "", sequence = "";
    while (getline(genomeSource, line))
    {
        if (line == "")
            return false; // no empty lines allowed
        
        /* If both name and sequence are empty, this is the start of a new genome. */
        if (line.at(0) == '>')
        {
            /* If name is empty, that means nothing was stored in name previously and this is an empty line. */
            if (!name.empty() && sequence.empty())
                return false;
            
            /* If the both name and sequence contain something, this is a new genome. */
            if (!name.empty() && !sequence.empty())
            {
                Genome newGenome(name, sequence);
                genomes.push_back(newGenome);
                name = "";
                sequence = "";
            }
            
            /* Otherwise, add the rest of the string in to the name. */
            name = line.substr(1);
        }
        
        /* Otherwise, this line should belong to the DNA sequence. */
        else
        {
            for (int i = 0; i < line.length(); i++)
            {
                char ch = line.at(i);
                if (!isalpha(ch))
                    return false; // must be a letter!
                
                /* If it is a letter, convert to upper case and make sure that it is either A, C, G, T, N. */
                if (islower(ch))
                    toupper(ch);
                if (ch != 'A' && ch != 'C' && ch != 'G' && ch != 'T' && ch != 'N')
                    return false; // not a base!
                
                sequence += ch;
            }
        }
    }
    /* Push the last genome in. */
    Genome newGenome(name, sequence);
    genomes.push_back(newGenome);
    
    return true;
}

int GenomeImpl::length() const
{
    return static_cast<int>(m_dna.length());
}

string GenomeImpl::name() const
{
    return m_name;
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if (position + length > m_dna.length())
        return false; // goes past end of genome!
    
    fragment = m_dna.substr(position, length);
    return true;
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes) 
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}
