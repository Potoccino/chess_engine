#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include <vector>
#include <bitset>
#include "bitBoard.h"
#include <iostream>

void iterateMoveMap(std::vector<std::bitset<16>> &moves,
    PieceSet *enemyPieceSet,
    const size_t srcIndex,
    std::bitset<64> &movesForPiece,
    char isSpecial = 0);

std::bitset<64> generatePawnMoves(size_t index , PieceSet*  , const std::bitset<64> occupancy, bool color);

std::bitset<64> generateKnightMoves(size_t index);

std::bitset<64> generateKingMoves(size_t index , const std::bitset<64> occupancy , const std::bitset<64> castleRooks , bool inCheck = false);

std::bitset<64> generateStraightMoves(size_t index , const std::bitset<64> occupancy) noexcept;

std::bitset<64> generateDiagonalMoves(size_t index, const std::bitset<64> occupancy) noexcept;

template<typename FUNCTOR, typename ...Args>
std::vector<std::bitset<16>> iteratePossibleMoves(
    std::bitset<64> piecePositionsBitset,
    PieceSet *allyPieceSet,
    PieceSet *enemyPieceSet,
    FUNCTOR generationFunction,
    Args... args
)
{
    std::vector<std::bitset<16>> moves;
    size_t size = piecePositionsBitset.size();
    size_t index;
    while ((index = piecePositionsBitset._Find_first()) != size)
    {
        std::bitset<64> movesForPiece = generationFunction(index ,args...) & (~allyPieceSet->occupied);
        iterateMoveMap(moves, enemyPieceSet, index, movesForPiece, 0);
        piecePositionsBitset.flip(index);
    }
    
    return moves;
}

#endif