//#include <iostream>
//#include <conio.h>
//#include <stack>
//#include <fstream>
//#include <string>
//#include <Windows.h>
//using namespace std;
//
//struct node
//{
//    char data;
//    node* alphabets[26];
//    bool isleaf;
//    node()
//
//    {
//        data = ' ';
//        for (int i = 0; i < 26; i++)
//        {
//            alphabets[i] = nullptr;
//        }
//        isleaf = false;
//    }
//};
//
//class Trie
//{
//    char* array;
//    string store[10];
//
//public:
//    node* root;
//    Trie()
//    {
//        for (int i = 0; i < 10; i++)
//        {
//            store[i] = " ";
//        }
//        array = new char[50];
//        for (int i = 0; i < 50; i++)
//        {
//            array[i] = ' ';
//        }
//        root = new node;
//    }
//    node* createnode(char d)
//    {
//        node* nn = new node;
//        for (int i = 0; i < 26; i++)
//        {
//            nn->alphabets[i] = nullptr;
//        }
//        nn->data = d;
//        nn->isleaf = false;
//        return nn;
//    }
//    string printSuggestion(int choice)
//    {
//        return store[choice - 1];
//    }
//    void insertWord(node* root, string word, int length, int i)
//    {
//        if (length == i)
//        {
//            root->isleaf = true;
//            return;
//        }
//        int index = word[i] - 'a';
//        if (root->alphabets[index] != NULL)
//        {
//            root = root->alphabets[index];
//        }
//        else
//        {
//            root->alphabets[index] = createnode(word[i]);
//            root = root->alphabets[index];
//        }
//
//        insertWord(root, word, length, i + 1);
//    }
//    // insert word into the trie;
//
//    void insert()
//    {
//        long long int no_of_words = 0;
//        bool flag = true;
//        ifstream in;
//        in.open("rDictionary.txt");
//        string word;
//        while (!in.eof())
//        {
//            getline(in, word);
//            int count = word.length();
//            for (int i = 0; i < count && flag; i++)
//            {
//                if (word[i] >= 'a' && word[i] <= 'z')
//                {
//                    flag = true;
//                }
//                else
//                {
//                    flag = false;
//                }
//            }
//            if (flag)
//            {
//                // cout << word << endl;
//                no_of_words++;
//                int i = 0;
//                insertWord(root, word, count, i);
//            }
//            word = " ";
//        }
//        cout << " Total words are = " << no_of_words << endl;
//
//        in.close();
//        return;
//    }
//    node* getroot()
//    {
//        return root;
//    }
//    void print(int pos, int index)
//    {
//        string word;
//        cout << index + 1 << ":";
//        for (int i = 0; i < pos; i++)
//        {
//            cout << array[i];
//            word += array[i];
//        }
//        store[index] = word;
//    }
//    void printcursor(int index)
//    {
//        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//
//        for (int i = 0; i < 10; i++)
//        {
//            if (i == index)
//            {
//                SetConsoleTextAttribute(hConsole, 11);
//                cout << i + 1 << ":" << store[i] << endl;
//                SetConsoleTextAttribute(hConsole, 7);
//            }
//            else
//            {
//                cout << i + 1 << ":" << store[i] << endl;
//            }
//        }
//    }
//    void suggestion(node* root, int index, string value, int& sc)
//    {
//        if (root->isleaf && root->data != ' ')
//        {
//            bool flag = true;
//            for (int x = 0; x < value.length() && flag; x++)
//            {
//                if (array[x] != value[x])
//                {
//                    flag = false;
//                }
//            }
//            if (flag)
//            {
//                if (sc == 10)
//                {
//                    return;
//                }
//                else
//                {
//                    print(index, sc);
//                    cout << endl;
//                    sc++;
//                }
//            }
//        }
//        if (sc != 10)
//        {
//            for (int i = 0; i < 26; i++)
//            {
//                // if NON NULL child is found
//                // add parent key to str and
//                // call the display function recursively
//                // for child node
//
//                if (root->alphabets[i] != NULL)
//                {
//
//                    array[index] = i + 'a';
//
//                    // cout << " value in array at index  " << index << "= " << array[index] << endl;
//                    index = index + 1;
//                    suggestion(root->alphabets[i], index, value, sc);
//                    index--;
//                    // cout << " value of index after function return =  " << index << endl;
//                }
//            }
//        }
//    }
//
//    string start(string array)
//    {
//        stack<char> s;
//
//        int length = array.length();
//
//        while (length != 0 && array.back() != ' ')
//        {
//            s.push(array.back());
//            array.pop_back();
//            length--;
//        }
//
//        string key;
//        while (!s.empty())
//        {
//            key += s.top();
//            s.pop();
//        }
//
//        return key;
//    }
//};
//
//int main()
//{
//
//    Trie t;
//    t.insert();
//    bool flag = true;
//
//    string key1, key;
//    int keyhit = 0;
//    int temp = 0;
//    cout << "Enter a sentance : ";
//
//    int choice = 0;
//    bool flag1 = true;
//    int i = 0;
//    while (true)
//    {
//        temp = _getch();
//
//        if (temp == 61)
//        {
//            break;
//        }
//        else if (temp == 13)
//        {
//            key = t.start(key1);
//            int curr = 0;
//            int sugcount = 0;
//            cout << endl;
//            system("cls");
//            t.suggestion(t.getroot(), 0, key, sugcount);
//
//            cout << "Choose the word " << endl;
//            int tempo = _getch();
//            while (tempo != 59)
//            {
//                if (tempo == 47)
//                {
//                    if (keyhit == 10)
//                    {
//                        keyhit = 1;
//                    }
//                    else
//                    {
//                        keyhit++;
//                    }
//
//                    system("cls");
//                    t.printcursor(keyhit - 1);
//                }
//                else
//                {
//                    cout << "Wrong key , pleaase enter a correct key \n";
//                }
//                tempo = _getch();
//            }
//
//            int length = key1.length();
//            while (length != 0 && key1.back() != ' ')
//            {
//                key1.pop_back();
//                length--;
//            }
//
//            key1 += t.printSuggestion(keyhit);
//            system("cls");
//            cout << key1;
//        }
//        else
//        {
//            char word = temp;
//            cout << word;
//            key1 += word;
//        }
//    }
//
//    cout << endl;
//    return 0;
//}