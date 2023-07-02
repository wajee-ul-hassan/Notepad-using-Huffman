#pragma once
#include<string>
using namespace std;

struct node
{
    char data;
    node* alphabets[26];
    bool isleaf;
    node()

    {
        data = ' ';
        for (int i = 0; i < 26; i++)
        {
            alphabets[i] = nullptr;
        }
        isleaf = false;
    }
};

class Trie
{
    char* array;
    string store[10];

public:
    node* root;
    Trie();
    string TextEditorMenue();
    node* createnode(char d);
    string printSuggestion(int choice);
    void insertWord(node* root, string word, int length, int i);
    void insert();// insert word into the trie;
    node* getroot();
    void print(int pos, int index);
    void printcursor(int index);
    void suggestion(node* root, int index, string value, int& sc, bool&);
    string start(string array);
};