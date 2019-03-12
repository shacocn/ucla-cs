#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <fstream>
using namespace std;

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    int m_minSearchLength;
    Trie<pair<int, int>> m_library;
    vector<Genome> m_genomes;
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength) : m_minSearchLength(minSearchLength) {}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    m_genomes.push_back(genome);
    
    /* Add DNA sequences of the newly-added genome by adding every substring of length minSearchLength. */
    for (int startPos = 0; startPos <= genome.length() - m_minSearchLength; startPos++)
    {
        string dna;
        genome.extract(startPos, m_minSearchLength, dna);
        cout << "dna sequence: " << dna << endl;
        pair<int, int> p(m_genomes.size() - 1, startPos);
        m_library.insert(dna, p);
    }
}

int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minSearchLength;
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    if (fragment.length() < minimumLength || minimumLength < m_minSearchLength)
        return false;
    
    /* First search for all the potential matches within the Trie. */
    vector<pair<int, int>> potentialMatches = m_library.find(fragment.substr(0, m_minSearchLength), exactMatchOnly);
    
    /* After collecting the potential matches, make sure that the rest of the fragment matches. */
    for (int i = 0; i < potentialMatches.size(); i++)
    {
        /* Extract the rest of the fragment for each genome and check that there is a match. */
        Genome genome = m_genomes[potentialMatches[i].first];
        string restOfMatch;
        int pos = potentialMatches[i].second;
        int restOfMatchLen = static_cast<int>(fragment.length() - m_minSearchLength);
        genome.extract(m_minSearchLength, restOfMatchLen, restOfMatch);
    }

    return true;  // This compiles, but may not be correct
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return false;  // This compiles, but may not be correct
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
