#include <fstream>
#include <iostream>
#include <cmath>
#include <sstream>
#include <chrono>
#include <string>
#include <vector>
#include "bit.h"
#include "Big.h"

using namespace std;
using namespace std::chrono;


int getVarNo(string& arr) {
	int varNo = stoi(arr);
	return varNo;
}

void CreateColBasedOn1s(vector <Big>& big, int num, vector <int> mins, vector <bit>& minterms) {
	//get minterms
	minterms.resize(mins.size());
	big.resize(mins.size());
	for (int i = 0; i < mins.size(); i++)
	{
		bit temp;
		temp.setBit(minterms[i].decToBinary(mins[i], num));
		temp.setMinterm(mins[i]);
		minterms[i] = (temp);
	}
	//generate first column
	for (int i = 0; i < num + 1; i++)
	{
		big[i].cols.resize(num + 1);
	}
	for (int j = 0; j < minterms.size(); j++) {
		big[0].cols[minterms[j].noOf1s()].terms.push_back(minterms[j]);
	}
}
bool Exist(vector <bit>& v, int i, string s) {
	for (int j = 0; j < i; j++)
		if (v[j].get_binary_bit_term() == s)
			return true;
	return false;
}
void CreateSecCol(Big& first, Big& second) {
	bit t;
	for (int i = 0; i < first.cols.size() - 1; i++)
	{
		for (int j = 0; j < first.cols[i].terms.size(); j++)
		{
			for (int z = 0; z < first.cols[i + 1].terms.size(); z++) {
				bit combined;
				if (t.IfAdjecentCreate1stCol(first.cols[i].terms[j], first.cols[i + 1].terms[z], combined))
				{
					if (!Exist(second.cols[combined.noOf1s()].terms, second.cols[combined.noOf1s()].terms.size(), combined.get_binary_bit_term())) {

						second.cols[combined.noOf1s()].terms.push_back(combined);

					}

				}
			}
		}



	}

}
vector<int> fromStr2Vint(string& arr)
{
	stringstream ss(arr);
	vector<string> result;
	while (ss.good())
	{
		string substr;
		getline(ss, substr, ',');
		result.push_back(substr);
	}
	vector<int> res;
	for (int i = 0; i < result.size(); i++)
	{
		res.push_back(atoi(result[i].c_str()));
	}
	return res;

}
void getPIs(vector<Big> big, vector<bit>& grp)
{

	for (int s = 0; s < big.size(); s++)
		for (int m = 0; m < big[s].cols.size(); m++)
			for (int i = 0; i < big[s].cols[m].terms.size(); i++)
				if (!big[s].cols[m].terms[i].Checked()) {
					grp.push_back(big[s].cols[m].terms[i]);
				}
} //awel, PIs vector y axis ,,, tany//: minterms x-axis 
void calcEssentialImplicants(vector <bit>& grp, vector <int>& minterms)
{
	grp.resize(minterms.size());
	minterms.resize(minterms.size());
	vector <vector<int>> grid(grp.size(), vector<int>(minterms.size()));
	for (int i = 0; i < grp.size(); i++) {
		istringstream iss(grp[i].get_binary_bit_term());
		string s;
		int n;
		while (getline(iss, s, ',')) {
			n = atoi(s.c_str());
			vector<int>::iterator it = find(minterms.begin(), minterms.end(), n);
			if (it == minterms.end())
			{
				continue;
			}
			else {
				int index = distance(minterms.begin(), it);
				grid[i][index] = 1;
			}
		}
	}
	int count = 0;
	int k;
	vector <string> EPI;
	vector <int> ks;
	for (int i = 0; i < minterms.size(); i++) {
		for (int j = 0; j < grp.size(); j++) {
			count += grid[j][i];
			if ((count == 1) && (grid[j][i] == 1)) k = j;
		}
		if (count == 1) {  // if the count still equals to 1 then the index in k is essential
			EPI.push_back(grp[k].get_binary_bit_term());
			ks.push_back(k);

		}
		count = 0; // reset the count for the next loop
	}

	for (int i = 0; i < EPI.size(); i++)
		cout << EPI[i] << endl;
	for (int x = 0; x < ks.size(); x++) {
		for (int y = 0; y < minterms.size(); y++) {
			if (grid[ks[x]][y] == 1) {
				for (int z = 0; z < grp.size(); z++)
					grid[z][y] = 0;
				grid[ks[x]][y] = 0;
			}
		}
	}
}
bool find(vector <int> v, int k) {
	for (int i = 0; i < v.size(); i++)
		if (v[i] == k)
			return true;
	return false;
}
/*bool check_for_value(vector <bit> v, int k) {
	for (int i = 0; i < v.size(); i++) {
		istringstream iss(v[i].get_binary_bit_term());
		string s;
		int n;
		while (getline(iss, s, ',')) {
			n = atoi(s.c_str());
			if (find(, n)
				return true;
			else false;
		}
	}
}*/
vector<string> ret;
void recurse(string minterm, int idx)
{
	if (idx == minterm.size())
	{
		ret.push_back(minterm);
		return;
	}
	if (minterm[idx] == '-')
	{
		minterm[idx] = '0';
		recurse(minterm, idx + 1);
		minterm[idx] = '1';
		recurse(minterm, idx + 1);
	}
	else recurse(minterm, idx + 1);
}
int binaryToDecimal(string binary)
{
	int sz = binary.size();
	int idx = 0;
	int val = 0;
	for (int i = sz - 1; i >= 0; i--)
	{
		if (binary[i] == '1')
		{
			val += pow(2, idx);
		}
		++idx;
	}
	return val;
}
void Run(int VarNo, vector<int> minterms, vector<int> dontCares, vector <Big>& col, vector<bit> b) {
	vector <Big> big;
	vector <bit> myPIs;
	vector <int> v;

	for (int i = 0; i < minterms.size(); i++)
		v.push_back(minterms[i]);

	if (VarNo == 0) {
		cout << "Invalid, You can not have a function with 0 Variables" << endl;
	}
	else if (minterms.size() == 0) {
		cout << "Warning, all minterms are zero so consequently, your function is zero" << endl;
	}
	else if (dontCares.size() == 1) {
		cout << "Warning, all possible combinations are included so consequently, your function is one";
	}
	else if (minterms.size() == pow(2, VarNo)) {
		cout << "Warning, all possible combinations are included so consequently, your function is one" << endl;
	}
	else {

	}
	minterms.insert(minterms.end(), dontCares.begin(), dontCares.end());
	CreateColBasedOn1s(col, VarNo, minterms, b);

	CreateSecCol(col[0], col[1]);
	CreateSecCol(col[1], col[2]);
	CreateSecCol(col[2], col[3]);
	CreateSecCol(col[3], col[4]);
	CreateSecCol(col[4], col[5]);

	vector<bit> Vstr;
	vector<bit>prime_imps;
	for (int i = 0; i < col.size(); ++i)
	{
		for (int j = 0; j < col[i].cols.size(); ++j)
		{
			for (int z = 0; z < col[i].cols[j].terms.size(); ++z)
			{
				col[i].cols[j].terms[z].print();
				if (!col[i].cols[j].terms[z].checked)
				{
					prime_imps.push_back(col[i].cols[j].terms[z]);
					Vstr.push_back(col[i].cols[j].terms[z]);
				}
			}
		}
	}

	cout << "Essential Prime Implicants" << endl;
	int arr[100] = { 0 };
	for (int i = 0; i < prime_imps.size(); i++)
	{
		ret.clear();
		recurse(prime_imps[i].get_binary_bit_term(), 0);
		cout << "the term " << prime_imps[i].get_binary_bit_term() << endl;
		for (int i = 0; i < ret.size(); ++i) {
			cout << ret[i] << ' ' << binaryToDecimal(ret[i]) << endl;
			arr[binaryToDecimal(ret[i])]++;
		}
	}
	vector<int> myEssentialNumbers;
	for (int i = 0; i < v.size(); ++i)
	{
		if (arr[v[i]] == 1)
		{
			myEssentialNumbers.push_back(v[i]);
		}
	}
	vector<string> myFinalEssentials;
	for (int i = 0; i < myEssentialNumbers.size(); ++i)
	{
		for (int j = 0; j < prime_imps.size(); ++j)
		{
			if (prime_imps[j].checkForValue(myEssentialNumbers[i]))
			{
				myFinalEssentials.push_back(prime_imps[j].fromBol2Var());
			}
		}
	}
	cout << "these are the final essentials!\n";
	for (int i = 0; i < myFinalEssentials.size(); ++i)
		cout << myFinalEssentials[i] << endl;

	/*for (int i = 0; i < v.size(); i++)
	{
		int count = 0;
		bit ess_prime_imp;
		for (int j = 0; j < prime_imps.size(); j++)
		{
			if (check_for_value(prime_imps[j],v[j]))
			{
				count++;
				ess_prime_imp = prime_imps[j];
			}
		}

		if (count == 1) {
			// Essential Prime implicant
			ess_prime_imp.print();
		}
	}*/

	/*for (int i = 0; i < col.size(); i++)
		for (int j = 0; j < col[i].cols.size(); j++)
			for (int k = 0; k < col[i].cols[j].terms.size(); k++)
				if (!col[i].cols[j].terms[k].Checked()) {

					b.push_back(col[i].cols[j].terms[k]);

				}*/

				//calcEssentialImplicants(myPIs,minterms);


				/*vector <bit> essential;
				if (essential.size() > 0)
					for (int i = 0; i < essential.size(); i++) {
						cout << essential[i].fromBol2Var() << " ";
						essential[i].print();
					}
				else
					cout << "zftttaa." << endl;*/

}

int main()
{
	clock_t start, end;

	/* Recording the starting clock tick.*/
	start = clock();

	
	


	ifstream infile;
	string file("test.txt");
	infile.open(file);
	string arr[3];
	int j = 0;
	string sLine;
	while (!infile.eof())
	{
		infile >> sLine;
		arr[j++] = sLine.data();
	}
	infile.close();
	vector<int> v;
	vector<Big> F;
	vector<bit> b;
	//cout<< getVarNo(arr[0]);

	Run(getVarNo(arr[0]), fromStr2Vint(arr[1]), fromStr2Vint(arr[2]), F, b);

	//v = fromStr2Vint(str);

	// for (int i = 0; i < v.size(); i++)
		//calcEssentialImplicants(b, v);
	// cout << v[i] << endl;;

	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "Time taken by program is : " << fixed
		<< time_taken << setprecision(5);
	cout << " sec " << endl;

	return 0;

}


