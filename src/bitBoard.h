#ifndef PIECES_H
#define PIECES_H
// 0 is the rooks
// 1 is the knights
// 2 is the bishops
// 3 is the queens
// 4 is the map of occupied positions
// 5 is the pawns
// 6 is the kings
# include <cstdint>
# include <bitset>

struct PieceSet
{
    std::bitset<64> rooks;
    std::bitset<64> knights;
    std::bitset<64> bishops;
    std::bitset<64> queens;
    std::bitset<64> kings;
    std::bitset<64> pawns;
    std::bitset<64> occupied;
    std::bitset<64> doublePushPawns;
    std::bitset<64> castleRooks;
};



struct bitBoard
{       
    PieceSet white;
    PieceSet black;

    bitBoard()
    {
        
    }

};

bitBoard* getStartingBitBoard();


#endif 