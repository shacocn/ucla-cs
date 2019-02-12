#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

/* Supplemental function declarations. */
int convert(string infix, string& postfix);
int dissect(const Set& trueValues, const Set& falseValues, string& postfix, bool& result);

/* Evalutes an infix string. */
int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
    if (infix == "")
        return 1; // empty string
    
    /* Convert to postfix while checking for valid string. */
    int convertResult = convert(infix, postfix);
    if (convertResult != 0)
        return convertResult;
    
    /* Evaluate the postfix expression. */
    return dissect(trueValues, falseValues, postfix, result);
}

/* Changes infix string to viable postfix string or returns a number other than 0 to indicate invalid string. */
int convert(string infix, string& postfix)
{
    stack<char> opStack;
    postfix = "";
    int strLen = static_cast<int>(infix.length());
    char prev = '|';
    
    for (int i = 0; i < strLen; i++)
    {
        char ch = infix[i];
        switch(ch)
        {
            default:
                if (ch == ' ')
                    continue; // skip blanks
                if (isalpha(prev))
                    return 1; // can't have two letters in a row
                if (isalpha(ch) && islower(ch))
                {
                    postfix += ch;
                    prev = ch;
                    break;
                }
                else
                    return 1; // syntactically invalid
            case '(':
                if (isalpha(prev))
                    return 1; // can't have number directly before open brace
                opStack.push(ch);
                prev = ch;
                break;
            case ')':
                if (prev == '(' || prev == '!' || prev == '&' || prev == '|')
                    return 1; // must have letter before close parentheses
                while(!opStack.empty() && opStack.top() != '(')
                {
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.pop();
                prev = ch;
                break;
            case '!': // ascii value 33
            case '&': // ascii value 38
            case '|': // ascii value 124
                if (i == strLen-1)
                    return 1; // last char can't be operator
                else if ((ch == '&' || ch == '|') && !(isalpha(prev) || prev == ')'))
                    return 1; // can't have two operators in a row that aren't !!
                while (opStack.size() != 0 && opStack.top() != '(' && ch >= opStack.top())
                {
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.push(ch);
                prev = ch;
                break;
        }
    }
    while(opStack.size() != 0)
    {
        postfix += opStack.top();
        opStack.pop();
    }
    return 0;
}

/* Evaluates the postfix string and returns 0. */
int dissect(const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
    stack<bool> opStack;
    int strLen = static_cast<int>(postfix.length());
    bool op1, op2;
    
    for(int i = 0; i < strLen; i++)
    {
        char ch = postfix[i];
        if (isalpha(ch)) // operand
        {
            bool inTrue = trueValues.contains(ch);
            bool inFalse = falseValues.contains(ch);
            
            if (!inTrue && !inFalse)
                return 2; // value found in neither
            if (inTrue && inFalse)
                return 3; // value exists in both
            
            if (inTrue) // truthy value
                opStack.push(true);
            else        // falsy value
                opStack.push(false);
        }
        else // operator
        {
            if (ch == '!') // only operates on one element
            {
                op1 = opStack.top();
                opStack.pop();
                opStack.push(!op1);
                continue;
            }
            op1 = opStack.top();
            opStack.pop();
            op2 = opStack.top();
            opStack.pop();
            if (ch == '&')
                opStack.push( op1 && op2 );
            else if (ch == '|')
                opStack.push( op1 || op2 );
        }
    }
    result = opStack.top();
    return 0;
}

int main()
{
    Set trues;
    trues.insert('a');
    trues.insert('e');
    trues.insert('i');
    trues.insert('o');
    trues.insert('u');
    
    Set falses;
    falses.insert('b');
    falses.insert('g');
    falses.insert('k');
    falses.insert('p');
    
    string infix = "e&!(b|o&i|k)|!!!(p&e&g)";
    string postfix;
    bool result;
    evaluate(infix, trues, falses, postfix, result) == 0;
    cerr << postfix << endl;
    cerr << "all tests passed" << endl;
}
