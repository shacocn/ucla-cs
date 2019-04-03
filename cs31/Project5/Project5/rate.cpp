#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;

/* Constants. */
const int MAX_WORD_LENGTH = 20;

/* Moves current value to end and shifts everything else left. */
void removeValue(int separation[], char arrOne[][MAX_WORD_LENGTH+1], char arrTwo[][MAX_WORD_LENGTH+1], int& nPatterns, int swapValue);

/* Checks if the word is all letters and converts it to proper case as well. */
bool validWord(char arr[][MAX_WORD_LENGTH+1], int r);

/* Formats the pattern or removes it from the array. */
int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int nPatterns);

/* Find words that matching pairs and remove the one with smallest separation value. */
void findMatches(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int& nPatterns);

/* Converts the array to lower case. */
void convertToLower(char arr[][MAX_WORD_LENGTH+1], int nPatterns);

/* Returns number of matched patterns in the document. */
int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns);

void printWordArray(char wordArray[][MAX_WORD_LENGTH+1], int wordsUsed);

/* Adds words to the array of c-strings. */
void addWords(char wordArray[][MAX_WORD_LENGTH+1], const char document[], int& numWords);

bool findNextMatch(char wordArray[][MAX_WORD_LENGTH+1], int numWords, int currentVal, const char wordToFind[], int sepValue, int& totalPatternCount);

/* Main function. */
int main()
{
    /* -------------makeProper() TEST CASES---------------- */
    // regular case
    const int RULES = 4;
    char one[RULES][MAX_WORD_LENGTH+1] = { "mAd", "dERAngED", "neFAriouS", "0890R" };
    char two[RULES][MAX_WORD_LENGTH+1] = { "scientist", "craZy", "plot", "mad" };
    int sep1[RULES] = { 1, 3, 0, 12 };
    assert(makeProper(one, two, sep1, RULES) == 3); // && strcmp(one[0], "mad") == 0 && strcmp(one[1], "deranged") == 0 && strcmp(one[2], "nefarious") == 0 && strcmp(two[1], "crazy") == 0);
    
    // empty string
    char first[RULES][MAX_WORD_LENGTH+1] = { "", "empty", "neFAriouS", "0890R" };
    char second[RULES][MAX_WORD_LENGTH+1] = { "scientist", "craZy", "plot", "mad" };
    assert(makeProper(first, second, sep1, RULES) == 2); // && strcmp(one[0], "empty") == 0 && strcmp(one[1], "nefarious") == 0 && strcmp(two[0], "crazy") == 0);
    
    // non-alpha characters as words
    char uno[RULES][MAX_WORD_LENGTH+1] = { "0h" , "thats" , "bab3" , "cra2y" };
    char dos[RULES][MAX_WORD_LENGTH+1] = { "on" , "cool" , "babe", "crazy" };
    assert(makeProper(uno, dos, sep1, RULES) == 1); // && strcmp(uno[0], "thats") == 0 && strcmp(two[0], "cool") == 0);
    
    // negative separation
    int sep2[RULES] = { 1, -2, 0, 12 };
    assert(makeProper(one, two, sep2, RULES) == 2); // && strcmp(one[0], "mad") == 0);
    
    // same pattern
    char bonjour[RULES][MAX_WORD_LENGTH+1] = { "oh", "very", "amazing", "FRIEND" };
    char aurevoir[RULES][MAX_WORD_LENGTH+1] = { "me", "amazing", "very", "classY" };
    assert(makeProper(bonjour, aurevoir, sep1, RULES) == 3); // && strcmp(bonjour[0], "oh") == 0 && strcmp(bonjour[1], "very") == 0);
    
    /* -------------rate() TEST CASES---------------- */
    const int TEST1_NRULES = 4;
    char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    int test1dist[TEST1_NRULES] = {
        1,           3,          0,           12
    };
    assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("**** 2018 ****",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    assert(rate("  That plot: NEFARIOUS!",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("deranged deranged robot deranged robot robot",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    
    cout << "All tests succeeded" << endl;
}

/* Converts array in the pattern to the proper format and returns number of valid patterns. */
int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int nPatterns)
{
    /* Convert to lowercase first (should not affect any error cases. */
    convertToLower(word1, nPatterns);
    convertToLower(word2, nPatterns);
    
    /* Goes through each pairing from word1 and word2. We go from the end to the beginning because this allows for us to avoid altering the conditional statement (in the case that nPatterns gets changed). */
    for (int r = nPatterns-1; r >= 0; r--)
    {
        if(separation[r] < 0 || !validWord(word1, r) || !validWord(word2, r))
            removeValue(separation, word1, word2, nPatterns, r);
    }
    
    /* Now that all words are properly formatted, we must remove duplications. */
    findMatches(word1, word2, separation, nPatterns);
    
    if (nPatterns < 0) // accounts for negative nPatterns
        return 0;
    return nPatterns;
}

/* Find words that matching pairs and remove the one with smallest separation value. */
void findMatches(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int& nPatterns)
{
    for (int i = nPatterns-1; i >= 1; i--)
    {
        for (int j = i-1; j >= 0; j--) // checks i-value with all values before it
        {
            if ((strcmp(word1[i], word1[j]) == 0 && strcmp(word2[i], word2[j]) == 0) || (strcmp(word1[i], word2[j]) == 0 && strcmp(word2[i], word1[j]) == 0))
            {
                /* If a match is found, remove the one that has a smaller separation. */
                if (separation[i] < separation[j])
                    removeValue(separation, word1, word2, nPatterns, i);
                else
                    removeValue(separation, word1, word2, nPatterns, j);
            }
        }
    }
}

/* Checks to see if the specific word has all letters. */
bool validWord(char arr[][MAX_WORD_LENGTH+1], int r)
{
    if(arr[r][0] == '\0') // accounts for empty string
        return false;
    
    /* Traverse the entire c-string and return false if a non-letter is found. */
    for (int c = 0; arr[r][c] != '\0'; c++)
    {
        if (!isalpha(arr[r][c]))
            return false;
    }
    return true; // no problem with the string; properly formatted
}

/* Swaps current value with the value at the end by holding temporary values. */
void removeValue(int separation[], char one[][MAX_WORD_LENGTH + 1], char two[][MAX_WORD_LENGTH + 1], int& nPatterns, int swapValue)
{
    char temp1[MAX_WORD_LENGTH+1];
    char temp2[MAX_WORD_LENGTH+1];
    int temp = separation[swapValue];
    strcpy(temp1, one[swapValue]);
    strcpy(temp2, two[swapValue]);
    for (int i = swapValue; i < nPatterns-1; i++)
    {
        strcpy(one[i], one[i+1]);
        strcpy(two[i], two[i+1]);
        separation[i] = separation[i+1];
    }
    strcpy(one[nPatterns-1], temp1);
    strcpy(two[nPatterns-1], temp2);
    separation[nPatterns-1] = temp;
    nPatterns--;
}

/* Converts the array to lowercase. */
void convertToLower(char arr[][MAX_WORD_LENGTH+1], int nPatterns)
{
    for (int i = 0; i < nPatterns; i++)
    {
        for (int j = 0; arr[i][j] != '\0'; j++)
            arr[i][j] = tolower(arr[i][j]);
    }
}

/* Returns number of matched patterns in the document. */
int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns)
{
    if (nPatterns <= 0) // no patterns to match!
        return 0;
    
    const int MAX_WORDS = 250;
    char wordArray[MAX_WORDS][MAX_WORD_LENGTH+1];
    int totalPatternCount = 0;
    int numWords = 0;
    
    /* Add words to an array of words. */
    addWords(wordArray, document, numWords);
    
    /* If there is a match, then search for the next one. */
    for (int i = 0; i < nPatterns; i++)
    {
        for (int j = 0; j < numWords; j++)
        {      /* Will compute the first condition before the second. */
            if (strcmp(wordArray[j], word1[i]) == 0 && findNextMatch(wordArray, numWords, j, word2[i], separation[i], totalPatternCount))
                break; // stop computing if a pattern is found!
        }
    }
    return totalPatternCount;
}

/* Finds the next match in the array. */
bool findNextMatch(char wordArray[][MAX_WORD_LENGTH+1], int numWords, int currentVal, const char wordToFind[], int sepValue, int& totalPatternCount)
{
    for (int i = 0; i < numWords; i++)
    {
        /* Find the range to search through (but keeping within the range of the actual wordArray. */
        int lowerBound = currentVal - sepValue - 1;
        if (lowerBound < 0)
            lowerBound = 0;
        for (int j = lowerBound; j < numWords && j <= currentVal + sepValue + 1; j++)
        {
            if (strcmp(wordArray[j], wordToFind) == 0)
            {
                totalPatternCount++;
                return true;
            }
        }
    }
    return false;
}

/* Adds words to the array of c-strings. */
void addWords(char wordArray[][MAX_WORD_LENGTH+1], const char document[], int& numWords)
{
    int wordArrayRow = 0;
    int wordArrayCol = 0;
    bool previousWasABlank = true;
    bool previousWasALetter = true;
    
    /* Add all words to an array of c-strings. */
    for (int i = 0; document[i] != '\0'; i++)
    {
        char currentChar = document[i];
        if (!previousWasABlank && currentChar == ' ') // new word
        {
            wordArrayCol = 0;
            wordArrayRow++;
            numWords++;
            previousWasABlank = true;
            previousWasALetter = false;
        }
        else if (isalpha(currentChar)) // add to word
        {
            currentChar = tolower(currentChar);
            wordArray[wordArrayRow][wordArrayCol] = currentChar;
            wordArray[wordArrayRow][wordArrayCol+1] = '\0';
            wordArrayCol++;
            previousWasABlank = false;
            previousWasALetter = true;
        }
    }
    if (previousWasALetter)
        numWords++;
}

/* Prints array. */
void printWordArray(char wordArray[][MAX_WORD_LENGTH+1], int wordsUsed)
{
    for (int i = 0; i < wordsUsed; i++)
    {
        for (int j = 0; wordArray[i][j] != '\0'; j++)
            cerr << wordArray[i][j];
        cerr << endl;
    }
}

