#include <stdio.h>
#include <iostream>
#include <bitset>
#include "attackMaps.h"

std::bitset<64> straightRays[4][65];
std::bitset<64> diagonalRays[4][65];
std::bitset<64> knightJumps[65];
std::bitset<64> kingAttacks[65];
std::bitset<64> pawnPush[2][65];
std::bitset<64> pawnCaptures[2][65];



ushort leftShift(ushort a)
{
    return a >> 3;
}

ushort mod(ushort a )
{
    return a & 7;
}

void generateStraightRays()
{
    for(auto [direction , limit] : straightRaysDirectionAndLimit)
    {
        short offset = direction == 0 || direction == 2 ? 8 : 1;
        
        offset *= direction == 0 || direction == 1 ? 1 : -1;
        
        ushort (*fun)(ushort) = direction == 0 || direction == 2 ? leftShift : mod;

        for(ushort i = 0 ; i < 64 ; i += 1)
        {
            size_t current_position = i;
            ushort squaresToCover = abs( fun(current_position) - limit );

            while(squaresToCover--)
            {
                current_position += offset;
                straightRays[direction][i].set(current_position);
            } 
        }
    }
}


void generateDiagonalRays()
{
    for(auto [direction , verticalLimit , horizontalLimit] : diagonalRaysDirectionAndlimit )
    {
        short horizontalOffset = direction == 0 || direction == 1 ? 1 : -1;
        short verticalOffset = direction == 0 || direction == 3 ? 8 : -8;

        for(int i = 0 ; i < 64 ; i += 1)
        {
            ushort squaresToCover = std::min(
                abs(mod(i) - horizontalLimit),
                abs(leftShift(i) - verticalLimit)
            );
            size_t currentPosition = i;

            while(squaresToCover--)
            {
                currentPosition += verticalOffset + horizontalOffset;
                diagonalRays[direction][i].set(currentPosition);
            }
        }

    }
}



void generateKnightJumps()
{
    const int dx[8] = {1 , 1 , -1 , -1 , 2 , 2 , -2 , -2};
    const int dy[8] = {2 , -2 , 2 , -2 , 1 , -1 , 1 , -1};

    auto inside = [&](int x , int y)-> bool{
        return x >= 0 && x <= 7 && y >= 0 && y <= 7;
    };

    for(int index = 0 ; index < 64 ; index += 1)
    {
        for(int j = 0 ; j < 8 ; j += 1)
        {
            int new_x = (index >> 3) + dx[j];
            int new_y = (index & 7) + dy[j];
            if(!inside(new_x , new_y)){
                continue;
            }
            size_t new_index = (new_x << 3) + new_y;
            knightJumps[index].set(new_index , true);
        }
    }

}


void generateKingAttacks()
{
    const int dx[8] = {1 , 1 , 1 , 0 , 0 , -1 , -1 , -1};
    const int dy[8] = {-1 , 0 , 1 , 1 , -1 , -1 , 0 , 1};

    auto inside = [&](int x , int y)-> bool{
        return x >= 0 && x <= 7 && y >= 0 && y <= 7;
    };


    for(int index = 0 ; index < 64 ; index += 1)
    {
        for(int j = 0 ; j < 8 ; j += 1)
        {

            int new_x = (index >> 3) + dx[j];
            int new_y = (index & 7) + dy[j];
            if(!inside(new_x , new_y)){
                continue;
            }
            size_t new_index = (new_x << 3) + new_y;
            kingAttacks[index].set(new_index , true);
        }
    }



}


void generatePawnPushesAndCaptures()
{

    auto inside = [&](int x , int y) -> bool   
    {
        return x >= 0 && y >=0 && x <= 7 && y <= 7;
    };

    for(int index = 8 ; index < 56 ; index += 1)
    {   
        pawnPush[0][index].set(index + 8);

        if(index & 7)
        {
            pawnCaptures[0][index].set(index + 7);
        }

        if((index & 7) != 7)
        {
            pawnCaptures[0][index].set(index + 9);
        }

    }


    for(int index = 55 ; index >=8 ; index -= 1)
    {
        pawnPush[1][index].set(index - 8);

        if(index & 7)
        {
            pawnCaptures[1][index].set(index - 9);
        }

        if((index & 7) != 7)
        {
            pawnCaptures[1][index].set(index - 7);
        }

    }
}



void generateAttackMaps()
{
    generateDiagonalRays();
    generateStraightRays();
    generateKingAttacks();
    generatePawnPushesAndCaptures();
    generateKnightJumps();
}
