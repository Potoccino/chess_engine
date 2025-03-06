#include <iostream>
#include <vector>
#include <bitset>

using namespace std;



int main()
{
    vector<int> moves = {1 , 2 , 3};
    vector<int> moves2 = {4 , 5 , 6};
    moves.insert(moves.end() , moves2.begin(), moves2.end());
    for(auto i : moves)
    {
        cout << i << '\n';
    }
}

