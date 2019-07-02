#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <map>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

string toBinary(int n)
{
    std::string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
}

string compare (string b1, string b2, int & pos, int &count)
{
    string result = "";
    count = 0;
    for (int i =0; i< b2.length() ; i++)
    { if (b1.length() != b2.length())
    {
        count = 5;
        return "";
    }
        if (b1[i] != b2[i])
        {
            count ++;
            pos = i;
            result+= "-";
            if (count > 1)
            {
                return "";
            }
        }
        else
            result += b1[i];
    }
    return result;
}

string constructKey(string b1, string b2)
{
    return b1 + "," + b2;
}

bool checkValue(map <string, string> someMap, string value)
{
    map<string, string>::iterator it;
    for (it = someMap.begin(); it != someMap.end(); ++it )
        if (it->second == value)
            return false;
    return true;
}

bool isNumber(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

void parseMinTerms(string line, vector<int> &input, int numberOfItems, int &count)
{
    istringstream iss(line);
    string s;
    while ( getline(iss,s,',')){
        trim (s);
        count ++;
        if (isNumber(s)) //to do adjust the isdigit
        {
            if (atoi(s.c_str()) < numberOfItems && count < numberOfItems)
            {
                if (input [atoi(s.c_str())] == 0)
                    input[atoi(s.c_str())] = 1;
                else
                {
                    cout << "There are repeated minterms \n" ;
                    exit(1);
                }
            }
            else {
                cout << "The numbers are not within range  \n";
                exit(1);
            }
        }
        else
        {
            cout << "There exists non-digits in the minterms \n";
            exit(1);
        }
        
    }
    if (count == 0){
        cout << "Your Function is always equal to 0" << endl;
        exit(1);
    }
    else if (count == pow(2, numberOfItems)){
        cout << "Your Function is always equal to 1" << endl;
    }
}

void parseDontCares(string line, vector<int> &input, int numberOfItems, int &count)
{
    string s;
    istringstream ivv(line);
    while ( getline(ivv,s,',')){
        trim (s);
        count ++;
        if (isNumber(s) && count < numberOfItems) //to do adjust the isdigit
        {
            if (atoi(s.c_str()) < numberOfItems && count < numberOfItems)
            {
                
                if (input[atoi(s.c_str())] == 1){
                    cout << "The number was used in the minterms \n";
                    exit(1);
                }
                else if (input[atoi(s.c_str())] == -1)
                {
                    cout << "There are repeated don't care terms \n" ;
                    exit(1);
                }
                else
                    input[atoi(s.c_str())] = -1;
            }
            else {
                cout << "The numbers are not within range  \n";
                exit(1);
            }
        }
        else
        {
            cout << "There exists non-digits and make sure sum of dont cares and \
            miterms within the range \n";
            exit(1);
        }
    }
}

vector<int> takeInput (string path)
{
    string line;
    vector <int> input ;
    ifstream myfile (path);
    int v ;
    int numberOfItems;
    int linesCount = 0;
    int count = 0;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            linesCount ++;
            if (linesCount == 1){
                v = atoi(line.c_str());
                numberOfItems = pow(2,v);
                if (v > 16 || v <1)
                {
                    cout << "Number is not within range (1-16)" ;
                    exit(1);
                }
                input.resize(numberOfItems, 0) ;
            }
            else if (linesCount == 2)
                parseMinTerms(line, input, numberOfItems, count);
            else if (linesCount == 3)
                parseDontCares(line, input, numberOfItems, count);
        }
        myfile.close();
    }
    return input;
}

void fillMinTermsDontCaresDict(vector<int> input,map <string, string>& minTerms_dontCares,
                               vector <string> & minTerms)
{
    string index;
    for  (int i =0; i < input.size() ; i++)
    {
        if (input[i] == 1 || input[i] == -1)
        {
            index = toBinary(i);
            while (index.size() < log2 (input.size()))
                index.insert(index.begin(), '0');
            minTerms_dontCares.insert({to_string(i), index});
            if (input[i] == 1)
                minTerms.push_back(to_string(i));
        }
    }
}

void calcFirstCol(map <string, string> & minTerms_dontCares,  vector <map<string, string>> &col1){
    
    map<string, string>::iterator itr;
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

void calcRestOfCols(vector <map<string, string>>& col1, map <string, string> & starredResults)
{
    map<string, string>::iterator itr;
    map<string, string>::iterator itr2;
    vector <string> matched ;
    vector <map<string, string>> resultantCol;
    int count = 0;
    int pos = 0;
    string result;
    
    for (int i=0; i< col1.size()  ; i++)
    {
        
        for (itr = col1[i].begin() ; itr != col1[i].end() ; ++itr)
        {
            for (itr2 = col1[i+1].begin() ; itr2 != col1[i+1].end() ; itr2++)
            {
                if (i == col1.size() -1)
                    break;
                result = compare (itr -> second, itr2 -> second, pos, count );
                if (count ==1)
                {
                    if (i >= resultantCol.size())
                        resultantCol.resize( i + 1);
                    string keyInResultCol;
                    keyInResultCol = constructKey(itr->first, itr2->first);
                    resultantCol[i].insert({keyInResultCol, result});
                    matched.push_back(itr->first);
                    matched.push_back(itr2->first);
                }
            }
            if (find(matched.begin(), matched.end(), itr->first) == matched.end() &&
                checkValue(starredResults, itr->second) ){
                starredResults.insert({itr->first, itr->second});
            }
        }
    }
    
    col1 = resultantCol ;
    while (col1.size() != 0 )
        calcRestOfCols(col1, starredResults);
}

void calcEssentialImplicants(map <string, string> & primeImplicants, vector <string> &minTerms)
{
    vector <vector<int>> grid (primeImplicants.size(),
                               std::vector<int>(minTerms.size()));
    vector <string> mapKeys ;
    map<string, string>::iterator itr;
    for(itr = primeImplicants.begin(); itr != primeImplicants.end(); ++itr ) {
        mapKeys.push_back( itr->first );
    }
    for (int i =0; i< mapKeys.size() ; i++){
        istringstream iss(mapKeys[i]);
        string s;
        int n ;
        while ( getline(iss,s,',')){
            n = atoi(s.c_str());
            vector<string>::iterator it = find(minTerms.begin(), minTerms.end(), s);
            if (it == minTerms.end())
            {
                continue;
            }
            else{
                int index = distance(minTerms.begin(), it);
                grid[i][index] = 1;
            }
            
        }
    }
    int count = 0;
    int i, j, k;
    vector <string> EPI;
    vector <int> ks;
    for (i=0; i<minTerms.size(); i++){
        for (j=0; j<mapKeys.size(); j++){
            count += grid[j][i];
            if ((count == 1) && (grid[j][i]==1)) k=j;
        }
        if (count == 1){  // if the count still equals to 1 then the index in k is essential
            if (find(EPI.begin(), EPI.end(), mapKeys[k]) == EPI.end())
            EPI.push_back(mapKeys[k]);
            ks.push_back(k);
        }
        count =0; // reset the count for the next loop
    }
    
    for (int x = 0; x < ks.size(); x++){
        for (int y=0; y<minTerms.size();y++){
            if (grid[ks[x]][y]==1){
                for(int z=0; z<mapKeys.size(); z++)
                    grid[z][y]=0;
                grid[ks[x]][y]=0;
            }
        }
    }

    vector <string> binaryRepEPI, binaryRepPI;
    
//    cout << "The Prime Implicants are: ";
    for(int i=0; i < mapKeys.size(); i++){
        binaryRepPI.push_back(primeImplicants[mapKeys[i]]);
//        cout << binaryRepPI[i] << ", ";
    }
//    cout << endl;

//    cout << "The Essentials are: ";
    for(int i=0; i < EPI.size(); i++){
        binaryRepEPI.push_back(primeImplicants[EPI[i]]);
//        cout << binaryRepEPI[i] << ", ";
    }
//    cout << endl;
    
    //vector <string> varRepPI, varRepEPI;
    char out[16]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};
    string outbar[16]={"A'","B'","C'","D'","E'","F'","G'","H'","I'","J'","K'","L'","M'","N'","O'","P'"};
    string e = "";
    cout << "The Prime Implicants are: ";
    for (int i=0; i<binaryRepPI.size(); i++){
        e = binaryRepPI[i];
        for (int j=0; j<e.size(); j++){
            if (e.at(j) == '0') cout << outbar[j];
            else if (e.at(j) == '1') cout << out[j];
            else continue;
        }
        if(i!= binaryRepPI.size()-1) cout << ", ";
    }
    cout << endl;
    cout << "The Prime Essentials are: ";
    e = "";
    for (int i=0; i<binaryRepEPI.size(); i++){
        e = binaryRepEPI[i];
        for (int j=0; j<e.size(); j++){
            if (e[j] == '0') cout << outbar[j];
            else if (e[j] == '1') cout << out[j];
            else continue;
        }
        if(i!= binaryRepEPI.size()-1) cout << ", ";
    }
    cout << endl;
}

int main()
{
    clock_t start, end;
    /* Recording the starting clock tick.*/
    start = clock();
        vector <int> input;
        vector <string> minTerms;
        vector <map<string, string>> col1;
        map <string, string> minTerms_dontCares;
        map <string, string> primeImplicants;
        input = takeInput("test.txt");
        fillMinTermsDontCaresDict (input ,minTerms_dontCares, minTerms );
        calcFirstCol(minTerms_dontCares, col1);
        calcRestOfCols(col1, primeImplicants);
        calcEssentialImplicants(primeImplicants, minTerms);
    
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(5);
    cout << " sec " << endl;
        return 0;
}
