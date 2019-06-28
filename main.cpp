#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;


string toBinary(int n)
{
    std::string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
}


vector<int> takeInput(){
    // To do : put all failures in for loops
    int v;
    cout << "enter number of variables: " ;
    cin >> v;
    if (v > 16 || v <1)
    {
        cout << "Please enter a valid number (1-16)" ;
        exit(1);
    }
    int numberOfItems = pow(2,v) ;
    vector <int> input (numberOfItems, 0);
    string inputStr;
    cout << "Please enter the minterms separated by a Comma: " ;
    cin.ignore();
    getline (cin, inputStr);
    istringstream iss(inputStr);
    string s;
    int count =0 ;
    while ( getline(iss,s,',')){
        count ++;
        if (1) //to do adjust the isdigit
        {
            if (atoi(s.c_str()) < numberOfItems && count < numberOfItems)
            {
                input[atoi(s.c_str())] = 1;
            }
            else {
                cout << "Please enter a number within range  \n";
                exit(1);
            }
        }
        else
        {
            cout << "Please enter only digits";
            exit(1);
        }
        
    }
    cout << "Please enter the dont cares separated by a Comma: " ;
    getline (cin, inputStr);
    istringstream ivv(inputStr);
    while ( getline(ivv,s,',')){
        count ++;
        if (1 && count < numberOfItems) //to do adjust the isdigit
        {
            if (atoi(s.c_str()) < numberOfItems && count < numberOfItems)
            {
                
                if (input[atoi(s.c_str())] == 1){
                    cout << "The number was used in the minterms";
                    exit(1);
                }
                else
                    input[atoi(s.c_str())] = -1;
            }
            else {
                cout << "Please Enter number within range  \n";
                exit(1);
            }
        }
        else
        {
            cout << "Please enter only digits and make sure sum of dont cares and \
            miterms within the range \n";
            exit(1);
        }
    }
    return input;
}

void fillMinTermsDontCaresDict(vector<int> input,map <int, string>& minTerms_dontCares)
{
    string index;
    for  (int i =0; i < input.size() ; i++)
    {
        if (input[i] == 1 || input[i] == -1)
        {
            index = toBinary(i);
            while (index.size() < log2 (input.size()))
                index.insert(index.begin(), '0');
            minTerms_dontCares.insert({i, index});
        }
    }
}

void calcFirstCol(map <int, string> & minTerms_dontCares, int numberOfVariables){
    
    vector <map<int, string>> col1;
    map<int, string>::iterator itr;
    int groupNo;
    for (itr = minTerms_dontCares.begin(); itr != minTerms_dontCares.end(); ++itr)
    {
        
        groupNo = count(itr->second.begin() , itr->second.end(), '1');
        if (groupNo >= col1.size()){
            col1.resize(groupNo +1);
            col1[groupNo].insert({itr->first, itr->second});
        }
        else {
            col1[groupNo].insert({itr->first, itr->second});
        }
    }
}

int main()
{
    //  vector <int> input;
    map <int,string> minTerms;
    map <int,string> dontCares;
    map <int, string> minTerms_dontCares;
    vector <int> input{ -1,1,1,0 };
    //    input = takeInput();
    fillMinTermsDontCaresDict (input ,minTerms_dontCares);
    calcFirstCol(minTerms_dontCares, log2 (input.size()));
    //    cout << toBinary(500) << endl;
    return 0;
}
