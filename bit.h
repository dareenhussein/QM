#pragma once
#ifndef BIT_H
#define BIT_H
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include<vector>
#include<bitset>
using namespace std;

class bit {
private:
	vector<int> bit_minterm;
	string binary_bit_term;
public:
	bool checked;

	bit()
	{
		bit_minterm;
		binary_bit_term = "";
		checked = false;
	}

	bit(int term, int var)
	{
		bit_minterm.push_back(term);
		checked = false;
	}
	bool checkForValue(int essential)
	{
		for (int i = 0; i < bit_minterm.size(); ++i)
		{
			if (bit_minterm[i] == essential) return true;
		}
		return false;
	}
	void setBit(string binary_bit_terms)
	{
		binary_bit_term = binary_bit_terms;
	}
	void setMinterm(vector<int> bit_minterms)
	{
		bit_minterm = bit_minterms;
	}
	void setMinterm(int minterm)
	{
		bit_minterm.push_back(minterm);
	}
	void Check()
	{
		checked = true;
	}
	vector<int> return_bit_minterm() {
		return bit_minterm;
	}
	bool Checked()
	{
		return checked;
	}

	void get_bit_minterm(vector <int>& mins) {
		//bit_minterm = mins;
		mins = bit_minterm;
	}

	string get_binary_bit_term()
	{
		return binary_bit_term;
	}

	void getBit_minterm(vector<int>& bit_minterms)
	{
		bit_minterm = bit_minterms;
	}
	string fromBol2Var()
	{
		string finalVar = "";
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

	int noOf1s() {
		int size = binary_bit_term.length();
		int i = 0;
		int ones = 0;
		while (i < size) {
			if (binary_bit_term[i] == '1')
				ones++;
			i++;
		}
		return ones;
	}
	bool IfAdjecentCreate1stCol(bit& b1, bit& b2, bit& combined)
	{
		string str1 = b1.binary_bit_term;
		string str2 = b2.binary_bit_term;
		bool flag = false;
		string combinedTerm = "";
		for (int i = 0; i < str1.length(); i++) {
			if (str1[i] == str2[i]) {
				combinedTerm += str1[i];
			}
			else if (str1[i] != str2[i] && !flag) {
				combinedTerm += '-';
				flag = true;
			}
			else
				return false;
		}

		vector <int> vectorOfmins1;
		vector <int> vectorOfmins2;
		vector <int> vectorOfCombinedMins;
		b1.get_bit_minterm(vectorOfmins1);
		b2.get_bit_minterm(vectorOfmins2);
		for (int i = 0; i < vectorOfmins1.size(); i++)
			vectorOfCombinedMins.push_back(vectorOfmins1[i]);
		for (int i = 0; i < vectorOfmins2.size(); i++)
			vectorOfCombinedMins.push_back(vectorOfmins2[i]);
		sort(vectorOfCombinedMins.begin(), vectorOfCombinedMins.end());

		combined.setMinterm(vectorOfCombinedMins);
		combined.setBit(combinedTerm);
		b1.checked = true;
		b2.checked = true;

		return true;
	}
	vector<int> CombinedFirstVec(vector <int> vectorOfmins1, vector <int> vectorOfmins2) {
		vector <int> vectorOfCombinedMins;
		for (int i = 0; i < vectorOfmins1.size(); i++)
			vectorOfCombinedMins.push_back(vectorOfmins1[i]);
		for (int i = 0; i < vectorOfmins2.size(); i++)
			vectorOfCombinedMins.push_back(vectorOfmins2[i]);
		sort(vectorOfCombinedMins.begin(), vectorOfCombinedMins.end());

		return vectorOfCombinedMins;

	}

	string decToBinary(int num, int& i)
	{
		string bin;
		int len;
		bin = bitset<16>(num).to_string();
		len = bin.length();
		bin = bin.erase(0, len - i);
		return bin;

	}

	void print() {
		string terms = "";
		for (int i = 0; i < bit_minterm.size(); i++)
			terms += to_string(bit_minterm[i]) + ",";

		terms = terms.substr(0, terms.size() - 1);
		cout << terms << "   " << binary_bit_term << " ";
		if (checked)
			cout << "#";

		cout << endl;
	}

};

#endif
