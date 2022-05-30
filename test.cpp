#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>

using namespace std;

int main()
{
     
    string line = "1-2-3-4-1-1-1-2-5";
     
    // Vector of string to save tokens
    unordered_set <string> name_set;
    
     
    // stringstream class check1
    stringstream check1(line);
     
    string intermediate;
     
    // Tokenizing w.r.t. space ' '
    while(getline(check1, intermediate, '-'))
    {
            name_set.insert(intermediate); 
    }

    vector<string> tokens(name_set.begin(), name_set.end());

    for(int i = 0; i < tokens.size(); i++)
        cout << tokens[i] << '\n';


        return 0;
}
