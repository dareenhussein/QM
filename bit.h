#pragma once
#ifndef BIT_H
#define BIT_H
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

class bit {
    private: 
    vector<int> bit_minterm;
    bool checked; 
    string binary_bit_term; 
    public:
    bit()
    {
        bit_minterm; 
        binary_bit_term="";
        checked= false; 
    }

    bit(int term, int var)
    {
        bit_minterm.push_back(term);
        checked = false;
    }
}

void setBit(string binary_bit_term)
{
    binary_bit_term = binary_bit_term;
}

void setMinterm(vector<int> bit_minterm)
{
    bit_minterm = bit_minterm;
}
void setMinterm(int minterm)
{
    bit_minterm.push_back(minterm);
}
void Check()
{
    checked = true;
}

bool Checked()
{
    return checked;
}

string get_binary_bit_term()
{
    return binary_bit_term;
}

void getBit_minterm(vector<int> &bit_minterms)
{
    bit_minterm = bit_minterms;
}


