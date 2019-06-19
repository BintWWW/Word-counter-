/*
Programmer: Bintao Wang
Program: bwangP6.cpp
Purpose: open a file and count the times of each words' appearance. And show it alphabetically.
And find word somes out in a somewhat range. And do the show appearance backward.

Input:file name, upper bound, and lower bound
Output:A list of words that apear more than two times alphabetically, list of words apear only
one time. List of words apear between upper bound and lower bound. And words that apear more
than two times anti-alphabetically.
*/
#include<iostream>
#include<iomanip>
#include<assert.h>
#include<cstring>
#include<fstream>
#include<stdio.h>
#include<string>
using namespace std;

struct Node          //struct of the linked list
{
    string list_word;       //word in the linked list
    int word_count=0;       //count of the word in the list
    Node* next;             //pointer to the next list

};
class laBlenk               //class name  Prof. LaBlenk
{
protected:
    Node *head;             //always points to beginning of list
public:
    laBlenk()               //implied "create" function
    {
        head = NULL;
    };
    bool readText (string);     //check if the file with that file name exists
    void Traverse() const;      //traverse list
    void displayStats();        //display the list of words alphabetically
    void displayStats(int,int); //display the list of words apears between the upper bound and the lower bound
    void displayStats(char);    //display the list of words anti-alphabetically

private:
    void RecTraverse (Node*);   //recursive traverse

};                              //const: used when class members are not changed
bool laBlenk::readText(string s)    //check if there is a file, read the file, and put the words in linked list.
{
    string word;                    //name of the string

    Node *cur;                      //pointer for traversing the list
    Node *prev;                     //pointer before the pointer traversing the list
    Node *newword;                  //pointer for the first word in linked list
    Node *newword2;                 //pointer for the next word in linked list
    bool found;                     //if there is a file or not


    ifstream inFP;
    inFP.open(s.c_str());           //try to open the file
    if(!inFP.is_open())             //check if the file is not opened
        return false;
    else
    {
        inFP >> word;               //there is a file, so get the first word in the list
        word[0] = tolower(word[0]); //put the first to the lowercase
    }

    newword=new Node;               //start
    newword->next=head;
    head=newword;
    newword->list_word=word;
    newword->word_count=1;


    inFP>>word;                     //get the words in
    while(word != "DONE")           //check every time if it is a DONE
    {

        newword2=new Node;
        if(word[word.length()-1]=='.'||word[word.length()-1]==','||word[word.length()-1]=='!'||word[word.length()-1]=='?')
            word.erase(word.length()-1);    //delete punctuation
        word[0] = tolower(word[0]); //put the rest words to the lowercase

        newword2->list_word = word;         //insert the next word
        cur = head;
        prev = NULL;
        found = false;

        bool isSame=false;                  //if there's no same words
        while (cur && !found)               //when there is words
        {
            if (newword2->list_word < cur->list_word)          //get the word and insert it before curent cur
                found = true;
            else if(newword2->list_word > cur->list_word)      //pass the word
            {
                prev = cur;
                cur = cur->next;
            }
            else                        //check if there's same words
            {
                isSame=true;
                found=true;
                cur->word_count++;
            }
        }
        if(!isSame)                     //check if there's same words
        {
            if (prev)                   // ++ the word count for the rest of the words
            {
                newword2->word_count++;
                newword2->next = cur;
                prev->next = newword2;
            }
            else                        // ++ the word count for the first word
            {
                newword2->word_count++;
                newword2->next = head;
                head = newword2;
            }
        }
        inFP>>word;                     //insert the next word
    }
    inFP.close();                       //close the file
    return true;
}
void laBlenk::Traverse() const  //print the list
{
    Node *cur;	// pointer for traversing the list
    cur = head;
    int line=0;
    while (cur)         // note call to class method
    {
        if(cur->word_count>1)       //print the list of words that apears more than twice
        {
            cout << cur->list_word << setw(20-cur->list_word.length()) << cur->word_count << endl;
        }
        cur = cur->next;
    }
    cout << endl;
    cout << "Words with count = 1" << endl;
    cout << "====================" << endl;
    cur = head;
    while(cur)                      //print the list of words that apears only once
    {
        if(cur->word_count==1)
        {
            if(line<10){
                cout << cur->list_word << " ";
                line++;
            }
            else{
                line=0;
                cout << endl;
            }
        }
        cur = cur->next;
    }
    cout << endl << endl;
}
void laBlenk::displayStats(char)    //print the list reversly
{
    Node *cur;	// pointer for traversing the list
    cur = head;
    cout << "Words in reverse alphabetical order:" << endl;
    cout << "Word           Count" << endl;
    cout << "====================" << endl;

    RecTraverse (head);             //call the recuirsive function
    cout << endl << endl;
}
void laBlenk::RecTraverse(Node *cur)    //the recursive function
{
    if(cur){                            //end if there is no cur
        RecTraverse(cur->next);         //get back
        if(cur->word_count>1)           //print
            cout << cur->list_word << setw(20-cur->list_word.length()) << cur->word_count << endl;
    }
}
void laBlenk::displayStats()        //print the first list
{
    Node *cur;	// pointer for traversing the list
    string word;
    int word_count;

    cout << "Words in alphabetical order:" << endl;
    cout << "Word           Count" << endl;
    cout << "====================" << endl;
    Traverse();                     //call print list function
}
void laBlenk::displayStats(int low,int high)    //the list that shows the frequency
{
    Node *cur;                      //the hardworking guy in computer
    cout << "Words in frequency order:" << endl;
    cout << "Word           Count" << endl;
    cout << "====================" << endl;
    int temp=high,a=low;
    while(temp>=a)   //check the cur appear temp times, temp-1 times, temp-2 times.......
        {
        cur = head;
        while(cur){
            if(cur->word_count==temp){  //print cur that has apears exact times.
            cout << cur->list_word << setw(20-cur->list_word.length()) << temp << endl;}
            cur = cur->next;
        }
    temp--;
    }
    cout << endl << endl;
}
int main ()                     //It's all your work, I don't wanna comment it!
{
    laBlenk myList;             //Fine, the start of every thing
    string fileName;            //yes the file's name
    int low, high;              //lower bound and upper bound
    cout << "Enter file name: ";

    cin >> fileName;
    if (myList.readText (fileName)) //read file read file
    {

        myList.displayStats();      //yes, display the first list
        cout << "Enter low count: ";
        cin >> low;
        cout << "Enter high count: ";
        cin >> high;
        myList.displayStats(low, high); //second list
        myList.displayStats('R');   //third list
    }
    else                                //show if there's no file
        cout << "Error - problem reading file." << endl;
    return 0;
}
