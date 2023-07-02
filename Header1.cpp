#include <iostream>
#include <fstream>
#include <string>
#include "Header1.h"
using namespace std;

huffman::huffman()
{
	head = NULL;
}

node1* huffman::gethead()
{
	return head;
}

node1* huffman::create_new_node(char value, int count)
{
    node1* nn = new node1;
    nn->data = value;
    nn->freq = count;
    nn->left = NULL;
    nn->right = NULL;
    nn->next = NULL;
    return nn;
}

node1* huffman::create_new_node2(char value, int count, node1* l, node1* r)
{
    node1* nn = new node1;
    nn->data = value;
    nn->freq = count;
    nn->left = l;
    nn->right = r;
    nn->next = NULL;
    return nn;
}

void huffman::insert(char value, int count)
{
    if (head == NULL)
    {
        head = create_new_node(value, count);
    }
    else
    {
        node1* curr = head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = create_new_node(value, count);
    }
}

void huffman::chkfreq(string str)
{
    int size = str.length();
    bool flag = true;
    char* visited = new char[size];
    for (int i = 0; i < size; i++)
    {
        visited[i] = '\0';
    }
    int count = 0;
    for (int i = 0; i < str.length(); i++)
    {
        for (int x = 0; x < size && flag; x++)
        {
            if (str[i] == visited[x])
            {
                flag = false;
            }
        }
        if (flag)
        {
            visited[i] = str[i];
            for (int j = 0; j < str.length(); j++)
            {
                if (str[i] == str[j])
                {
                    count++;
                }
            }
            insert(str[i], count);
            count = 0;
        }
        flag = true;
    }
}

void huffman::sort()
{
    node1* temp = head;
    bool flag = false;
    do
    {
        flag = false;
        while (temp->next != NULL)
        {
            if (temp->freq > temp->next->freq)
            {
                swap(temp, temp->next);
                flag = true;
            }
            temp = temp->next;
        }
        temp = head;
    } while (flag);
}

void huffman::swap(node1*& first, node1*& sec)
{
    node1* temp = NULL;
    int tfreq = 0;
    char tdata = ' ';
    //
    tfreq = first->freq;
    first->freq = sec->freq;
    sec->freq = tfreq;
    //
    tdata = first->data;
    first->data = sec->data;
    sec->data = tdata;
    //
    temp = first->left;
    first->left = sec->left;
    sec->left = temp;
    //
    temp = NULL;
    //
    temp = first->right;
    first->right = sec->right;
    sec->right = temp;
}

void huffman::merge()
{
    node1* curr = head;
    node1* curr1 = NULL;
    node1* pleft = NULL;
    node1* pright = NULL;
    node1* temp = NULL;
    int mergesum = 0;
    while (head->next != NULL)
    {
        //
        pleft = curr;
        pright = curr->next;

        head = head->next;
        curr->next = NULL;
        curr1 = head;

        head = head->next;
        curr1->next = NULL;
        mergesum = pleft->freq + pright->freq;
        temp = create_new_node2('$', mergesum, pleft, pright);
        temp->next = head;
        head = temp;
        // re-intializing the values
        curr = head;
        curr1 = NULL;
        mergesum = 0;
        sort();
    }
}

void huffman::pathway(node1* root, char d, string code, bool& flag, string& store)
{
    if (flag == false)
    {
        return;
    }
    if (root == NULL)
    {
        return;
    }
    if (root->data == d)
    {
        store = code;
        flag = false;
        return;
    }
    if (flag)
    {
        pathway(root->left, d, code + '0', flag, store);
    }
    if (flag)
    {
        pathway(root->right, d, code + '1', flag, store);
    }
}

void huffman::encode(string str)
{
    ofstream out;
    bool flag = true;
    out.open("encode.txt");
    string store;
    string code;
    for (int i = 0; i < str.length(); i++)
    {
        node1* temp = head;
        pathway(temp, str[i], code, flag, store);
        flag = true;
        out << store;
    }
}

void huffman::binary_to_realstring(node1* root, string str, int& i, bool& flag, int l,string &key)
{
    if (i == l)
    {
        flag = false;
    }
    if (root == NULL)
    {
        return;
    }
    if (root->left == NULL && root->right == NULL)
    {
        key += root->data;
        if (flag)
        {
            root = head;
            binary_to_realstring(root, str, i, flag, l,key);
        }
        return;
    }
    if (flag)
    {
        if (str[i] == '0')
        {
            binary_to_realstring(root->left, str, i += 1, flag, l,key);
            // i = i + 1;
        }
        else
        {
            binary_to_realstring(root->right, str, i += 1, flag, l,key);
            // i = i + 1;
        }
    }
}

void huffman::decode(string &key)
{
    ifstream in;
    in.open("encode.txt");
    string codedstr;
    int i = 0;
    bool flag = true;
    node1* temphead = head;
    while (!in.eof())
    {
        in >> codedstr;
        int l = codedstr.length();
        binary_to_realstring(temphead, codedstr, i, flag, l,key);
    }
}