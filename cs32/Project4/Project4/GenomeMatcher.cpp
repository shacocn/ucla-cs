#include "provided.h"
#include "Trie.h"
#include <string>
#include <map>
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
    /* Private data members. */
    int m_minSearchLength;
    Trie<pair<int, int>> m_library;
    vector<Genome> m_genomes;
    
    /* Private member functions. */
    void insertIntoResults(Genome genome, double percentage, vector<GenomeMatch>& results) const;
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
    string restOfFragment = fragment.substr(m_minSearchLength);
    
    /* After collecting the potential matches, make sure that the rest of the fragment matches. */
    for (int i = 0; i < potentialMatches.size(); i++)
    {
        /* Extract the rest of the fragment for each genome and check that there is a match. */
        Genome genome = m_genomes[potentialMatches[i].first];
        int genomePos = potentialMatches[i].second;
        string startOfGenome, restOfGenome;
        genome.extract(genomePos, m_minSearchLength, startOfGenome);
        genome.extract(genomePos + m_minSearchLength, genome.length() - (genomePos + m_minSearchLength), restOfGenome);
        
        /* Check to see if the first segment of length m_minSearchLength did not already have a mismatch. */
        bool alreadyASnip = true;
        if (fragment.substr(0, m_minSearchLength) == startOfGenome)
            alreadyASnip = false; // exact match
        
        /* Compare the rest of the characters in the fragment to the rest of the characters in the genome. */
        int longestLength = m_minSearchLength;
        bool validWord = true;
        for (int j = 0; j < restOfFragment.length() && j < restOfGenome.length(); j++)
        {
            /* If the first characters do not match, check to see if is allowable. */
            if (restOfFragment.at(j) != restOfGenome.at(j))
            {
                if (exactMatchOnly)
                {
                    if (longestLength < minimumLength)
                        validWord = false;
                    break; // perfect matches only!
                }
                
                /* If it was a perfect match until now, we can let the mismatch be. */
                if (!alreadyASnip)
                {
                    alreadyASnip = true;
                    longestLength++;
                    continue;
                }
                
                /* Otherwise, there are already too many mismatched characters. This is not a match. */
                if (longestLength < minimumLength)
                    validWord = false;
                break;
            }
            longestLength++;
        }
        
        if (!validWord)
            continue;
        
        /* If all tests are passed, then create a new DNAMatch and add it to matches. */
        DNAMatch newMatch;
        newMatch.genomeName = genome.name();
        newMatch.length = longestLength;
        newMatch.position = genomePos;
        
        /* Make sure that there are no duplicates for this genome! */
        bool replaced = false;
        for (int i = 0; i < matches.size(); i++)
        {
            if (matches[i].genomeName == newMatch.genomeName)
            {
                if (newMatch.length > matches[i].length)
                {
                    matches.erase(matches.begin() + i);
                    matches.push_back(newMatch);
                    replaced = true;
                    break;
                }
                replaced = true;
                break;
            }
        }
        if (!replaced)
            matches.push_back(newMatch);
    }
    return true;
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    if (fragmentMatchLength < m_minSearchLength)
        return false;
    
    /* Create a map that links a genome name to its count. */
    map<string, int> potentialMatches;
    for (int i = 0; i < m_genomes.size(); i++)
        potentialMatches[m_genomes[i].name()] = 0;
    
    int numSequences = query.length() / fragmentMatchLength;
    for (int i = 0; i < numSequences; i++)
    {
        string str;
        query.extract(i * fragmentMatchLength, fragmentMatchLength, str);
        vector<DNAMatch> matches;
        if (!findGenomesWithThisDNA(str, fragmentMatchLength, exactMatchOnly, matches))
            return false; // no matches found!
        
        for (int j = 0; j < matches.size(); j++)
            potentialMatches[matches[j].genomeName]++;
    }
    
    // for each genome that has a matching sequence
    for (int i = 0; i < m_genomes.size(); i++)
    {
        double percentage = (static_cast<double>(potentialMatches[m_genomes[i].name()]) / numSequences) * 100;
        if (percentage > matchPercentThreshold)
            insertIntoResults(m_genomes[i], percentage, results);
    }
    
    return true;
}

void GenomeMatcherImpl::insertIntoResults(Genome genome, double percentage, vector<GenomeMatch>& results) const
{
    GenomeMatch newMatch;
    newMatch.genomeName = genome.name();
    newMatch.percentMatch = percentage;
    
    /* If there's nothing in results, then just add the percentage. */
    if (results.size() == 0)
    {
        results.push_back(newMatch);
        return;
    }
    
    /* Afterwards, pos will hold the index of the element that should go before the inserted element. */
    int pos = 0;
    while (pos < results.size() && results[pos].percentMatch >= percentage)
        pos++;
    
    /* Break ties by comparing genome name. */
    if (results[pos].percentMatch == percentage && results[pos].genomeName < genome.name())
        pos++;
    
    /* Finally, insert the newMatch into the vector. */
    results.insert(results.begin() + pos, newMatch);
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
