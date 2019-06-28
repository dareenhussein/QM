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

string fromBol2Var(string str)
{        string finalVar = "";
    for (int i = 0; i < binary_bit_term.size(); i++)
        if (binary_bit_term[i] != '-')
            switch (i)
            {
            case 0:
                if (binary_bit_term[i] == '1')
                    finalVar += "A";
                else
                    finalVar += "A'";
                break;

            case 1:
                if (binary_bit_term[i] == '1')
                    finalVar += "B";
                else
                    finalVar += "B'";
                break;

            case 2:
                if (binary_bit_term[i] == '1')
                    finalVar += "C";
                else
                    finalVar += "C'";
                break;

            case 3:
                if (binary_bit_term[i] == '1')
                    finalVar += "D";
                else
                    finalVar += "D'";
                break;

            case 4:
                if (binary_bit_term[i] == '1')
                    finalVar += "E";
                else
                    finalVar += "E'";
                break;

            case 5:
                if (binary_bit_term[i] == '1')
                    finalVar += "F";
                else
                    finalVar += "F'";
                break;

            case 6:
                if (binary_bit_term[i] == '1')
                    finalVar += "G";
                else
                    finalVar += "G'";
                break;

            case 7:
                if (binary_bit_term[i] == '0')
                    finalVar += "H";
                else
                    finalVar += "H'";
                break;

            case 8:
                if (binary_bit_term[i] == '1')
                    finalVar += "I";
                else
                    finalVar += "I'";
                break;

            case 9:
                if (binary_bit_term[i] == '1')
                    finalVar += "J";
                else
                    finalVar += "J'";
                break;

            case 10:
                if (binary_bit_term[i] == '1')
                    finalVar += "K'";
                else
                    finalVar += "K";
                break;

            case 11:
                if (binary_bit_term[i] == '1')
                    finalVar += "L";
                else
                    finalVar += "L'";
                break;

            case 12:
                if (binary_bit_term[i] == '1')
                    finalVar += "M";
                else
                    finalVar += "M'";
                break;

            case 13:
                if (binary_bit_term[i] == '1')
                    finalVar += "N";
                else
                    finalVar += "N'";
                break;

            case 14:
                if (binary_bit_term[i] == '1')
                    finalVar += "O";
                else
                    finalVar += "O'";
                break;

            case 15:
                if (binary_bit_term[i] == '1')
                    finalVar += "P";
                else
                    finalVar += "P'";
                break;

            case 16:
                if (binary_bit_term[i] == '1')
                    finalVar += "Q";
                else
                    finalVar += "Q'";
                break;

            default:
                break;
            }

    return finalVar;
    }
}



