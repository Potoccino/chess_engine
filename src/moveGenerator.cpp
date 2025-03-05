#include <vector>
#include "pieces.h"
#include "attackMaps.h"
#include "bitBoard.h"
#include <iostream>
#include <functional>

// void print_moves(bitset<64> attacks , char* name , FILE * file)
// {

//     fprintf(file , "%s : \n" , name);
//     for(int i = 7 ; i >= 0 ; i-= 1)
//     {
//         for(int j = 0 ; j < 8 ; j += 1)
//         {
//             fprintf(file , "%c " , (attacks[i * 8 + j] ? '1' : '0'));
//         }
//         fprintf(file ,"\n");
//     }

//     fprintf(file , "\n");
//     fprintf(file , "\n");
// }

const std::bitset<16> PIECES[6]{
    1 << 12, 2 << 12, 3 << 12, 4 << 12, 5 << 12, 6 << 12
};

inline ushort getCords(size_t index)
{
    return index >> 3 | ((index & 7) << 3);
}

inline std ::bitset<16> moveFromSrcAndDis(size_t src, size_t dis)
{
    return getCords(src) | (getCords(dis) << 6);
}
    

std::bitset<64> generateDiagonalMoves(size_t index , PieceSet* enemyPieceSet , const std::bitset<64> &occupancy) noexcept
{
    std::bitset<64> moves;
    for (auto direction : {0, 1, 2, 3})
    {
        const std::bitset<64> attacks = diagonalRays[direction][index];
        const unsigned long long blockers = (attacks & occupancy).to_ullong();
        int need_lsb = (direction == 0 || direction == 3);
        size_t blocker = need_lsb * __builtin_ctzll(blockers) + (1 - need_lsb) * (63 - __builtin_clzll(blockers));
        moves |= (attacks ^ diagonalRays[direction][blocker]);
    }

    return moves;
}


std::bitset<64> generateStraightMoves(size_t index , PieceSet* enemyPieceSet , const std::bitset<64> &occupancy ) noexcept
{
    std::bitset<64> moves;
    for (auto direction : {0, 1, 2, 3})
    {
        const std::bitset<64> attacks = straightRays[direction][index];
        const unsigned long long blockers = (attacks & occupancy).to_ullong();
        int need_lsb = (direction == 0 || direction == 1);
        size_t blocker = need_lsb * __builtin_ctzll(blockers) + (1 - need_lsb) * (63 - __builtin_clzll(blockers));
        moves |= (attacks ^ straightRays[direction][blocker]);
    }
    
    return moves;
}



std::bitset<64> generateKingMoves(size_t index , PieceSet* enemyPieceSet ,const std::bitset<64> &occupancy , const std::bitset<64> castleRooks , bool inCheck = false) 
{

    std::bitset<64> moves = kingAttacks[index];
    if(inCheck)
    {
        return moves;
    }

    if(index == 4)
    {
        std :: cout << castleRooks.test(0) << '\n';
        if(castleRooks.test(0) && !(std::bitset<64>(1ll << 1 | 1ll << 2 | 1ll << 3) & occupancy).any())
        {
            moves.set(2);
        }
        if(castleRooks.test(7) && !(std::bitset<64>(1ll << 5 | 1ll << 6) & occupancy).any())
        {
            moves.set(6);
        }
    }
    else if(index == 60)
    {
        if(castleRooks.test(56) && !(std::bitset<64>(1ll << 57 | 1ll << 58 | 1ll << 59) & occupancy).any())
        {
            moves.set(58);
        }
        if(castleRooks.test(63) && !(std::bitset<64>(1ll << 61 | 1ll << 62) & occupancy).any())
        {
            moves.set(62);
        }
    }


    return moves;
}


inline std::bitset<64> generateKnightMoves(size_t index , PieceSet* enemyPieceSet) 
{
   return knightJumps[index];
}


std::bitset<64> generatePawnMoves(size_t index , PieceSet* enemyPieceSet , const std::bitset<64> &occupancy , bool color )
{
    std::bitset<64> pawnOnePush =  pawnPush[color][index] & ~(occupancy);;
    
    int rank = index >> 3;
    std::bitset<64> pawnTwoPush = (
        (pawnOnePush << (8 * (rank == 1) * (1 - color))) | 
        (pawnOnePush >> (8 * (rank == 6) * color))         
    ) & ~(occupancy);
    
    // pawn pushes
    std::bitset<64> moves = pawnOnePush | pawnTwoPush;

    // pawn captures
    moves |= pawnCaptures[color][index] & (occupancy) ;

    // en passant capture
    moves |= (pawnCaptures[color][index] & enemyPieceSet-> doublePushPawns);

    return moves;
}


void iterateMoveMap(std::vector<std::bitset<16>> &moves,
    PieceSet *enemyPieceSet,
    const size_t srcIndex,
    std::bitset<64> &movesForPiece , char isSpecial = 0)  
{
    size_t disIndex;
    size_t size = movesForPiece.size();
    while ((disIndex = movesForPiece._Find_first() ) != size )
    {
        std::bitset<16> move = moveFromSrcAndDis(srcIndex, disIndex);
        ushort distance = abs(disIndex - srcIndex) ;
        if(isSpecial == 1)
        {
            if( disIndex >= 56 || disIndex <= 7)
            {
                moves.push_back(move | KNIGHT_PROMOTED);
                moves.push_back(move | BISHOP_PROMOTED);
                moves.push_back(move | ROOK_PROMOTED); 
                moves.push_back(move | QUEEN_PROMOTED);
            }
            else if((distance == 7 || distance == 9) && !enemyPieceSet->occupied.test(disIndex))
            {
                moves.push_back(move | EN_PASSANT);
            }       
            else
            {
                moves.push_back(move);
            }
        }
        else if(isSpecial == 2 && distance >= 2)
        {
            if(distance == 2)
            {
                moves.push_back(move | castleKing);
            }
            else
            {
                moves.push_back(move | castleQueen);
            }
        }
        else
        {
            moves.push_back(move);
        }

        movesForPiece.flip(disIndex);
    }
}


