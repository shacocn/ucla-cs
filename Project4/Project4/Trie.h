#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>
#include <list>
#include <iostream>

template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;
    
    // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
private:
    /* Private data structures. */
    struct TrieNode
    {
        char label;
        std::list<ValueType> values;
        std::vector<TrieNode*> children;
    };
    
    /* Private data members. */
    TrieNode* root; // points to empty first node of Trie
    
    /* Recursively frees memory in nodes of the Trie. */
    void freeTrieMemory(TrieNode* node);
    
    /* Recursively insert values into the Trie. */
    void insertIntoTrie(const std::string& key, const ValueType&, TrieNode* node);
    
    /* Recursively finds both exact and SNiP matches in the Trie. */
    void findTrieValues(const std::string& key, bool exactMatchOnly, bool charAlreadyFound, std::vector<ValueType>& matches, TrieNode* node) const;
};

template<typename ValueType>
Trie<ValueType>::Trie()
{
    root = new TrieNode;
    root->label = ' ';
    for (int i = 0; i < 26; i++)
        root->children.push_back(nullptr);
}

template<typename ValueType>
Trie<ValueType>::~Trie()
{
    freeTrieMemory(root);
}

template <typename ValueType>
void Trie<ValueType>::freeTrieMemory(TrieNode* node)
{
   if (node != nullptr)
   {
       for (int i = 0; i < 26; i++)
       {
           freeTrieMemory(node->children[i]);
       }
       delete node;
   }
}

/* Frees memory associated with current Trie and allocates new empty Trie with a single root node. */
template <typename ValueType>
void Trie<ValueType>::reset()
{
    freeTrieMemory(root);
    root = new TrieNode;
    for (int i = 0; i < 26; i++)
        root->children.push_back(nullptr);
    root->label == ' ';
}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value)
{
    insertIntoTrie(key, value, root);
}

template<typename ValueType>
void Trie<ValueType>::insertIntoTrie(const std::string& key, const ValueType& value, TrieNode* node)
{
    if (key.length() == 0)
        return; // nothing to do!
    else
    {
        /* Convert the char to its ascii value. */
        int ch = key.at(0) - 'A';

        /* If the character node does not exist, create a new node. */
        if (node->children[ch] == nullptr)
        {
            node->children[ch] = new TrieNode;
            node->children[ch]->label = key.at(0);
            for (int i = 0; i < 26; i++)
                node->children[ch]->children.push_back(nullptr);
        }

        /* Then, if the string is down to its last character, add value into the Trie; otherwise, continue searching with the rest of the string. */
        if (key.length() == 1)
            node->children[ch]->values.push_back(value);
        else
            insertIntoTrie(key.substr(1), value, node->children[ch]);
    }
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const
{
    std::vector<ValueType> matches;
    
    /* Regardless of whether or not we are searching for an exact match, the first character must match. */
    int firstCh = key.at(0) - 'A';
    if (root->children[firstCh] == nullptr)
        return matches;
    
    /* We then recursively try and find the rest of the key. */
    findTrieValues(key, exactMatchOnly, false, matches, root->children[firstCh]);
    
    return matches;
}

template <typename ValueType>
void Trie<ValueType>::findTrieValues(const std::string& key, bool exactMatchOnly, bool charAlreadyFound, std::vector<ValueType>& matches, TrieNode* node) const
{
    if (key.length() == 0)
        return; // nothing to do!
    if (node == nullptr)
        return; // nothing to do!
    else
    {
        /* If value is nullptr, char does not follow previous char. */
        if (node->label != key.at(0))
        {
            if (exactMatchOnly)
                return; // no exceptions!
            else if (charAlreadyFound)
                return; // already one char difference found!
            charAlreadyFound = true;
        }
        
        /* If the length of the string is 1, this means that we have hit the end of a word. Append the values from this word to matches. */
        if (key.length() == 1)
        {
            matches.insert(matches.end(), node->values.begin(), node->values.end());
            return;
        }
        
        /* Now that we know the current value is acceptable and that we have not yet hit the end of the string, we need to check for a match in each of the node's children/ */
        for (int i = 0; i < 26; i++)
        {
            findTrieValues(key.substr(1), exactMatchOnly, charAlreadyFound, matches, node->children[i]);
        }
    }
}

#endif // TRIE_INCLUDED
