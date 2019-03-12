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
    string name, line;
    getline(genomeSource, line);
    if (line.at(0) != '>')
        return false; // first character must indicate name
    
    /* Insert the rest of the line into the name. */
    name = line.substr(1);
    if (name == "")
        return false; // must have something after >
    
    /* Now, we know everything else after this line must be part of the DNA sequence. */
    string dna = "";
    while (getline(genomeSource, line))
    {
        if (line == "")
            return false; // no empty lines!
        
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
            
            /* If it's a proper base, add it to the DNA sequence. */
            dna += ch;
        }
    }
    
    /* If all tests are passed and the file is properly formatted, create a new Genome object with the name and DNA sequence. */
    Genome newGenome(name, dna);
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

int main()
{
    cout << "===============================" << endl;
    
    Trie<string> newTrie;
    newTrie.insert("ACTG", "genome1");
    newTrie.insert("TCGACT", "genome2");
    newTrie.insert("TCTCG", "genome3");
    vector<string> values = newTrie.find("ACTG", false);
    cout << "size: " << values.size() << endl;
    for (int j = 0; j < values.size(); j++)
        cout << values[j] << endl;
    
    Genome g("oryx", "GCTCGGNACACATCCGCCGCGGACGGGACGGGATTCGGGCTGTCGATTGTCTCACAGATCGTCGACGTACATGACTGGGA");
    std::string f1, f2;
    std::string f3 = "GAC";
    bool result1 = g.extract(0, 5, f1);
    bool result2 = g.extract(74, 6, f2);
    bool result3 = g.extract(74, 7, f3);
    assert(result1 && f1 == "GCTCG");
    assert(result2 && f2 == "CTGGGA");
    assert(!result3 && f3 == "GAC");
    
    cout << "===============================" << endl;
    
    Trie<int>* root = new Trie<int>;
    root->insert("HIT", 1);
    root->insert("HIT", 2);
    root->insert("HIP", 10);
    root->insert("HIP", 20);
    root->insert("HAT", 7);
    root->insert("HAT", 8);
    root->insert("HAT", 9);
    root->insert("A", 14);
    root->insert("TO", 22);
    root->insert("TO", 23);
    root->insert("TAP", 19);
    root->insert("TAP", 6);
    root->insert("TAP", 32);
    root->insert("HI", 9);
    root->insert("HI", 17);

    vector<int> result = root->find("TO", true);
    if (result.size() == 0)
        cerr << "not found!" << endl;
    else
    {
        cerr << "result size: " << result.size() << endl;
        for (int i = 0; i < result.size(); i++)
            std::cout << result[i] << std::endl;
    }
    
    cout << "===============================" << endl;
    
    string name = "ZIANICUS CHENICUS";
    string sequence = "ZIANC";
    GenomeImpl obj(name, sequence);
    
    string filename = "/Users/zianchen/Dev/cs32-w18/Project4/data/Ferroplasma_acidarmanus.txt";
    ifstream strm(filename);
    if (!strm)
    {
        cout << "Cannot open " << filename << endl;
    }
    else
    {
        vector<Genome> vg;
        bool success = Genome::load(strm, vg);
        
        if (success)
        {
            cout << "Loaded " << vg.size() << " genomes successfully: " << endl;
            for (int k = 0; k != vg.size(); k++)
                cout << vg[k].name() << endl;
        }
        else
            cout << "Error loading genome data" << endl;
    }
    
    cout << "===============================" << endl;
    
    GenomeMatcher gMatcher(3);
    Genome genome1 ("Genome 1", "ACTG");
    Genome genome2 ("Genome 2", "TCGACT");
    Genome genome3 ("Genome 3", "TCTCG");
    gMatcher.addGenome(genome1);
    gMatcher.addGenome(genome2);
    gMatcher.addGenome(genome3);
    
    cout << "===============================" << endl;
    
    vector<DNAMatch> matches;
    gMatcher.findGenomesWithThisDNA("ACTG", 4, false, matches);
}
