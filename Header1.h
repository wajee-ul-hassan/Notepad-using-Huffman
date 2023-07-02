#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct node1
{
    char data;
    int freq;
    node1* left, * right, * next;
    node1()
    {
        data = ' ';
        freq = 0;
        left = NULL;
        right = NULL;
        next = NULL;
    }
};
class huffman
{
    node1* head;

public:
    huffman();
    node1* gethead();
    node1* create_new_node(char value, int count);
    node1* create_new_node2(char value, int count, node1* l, node1* r);
    void insert(char value, int count);
    void chkfreq(string str);
    void sort();
    void swap(node1*& first, node1*& sec);
    void merge();
    void pathway(node1* root, char d, string code, bool& flag, string& store);
    void encode(string str);
    void binary_to_realstring(node1* root, string str, int& i, bool& flag, int l,string &);
    void decode(string &key);
};