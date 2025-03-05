#include <iostream>
#include "bitBoard.h"
#include "attackMaps.h"

using namespace std;



int main()
{
    for(int i = 7 ; i >= 0; i -= 1)
    {
        for(int j = 0 ; j < 8 ; j +=1)
        {
            cout << pawnCaptures[1][6][(i << 3) + j] << " ";
        }
        cout << '\n';
    }

}

