#include <bitset>


extern std::bitset<64> straightRays[4][65];
extern std::bitset<64> diagonalRays[4][65];
extern std::bitset<64> knightJumps[65];
extern std::bitset<64> kingAttacks[65];
extern std::bitset<64> pawnPush[2][65];
extern std::bitset<64> pawnCaptures[2][65];


// 0 is north , 1 is east , 2 is south , 3 is west;
const std::pair<ushort, ushort> straightRaysDirectionAndLimit[4] =
    {
        {0, 7},
        {1, 7},
        {2, 0},
        {3, 0}};

// 0 is north-east , 1 is south-east , 2 is south-west , 3 is north-west
const std::tuple<ushort, ushort, ushort> diagonalRaysDirectionAndlimit[4] =
    {
        {0, 7, 7},
        {1, 0, 7},
        {2, 0, 0},
        {3, 7, 0}};


extern void generateAttackMaps();