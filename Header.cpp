#include "Header.h"
#include<fstream>
#include <conio.h>
#include <stack>
#include <string>
#include <Windows.h>
#include<iostream>
#include "Header1.h"
using namespace std;

Trie::Trie()
{

    for (int i = 0; i < 10; i++)
    {
        store[i] = " ";
    }
    array = new char[50];
    for (int i = 0; i < 50; i++)
    {
        array[i] = ' ';
    }
    root = new node;
}

string Trie::TextEditorMenue()
{
    char num = ' ';
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    cout << endl << "\t\t\t\t\t*WELCOME TO TEXT EDITOR* " << endl;
    cout << "\n\n\n\n";
    SetConsoleTextAttribute(hConsole, 15);
    system("CLS");
    SetConsoleTextAttribute(hConsole, 4);
    cout << "\n\n\n\n\t\t\t\t\t\t\t*TEXT EDITOR IS STARTING*\n\n\n";
    SetConsoleTextAttribute(hConsole, 11);
    cout << "\t\t\t\t\t\t1. New File\n\n " << "\t\t\t\t\t\t2. Load File\n\n ";
    SetConsoleTextAttribute(hConsole, 13);
    cout << "\n\n\t\t\t\t\t\tChoose option : ";
    cin >> num;
    while (num != '1' && num != '2')
    {
        SetConsoleTextAttribute(hConsole, 15);
        system("CLS");
        SetConsoleTextAttribute(hConsole, 4);
        cout << "\n\n\n\n\t\t\t\t\t\t\t*TEXT EDITOR IS STARTING*\n\n\n";
        SetConsoleTextAttribute(hConsole, 11);
        cout << "\t\t\t\t\t\t1. New File\n\n " << "\t\t\t\t\t\t2. Load File\n\n " << "\t\t\t\t\t\t3. Exit\n ";
        SetConsoleTextAttribute(hConsole, 13);
        cout << "\n\n\t\t\t\t\t\tWrong input, Choose option again : ";
        cin >> num;
    }
    if (num == '1')
    {
        SetConsoleTextAttribute(hConsole, 10);
        cout << "\n :) Creating new file...";
        Sleep(1000);
        system("CLS");
        SetConsoleTextAttribute(hConsole, 7);
        return "\0";
    }
    else if (num == '2')
    {
        string key;
        SetConsoleTextAttribute(hConsole, 10);
        cout << "\n :) Loading from file...";
        Sleep(2000);
        system("CLS");
        SetConsoleTextAttribute(hConsole, 7);
        
        ifstream in;
        in.open("Text.txt");
        char a;
        while (!in.eof())
        {
            getline(in, key , '\0');
        }
        huffman obj;
        obj.chkfreq(key);
        obj.sort();
        obj.merge();
        string key1;
        obj.decode(key1);
        return key1;
        
    }
}

node* Trie::createnode(char d)
{
    node* nn = new node;
    for (int i = 0; i < 26; i++)
    {
        nn->alphabets[i] = nullptr;
    }
    nn->data = d;
    nn->isleaf = false;
    return nn;
}

string Trie::printSuggestion(int choice)
{
    return store[choice - 1];
}

void Trie::insertWord(node* root, string word, int length, int i)
{
    if (length == i)
    {
        root->isleaf = true;
        return;
    }
    int index = word[i] - 'a';
    if (root->alphabets[index] != NULL)
    {
        root = root->alphabets[index];
    }
    else
    {
        root->alphabets[index] = createnode(word[i]);
        root = root->alphabets[index];
    }

    insertWord(root, word, length, i + 1);
}

void Trie::insert()
{
    long long int no_of_words = 0;
    bool flag = true;
    ifstream in;
    in.open("rDictionary.txt");
    string word;
    while (!in.eof())
    {
        getline(in, word);
        int count = word.length();
        for (int i = 0; i < count && flag; i++)
        {
            if (word[i] >= 'a' && word[i] <= 'z')
            {
                flag = true;
            }
            else
            {
                flag = false;
            }
        }
        if (flag)
        {
            // cout << word << endl;
            no_of_words++;
            int i = 0;
            insertWord(root, word, count, i);
        }
        word = " ";
    }
    cout << "\t\t\t\Total words in a dictionary are : " << no_of_words << endl << endl ;

    in.close();
    return;
}

node* Trie::getroot()
{
    return root;
}

void Trie::print(int pos, int index)
{
    string word;
    cout << index + 1 << ":";
    for (int i = 0; i < pos; i++)
    {
        cout << array[i];
        word += array[i];
    }
    store[index] = word;
}

void Trie::printcursor(int index)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < 10; i++)
    {
        if (i == index)
        {
            SetConsoleTextAttribute(hConsole, 11);
            cout << i + 1 << ":" << store[i] << endl;
            SetConsoleTextAttribute(hConsole, 7);
        }
        else
        {
            cout << i + 1 << ":" << store[i] << endl;
        }
    }
}

void Trie::suggestion(node* root, int index, string value, int& sc , bool &checkNoSug)
{
    if (root->isleaf && root->data != ' ')
    {
        bool flag = true;
        for (int x = 0; x < value.length() && flag; x++)
        {
            if (array[x] != value[x])
            {
                flag = false;
            }
        }
        if (flag)
        {
            if (sc == 10)
            {
                return;
            }
            else
            {
                checkNoSug = true;
                print(index, sc);
                cout << endl;
                sc++;
          }
        }
    }
    if (sc != 10)
    {
        for (int i = 0; i < 26; i++)
        {
            // if NON NULL child is found
            // add parent key to str and
            // call the display function recursively
            // for child node

            if (root->alphabets[i] != NULL)
            {

                array[index] = i + 'a';

                // cout << " value in array at index  " << index << "= " << array[index] << endl;
                index = index + 1;
                suggestion(root->alphabets[i], index, value, sc, checkNoSug);
                index--;
                // cout << " value of index after function return =  " << index << endl;
            }
        }
    }
}

string Trie::start(string array)
{
    stack<char> s;

    int length = array.length();

    while (length != 0 && array.back() != ' ')
    {
        s.push(array.back());
        array.pop_back();
        length--;
    }

    string key;
    while (!s.empty())
    {
        key += s.top();
        s.pop();
    }

    return key;
}
