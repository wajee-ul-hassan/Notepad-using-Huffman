#include <iostream>
#include <conio.h>
#include <stack>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Header.h"
#include "Header1.h"
using namespace std;

int main()
{
    Trie t;
    string key1 = t.TextEditorMenue();
    t.insert();
    bool flag = true;

    cout << "Enter a sentence : ";
    string key;
    int keyhit = 0;
    int temp = 0;

    int choice = 0 , checkSpace = 0;
    bool flag1 = true;
    int i = 0;
    bool flagCheck = false;

    cout << key1;

    while (true)
    {   
        if (checkSpace == 32 && temp == 13)
        {
            flagCheck = true;
        }
        if (flagCheck == false)
        {
            checkSpace = temp;
        }
        flagCheck = false;

        temp = _getch();
       
        if (temp == 61)
        {   
            ofstream out2;
            out2.open("Text.txt");

            out2 << key1;

            cout << "\n\nFile compressed successfully\n";
            huffman obj;
            obj.chkfreq(key1);
            obj.sort();
            obj.merge();
            obj.encode(key1);

            return 0;
        }

        else if (temp == 13)
        {
            if (checkSpace == 32)
            {
                continue;
            }
            key = t.start(key1);
            int curr = 0;
            int sugcount = 0;
            cout << endl;
            system("cls");
            cout << "\t\t\tSuggestions\n\n";

            bool checkNoSug = false ;
            t.suggestion(t.getroot(), 0, key, sugcount, checkNoSug);

            if (checkNoSug == false)
            {
                cout << "No suggestions ";
                Sleep(2000);
                system("cls");
                cout << "Enter a sentence : " << key1;
                continue;
            }

            cout << "\nChoose the word using forward slash ( / ) \n\n" ;
            int tempo = _getch();
            while (tempo != 59)
            {
                if (tempo == 47)
                {
                    if (keyhit == 10)
                    {
                        keyhit = 1;
                    }
                    else
                    {
                        keyhit++;
                    }
                    system("cls");
                    cout << "\nChoose the word using semicolon ( ; )\n\n";
                    t.printcursor(keyhit - 1);

                }
                else
                {
                    cout << "Wrong key , pleaase enter a correct key \n";
                }
                tempo = _getch();
            }

            int length = key1.length();
            while (length != 0 && key1.back() != ' ')
            {
                key1.pop_back();
                length--;
            }

            key1 += t.printSuggestion(keyhit);
            keyhit = 0; 
            system("cls");
            cout << "Enter a sentence : " << key1;
        }
        else if ((temp >= 97 && temp <= 122 ) || temp == 32 )
        {
            char word = temp;
            cout << word;
            key1 += word;
        }
        else
        {
            continue;
        }
    }

    cout << endl;
    return 0;
}